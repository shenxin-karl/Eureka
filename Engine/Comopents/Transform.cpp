#include "Transform.h"

namespace Eureka {

using namespace Math;

Transform::Transform(GameObject *pGameObject) : IComponent(pGameObject), _dirtyFlag(None) {

}

void Transform::setParent(Transform *parent) {
	if (_parent == parent)
		return;
	if (_parent != nullptr) {
		removeChild(this);
		_parent = nullptr;
	}
	if (parent != nullptr) {
		_parent = parent;
		parent->addChild(this);
	}
	_dirtyFlag.set(WorldPropertyDirty);
}

auto Transform::getParent() const -> Transform * {
	return _parent;
}

auto Transform::getChildren() const -> const std::vector<Transform *> & {
	return _children;
}

void Transform::setLocalPosition(const Math::float3 &localPosition) {
	if (_transformData.localPosition != localPosition) {
		_transformData.localPosition = localPosition;
		_dirtyFlag.set(LocalMatrixDirty | WorldMatrixDirty | WorldPositionDirty);
	}
}

void Transform::setLocalScale(const Math::float3 &localScale) {
	if (_transformData.localScale != localScale) {
		_transformData.localScale = localScale;
		_dirtyFlag.set(LocalMatrixDirty | WorldMatrixDirty | WorldScaleDirty);
	}
}

void Transform::setLocalRotate(const Math::float4 &quaternion) {
	if (_transformData.localRotate != quaternion) {
		_transformData.localRotate = quaternion;
		_dirtyFlag.set(LocalMatrixDirty | WorldMatrixDirty | WorldRotateDirty);
	}
}

void Transform::setWorldPosition(const Math::float3 &worldPosition) {
	if (_transformData.worldPosition != worldPosition) {
		if (_parent != nullptr) {
			Matrix4 parentInverse(_parent->getWorldTransform());
			parentInverse = inverse(parentInverse);
			Vector4 localPosition = parentInverse * Vector4(worldPosition, 1.f);
			_transformData.localPosition = float3(localPosition);
		} else {
			_transformData.localPosition = worldPosition;
		}
		_transformData.worldPosition = worldPosition;
		_dirtyFlag.set(LocalMatrixDirty | WorldMatrixDirty);
	}
}

void Transform::setWorldRotate(const Math::float4 &quaternion) {
	if (_transformData.worldRotate != quaternion) {
		if (_parent != nullptr) {
			Quaternion q(_parent->getWorldRotate());
			_transformData.localRotate = float4(inverse(q) * Quaternion(quaternion));
		} else {
			_transformData.localRotate = quaternion;
		}
		_transformData.localRotate = quaternion;
		_dirtyFlag.set(LocalMatrixDirty | WorldMatrixDirty);
	}
}

auto Transform::getLocalPosition() const -> const Math::float3 & {
	return _transformData.localPosition;
}

auto Transform::getLocalScale() const -> const Math::float3 & {
	return _transformData.localScale;
}

auto Transform::getLocalRotate() const -> const Math::float4 & {
	return _transformData.localRotate;
}

auto Transform::getWorldPosition() const -> const Math::float3 & {
	if (_dirtyFlag.test(WorldPositionDirty)) {
		Vector3 parentPosition((_parent != nullptr) ? _parent->getWorldPosition() : float3::zero());
		_transformData.worldPosition = float3(parentPosition + Vector3(_transformData.localPosition));
		_dirtyFlag.reset(WorldPositionDirty);
	}
	return _transformData.worldPosition;
}

auto Transform::getWorldScale() const -> const Math::float3 & {
	if (_dirtyFlag.test(WorldScaleDirty)) {
		Vector3 parentScale((_parent != nullptr) ? _parent->getWorldScale() : float3::one());
		_transformData.worldScale = float3(parentScale * Vector3(_transformData.localScale));
		_dirtyFlag.reset(WorldScaleDirty);
	}
	return _transformData.worldScale;
}

auto Transform::getWorldRotate() const -> const Math::float4 & {
	if (_dirtyFlag.test(WorldRotateDirty)) {
		Quaternion parentRotate((_parent != nullptr) ? _parent->getWorldRotate() : float4::QuaternionIdentity());
		_transformData.worldRotate = float4(Quaternion(_transformData.localRotate) * parentRotate);
		_dirtyFlag.reset(WorldRotateDirty);
	}
	return _transformData.worldRotate;
}

auto Transform::getLocalTransform() const -> const Math::float4x4 & {
	if (_dirtyFlag.test(LocalMatrixDirty)) {
		Vector3 translation(getLocalPosition());
		Vector3 scale(getLocalScale());
		Quaternion rotateQuat(getLocalRotate());
		_transformData.localTransform = float4x4(Matrix4::Affine(translation, rotateQuat, scale));
		_dirtyFlag.reset(LocalMatrixDirty);
	}
	return _transformData.localTransform;
}

auto Transform::getWorldTransform() const -> const Math::float4x4 & {
	if (_dirtyFlag.test(WorldMatrixDirty)) {
		if (_parent == nullptr) {
			_transformData.worldTransform = getLocalTransform();
		} else {
			Matrix4 localTransform(getLocalTransform());
			Matrix4 parentTransform(_parent->getWorldTransform());
			_transformData.worldTransform = float4x4(localTransform * parentTransform);
			_dirtyFlag.reset(WorldMatrixDirty);
		}
	}
	return _transformData.worldTransform;
}

void Transform::removeChild(Transform *pChild) {
	if (pChild == nullptr) {
		Exception::Assert(pChild != nullptr, "Transform::removeChild pChild is nullptr");
		return;
	}
	auto iter = std::ranges::find(_children, pChild);
	if (iter != _children.end()) {
		_children.erase(iter);
		pChild->_dirtyFlag.set(WorldPropertyDirty);
	}
}

void Transform::addChild(Transform *pChild) {
	if (pChild == nullptr) {
		Exception::Assert(pChild != nullptr, "Transform::addChild pChild is nullptr");
		return;
	}
	for (auto *child : _children) {
		if (child == pChild)
			return;
	}
	pChild->_dirtyFlag.set(WorldPropertyDirty);
	_children.push_back(pChild);
}

}
