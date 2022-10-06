#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>
#include <RenderGraph/Pass/GraphicsPass.h>
#include <RenderGraph/Pass/RenderQueuePass.h>

namespace Eureka {

constexpr rgph::TechniqueType kTechGBuffer = rgph::TechniqueType(1);
inline const std::string kGBufferPassName = "GBuffer";

class GBufferPass : public rgph::RenderQueuePass {
public:
	explicit GBufferPass(const std::string &passName);
	void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) override;
	void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) override;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer0;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer1;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer2;
	rgph::PassResourcePtr<dx12lib::Texture> pDepthStencil;
};


class EurekaApplication;
std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp);

}
