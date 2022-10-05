#include "ConstantBufferBindable.h"

namespace rgph {

std::shared_ptr<ConstantBufferBindable> ConstantBufferBindable::make(
	std::string shaderInputName,
	std::shared_ptr<dx12lib::IConstantBuffer> pConstantBuffer)
{
	assert(pConstantBuffer != nullptr);
	auto pBindable = std::make_shared<ConstantBufferBindable>();
	pBindable->_pConstantBuffer = pConstantBuffer;
	pBindable->_shaderInputName = std::move(shaderInputName);
	return pBindable;
}

void ConstantBufferBindable::bind(dx12lib::IGraphicsContext &graphicsCtx) const {
	graphicsCtx.setConstantBufferView(_shaderInputName, _pConstantBuffer->getCBV());
}

}
