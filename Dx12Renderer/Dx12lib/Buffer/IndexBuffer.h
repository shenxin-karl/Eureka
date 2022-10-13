#pragma once
#include <Dx12lib/Buffer/DefaultBuffer.h>

namespace dx12lib {

class IndexBuffer : public IIndexBuffer {
protected:
	IndexBuffer(std::weak_ptr<Device> pDevice, 
		std::shared_ptr<CommandList> pCmdList, 
		const void *pData,
		size_t numElements,
		DXGI_FORMAT format
	);
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const final;
	size_t getBufferSize() const final;
	size_t getIndexCount() const final;
	size_t getIndexStride() const final;
	DXGI_FORMAT getIndexFormat() const final;
	const IndexBufferView &getIndexBufferView() const final;
	static size_t getIndexStrideByFormat(DXGI_FORMAT format);
private:
	DXGI_FORMAT                    _indexFormat;
	IndexBufferView				   _indexBufferView;
	std::unique_ptr<DefaultBuffer> _pDefaultBuffer;
};

}