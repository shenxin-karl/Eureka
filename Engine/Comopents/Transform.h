#pragma once
#include <vector>
#include "IComponent.h"
#include "Math/MathStd.hpp"
#include "Foundation/BitFlag.hpp"

namespace Eureka {

struct TransformData {
	Math::float3   localPosition  = Math::float3::zero();
	Math::float3   worldPosition  = Math::float3::zero();
	Math::float3   localScale     = Math::float3::one();
	Math::float3   worldScale     = Math::float3::one();
	Math::float4   localRotate    = Math::float4::QuaternionIdentity();
	Math::float4   worldRotate    = Math::float4::QuaternionIdentity();;
	Math::float4x4 localTransform = Math::float4x4::identity();
	Math::float4x4 worldTransform = Math::float4x4::identity();
};

class GameObject;
class Transform : public IComponent {
	friend GameObject;
	enum TransformDirty {
		None			   = (0),
		LocalMatrixDirty   = (1 << 0),
		WorldMatrixDirty   = (1 << 1),
		WorldPositionDirty = (1 << 2),
		WorldScaleDirty    = (1 << 3),
		WorldRotateDirty   = (1 << 4),
		WorldPropertyDirty = (WorldMatrixDirty | WorldPositionDirty | WorldScaleDirty | WorldRotateDirty),
	};
public:
	Transform(GameObject *pGameObject);
	void setParent(Transform *parent);
	auto getParent() const -> Transform *;
	auto getChildren() const -> const std::vector<Transform *> &;
	void setLocalPosition(const Math::float3 &localPosition);
	void setLocalScale(const Math::float3 &localScale);
	void setLocalRotate(const Math::float4 &quaternion);
	void setWorldPosition(const Math::float3 &worldPosition);
	void setWorldRotate(const Math::float4 &quaternion);
	auto getLocalPosition() const -> const Math::float3 &;
	auto getLocalScale() const -> const Math::float3 &;
	auto getLocalRotate() const -> const Math::float4 &;
	auto getWorldPosition() const -> const Math::float3 &;
	auto getWorldScale() const -> const Math::float3 &;
	auto getWorldRotate() const -> const Math::float4 &;
	auto getLocalTransform() const -> const Math::float4x4 &;
	auto getWorldTransform() const -> const Math::float4x4 &;
private:
	void removeChild(Transform *pChild);
	void addChild(Transform *pChild);
private:
	Transform				 *_parent = nullptr;
	std::vector<Transform *>  _children;
	mutable BitFlag<uint32_t> _dirtyFlag;
	mutable TransformData	  _transformData;
};

}
