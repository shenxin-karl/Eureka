#include "ClusterDeferredPass.h"

namespace Eureka {

ClusterDeferredPass::ClusterDeferredPass(const std::string &passName, 
	dx12lib::IDirectContext &directCtx,
	size_t maxPointLight,
	size_t maxSpotLight)
: TileBased(passName, directCtx, maxPointLight, maxSpotLight)
{
}

size_t ClusterDeferredPass::calcClusterSize(float zFar) noexcept {
	assert(zFar <= kDepthSlicing16[16]);
	for (size_t i = 0; i < std::size(kDepthSlicing16); ++i) {
		if (zFar < kDepthSlicing16[i])
			return i+1;
	}
	return 17;
}

}
