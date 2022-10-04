#pragma once
#include <cassert>
#include <functional>
#include <RenderGraph/Pass/PassResourceBase.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Buffer/BufferStd.h>

namespace rgph {

template<typename T> requires(std::is_base_of_v<dx12lib::IResource, T>)
class PassResourcePtr : public PassResourceBase {
public:
	using PassResourceBase::PassResourceBase;

	using ResourceType = T;

	template<typename U0, typename U1>
	friend void operator>>(PassResourcePtr<U0> &lhs, PassResourcePtr<U1> &rhs);

	void link(dx12lib::ICommonContext &commonCtx) override {
		assert(_linkResourceFunc != nullptr);
		_linkResourceFunc();
		assert(_pResource != nullptr);
		if (preExecuteState != kNoneType)
			commonCtx.transitionBarrier(_pResource, preExecuteState);
	}

	PassResourcePtr &operator=(std::nullptr_t) {
		_pResource = nullptr;
		return *this;
	}

	~PassResourcePtr() override {
		PassResourcePtr::reset();
	}

	operator std::shared_ptr<T> &() noexcept {
		return _pResource;
	}

	T *operator->() noexcept {
		return _pResource.get();
	}

	operator const std::shared_ptr<T> &() const noexcept {
		return _pResource;
	}

	const T *operator->() const noexcept {
		return _pResource.get();
	}

	friend bool operator==(const PassResourcePtr &pResource, std::nullptr_t) noexcept {
		return pResource._pResource == nullptr;
	}

	friend bool operator!=(const PassResourcePtr &pResource, std::nullptr_t) noexcept {
		return pResource._pResource != nullptr;
	}

	friend void operator>>(std::function<std::shared_ptr<dx12lib::IResource>()> callback, PassResourcePtr &rhs) {
		assert(rhs.getResourceSource() == nullptr);
		assert(callback != nullptr);
		rhs._linkResourceFunc = [&, cb = std::move(callback)]() {
			rhs._pResource = std::dynamic_pointer_cast<T>(cb());
		};
	}

	template<typename U> requires(std::is_base_of_v<dx12lib::IResource, U>)
	friend void operator>>(const std::shared_ptr<U> &pOther, PassResourcePtr &rhs) {
		assert(pOther != nullptr);
		rhs._linkResourceFunc = [&]() mutable {
			rhs._pResource = std::dynamic_pointer_cast<T>(pOther);
		};
	}

	void reset() override {
		_pResource = nullptr;
	}

	T *get() noexcept {
		return _pResource.get();
	}

	const T *get() const noexcept {
		return _pResource.get();
	}

	std::shared_ptr<dx12lib::IResource> getResource() const override {
		return std::static_pointer_cast<dx12lib::IResource>(_pResource);
	}
private:
	bool tryLink() override {
		if (_linkResourceFunc == nullptr)
			return false;
		_linkResourceFunc();
		return _pResource != nullptr;
	}

private:
	std::shared_ptr<T> _pResource;
	std::function<void()> _linkResourceFunc;
};


template<typename U0, typename U1>
void operator>>(PassResourcePtr<U0> &lhs, PassResourcePtr<U1> &rhs) {
	assert(static_cast<PassResourceBase *>(&lhs) != static_cast<PassResourceBase *>(&rhs));
	assert(rhs.getResourceSource() == nullptr);
	rhs.setResourceSource(&lhs);
	rhs._linkResourceFunc = [&]() {
		if constexpr (std::is_same_v<U0, U1>)
			rhs._pResource = lhs._pResource;
		else
			rhs._pResource = std::dynamic_pointer_cast<U1>(lhs._pResource);
	};
}

}
