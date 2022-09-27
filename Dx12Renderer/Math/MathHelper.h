#pragma once
#include <DirectXMath.h>
#include "Math/MatrixHelper.h"

namespace Math {

namespace DX = DirectX;
namespace XM = DirectX;

class MathHelper {
public:
	template<typename T>
	static T lerp(const T &lhs, const T &rhs, float t) {
		return lhs + (rhs - lhs) * t;
	}
};


}

