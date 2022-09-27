#pragma once
#include <DirectXMath.h>


namespace Math {

namespace DX = DirectX;

template<typename T, size_t C, size_t R>
struct MatrixHelper;

template<>
struct MatrixHelper<float, 4, 4> : public DX::XMFLOAT4X4 {
	using DX::XMFLOAT4X4::XMFLOAT4X4;
};

}

