#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>
#include <Dx12lib/Texture/Texture.h>

namespace rgph {

class GraphicsPass : public ExecutablePass {
public:
	GraphicsPass(const std::string &passName);
	void preExecute(dx12lib::DirectContextProxy pDirectCtx) override;
	void execute(dx12lib::DirectContextProxy pDirectCtx) override;
	void postExecute(dx12lib::DirectContextProxy pDirectCtx) override;
	auto getPassType() const ->PassType override;
	virtual void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) = 0;
	virtual void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) = 0;
};

}
