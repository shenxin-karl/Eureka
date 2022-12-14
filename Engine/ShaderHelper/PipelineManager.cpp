#include "PipelineManager.h"
#include "EngineDefinition/EngineDefinition.h"
#include "ShaderHelper/ComputePipeline.h"
#include "ShaderHelper/GraphicsPipeline.h"

namespace Eureka {

void PipelineManager::initialize(std::weak_ptr<dx12lib::Device> pDevice) {
	auto pDeferredPBR = std::make_shared<GraphicsPipeline>(pDevice, "Engine/EngineAssets/Shaders/DeferredPBR.hlsl");
	pDeferredPBR->setVertexShader("VS");
	pDeferredPBR->setPixelShader("PS");
	pDeferredPBR->setRenderTargetFormats({ kGBuffer0Format, kGBuffer1Format, kGBuffer2Format, kVelocityFormat });
	pDeferredPBR->setDepthStencilFormat(kSwapChainDepthStencilFormat);
	_graphicsShaders["DeferredPBR"] = pDeferredPBR;

	auto pFXAAShader = std::make_shared<GraphicsPipeline>(pDevice, "Engine/EngineAssets/Shaders/FXAA.hlsl");
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

	auto pLightingShader = std::make_shared<ComputePipeline>(pDevice, "Engine/EngineAssets/Shaders/LightingPassCS.hlsl");
	pLightingShader->setComputeShader("CS");
	_computeShaders["Lighting"] = pLightingShader;

	auto pPostProcessingShader = std::make_shared<ComputePipeline>(pDevice, "Engine/EngineAssets/Shaders/PostProcessing.hlsl");
	pPostProcessingShader->setComputeShader("CS");
	_computeShaders["PostProcessing"] = pPostProcessingShader;

	auto pTileDeferred = std::make_shared<ComputePipeline>(pDevice, "Engine/EngineAssets/Shaders/TiledDeferredCS.hlsl");
	pTileDeferred->setComputeShader("CS");
	_computeShaders["TileDeferred"] = pTileDeferred;
}

auto PipelineManager::getComputePipeline(const std::string &key) const -> std::shared_ptr<ComputePipeline> {
	auto iter = _computeShaders.find(key);
	if (iter != _computeShaders.end())
		return iter->second;
	return nullptr;
}

auto PipelineManager::getGraphicsPipeline(const std::string &key) const -> std::shared_ptr<GraphicsPipeline> {
	auto iter = _graphicsShaders.find(key);
	if (iter != _graphicsShaders.end())
		return iter->second;
	return nullptr;
}

}
