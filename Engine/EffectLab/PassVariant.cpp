#include "PassVariant.h"

namespace Eureka {


PassVariant::PassVariant(Pass *pass) {
	_tag = pass->getTag();
	_stencilRef = pass->getStencilRef();
	_renderQueue = pass->getRenderQueue();
	// todo: ���ﹹ���� pso, ��Ҫ������
}

auto PassVariant::getStencilRef() const -> int {
	return _stencilRef;
}

auto PassVariant::getRenderQueue() const -> RenderQueueLabel {
	return _renderQueue;
}

auto PassVariant::getPipelineStateObject() const -> const std::shared_ptr<dx12lib::GraphicsPSO> & {
	return _pso;
}

}
