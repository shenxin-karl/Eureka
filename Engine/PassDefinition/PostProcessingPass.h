#pragma once
#include "Dx12lib/Texture/Texture.h"
#include "RenderGraph/Pass/ExecutablePass.h"

namespace Eureka {

class ComputeShader;
class PostProcessingPass : public rgph::ExecutablePass {
public:
	PostProcessingPass(const std::string &passName);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
	bool setColorLutMap(std::shared_ptr<dx12lib::Texture> pColorLutMap);
	rgph::PassResourcePtr<dx12lib::Texture> pScreenMap;
	rgph::PassResourcePtr<dx12lib::Texture> pOutputMap;
private:
	std::shared_ptr<ComputeShader>			_pPipeline;
	std::shared_ptr<dx12lib::Texture>		_pColorLutMap;
};

}
