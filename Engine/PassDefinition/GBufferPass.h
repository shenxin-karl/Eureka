#pragma once
#include <RenderGraph/Pass/RenderQueuePass.h>

namespace Eureka {

class EurekaApplication;
class GBufferPass : public rgph::RenderQueuePass {
public:
	explicit GBufferPass(const std::string &passName);
	void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) override;
	void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) override;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer0;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer1;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer2;
	rgph::PassResourcePtr<dx12lib::Texture> pVelocityMap;
	rgph::PassResourcePtr<dx12lib::Texture> pDepthStencil;
	EurekaApplication *pApplication;
};

}
