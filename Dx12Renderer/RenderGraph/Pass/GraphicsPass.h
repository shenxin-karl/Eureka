#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>
#include <Dx12lib/Texture/Texture.h>
#include "RenderGraph/Utility/Utility.h"

namespace rgph {

class GraphicsPass : public ExecutablePass {
public:
	GraphicsPass(const std::string &passName);
	void preExecute(dx12lib::IDirectContext &directCtx, const RenderView &view) override;
	void execute(dx12lib::IDirectContext &directCtx, const RenderView &view) override;
	void postExecute(dx12lib::IDirectContext &directCtx, const RenderView &view) override;
	auto getPassType() const ->PassType override;
	virtual void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) = 0;
	virtual void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) = 0;
};

}
