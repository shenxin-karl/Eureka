#include "ClusterDeferredPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineShaders/ClusterDeferredCS.h"

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
		{ dx12lib::RegisterSlot::SRV0, 5 },	// t0-t4
		{ dx12lib::RegisterSlot::UAV0, 1 },	// u0
	});
	pRootSignature->finalize();

	_pPipeline = pSharedDevice->createComputePSO("ClusterDeferredPass");
	_pPipeline->setComputeShader(g_ClusterDeferredCS, sizeof(g_ClusterDeferredCS));
	_pPipeline->setRootSignature(pRootSignature);
	_pPipeline->finalize();
}

void ClusterDeferredPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	TileBased::execute(pDirectCtx, view);
	updateClusterFrustums(*pDirectCtx, view);
	if (!_needUpdateTile)
		return;
}

size_t ClusterDeferredPass::calcClusterSize(float zFar) noexcept {
	assert(zFar <= kDepthSlicing16[16]);
	for (size_t i = 0; i < std::size(kDepthSlicing16); ++i) {
		if (zFar < kDepthSlicing16[i])
			return i+1;
	}
	return 17;
}

void ClusterDeferredPass::updateClusterFrustums(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	bool updateFrustum = std::memcmp(&_matProj, &view.cameraData.matProj, sizeof(float4x4)) == 0;
	updateFrustum = updateFrustum || _pClusterFrustums == nullptr;

	if (_pClusterFrustums == nullptr) {
		
	}

}

}
