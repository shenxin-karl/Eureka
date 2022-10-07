#include "ShaderManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "Defined/EngineDefined.h"

namespace Eureka {

void ShaderManager::loading(std::weak_ptr<dx12lib::Device> pDevice) {
	auto pDeferredPBR = std::make_shared<GraphicsShader>(pDevice, "Engine/HlslShader/DeferredPBR.hlsl");
	{
		pDeferredPBR->setVertexShader("VS");
		pDeferredPBR->setPixelShader("PS");
		pDeferredPBR->setRenderTargetFormats({ kGBuffer0Format, kGBuffer1Format, kGBuffer2Format });
		pDeferredPBR->setDepthStencilFormat(kSwapChainDepthStencilFormat);
		_graphicsShaders["DeferredPBR"] = pDeferredPBR;
	}

	auto pFXAAShader = std::make_shared<GraphicsShader>(pDevice, "Engine/HlslShader/FXAA.hlsl");
	{
		pFXAAShader->setVertexShader("VS");
		pFXAAShader->setPixelShader("PS");
		pFXAAShader->setRenderTargetFormats({ kSwapChainRenderTargetFormat });
		CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc(D3D12_DEFAULT);
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		pFXAAShader->setDepthStencilDesc(depthStencilDesc);
		CD3DX12_RASTERIZER_DESC rasterizerDesc(D3D12_DEFAULT);
		rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		pFXAAShader->setRasterizerDesc(rasterizerDesc);
		_graphicsShaders["FXAA"] = pFXAAShader;
	}
}

auto ShaderManager::getGraphicsShader(const std::string &key) const -> std::shared_ptr<GraphicsShader> {
	auto iter = _graphicsShaders.find(key);
	if (iter != _graphicsShaders.end())
		return iter->second;
	return nullptr;
}

}