#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Buffer/UploadBuffer.h>
#include <memory>

namespace dx12lib {

class VertexBuffer : public IVertexBuffer {
protected:
	VertexBuffer(std::weak_ptr<Device> pDevice, 
		std::shared_ptr<CommandList> pCmdList, 
		const void *pData, 
		size_t numElements, 
		size_t stride
	);
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	size_t getBufferSize() const override;
	size_t getVertexCount() const override;
	size_t getVertexStride() const override;
	const VertexBufferView &getVertexBufferView() const override;
private:
	size_t _vertexStride;
	VertexBufferView _vertexBufferView;
	std::unique_ptr<DefaultBuffer> _pDefaultBuffer;
};

}