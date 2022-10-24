#pragma once
#include <RenderGraph/Pass/GraphicsPass.h>

namespace Eureka {

class CopyToBackPass : public rgph::GraphicsPass {
public:
	CopyToBackPass(const std::string &passName, dx12lib::IDirectContext &directCtx);
	void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
	void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) override;
	void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) override;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pScreenMap;
	rgph::PassResourcePtr<dx12lib::Texture> pBackBufferMap;
private:
	std::shared_ptr<rgph::Geometry>         _pFullScreenGeometry;
	std::shared_ptr<dx12lib::GraphicsPSO>   _pPipeline;
};

}
