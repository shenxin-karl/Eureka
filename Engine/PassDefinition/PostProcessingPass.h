#pragma once
#include "Dx12lib/Texture/Texture.h"
#include "RenderGraph/Pass/ExecutablePass.h"

namespace Eureka {

class ComputePipeline;
class PostProcessingPass : public rgph::ExecutablePass {
public:
	PostProcessingPass(const std::string &passName);
	void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
	bool setColorLutMap(std::shared_ptr<dx12lib::Texture> pColorLutMap);
	rgph::PassResourcePtr<dx12lib::Texture> pScreenMap;
	rgph::PassResourcePtr<dx12lib::Texture> pOutputMap;
private:
	std::shared_ptr<ComputePipeline>			_pPipeline;
	std::shared_ptr<dx12lib::Texture>		_pColorLutMap;
};

}
