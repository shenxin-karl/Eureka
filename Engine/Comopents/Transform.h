#pragma once
#include "IComponent.h"
#include "Math/MathStd.hpp"
#include <vector>

namespace Eureka {

enum class TransformDirty {
	None			   = (0),
	LocalMatrixChanged = (1 << 0),
	WorldMatrixChanged = (1 << 1),
};

struct TransformData {
	Math::float3   localPosition  = Math::float3::zero();
	Math::float3   worldPosition  = Math::float3::zero();
	Math::float3   localScale     = Math::float3::identity();
	Math::float3   worldScale     = Math::float3::identity();
	Math::float4   localRotate    = Math::float4::rotateIdentity();
	Math::float4   worldRotate    = Math::float4::rotateIdentity();;
	Math::float4x4 localTransform = Math::float4x4::identity();
	Math::float4x4 worldTransform = Math::float4x4::identity();
};

class GameObject;
class Transform : public IComponent {
	friend GameObject;
public:
	Transform(GameObject *pGameObject);
	void setParent(Transform *parent);
	auto getParent() const -> Transform *;
	void setLocalPosition(const Math::float3 &localPosition);
	void setLocalScale(const Math::float3 &localScale);
	void setLocalRotate(const Math::float4 &quaternion);
private:
	void removeChild(Transform *pChild);
	void addChild(Transform *pChild);
private:
	Transform				 *_parent = nullptr;
	std::vector<Transform *>  _children;
	TransformData			  _transformData;
};

}
