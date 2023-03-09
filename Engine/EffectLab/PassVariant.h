#pragma once
#include <memory>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include "Pass.h"

namespace Eureka {

class Pass;
class PassVariant {
public:
	explicit PassVariant(Pass *pass, const ShaderKeyword &keyword);
	auto getStencilRef() const -> int;
	auto getRenderQueue() const -> RenderQueueLabel;
	auto getPipelineStateObject() const -> const std::shared_ptr<dx12lib::GraphicsPSO> &;
private:
	std::string							  _tag;
	int									  _stencilRef;
	RenderQueueLabel					  _renderQueue;
	std::shared_ptr<dx12lib::GraphicsPSO> _pso;
};

}
