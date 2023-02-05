#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Descriptor/DescriptorAllocatorPage.h>

namespace dx12lib {

DescriptorAllocation::DescriptorAllocation()
: _numHandle(0), _handleSize(0), _pRefCount(nullptr), _baseHandle(D3D12_CPU_DESCRIPTOR_HANDLE{ 0 })
{
}

DescriptorAllocation::DescriptorAllocation(const DescriptorAllocation &other)
: _numHandle(0), _handleSize(other._handleSize)
, _pRefCount(nullptr), _baseHandle(D3D12_CPU_DESCRIPTOR_HANDLE{ 0 }), _pPage(other._pPage)
{
	if (other._pRefCount == nullptr)
		return;

	size_t count = other._pRefCount->load();
	while (count != 0) {
		if (other._pRefCount->compare_exchange_strong(count, count + 1))
			break;
	}

	if (count != 0) {
		_pRefCount = other._pRefCount;
		_numHandle = other._numHandle;
		_baseHandle = other._baseHandle;
	}
}

DescriptorAllocation::DescriptorAllocation(DescriptorAllocation &&other) noexcept : DescriptorAllocation() {
	swap(*this, other);
}

DescriptorAllocation &DescriptorAllocation::operator=(const DescriptorAllocation &other) {
	DescriptorAllocation tmp { other };
	swap(*this, tmp);
	return *this;
}

void swap(DescriptorAllocation &lhs, DescriptorAllocation &rhs) noexcept {
	using std::swap;
	swap(lhs._numHandle, rhs._numHandle);
	swap(lhs._handleSize, rhs._handleSize);
	swap(lhs._pRefCount, rhs._pRefCount);
	swap(lhs._baseHandle, rhs._baseHandle);
	swap(lhs._pPage, rhs._pPage);
}


DescriptorAllocation::~DescriptorAllocation() {
	if (_pRefCount == nullptr)
		return;

	size_t refCount = _pRefCount->fetch_sub(1);
	if (refCount == 1)
		free();
}

DescriptorAllocation::DescriptorAllocation(D3D12_CPU_DESCRIPTOR_HANDLE handle,
	std::atomic_size_t *pRefCount,
	size_t numHandle,
	size_t handleSize,
	std::shared_ptr<DescriptorAllocatorPage> pPage)
: _numHandle(numHandle), _handleSize(handleSize), _pRefCount(pRefCount)
, _baseHandle(handle), _pPage(pPage)
{
	assert(pRefCount->load() == 1);
}

DescriptorAllocation &DescriptorAllocation::operator=(DescriptorAllocation &&other) noexcept {
	DescriptorAllocation tmp;
	swap(*this, tmp);
	swap(*this, other);
	return *this;
}

size_t DescriptorAllocation::getNumHandle() const noexcept {
	return _numHandle;
}

size_t DescriptorAllocation::getHandleSize() const noexcept {
	return _handleSize;
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorAllocation::getCPUHandle(size_t offset) const {
	assert(offset < _numHandle);
	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(_baseHandle);
	handle.Offset(static_cast<INT>(offset), static_cast<UINT>(_handleSize));
	return handle;
}

bool DescriptorAllocation::isNull() const noexcept {
	return _baseHandle.ptr == 0;
}

bool DescriptorAllocation::isValid() const noexcept {
	return _baseHandle.ptr != 0;
}

void DescriptorAllocation::free() {
	if (isNull() || _pPage == nullptr)
		return;
	auto pPage = _pPage;
	pPage->free(std::move(*this));
}

void DescriptorAllocation::reset() noexcept {
	_numHandle = 0;
	_handleSize = 0;
	_baseHandle = D3D12_CPU_DESCRIPTOR_HANDLE{ 0 };
	_pRefCount = nullptr;
	_pPage = nullptr;
}

}