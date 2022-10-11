#include "LightingPass.h"
#include "LightingPassCS.h"

namespace Eureka {

LightingPass::LightingPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
	: ExecutablePass(passName)
	, pGBuffer0(this, "GBuffer0")
	, pGBuffer1(this, "GBuffer1")
	, pGBuffer2(this, "GBuffer2")
	, pDepthMap(this, "DepthMap")
{
	
}

void LightingPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);
}

}
