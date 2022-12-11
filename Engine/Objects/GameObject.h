#pragma once
#include <memory>
#include <typeindex>
#include <vector>

namespace Eureka {

class IComponent;
class GameObject {
	struct ComponentItem {
		std::type_index typeIndex;
		std::unique_ptr<IComponent> pComponent;
	};
public:
	GameObject();
	~GameObject();

	template<typename T> requires(std::is_base_of_v<IComponent, T>)
	T *getComponent(size_t index = 0) {
		auto typeIndex = std::type_index(typeid(T));
		for (auto &item : _components) {
			if (item.typeIndex == typeIndex) {
				if (index == 0)
					return static_cast<T *>(item.pComponent.get());
				--index;
			}
		}
		return nullptr;
	}

	template<typename T, typename...Args> requires(std::is_base_of_v<IComponent, T>)
	T *addComponent(Args&&... args) {
		ComponentItem item {
			.typeIndex = std::type_index(typeid(T)),
			.pComponent = std::make_unique<T>(this, std::forward<Args>(args)...),
		};
		_components.push_back(std::move(item));
		return static_cast<T *>(_components.back().pComponent.get());
	}
private:
	std::vector<ComponentItem> _components;
};

}
