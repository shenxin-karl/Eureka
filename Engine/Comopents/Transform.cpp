#include "Transform.h"

namespace Eureka {

Transform::Transform(GameObject *pGameObject) : IComponent(pGameObject) {

}

void Transform::setParent(Transform *parent) {
	if (_parent != nullptr) {
		removeChild(this);
		_parent = nullptr;
	}
	if (parent != nullptr) {
		_parent = parent;
		parent->addChild(this);
	}
}

auto Transform::getParent() const -> Transform * {
	return _parent;
}

void Transform::removeChild(Transform *pChild) {
	// todo
}

void Transform::addChild(Transform *pChild) {
	// todo
}

}
