#include "ClusterDeferredPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineDefinition/EngineDefinition.h"
#include "EngineShaders/ClusterDeferredCS.h"
#include "Math/MathHelper.h"

#include "EngineShaders/CalcClusterFrustumCS.h"
#include "ShaderHelper/ShaderHelper.h"

using namespace Math;

namespace Eureka {

ClusterDeferredPass::ClusterDeferredPass(const std::string &passName, 
	dx12lib::IDirectContext &directCtx,
	size_t maxPointLight,
	size_t maxSpotLight)
: TileBased(passName, directCtx, maxPointLight, maxSpotLight)
{
	auto pSharedDevice = directCtx.getDevice().lock();
	auto pRootSignature = pSharedDevice->createRootSignature(2);
	pRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, 2);
	pRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::UAV0, 1 },	// u0
		{ dx12lib::RegisterSlot::SRV0, 3 },	// t0-t4
	});
	pRootSignature->finalize();

	_pPipeline = pSharedDevice->createComputePSO("ClusterDeferredPass");
#if 1 || defined(_DEBUG) || defined(DEBUG)
	auto pBlob = ShaderHelper::compile(L"Engine/HlslShader/ClusterDeferredCS.hlsl", 
		nullptr, 
		"CS", 
		"cs_5_1"
	);
	_pPipeline->setComputeShader(pBlob);
#else
	_pPipeline->setComputeShader(g_ClusterDeferredCS, sizeof(g_ClusterDeferredCS));
#endif
	_pPipeline->setRootSignature(pRootSignature);
	_pPipeline->finalize();

	_pCbParam = directCtx.createFRConstantBuffer<CbParam>();

	_pCalcClusterFrustumPipeline = pSharedDevice->createComputePSO("CalcClusterFrustum");
	_pCalcClusterFrustumPipeline->setComputeShader(g_CalcClusterFrustumCS, sizeof(g_CalcClusterFrustumCS));
	ShaderHelper::generateRootSignature(_pCalcClusterFrustumPipeline);
	_pCalcClusterFrustumPipeline->finalize();
}

void ClusterDeferredPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	TileBased::execute(directCtx, view);
	updateClusterFrustums(directCtx, view);
	//if (!_needUpdateTile)
		//return;

	uint32_t numCluster = static_cast<uint32_t>(calcClusterSize(view.cameraData.zFar));
	uint32_t width = static_cast<uint32_t>(view.viewport.width);
	directCtx.setComputePSO(_pPipeline);
	directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 1, &numCluster, 0);
	directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 1, &width, 1);
	directCtx.setUnorderedAccessView(StringName("gLightList"), pTileLightLists->getUAV());
	directCtx.setShaderResourceView(StringName("gClusterFrustums"), _pClusterFrustums->getSRV());
	directCtx.setShaderResourceView(StringName("gPointList"), pPointLightLists->getSRV());
	directCtx.setShaderResourceView(StringName("gPointBoundingSphere"), _pPointLightBoundingSpheres->getSRV());
	auto dispatchArgs = _pPipeline->calcDispatchArgs(view.viewport.width, view.viewport.height);
	directCtx.dispatch(dispatchArgs);
}

size_t ClusterDeferredPass::calcClusterSize(float zFar) noexcept {
	assert(zFar <= kDepthSlicing16[15]);
	for (size_t i = 0; i < std::size(kDepthSlicing16)-1; ++i) {
		if (zFar < kDepthSlicing16[i])
			return i;
	}
	return 16;
}

size_t ClusterDeferredPass::calcTileSize(size_t width, size_t height, float zFar) {
	size_t x = MathHelper::divideByMultiple(width, kTileDimension);
	size_t y = MathHelper::divideByMultiple(height, kTileDimension);
	size_t z = calcClusterSize(zFar);
	return x * y * z;
}

void ClusterDeferredPass::updateClusterFrustums(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	const auto &viewport = view.viewport;
	bool updateFrustum = std::memcmp(&_matProj, &view.cameraData.matProj, sizeof(float4x4)) == 0;
	if (_pClusterFrustums == nullptr || _width != view.viewport.width || _height != view.viewport.height) {
		_width = viewport.width;
		_height = viewport.height;
		updateFrustum = true;
		size_t numTile = calcTileSize(viewport.width, viewport.height, view.cameraData.zFar);
		directCtx.trackResource(_pClusterFrustums);
		_pClusterFrustums = directCtx.createUAStructuredBuffer(
			nullptr,
			numTile,
			sizeof(ClusterFrustum)
		);
	}

	if (true || updateFrustum) {
		auto visitor = _pCbParam->visit();
		visitor->gProj = view.cameraData.matProj;
		visitor->gRenderTargetWidth = static_cast<uint32_t>(viewport.width);
		visitor->gRenderTargetHeight = static_cast<uint32_t>(viewport.height);
		visitor->gNumCluster = static_cast<uint32_t>(calcClusterSize(view.cameraData.zFar));
		directCtx.transitionBarrier(_pClusterFrustums, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		directCtx.setComputePSO(_pCalcClusterFrustumPipeline);
		directCtx.setConstantBufferView(StringName("CbParam"), _pCbParam->getCBV());
		directCtx.setUnorderedAccessView(StringName("gOutputClusterFrustum"), _pClusterFrustums->getUAV());
		auto numTileSize = _pClusterFrustums->getElementCount();
		auto dispatchArgs = _pCalcClusterFrustumPipeline->calcDispatchArgs(numTileSize);
		directCtx.dispatch(dispatchArgs);
		directCtx.transitionBarrier(_pClusterFrustums, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
	}
}

}
