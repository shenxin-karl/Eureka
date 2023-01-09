#pragma once
#include "Foundation/Exception.h"

namespace Eureka {

class GameObject;

class IComponent {
public:
	friend GameObject;
	IComponent(const IComponent &) = delete;
	IComponent &operator=(const IComponent &) = delete;
	virtual ~IComponent() = default;
protected:
	IComponent(GameObject *pGameObject) {
		Exception::Throw(pGameObject != nullptr, "IComponent::setGameObject pGameObject is nullptr");
		_pGameObject = pGameObject;
	}
public:
	auto getGameObject() const -> GameObject * {
		return _pGameObject;
	}
private:
	GameObject *_pGameObject = nullptr;
};

}