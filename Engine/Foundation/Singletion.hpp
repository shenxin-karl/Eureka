#pragma once
#include <memory>
#include <cassert>
#include "Exception.h"

namespace Eureka {

struct ISingletion {
public:
	ISingletion() = default;
	ISingletion(const ISingletion &) = delete;
	ISingletion &operator=(const ISingletion &) = delete;
	virtual void initialize() {
	}
	virtual void destroy() {
	}
	virtual ~ISingletion() {
	}
};

template<typename T> 
class Singletion : public ISingletion {
public:
	static T *instance() noexcept {
		return pInstance;
	}
	template<typename... Args>
	static void SingletionEmplace(Args&& ...args) {
		static_assert(std::is_base_of_v<Singletion<T>, T>);
		Exception::Throw(pInstance == nullptr, "SingletionEmplace pInstance has value!");
		pInstance = new T { std::forward<Args>(args)... };
	}
	static void SingletionRelease() {
		delete pInstance;
		pInstance = nullptr;
	}
private:
	static inline T *pInstance;
};

class SingletionCollector {
public:
	template<typename T, typename...Args>
	void add(Args&&...args) {
		T::SingletionEmplace(std::forward<Args>(args)...);
		_singletions.push_back(T::instance());
		_deleters.push_back(&T::SingletionRelease);
	}
	void initialize() {
		for (auto *ptr : _singletions) {
			ptr->initialize();
		}
	}
	void destroy() {
		for (auto iter = _singletions.rbegin(); iter != _singletions.rend(); ++iter) {
			(*iter)->destroy();
		}
	}
	void release() {
		for (auto iter = _deleters.rbegin(); iter != _deleters.rend(); ++iter) {
			(*iter)();
		}
		_deleters.clear();
		_singletions.clear();
	}
	~SingletionCollector() {
		release();
	}
private:
	std::vector<void(*)()> _deleters;
	std::vector<ISingletion *> _singletions;
};

}