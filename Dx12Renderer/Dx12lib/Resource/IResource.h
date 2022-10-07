#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/ResourceView.hpp>
#include <d3d12.h>
#include <wrl.h>

namespace dx12lib {

interface IResource : NonCopyable {
	IResource() = default;
	~IResource() override = default;
	void setResourceName(const std::string &name);
	void setResourceName(const std::wstring &name);
	void setDevice(std::weak_ptr<Device> pDevice);
	size_t getWidth() const;
	size_t getHeight() const;
	DXGI_FORMAT getFormat() const;
	std::weak_ptr<Device> getDevice() const;
	virtual WRL::ComPtr<ID3D12Resource> getD3DResource() const = 0;
	virtual bool checkRTVState(D3D12_RESOURCE_STATES state) const;
	virtual bool checkDSVState(D3D12_RESOURCE_STATES state) const;
	virtual bool checkCBVState(D3D12_RESOURCE_STATES state) const;
	virtual bool checkSRVState(D3D12_RESOURCE_STATES state) const;
	virtual bool checkUAVState(D3D12_RESOURCE_STATES state) const;
protected:
	std::wstring		  _resourceName;
	std::weak_ptr<Device> _pDevice;
};

/////////////////////////////////////////////IBufferResource/////////////////////////////////////////////

interface IBufferResource : virtual IResource {
	virtual BufferType getBufferType() const = 0;
	virtual size_t getBufferSize() const = 0;
};
/////////////////////////////////////////////IConstantBuffer/////////////////////////////////////////////
interface IConstantBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual size_t getElementStride() const = 0;
	virtual BYTE *getMappedPtr() = 0;
	virtual const BYTE *getMappedPtr() const = 0;
	virtual void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) = 0;
	virtual const ConstantBufferView &getCBV() const = 0;
};
/////////////////////////////////////////////IVertexBuffer/////////////////////////////////////////////
interface IVertexBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual size_t getVertexCount() const = 0;
	virtual size_t getVertexStride() const = 0;
	virtual const VertexBufferView &getVertexBufferView() const = 0;
};
/////////////////////////////////////////////IIndexBuffer/////////////////////////////////////////////
interface IIndexBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual size_t getIndexCount() const = 0;
	virtual size_t getIndexStride() const = 0;
	virtual DXGI_FORMAT getIndexFormat() const = 0;
	virtual const IndexBufferView &getIndexBufferView() const = 0;
};
//////////////////////////////////////////ISRStructuredBuffer//////////////////////////////////////////
interface ISRStructuredBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual size_t getElementCount() const = 0;
	virtual size_t getElementStride() const = 0;
	virtual void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) = 0;
	virtual const ShaderResourceView &getSRV() const = 0;
};
//////////////////////////////////////////IUAStructuredBuffer//////////////////////////////////////////
interface IUAStructuredBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual size_t getElementCount() const = 0;
	virtual size_t getElementStride() const = 0;
	virtual const UnorderedAccessView &getUAV() const = 0;
	virtual const ShaderResourceView &getSRV() const = 0;
};
//////////////////////////////////////////IReadBackBuffer//////////////////////////////////////////
interface IReadBackBuffer : IBufferResource {
	BufferType getBufferType() const override;
	virtual bool isCompleted() const = 0;
	virtual const void *getMappedPtr() const = 0;
	virtual size_t getElementCount() const = 0;
	virtual size_t getElementStride() const = 0;
	virtual void setCompletedCallback(const std::function<void(IReadBackBuffer *)> &callback) = 0;
};

}