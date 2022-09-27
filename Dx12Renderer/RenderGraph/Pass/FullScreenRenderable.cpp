#include "FullScreenRenderable.h"

#include "Dx12lib/Buffer/VertexBuffer.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "RenderGraph/Bindable/Bindable.hpp"

namespace rgph {

FullScreenRenderable::FullScreenRenderable(std::weak_ptr<dx12lib::GraphicsPSO> pGraphicsPSO) {
	setGraphicsPSO(std::move(pGraphicsPSO));
}

auto FullScreenRenderable::getName() const -> const std::string & {
	return _name;
}

void FullScreenRenderable::setGraphicsPSO(std::weak_ptr<dx12lib::GraphicsPSO> pGraphicsPSO) {
	_pGraphicsPSO = std::move(pGraphicsPSO);
	_name = _pGraphicsPSO.lock()->getName();
}

auto FullScreenRenderable::getGraphicsPSO() const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	return _pGraphicsPSO.lock();
}

void FullScreenRenderable::setVertexBuffer(std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer) {
	_pVertexBuffer = std::move(pVertexBuffer);
}

auto FullScreenRenderable::getVertexBuffer() const -> std::shared_ptr<dx12lib::VertexBuffer> {
	return _pVertexBuffer;
}

void FullScreenRenderable::setVertexInputSlot(size_t slot) {
	_vertexInputSlot = slot;
}

auto FullScreenRenderable::getVertexInputSlot() const -> size_t {
	return _vertexInputSlot;
}

void FullScreenRenderable::addBindable(std::shared_ptr<Bindable> pBindable) {
	_bindables.push_back(std::move(pBindable));
}

void FullScreenRenderable::clearBindables() {
	_bindables.clear();
}

void FullScreenRenderable::execute(dx12lib::IGraphicsContext &graphicsCtx) {
	assert(_pVertexBuffer != nullptr);
	if (auto pSharedGraphicsPSO = _pGraphicsPSO.lock()) {
		graphicsCtx.setVertexBuffer(_pVertexBuffer, static_cast<UINT>(_vertexInputSlot));
		graphicsCtx.setGraphicsPSO(pSharedGraphicsPSO);
		for (auto &pBindable : _bindables)
			pBindable->bind(graphicsCtx);
		graphicsCtx.drawInstanced(
			_pVertexBuffer->getVertexCount(), 
			0, 
			0, 
			0
		);
	}
}

}
