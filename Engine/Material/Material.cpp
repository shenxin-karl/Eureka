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
#include "ShaderHelper/ShaderHelper.h"

namespace Eureka {

static std::shared_ptr<dx12lib::Texture> loadTexture(
	dx12lib::IGraphicsContext &graphicsCtx,
	const ALTexture &alTexture
)
{
	std::shared_ptr<dx12lib::Texture> pTex;
	if (alTexture.pTextureData != nullptr) {
		pTex = graphicsCtx.createTextureFromMemory(alTexture.textureExtName,
			alTexture.pTextureData.get(),
			alTexture.textureDataSize
		);
	} else {
		pTex = graphicsCtx.createTextureFromFile(dx12lib::to_wstring(alTexture.path), true);
	}
	assert(pTex);
	return pTex;
}

Material::Material(const MaterialDesc &desc) : rgph::Material(desc.materialName) {
	auto *pALMaterial = desc.pAlMaterial;
	auto &graphicsCtx = desc.graphicsCtx;

	_pCbMaterial = graphicsCtx.createFRConstantBuffer<CbMaterial>(CbMaterial{});

	auto pDeferredPBRShader = ShaderManager::instance()->getGraphicsShader("DeferredPBR");
	auto pGBufferTecinique = std::make_shared<rgph::Technique>("GBuffer", kTechGBuffer);
	{
		auto keywordMask = pDeferredPBRShader->getKeywordMask();
		std::vector<std::shared_ptr<rgph::Bindable>> bindables;

		if (pALMaterial->getDiffuseMap().valid()) {
			keywordMask.setKeyWord("_ENALBE_DIFFUSE_MAP", true);
			auto pDiffseMap = loadTexture(graphicsCtx, pALMaterial->getDiffuseMap());
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gDiffuseMap",
				pDiffseMap->get2dSRV(),
				pDiffseMap
			));
		} 

		if (pALMaterial->getNormalMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_NORMAL_MAP", true);
			auto pNormalMap = loadTexture(graphicsCtx, pALMaterial->getNormalMap());
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gNormalMap",
				pNormalMap->get2dSRV(),
				pNormalMap
			));
		}

		if (pALMaterial->getSmoothnessMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_ROUGHNESS_MAP", true);
			auto pRoughnessMap = loadTexture(graphicsCtx, pALMaterial->getSmoothnessMap());
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gRoughnessMap",
				pRoughnessMap->get2dSRV(),
				pRoughnessMap
			));
		}

		if (pALMaterial->getMetallicMap().valid()) {
			keywordMask.setKeyWord("_ENALBE_METALLIC_MAP", true);
			auto pMetallicMap = loadTexture(graphicsCtx, pALMaterial->getMetallicMap());
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gMetallicMap",
				pMetallicMap->get2dSRV(),
				pMetallicMap
			));
		}

		if (pALMaterial->getAmbientOcclusionMap().valid()) {
			keywordMask.setKeyWord("_ENABLE_AO_MAP", true);
			auto pAssimpOcclusion = loadTexture(graphicsCtx, pALMaterial->getAmbientOcclusionMap());
			bindables.push_back(rgph::SamplerTextureBindable::make(
				"gAoMap",
				pAssimpOcclusion->get2dSRV(),
				pAssimpOcclusion
			));
		}

		auto pSubPass = getGBufferSubPass(desc, pDeferredPBRShader->getPSO(keywordMask));
		auto pStep = std::make_unique<rgph::Step>(pSubPass);
		pStep->addBindables(std::move(bindables));
		pGBufferTecinique->addStep(std::move(pStep));
	}
	_techniques.push_back(pGBufferTecinique);
}

rgph::SubPass *Material::getGBufferSubPass(const MaterialDesc &desc, std::shared_ptr<dx12lib::GraphicsPSO> pso) {
	rgph::RenderQueuePass *pGBufferPass = desc.pRenderGraph->getRenderQueuePass(kGBufferPassName);
	auto pSubPass = pGBufferPass->getSubPassByName(pso->getName());
	if (pSubPass != nullptr)
		return pSubPass.get();

	pSubPass = std::make_shared<rgph::SubPass>(pso);
	rgph::ShaderLayoutMask shaderLayoutMask = ShaderHelper::calcShaderLayoutMask(pso->getInputLayout());
	pSubPass->setShaderLayoutMask(shaderLayoutMask);
	return pSubPass.get();
}

}