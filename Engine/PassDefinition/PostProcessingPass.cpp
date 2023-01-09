#include "PostProcessingPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "EngineDefinition/EngineDefinition.h"
#include "ShaderHelper/ComputePipeline.h"
#include "ShaderHelper/PipelineManager.h"

namespace Eureka {

PostProcessingPass::PostProcessingPass(const std::string &passName)
	: ExecutablePass(passName)
	, pScreenMap(this, "ScreenMap")
	, pOutputMap(this, "OutputMap")
{
	_pPipeline = PipelineManager::instance()->getComputePipeline("PostProcessing");
}

void PostProcessingPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(directCtx, view);

	auto keyword = _pPipeline->getKeywordMask();
	std::shared_ptr<dx12lib::ComputePSO> pso;
	if (_pColorLutMap != nullptr) {
		keyword.setKeyWord(StringName("_COLOR_GRADING"), true);
		pso = _pPipeline->getPSO(keyword);
		directCtx.setComputePSO(pso);
		directCtx.setShaderResourceView(StringName("gColorLutMap"), _pColorLutMap->get2dSRV());
	} else {
		pso = _pPipeline->getPSO(keyword);
		directCtx.setComputePSO(pso);
	}

	const auto &desc = pScreenMap->getDesc();
	directCtx.setShaderResourceView(StringName("gScreenTexture"), pScreenMap->get2dSRV());
	directCtx.setUnorderedAccessView(StringName("gOutputMap"), pOutputMap->get2dUAV());
	auto dispatchArgs = pso->calcDispatchArgs(desc.Width, desc.Height);
	directCtx.dispatch(dispatchArgs);
}

bool PostProcessingPass::setColorLutMap(std::shared_ptr<dx12lib::Texture> pColorLutMap) {
	assert(pColorLutMap != nullptr);
	const auto &desc = pColorLutMap->getDesc();
	if (desc.Width != 256 || desc.Height != 16)
		return false;

	_pColorLutMap = std::move(pColorLutMap);
	return true;
}
}
