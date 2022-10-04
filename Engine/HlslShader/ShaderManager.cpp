#include "ShaderManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "Defined/EngineDefined.h"

namespace Eureka {

void ShaderManager::loading(std::weak_ptr<dx12lib::Device> pDevice) {
	auto pDeferredPBR = std::make_shared<GraphicsShader>(pDevice, "Engine/HlslShader/DeferredPBR.hlsl");
	pDeferredPBR->addShaderFeatures({ "_ENALBE_DIFFUSE_MAP" });
	pDeferredPBR->addShaderFeatures({ "_ENABLE_NORMAL_MAP" });
	pDeferredPBR->addShaderFeatures({ "_ENABLE_ROUGHNESS_MAP" });
	pDeferredPBR->addShaderFeatures({ "_ENALBE_METALLIC_MAP" });
	pDeferredPBR->addShaderFeatures({ "_ENABLE_AO_MAP" });
	pDeferredPBR->setVertexShader("VS");
	pDeferredPBR->setPixelShader("PS");
	pDeferredPBR->setRenderTargetFormats({ kGBuffer0Format, kGBuffer1Format, kGBuffer2Format });
	pDeferredPBR->setDepthStencilFormat(kSwapChainDepthStencilFormat);
	_graphicsShaders["DeferredPBR"] = pDeferredPBR;
}

auto ShaderManager::getGraphicsShader(const std::string &key) const -> std::shared_ptr<GraphicsShader> {
	auto iter = _graphicsShaders.find(key);
	if (iter != _graphicsShaders.end())
		return iter->second;
	return nullptr;
}

}