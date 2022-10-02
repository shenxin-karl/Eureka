#pragma once
#include "Math/MathStd.hpp" 

namespace Eureka {

struct IBounding {
	virtual DX::ContainmentType contains(const Math::BoundingBox &box) const = 0;
	virtual ~IBounding() = default;
};

template<typename T>
struct BoundingWrap : public IBounding {
	BoundingWrap(const T &bound) : bound(bound) {}
	DX::ContainmentType contains(const Math::BoundingBox &box) const override {
		return bound.contains(box);
	}
public:
	const T &bound;
};

template<typename T>
BoundingWrap<std::decay_t<T>> MakeBoundingWrap(const T &bound) {
	return BoundingWrap<std::decay_t<T>>(bound);
}

}