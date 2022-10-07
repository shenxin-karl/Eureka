#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#define SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <locale>

namespace dx12lib {

void IResource::setResourceName(const std::string &name) {
	setResourceName(to_wstring(name));
}

void IResource::setResourceName(const std::wstring &name) {
	WRL::ComPtr<ID3D12Resource> pResource = getD3DResource();
	assert(pResource != nullptr);
	_resourceName = name;
	pResource->SetName(name.c_str());
}

void IResource::setDevice(std::weak_ptr<Device> pDevice) {
	_pDevice = std::move(pDevice);
}

size_t IResource::getWidth() const {
	return getD3DResource()->GetDesc().Width;
}

size_t IResource::getHeight() const {
	return getD3DResource()->GetDesc().Height;
}

DXGI_FORMAT IResource::getFormat() const {
	return getD3DResource()->GetDesc().Format;
}

std::weak_ptr<Device> IResource::getDevice() const {
	return _pDevice;
}

bool IResource::checkRTVState(D3D12_RESOURCE_STATES state) const {
	return state == D3D12_RESOURCE_STATE_COMMON || state & D3D12_RESOURCE_STATE_RENDER_TARGET;
}

bool IResource::checkDSVState(D3D12_RESOURCE_STATES state) const {
	return state == D3D12_RESOURCE_STATE_COMMON || state & D3D12_RESOURCE_STATE_DEPTH_WRITE;
}

bool IResource::checkCBVState(D3D12_RESOURCE_STATES state) const {
	return state == D3D12_RESOURCE_STATE_COMMON || state & D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
}

bool IResource::checkSRVState(D3D12_RESOURCE_STATES state) const {
	return state == D3D12_RESOURCE_STATE_COMMON					  ||
		   state & D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE ||
		   state & D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
}

bool IResource::checkUAVState(D3D12_RESOURCE_STATES state) const {
	return state == D3D12_RESOURCE_STATE_COMMON || state & D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
}

BufferType IConstantBuffer::getBufferType() const {
	return BufferType::ConstantBuffer;
}

BufferType IVertexBuffer::getBufferType() const {
	return BufferType::IndexBuffer;
}

BufferType IIndexBuffer::getBufferType() const {
	return BufferType::IndexBuffer;
}

BufferType ISRStructuredBuffer::getBufferType() const {
	return BufferType::StructuredBuffer;
}

BufferType IUAStructuredBuffer::getBufferType() const {
	return BufferType::StructuredBuffer;
}

BufferType IReadBackBuffer::getBufferType() const {
	return BufferType::ReadBackBuffer;
}

}
