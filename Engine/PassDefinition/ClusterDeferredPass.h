#pragma once
#include <Math/MathStd.hpp>
#include "RenderGraph/Pass/ExecutablePass.h"

namespace Eureka {

struct ClusterFrustum {
	Math::float3 frustumPlanes[6];
};

class ClusterDeferredPass : public rgph::ExecutablePass {
public:
	ClusterDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx);
public:
	constexpr static float kDepthSlicing16[17] = {
		1.0f, 20.0f, 29.7f, 44.0f, 65.3f,
		96.9f, 143.7f, 213.2f, 316.2f, 469.1f,
		695.9f, 1032.4f, 1531.5f, 2272.0f, 3370.5f,
		5000.0f, 50000.0f
	};
public:
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pPointLights;
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pSpotLights;
	rgph::PassResourcePtr<dx12lib::IUAStructuredBuffer> pLightList;
};

}
