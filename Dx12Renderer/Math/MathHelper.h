#pragma once
#include <DirectXMath.h>
#include "MatrixHelper.h"
#include <concepts>

namespace Math {

namespace DX = DirectX;
namespace XM = DirectX;

class MathHelper {
public:
	template<typename T>
	static T lerp(const T &lhs, const T &rhs, float t) {
		return lhs + (rhs - lhs) * t;
	}

	template <typename T>
	static T divideByMultiple(T value, size_t alignment) {
		return reinterpret_cast<T>((value + alignment - 1) / alignment);
	}

	template<std::integral T>
	static T alignTo16(T val) {
		constexpr T kMask = ~T{16};
		return val + (val & kMask);
	}

	template<std::integral T>
	static bool isMultiplesOf16(T val) {
		constexpr T kMask{16};
		return (val & kMask) == 0;
	}
};


}

