#include "PostProcessingPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/ComputeShader.h"

namespace Eureka {

PostProcessingPass::PostProcessingPass(const std::string &passName)
	: ExecutablePass(passName)
	, pScreenMap(this, "ScreenMap")
	, pOutputMap(this, "OutputMap")
{
	_pPipeline = ShaderManager::instance()->getComputeShader("PostProcessing");
}

void PostProcessingPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);

	auto keyword = _pPipeline->getKeywordMask();
	std::shared_ptr<dx12lib::ComputePSO> pso;
	if (_pColorLutMap != nullptr) {
		keyword.setKeyWord("_COLOR_GRADING", true);
		pso = _pPipeline->getPSO(keyword);
		pDirectCtx->setComputePSO(pso);
		pDirectCtx->setShaderResourceView("gColorLutMap", _pColorLutMap->get2dSRV());
	} else {
		pso = _pPipeline->getPSO(keyword);
		pDirectCtx->setComputePSO(pso);
	}

	const auto &desc = pScreenMap->getDesc();
	pDirectCtx->setShaderResourceView("gScreenTexture", pScreenMap->get2dSRV());
	pDirectCtx->setUnorderedAccessView("gOutputMap", pOutputMap->get2dUAV());
	auto dispatchArgs = pso->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
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
