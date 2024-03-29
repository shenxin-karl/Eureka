#include "TileBased.h"
#include "Dx12lib/Context/ContextProxy.hpp"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineDefinition/EngineDefinition.h"
#include "RenderGraph/Utility/Utility.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "Objects/PathManager.h"
#include "ShaderHelper/ShaderLoader.h"

using namespace Math;

namespace Eureka {

TileBased::TileBased(const std::string &passName, 
	dx12lib::IDirectContext &directCtx, 
	size_t maxPointLights, 
	size_t maxSpotLights)
: ExecutablePass(passName)
, _maxSpotLights(maxSpotLights)
, _maxPointLights(maxPointLights)
, pPointLightLists(this, "PointLightLists")
, pTileLightLists(this, "TileLightLists")
{
	if (maxPointLights > 0)
		_pPointLightBoundingSpheres = directCtx.createUAStructuredBuffer(nullptr, maxPointLights, sizeof(float4));
	if (maxSpotLights > 0)
		_pSpotLightBoundingSpheres = directCtx.createUAStructuredBuffer(nullptr, maxSpotLights, sizeof(float4));

	auto pSharedDevice = directCtx.getDevice().lock();
	auto pRootSignature = pSharedDevice->createRootSignature(2);
	pRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, 16);
	pRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::SRV0, 1 },
		{ dx12lib::RegisterSlot::UAV0, 1 },
	});
	pRootSignature->finalize();

	_pUpdatePointLightBoundingSpherePipeline = pSharedDevice->createComputePSO("UpdateSpotLightBoundingSpherePSO");

	D3D_SHADER_MACRO pointLightShaderMacros[] = {
		{ "UPDATE_POINT_LIGHT", "1" },
		{ nullptr, nullptr }
	};
	_pUpdatePointLightBoundingSpherePipeline->setComputeShader(ShaderLoader::dxc(
		 PathManager::toAssetPath("Shaders/UpdateLightBoundingSphere.hlsl"),
		"CS",
		"cs_6_0",
		pointLightShaderMacros
	));
	_pUpdatePointLightBoundingSpherePipeline->setRootSignature(pRootSignature);
	_pUpdatePointLightBoundingSpherePipeline->finalize();

	D3D_SHADER_MACRO spotLightShaderMacros[] = {
		{ "UPDATE_SPOT_LIGHT", "1" },
		{ nullptr, nullptr }
	};
	_pUpdateSpotLightBoundingSpherePipeline = pSharedDevice->createComputePSO("UpdateSpotLightBoundingSpherePipePSO");
	_pUpdateSpotLightBoundingSpherePipeline->setComputeShader(ShaderLoader::dxc(
		PathManager::toAssetPath("Shaders/UpdateLightBoundingSphere.hlsl"),
		"CS",
		"cs_6_0",
		spotLightShaderMacros
	));
	_pUpdateSpotLightBoundingSpherePipeline->setRootSignature(pRootSignature);
	_pUpdateSpotLightBoundingSpherePipeline->finalize();
}

void TileBased::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(directCtx, view);
	_needUpdateTile = _needUpdateTile || std::memcmp(&_matView, &view.cameraData.matView, sizeof(float4x4)) != 0;
	if (_needUpdateTile) {
		if (_maxPointLights > 0) {
			directCtx.setComputePSO(_pUpdatePointLightBoundingSpherePipeline);
			directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 16, &_matView);
			const auto &srv = pPointLightLists->getSRV();
			directCtx.setShaderResourceView(StringName("gPointList"), srv);
			directCtx.transitionBarrier(_pPointLightBoundingSpheres, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
			const auto &uav = _pPointLightBoundingSpheres->getUAV();
			directCtx.setUnorderedAccessView(StringName("gOutputBoundingSphere"), uav);
			size_t numPointLight = pPointLightLists->getElementCount();
			auto dispatchArgs = _pUpdatePointLightBoundingSpherePipeline->calcDispatchArgs(numPointLight);
			directCtx.dispatch(dispatchArgs);
			directCtx.transitionBarrier(_pPointLightBoundingSpheres, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
		}
	}
}

void TileBased::postExecute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::postExecute(directCtx, view);
	_matView = view.cameraData.matView;
	_needUpdateTile = false;
}

void TileBased::onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height) {
	ExecutablePass::onResize(directCtx, width, height);
	_needUpdateTile = true;
}


}
