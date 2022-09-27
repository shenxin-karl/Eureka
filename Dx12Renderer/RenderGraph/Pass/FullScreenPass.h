#pragma once
#include <RenderGraph/Pass/GraphicsPass.h>

namespace rgph {

class FullScreenRenderable;
class FullScreenPass : public GraphicsPass {
public:
	FullScreenPass(const std::string &passName, bool rtActive = true, bool dsActive = false);
	void execute(dx12lib::DirectContextProxy pDirectCtx) override;
	void setFullScreenRenderable(std::shared_ptr<FullScreenRenderable> pFullScreenRenderable);
	auto getFullScreenRenderable() const -> std::shared_ptr<FullScreenRenderable>;
	auto getPassType() const -> PassType override;
private:
	std::shared_ptr<FullScreenRenderable> _pFullScreenRenderable;
};

}
