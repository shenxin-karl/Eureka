#include <Dx12lib/Buffer/VertexBuffer.h>
#include <Dx12lib/Buffer/DefaultBuffer.h>
#include <Dx12lib/Context/CommandList.h>
#include <Dx12lib/Device/Device.h>

namespace dx12lib {

VertexBuffer::VertexBuffer(std::weak_ptr<Device> pDevice, 
	std::shared_ptr<CommandList> pCmdList,
	const void *pData, 
	size_t numElements, 
	size_t stride)
: _vertexStride(stride)
{
	size_t sizeInByte = numElements * stride;
	_pDefaultBuffer = std::make_unique<DefaultBuffer>(
		pDevice,
		pCmdList->getD3DCommandList(), 
		pData, 
		sizeInByte
	);

	_vertexBufferView = VertexBufferView {
		_pDefaultBuffer->getAddress(),
		static_cast<UINT>(getBufferSize()),
		static_cast<UINT>(_vertexStride)
	};
}

WRL::ComPtr<ID3D12Resource> VertexBuffer::getD3DResource() const {
	return _pDefaultBuffer->getD3DResource();
}

size_t VertexBuffer::getBufferSize() const {
	return _pDefaultBuffer->getBufferSize();
}

size_t VertexBuffer::getVertexCount() const {
	assert(_vertexStride != 0);
	return getBufferSize() / _vertexStride;
}

size_t VertexBuffer::getVertexStride() const {
	return _vertexStride;
}

const VertexBufferView &VertexBuffer::getVertexBufferView() const {
	return _vertexBufferView;
}

}