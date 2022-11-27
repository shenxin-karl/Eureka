#pragma once
#include <Dx12lib/Texture/Texture.h>
#include <RenderGraph/Pass/ExecutablePass.h>

namespace Eureka {

class TemporalAAPass : public rgph::ExecutablePass {
public:
	TemporalAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx);
	void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
	void onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height) override;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pScreenMap;
	rgph::PassResourcePtr<dx12lib::Texture> pVelocityMap;
	rgph::PassResourcePtr<dx12lib::Texture> pOutputMap;
	float sharpenFactor = 0.5f;
private:
	bool _hasHistory = false;
	std::shared_ptr<dx12lib::Texture> _pTemporalColor[2];
	std::shared_ptr<dx12lib::ComputePSO> _pTemporalPipeline;
	std::shared_ptr<dx12lib::ComputePSO> _pSharpenPipeline;
};

}
