#pragma once
#include <memory>
#include <cassert>

namespace Eureka {

template<typename T>
class Singletion {
public:
	static T *instance() noexcept {
		return _pInstance.get();
	}
	template<typename... Args>
	static void SingletionEmplace(Args&& ...args) {
		assert(_pInstance == nullptr);
		_pInstance = std::make_unique<T>(std::forward<Args>(args)...);
	}
	static void SingletionDestory() {
		assert(_pInstance != nullptr);
		_pInstance = nullptr;
	}
private:
	static inline std::unique_ptr<T> _pInstance;
};

}