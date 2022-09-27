#include <iostream>
#include "MathStd.hpp"

//void float2Test() {
//	using namespace Math;
//	using namespace std;
//	float2 f1;
//	float2 f2(1);
//	float2 f3(2, 2);
//	cout << "f1: " << f1 << endl;
//	cout << "f2: " << f2 << endl;
//	cout << "f3: " << f3 << endl;
//	f1 = float2(0);
//}
//
//void float3Test() {
//
//}
//
//void float4Test() {
//	using namespace Math;
//	using namespace std;
//	float4 f1;
//	float4 f2(1);
//	float4 f3(2, 2, 2, 2);
//	cout << "f1: " << f1 << endl;
//	cout << "f2: " << f2 << endl;
//	cout << "f3: " << f3 << endl;
//	f1 = float4(0);
//	cout << "dot(f2, f3): " << dot(f2, f3) << endl;
//	auto f4 = normalize(f3);
//	cout << "length(f4): " << length(f4) << endl;
//	f4 += 1.f;
//	1 + f4;
//	f4 += f1;
//	f4 + f1;
//
//	f4 -= 1.f;
//	1 - f4;
//	f4 -= f1;
//	f4 - f1;
//
//	f4 *= 1.f;
//	1 * f4;
//	f4 *= f1;
//	f4 *f1;
//
//	f4 /= 1.f;
//	1 / f4;
//	f4 /= f1;
//	f4 / f1;
//}

void buildBoundingFrustumTest() {
	namespace DX = DirectX;
	float near = 0.1f;
	float far = 100.f;
	float aspect = 1.f;
	float radianFov = DX::XMConvertToRadians(45.f);
	DX::XMMATRIX projection = DX::XMMatrixPerspectiveFovLH(radianFov, aspect, near, far);
	DX::XMVECTOR det = DX::XMMatrixDeterminant(projection);
	DX::XMMATRIX invProj = DX::XMMatrixInverse(&det, projection);

	DX::XMVECTOR HomogenousPoints[6] = {
		DX::XMVectorSet(+1, +0, +1, +1),
		DX::XMVectorSet(-1, +0, +1, +1),
		DX::XMVectorSet(+0, +1, +1, +1),
		DX::XMVectorSet(+0, -1, +1, +1),
		DX::XMVectorSet(+0, +0, +0, +1),
		DX::XMVectorSet(+0, +0, +1, +1),
	};

	DX::XMVECTOR points[6];
	for (size_t i = 0; i < 6; ++i)
		points[i] = DX::XMVector4Transform(HomogenousPoints[i], invProj);

	using namespace Math;
	float depth = 1.f / float4(points[0]).w;
	std::cout << Vector3(points[0]) * depth << std::endl;
	std::cout << Vector3(points[1]) * depth << std::endl;
	std::cout << Vector3(points[2]) * depth << std::endl;
	std::cout << Vector3(points[3]) * depth << std::endl;
	float zNear = 1.f / float4(points[4]).w;
	float zFar = 1.f / float4(points[5]).w;
	std::cout << "zNear: " << zNear << " zFar:" << zFar << std::endl;
}

void vector2Test() {
	using namespace Math;
	Vector2 v0;
	Vector2 v1;
	v0.xy = float2(1.f, 0.f);
	std::cout << v0.xy << std::endl;
	v1 = v0;
	std::cout << v1.yx << std::endl;

	v0 = Vector2(0.f, 0.f);
	v1 = Vector2(1.f, 1.f);
	v0 += v1;
	std::cout << "v0 + v1" << v0 << std::endl;
	v0 *= 5.f;
	std::cout << "v0 *= 5" << v0 << std::endl;
	std::cout << "lengthSquare(v0)" << lengthSquare(v0) << std::endl;
	std::cout << "length(v0)" << length(v0) << std::endl;

	v0 = Vector2(10.f, -10.f);
	std::cout << "sqrt(v0)" << sqrt(v0) << std::endl;


	v0 = Vector2(0.f, 0.f);
	v1 = Vector2(10.f);
	std::cout << "lerp(v0, v1, 0.5)" << lerp(v0, v1, 0.5f) << std::endl;
	std::cout << "lerp(v0, v1, Vector2(0.1, 0.5))" << lerp(v0, v1, Vector2(0.1f, 0.5f)) << std::endl;

	v0 = Vector2(-1.f, 10.f);
	std::cout << "clamp(v0, Vector2(0.f), Vector2(9.f))" << clamp(v0, Vector2(0.f), Vector2(9.f)) << std::endl;
}

void vector3Test() {
	using namespace Math;
	Vector3 v1;
	Vector3 v2;
	v1 = Vector3(1.0);
	v2 = Vector3(2.f);
	std::cout << "v1 + v2: " << (v1 + v2) << std::endl;
	std::cout << "v1 - v2: " << (v1 - v2) << std::endl;
	std::cout << "v1 * v2: " << (v1 * v2) << std::endl;
	std::cout << "v1 / v2: " << (v1 / v2) << std::endl;
	std::cout << "--------------------------" << std::endl;

	std::cout << "v1 + 2.f: " << (v1 + 2.f) << std::endl;
	std::cout << "v1 - 2.f: " << (v1 - 2.f) << std::endl;
	std::cout << "v1 * 2.f: " << (v1 * 2.f) << std::endl;
	std::cout << "v1 / 2.f: " << (v1 / 2.f) << std::endl;
	std::cout << "--------------------------" << std::endl;

	Vector3 v3 = Vector3(100.f);
	Vector3 v4 = Vector3(100.f);
	Vector3 v5 = Vector3(100.f);
	Vector3 v6 = Vector3(100.f);

	v3 += Vector3(0.5);
	v4 -= Vector3(0.5);
	v5 *= Vector3(0.5);
	v6 /= Vector3(0.5);

	std::cout << "	v3 += Vector3(0.5);: " << (v3) << std::endl;
	std::cout << "	v4 -= Vector3(0.5);: " << (v4) << std::endl;
	std::cout << "	v5 *= Vector3(0.5);: " << (v5) << std::endl;
	std::cout << "	v6 /= Vector3(0.5);: " << (v6) << std::endl;
	std::cout << "--------------------------" << std::endl;

	v3 = Vector3(100.f);
	v4 = Vector3(100.f);
	v5 = Vector3(100.f);
	v6 = Vector3(100.f);

	v3 += (0.5);
	v4 -= (0.5);
	v5 *= (0.5);
	v6 /= (0.5);
	std::cout << "	v3 += (0.5);: " << (v3) << std::endl;
	std::cout << "	v4 -= (0.5);: " << (v4) << std::endl;
	std::cout << "	v5 *= (0.5);: " << (v5) << std::endl;
	std::cout << "	v6 /= (0.5);: " << (v6) << std::endl;
	std::cout << "--------------------------" << std::endl;

	v3 = Vector3(100.f);
	v4 = Vector3(100.f);
	v5 = Vector3(100.f);
	v6 = Vector3(100.f);

	v3 = 0.5 + v3;
	v4 = 0.5 - v4;
	v5 = 0.5 * v5;
	v6 = 0.5 / v6;

	std::cout << "	v3 = 0.5 + v3: " << (v3) << std::endl;
	std::cout << "	v4 = 0.5 - v4: " << (v4) << std::endl;
	std::cout << "	v5 = 0.5 * v5: " << (v5) << std::endl;
	std::cout << "	v6 = 0.5 / v6: " << (v6) << std::endl;
	std::cout << "--------------------------" << std::endl;

	std::cout << "v3.x:" << v3.x << std::endl;
	std::cout << "v4.xy:" << v4.xy << std::endl;
	std::cout << "v5.xyz:" << v5.xyz << std::endl;

	float3 f1 = v3.xyz;
	float3 f2 = v3.xxx;
	float3 f3 = v3.zyx;
}

void matrix3Test() {
	using namespace Math;
	Matrix3 rotate = Matrix3::makeXRotationByRadian(30.f);
	Vector3 yAxist = Vector3(0.f, 1.f, 0.f);
	auto res = rotate * yAxist;
	std::cout << "yAxist " << res << std::endl;
}

int main() {
	//float2Test();
	//float3Test();
	//float4Test();
	std::cout << std::endl << "-----vector3Test--------" << std::endl;
	vector2Test();
	std::cout << std::endl << "-----vector3Test--------" << std::endl;
	vector3Test();
	std::cout << std::endl << "-----matrix3Test--------" << std::endl;
	matrix3Test();
	buildBoundingFrustumTest();
}