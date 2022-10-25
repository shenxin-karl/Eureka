#pragma once
#include <Dx12lib/Texture/Texture.h>
#include <RenderGraph/Pass/ExecutablePass.h>

namespace Eureka {

class TemporalAAPass : public rgph::ExecutablePass {
public:
	TemporalAAPass(const std::string &passName);
	void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
	void onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height) override;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pScreenMap;
	rgph::PassResourcePtr<dx12lib::Texture> pOutputMap;
private:
	bool _hasHistory = false;
	std::shared_ptr<dx12lib::Texture> _pTemporalColor[2];
};

}
