#include "Material.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "AssimpLoader/ALTree.h"
#include "RenderGraphDefined/RenderGraphDefined.h"
#include <RenderGraph/Bindable/SamplerTextureBindable.h>
#include <RenderGraph/Technique/Technique.h>
#include <RenderGraph/Technique/Step.h>
#include <Dx12lib/Texture/Texture.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <RenderGraph/RenderGraph/RenderGraph.h>
#include <RenderGraph/Pass/RenderQueuePass.h>
#include <RenderGraph/Pass/SubPass.h>
#include <RenderGraph/Bindable/ConstantBufferBindable.h>
#include "ShaderHelper/ShaderHelper.h"
#include "TextureManager/TextureManager.h"

namespace Eureka {

static std::shared_ptr<dx12lib::Texture> loadTexture(
	dx12lib::IGraphicsContext &graphicsCtx,
	const ALTexture &alTexture,
	bool sRGB)
{

	std::shared_ptr<dx12lib::Texture> pTex;
	if (!alTexture.path.empty()) {
		if ((pTex = TextureManager::instance()->getTexture(alTexture.path)) != nullptr)
			return pTex;
	}

	if (alTexture.pTextureData != nullptr) {
		pTex = graphicsCtx.createTextureFromMemory(alTexture.textureExtName,
			alTexture.pTextureData.get(),
			alTexture.textureDataSize
		);
	} else {
		pTex = graphicsCtx.createTextureFromFile(dx12lib::to_wstring(alTexture.path), sRGB, -1);
	}

	if (!alTexture.path.empty())
		TextureManager::instance()->setTexture(alTexture.path, pTex);

	assert(pTex);
	return pTex;
}

Material::Material(const MaterialDesc &desc) : rgph::Material(desc.materialName) {
	auto *pALMaterial = desc.pAlMaterial;
	auto &graphicsCtx = desc.graphicsCtx;

	CbMaterial data;
	data.alphaCutoff = pALMaterial->getAlphaCutoff();
	pCbMaterial = graphicsCtx.createFRConstantBuffer<CbMaterial>(data);

	auto pDeferredPBRShader = ShaderManager::instance()->getGraphicsShader("DeferredPBR");
	auto pGBufferTechnique = std::make_shared<rgph::Technique>("GBuffer", kTechGBuffer);
	{
		auto keywordMask = pDeferredPBRShader->getKeywordMask();
		std::vector<std::shared_ptr<rgph::Bindable>> bindables;

		bindables.push_back(rgph::ConstantBufferBindable::make("cbMaterial", pCbMaterial));

		if (pALMaterial->getDiffuseMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_DIFFUSE_MAP", true);
			auto pDiffuseMap = loadTexture(graphicsCtx, pALMaterial->getDiffuseMap(), true);

			if (pALMaterial->getEnableAlphaTest() && pDiffuseMap->hasAlpha())
				keywordMask.setKeyWord("_ENABLE_ALPHA_CUTOFF", true);

			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gDiffuseMap",
				pDiffuseMap->get2dSRV(),
				pDiffuseMap
			));
		} 

		if (pALMaterial->getNormalMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_NORMAL_MAP", true);
			auto pNormalMap = loadTexture(graphicsCtx, pALMaterial->getNormalMap(), false);
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gNormalMap",
				pNormalMap->get2dSRV(),
				pNormalMap
			));
		}

		bool hasRoughnessMap = false;
		if (pALMaterial->getRoughnessMap().valid()) {
			hasRoughnessMap = true;
			keywordMask.setKeyWord("_ENABLE_ROUGHNESS_MAP", true);
			auto pRoughnessMap = loadTexture(graphicsCtx, pALMaterial->getRoughnessMap(), false);
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gRoughnessMap",
				pRoughnessMap->get2dSRV(),
				pRoughnessMap
			));
		} else if (pALMaterial->getSpecularMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_SPECULAR_MAP", true);
			auto pSpecularMap = loadTexture(graphicsCtx, pALMaterial->getSpecularMap(), false);
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gSpecularMap",
				pSpecularMap->get2dSRV(),
				pSpecularMap
			));
		}

		if (pALMaterial->getMetallicMap().valid()) {
			if (hasRoughnessMap && pALMaterial->getMetallicMap().path == pALMaterial->getRoughnessMap().path) {
				keywordMask.setKeyWord("_ENABLE_METALLIC_ROUGHNESS_MAP_G", true);
			} else {
				keywordMask.setKeyWord("_ENABLE_METALLIC_MAP", true);
				auto pMetallicMap = loadTexture(graphicsCtx, pALMaterial->getMetallicMap(), false);
				bindables.push_back(rgph::SamplerTextureBindable::make(
					"gMetallicMap",
					pMetallicMap->get2dSRV(),
					pMetallicMap
				));
			}
		} 

		if (pALMaterial->getAmbientOcclusionMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_AO_MAP", true);
			auto pAmbientOcclusionMap = loadTexture(graphicsCtx, pALMaterial->getAmbientOcclusionMap(), false);
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gAoMap",
				pAmbientOcclusionMap->get2dSRV(),
				pAmbientOcclusionMap
			));
		} else if (pALMaterial->getLightMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_LIGHT_MAP", true);
			auto pLightMap = loadTexture(graphicsCtx, pALMaterial->getLightMap(), false);
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gLightMap",
				pLightMap->get2dSRV(),
				pLightMap
			));
			if (!keywordMask.hasKeyword("_ENABLE_METALLIC_MAP") && !keywordMask.hasKeyword("_ENABLE_METALLIC_ROUGHNESS_MAP_G"))
				keywordMask.setKeyWord("_ENABLE_LIGHT_MAP_G", true);
		}
		

		auto pso = pDeferredPBRShader->getPSO(keywordMask);
		_shaderLayoutMask |= ShaderHelper::calcShaderLayoutMask(pso->getInputLayout());

		auto pSubPass = getGBufferSubPass(desc, pso);
		auto pStep = std::make_unique<rgph::Step>(pSubPass);
		pStep->addBindables(std::move(bindables));
		pGBufferTechnique->addStep(std::move(pStep));
	}
	_techniques.push_back(pGBufferTechnique);

}

rgph::SubPass *Material::getGBufferSubPass(const MaterialDesc &desc, std::shared_ptr<dx12lib::GraphicsPSO> pso) {
	rgph::RenderQueuePass *pGBufferPass = desc.pRenderGraph->getRenderQueuePass(kGBufferPassName);
	auto pSubPass = pGBufferPass->getSubPassByName(pso->getName());
	if (pSubPass != nullptr)
		return pSubPass.get();

	pSubPass = std::make_shared<rgph::SubPass>(pso);
	rgph::ShaderLayoutMask shaderLayoutMask = ShaderHelper::calcShaderLayoutMask(pso->getInputLayout());
	pSubPass->setShaderLayoutMask(shaderLayoutMask);

	if (auto pCbPreObject = pso->getBoundResource("CbPreObject"))
		pSubPass->setTransformCBufferShaderRegister(pCbPreObject->shaderRegister);
	if (auto pCbPrePass = pso->getBoundResource("CbPrePass"))
		pSubPass->setPassCBufferShaderRegister(pCbPrePass->shaderRegister);

	pGBufferPass->addSubPass(pSubPass);
	return pSubPass.get();
}

}
