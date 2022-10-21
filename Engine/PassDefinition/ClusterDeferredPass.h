#pragma once
#include <Math/MathStd.hpp>
#include "TileBased.h"

namespace Eureka {

struct ClusterFrustum {
	Math::float3 frustumPlanes[6];
};

class ClusterDeferredPass : public TileBased {
public:
	ClusterDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx, 
		size_t maxPointLight = 0, 
		size_t maxSpotLight = 0
	);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
public:
	constexpr static float kDepthSlicing16[17] = {
		1.0f, 20.0f, 29.7f, 44.0f, 65.3f,
		96.9f, 143.7f, 213.2f, 316.2f, 469.1f,
		695.9f, 1032.4f, 1531.5f, 2272.0f, 3370.5f,
		5000.0f, 50000.0f
	};
	constexpr static size_t kTileDimension = 64;
	static size_t calcClusterSize(float zFar) noexcept;
private:
	void updateClusterFrustums(dx12lib::IDirectContext &directCtxm const rgph::RenderView &view);
private:
	Math::float4x4 _matProj;
	std::shared_ptr<dx12lib::ComputePSO> _pPipeline;
	std::shared_ptr<dx12lib::IUAStructuredBuffer> _pClusterFrustums;
};

}
