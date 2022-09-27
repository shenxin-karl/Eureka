#include "ConstantBufferBindable.h"

namespace rgph {

std::shared_ptr<ConstantBufferBindable> ConstantBufferBindable::make(const dx12lib::ShaderRegister &sr,
	std::shared_ptr<dx12lib::IConstantBuffer> pConstantBuffer)
{
	assert(pConstantBuffer != nullptr);
	assert(sr.slot && !sr.slot.isSampler());
	auto pBindable = std::make_shared<ConstantBufferBindable>();
	pBindable->_pConstantBuffer = pConstantBuffer;
	pBindable->_shaderRegister = sr;
	return pBindable;
}

void ConstantBufferBindable::bind(dx12lib::IGraphicsContext &graphicsCtx) const {
	graphicsCtx.setConstantBuffer(_shaderRegister, _pConstantBuffer);
}

}
