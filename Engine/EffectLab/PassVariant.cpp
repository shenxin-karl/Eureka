#include "PassVariant.h"
#include "Application/Application.h"

namespace Eureka {

PassVariant::PassVariant(Pass *pass, const std::string &name) {
	_tag = pass->getTag();
	_stencilRef = pass->getStencilRef();
	_renderQueue = pass->getRenderQueue();

	auto pDevice = Application::getDevice();
	_pso = pDevice->createGraphicsPSO(name);
	_pso->setRasterizerState(pass->getRasterizerDesc());
	_pso->setBlendState(pass->getBlendDesc());
	_pso->setDepthStencilState(pass->getDepthStencilDesc());
	// todo: 
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
