#pragma once

namespace dx12lib {

template<typename T>
class CBufferVisitor {
public:
	CBufferVisitor(T *ptr) : _ptr(ptr) {}
	CBufferVisitor(const CBufferVisitor &) = delete;
	CBufferVisitor(CBufferVisitor &&other) = default;
	decltype(auto) operator->() const {
		return _ptr;
	}
	decltype(auto) operator*() const {
		return *_ptr;
	}
	T *ptr() noexcept {
		return _ptr;
	}
	const T *ptr() const {
		return _ptr;
	}
private:
	T *const _ptr;
};

}
