#pragma once
#define NOMINMAX
#include <algorithm>
#include <DirectXMath.h>
#include <ostream>
#include <DirectXCollision.h>
#include <array>
#include <utility>

#include "MathStd.hpp"
#undef min
#undef max
#define FORCEINLINE __forceinline

namespace Math {

namespace DX = DirectX;

template<size_t N>
struct FloatStore;

using float2 = FloatStore<2>;
using float3 = FloatStore<3>;
using float4 = FloatStore<4>;
using float3x3 = FloatStore<33>;
using float4x3 = FloatStore<43>;
using float4x4 = FloatStore<44>;

class Vector2;
class Vector3;
class Vector4;
class Matrix3;
class Matrix4;
class Quaternion;

template<>
struct FloatStore<2> : public DX::XMFLOAT2 {
	using DX::XMFLOAT2::XMFLOAT2;
	using DX::XMFLOAT2::operator=;

	FORCEINLINE FloatStore() noexcept = default;
	FORCEINLINE FloatStore(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore(FloatStore &&) noexcept = default;
	FORCEINLINE FloatStore &operator=(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore &operator=(FloatStore &&) noexcept = default;
	FORCEINLINE explicit FloatStore(DX::FXMVECTOR v) noexcept;
	FORCEINLINE explicit FloatStore(const Vector3 &vec) noexcept;
	FORCEINLINE explicit FloatStore(const Vector4 &vec) noexcept;
	FORCEINLINE float &operator[](size_t n) noexcept;
	FORCEINLINE float operator[](size_t n) const noexcept;
	FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const FloatStore &v) noexcept;
	FORCEINLINE FloatStore operator-() const noexcept;
	FORCEINLINE explicit operator DX::XMVECTOR() const noexcept;
	template<typename T> requires(std::is_convertible_v<T, float>)
	FORCEINLINE explicit FloatStore(T v) noexcept;

	template<typename T1, typename T2>
		requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float>)
	FORCEINLINE FloatStore(T1 x, T2 y) noexcept;

	FORCEINLINE static const FloatStore<2> &identity() noexcept;
	FORCEINLINE static const FloatStore<2> &zero() noexcept;
};

template<>
struct FloatStore<3> : public DX::XMFLOAT3 {
	using DX::XMFLOAT3::XMFLOAT3;
	using DX::XMFLOAT3::operator=;

	FORCEINLINE FloatStore() noexcept = default;
	FORCEINLINE FloatStore(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore(FloatStore &&) noexcept = default;
	FORCEINLINE explicit FloatStore(const Vector3 &vec) noexcept;
	FORCEINLINE explicit FloatStore(const Vector4 &vec) noexcept;
	FORCEINLINE FloatStore(const FloatStore<2> &f2, float z) noexcept;
	FORCEINLINE FloatStore &operator=(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore &operator=(FloatStore &&) noexcept = default;
	FORCEINLINE explicit FloatStore(DX::FXMVECTOR v) noexcept;
	FORCEINLINE FloatStore(const DX::XMFLOAT3 &f3) noexcept;
	FORCEINLINE float &operator[](size_t n) noexcept;
	FORCEINLINE float operator[](size_t n) const noexcept;
	FORCEINLINE explicit FloatStore(const DX::XMVECTORF32 &color) noexcept;
	FORCEINLINE FloatStore operator-() const noexcept;
	FORCEINLINE explicit operator DX::XMVECTOR() const noexcept;

	template<typename T> requires(std::is_convertible_v<T, float>)
	FORCEINLINE explicit FloatStore(T v);

	template<typename T1, typename T2, typename T3>
		requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float> &&
	std::is_convertible_v<T3, float>)
	FORCEINLINE FloatStore(T1 x, T2 y, T3 z) noexcept;

	template<size_t N> requires(N <= 3)
	FORCEINLINE explicit operator FloatStore<N> &() noexcept;

	template<size_t N> requires(N <= 3)
	FORCEINLINE explicit operator const FloatStore<N> &() const noexcept;
	FORCEINLINE static const FloatStore<3> &identity() noexcept;
	FORCEINLINE static const FloatStore<3> &zero() noexcept;
};

template<>
struct FloatStore<4> : public DX::XMFLOAT4 {
	using DX::XMFLOAT4::XMFLOAT4;
	using DX::XMFLOAT4::operator=;

	FORCEINLINE FloatStore() noexcept = default;
	FORCEINLINE FloatStore(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore(FloatStore &&) noexcept = default;
	FORCEINLINE FloatStore &operator=(const FloatStore &) noexcept = default;
	FORCEINLINE FloatStore &operator=(FloatStore &&) noexcept = default;
	FORCEINLINE explicit FloatStore(DX::FXMVECTOR v) noexcept;
	FORCEINLINE explicit FloatStore(const Vector4 &v4) noexcept;
	FORCEINLINE explicit FloatStore(const Quaternion &q);
	FORCEINLINE FloatStore(const FloatStore<2> &f2, float z, float w) noexcept;
	FORCEINLINE FloatStore(const FloatStore<3> &f3, float w) noexcept;
	FORCEINLINE float &operator[](size_t n) noexcept;
	FORCEINLINE float operator[](size_t n) const noexcept;
	FORCEINLINE explicit FloatStore(const DX::XMVECTORF32 &color) noexcept;
	FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const FloatStore &v) noexcept;
	FORCEINLINE FloatStore operator-() const noexcept;
	FORCEINLINE explicit operator DX::XMVECTOR() const noexcept;

	template<typename T> requires(std::is_convertible_v<T, float>)
	FORCEINLINE explicit FloatStore(T v) noexcept;
	template<typename T1, typename T2, typename T3, typename T4>
		requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float> &&
	std::is_convertible_v<T3, float> &&std::is_convertible_v<T4, float>)
	FORCEINLINE FloatStore(T1 x, T2 y, T3 z, T4 w) noexcept;

	template<size_t N> requires(N <= 4)
	FORCEINLINE explicit operator FloatStore<N> &() noexcept;

	template<size_t N> requires(N <= 4)
	FORCEINLINE explicit operator const FloatStore<N> &() const noexcept;
	FORCEINLINE static const FloatStore<4> &identity() noexcept;
	FORCEINLINE static const FloatStore<4> &zero() noexcept;
};

template<>
struct FloatStore<33> : public DX::XMFLOAT3X3 {
public:
	using DX::XMFLOAT3X3::XMFLOAT3X3;
	FORCEINLINE static const FloatStore<33> &identity() noexcept;
};

template<>
struct FloatStore<43> : public DX::XMFLOAT4X3 {
public:
	using DX::XMFLOAT4X3::XMFLOAT4X3;
	FORCEINLINE static const FloatStore<43> &identity() noexcept;
};

template<>
struct FloatStore<44> : public DX::XMFLOAT4X4 {
public:
	using DX::XMFLOAT4X4::XMFLOAT4X4;
	FORCEINLINE static const FloatStore<44> &identity() noexcept;
};

class alignas(16) Scalar {
public:
	FORCEINLINE Scalar() = default;
	FORCEINLINE Scalar(const Scalar &) = default;
	FORCEINLINE Scalar &operator=(const Scalar &) = default;
	FORCEINLINE Scalar(DX::XMVECTOR vec) noexcept;
	FORCEINLINE explicit Scalar(float v) noexcept;
	FORCEINLINE operator float() const noexcept;
	FORCEINLINE DX::XMVECTOR *operator&() noexcept;
	FORCEINLINE const DX::XMVECTOR *operator&() const noexcept;
	FORCEINLINE operator DX::XMVECTOR() const noexcept;
	FORCEINLINE friend Scalar operator- (Scalar s) noexcept;
	FORCEINLINE friend Scalar operator+ (Scalar s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator- (Scalar s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator* (Scalar s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator/ (Scalar s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator+ (Scalar s1, float s2) noexcept;
	FORCEINLINE friend Scalar operator- (Scalar s1, float s2) noexcept;
	FORCEINLINE friend Scalar operator* (Scalar s1, float s2) noexcept;
	FORCEINLINE friend Scalar operator/ (Scalar s1, float s2) noexcept;
	FORCEINLINE friend Scalar operator+ (float s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator- (float s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator* (float s1, Scalar s2) noexcept;
	FORCEINLINE friend Scalar operator/ (float s1, Scalar s2) noexcept;
private:
	DX::XMVECTOR _vec;
};

template<typename T, bool EnableAssign, size_t...I>
struct Swizzle {
	constexpr static size_t indices[] = { I... };

	Swizzle() noexcept = default;
	template<typename = void> requires(EnableAssign)
	FORCEINLINE T &operator=(const T &other) noexcept;
	FORCEINLINE operator T() const noexcept;
public:
	template<size_t Idx>
	FORCEINLINE float &at() noexcept;

	template<size_t Idx>
	FORCEINLINE float at() const noexcept;
};

class alignas(16) BoolVector {
public:
	FORCEINLINE BoolVector(DX::FXMVECTOR vec) noexcept;
	FORCEINLINE operator DX::XMVECTOR() const;
private:
	DX::XMVECTOR _vec;
};

class Vector2 {
public:
	FORCEINLINE Vector2() noexcept = default;
	FORCEINLINE Vector2(float x, float y) noexcept;
	FORCEINLINE explicit Vector2(float val) noexcept;
	FORCEINLINE explicit Vector2(const float2 &f2) noexcept;
	FORCEINLINE explicit Vector2(const Vector3 &v3) noexcept;
	FORCEINLINE explicit Vector2(const Vector4 &v4) noexcept;
	FORCEINLINE Vector2 &operator=(const Vector2 &other) noexcept;
	FORCEINLINE float &operator[](size_t index) noexcept;
	FORCEINLINE float operator[](size_t index) const noexcept;
	FORCEINLINE explicit operator float2() const noexcept;
	FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) noexcept;
public:
	union {
		struct {
			float x;
			float y;
		};
#define VEC2
#include "VectorMember.ini"
#undef VEC2
	};
};

class alignas(16) Vector3 {
public:
	FORCEINLINE Vector3() = default;
	FORCEINLINE Vector3(const Vector3 &) noexcept = default;
	FORCEINLINE Vector3(const float2 &f2, float v) noexcept;
	FORCEINLINE explicit Vector3(const float3 &f3) noexcept;
	FORCEINLINE Vector3(DX::XMVECTOR vec) noexcept;
	FORCEINLINE Vector3(const Scalar &s) noexcept;
	FORCEINLINE Vector3(float x, float y, float z) noexcept;
	FORCEINLINE Vector3(const Vector4 &v4) noexcept;
	FORCEINLINE explicit Vector3(float val) noexcept;
	FORCEINLINE Vector3 &operator=(const Vector3 &other) noexcept;
	FORCEINLINE float &operator[](size_t index) noexcept;
	FORCEINLINE float operator[](size_t index) const noexcept;
	FORCEINLINE DX::XMVECTOR *operator&() noexcept;
	FORCEINLINE const DX::XMVECTOR *operator&() const noexcept;
	FORCEINLINE operator DX::XMVECTOR() const noexcept;
	FORCEINLINE explicit operator float2() const noexcept;
	FORCEINLINE explicit operator float3() const noexcept;
	FORCEINLINE static const Vector3 &identity() noexcept;
	FORCEINLINE static const Vector3 &zero() noexcept;
	FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector3 &v) noexcept;
public:
	union {
		DX::XMVECTOR vec;
#define VEC3
#include "VectorMember.ini"
#undef VEC3
	};
};

class alignas(16) Vector4 {
public:
	FORCEINLINE Vector4() = default;
	FORCEINLINE Vector4(const Vector4 &) noexcept = default;
	FORCEINLINE Vector4(const float3 &f3, float v) noexcept;
	FORCEINLINE explicit Vector4(const float4 &f4) noexcept;
	FORCEINLINE Vector4(DX::XMVECTOR vec) noexcept;
	FORCEINLINE Vector4(const Scalar &s) noexcept;
	FORCEINLINE Vector4(float x, float y, float z, float w) noexcept;
	FORCEINLINE explicit Vector4(float val) noexcept;
	FORCEINLINE Vector4(const Vector3 &v3, float w) noexcept;
	FORCEINLINE Vector4 &operator=(const Vector4 &other) noexcept;
	FORCEINLINE float &operator[](size_t index) noexcept;
	FORCEINLINE float operator[](size_t index) const noexcept;
	FORCEINLINE DX::XMVECTOR *operator&() noexcept;
	FORCEINLINE const DX::XMVECTOR *operator&() const noexcept;
	FORCEINLINE operator DX::XMVECTOR() const noexcept;
	FORCEINLINE explicit operator float2() const noexcept;
	FORCEINLINE explicit operator float3() const noexcept;
	FORCEINLINE explicit operator float4() const noexcept;
	FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector4 &v) noexcept;
public:
	union {
		DX::XMVECTOR vec;
#define VEC4
#include "VectorMember.ini"
#undef VEC4
	};
};

class alignas(16) Matrix3 {
public:
	FORCEINLINE Matrix3() noexcept = default;
	FORCEINLINE Matrix3(const Matrix3 &) noexcept = default;
	FORCEINLINE Matrix3(Matrix3 &&) noexcept = default;
	FORCEINLINE Matrix3 &operator=(const Matrix3 &) = default;
	FORCEINLINE Matrix3 &operator=(Matrix3 &&) = default;
	FORCEINLINE explicit Matrix3(const float3x3 &f3x3) noexcept;
	FORCEINLINE explicit Matrix3(const DX::XMMATRIX &mat) noexcept;
	FORCEINLINE explicit Matrix3(const Matrix4 &mat4) noexcept;
	FORCEINLINE Matrix3(const Vector3 &x, const Vector3 &y, const Vector3 &z) noexcept;
	FORCEINLINE void setX(const Vector3 &x) noexcept;
	FORCEINLINE void setY(const Vector3 &y) noexcept;
	FORCEINLINE void setZ(const Vector3 &z) noexcept;
	FORCEINLINE Vector3 getX() const noexcept;
	FORCEINLINE Vector3 getY() const noexcept;
	FORCEINLINE Vector3 getZ() const noexcept;
	FORCEINLINE explicit operator DX::XMMATRIX() const noexcept;
	FORCEINLINE explicit operator Matrix4() const noexcept;
	FORCEINLINE explicit operator float3x3() const noexcept;
	FORCEINLINE Vector3 &operator[](size_t index) noexcept;
	FORCEINLINE const Vector3 &operator[](size_t index) const noexcept;
	FORCEINLINE Matrix3 operator*(const Scalar &s) const noexcept;
	FORCEINLINE Vector3 operator*(const Vector3 &v) const noexcept;
	FORCEINLINE Matrix3 operator*(const Matrix3 &mat) const noexcept;
	static FORCEINLINE Matrix3 makeZRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix3 makeXRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix3 makeYRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix3 makeZRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix3 makeXRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix3 makeYRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix3 makeAxisRotationByDegree(const Vector3 &axis, float angle) noexcept;
	static FORCEINLINE Matrix3 makeAxisRotationByRadian(const Vector3 &axis, float radian) noexcept;
	static FORCEINLINE Matrix3 makeScale(float scale) noexcept;
	static FORCEINLINE Matrix3 makeScale(float sx, float sy, float sz) noexcept;
	static FORCEINLINE Matrix3 makeScale(const float3 &scale) noexcept;
	static FORCEINLINE Matrix3 makeScale(const Vector3 &scale) noexcept;
	static FORCEINLINE Matrix3 identity() noexcept;
private:
	Vector3 _mat[3];
};
 
class alignas(16) Matrix4 {
public:
	FORCEINLINE Matrix4() noexcept = default;
	FORCEINLINE Matrix4(const Matrix4 &) noexcept = default;
	FORCEINLINE Matrix4(Matrix4 &&) noexcept = default;
	FORCEINLINE Matrix4 &operator=(const Matrix4 &) noexcept = default;
	FORCEINLINE Matrix4 &operator=(Matrix4 &&) noexcept = default;
	FORCEINLINE Matrix4(const DX::XMMATRIX &mat) noexcept;
	FORCEINLINE explicit Matrix4(const float4x4 &f4x4) noexcept;
	FORCEINLINE explicit Matrix4(const Matrix3 &mat3) noexcept;
	FORCEINLINE explicit Matrix4(const float *data) noexcept;
	FORCEINLINE Matrix4(const Vector3 &x, const Vector3 &y, const Vector3 &z, const Vector3 &w) noexcept;
	FORCEINLINE Matrix4(const Vector4&x, const Vector4&y, const Vector4&z, const Vector4&w) noexcept;
	FORCEINLINE const Matrix3 &get3x3() const noexcept;
	FORCEINLINE void set3x3(const Matrix3 &xyz) noexcept;
	FORCEINLINE Vector4 getX() const noexcept;
	FORCEINLINE Vector4 getY() const noexcept;
	FORCEINLINE Vector4 getZ() const noexcept;
	FORCEINLINE Vector4 getW() const noexcept;
	FORCEINLINE void setX(Vector4 x) noexcept;
	FORCEINLINE void setY(Vector4 y) noexcept;
	FORCEINLINE void setZ(Vector4 z) noexcept;
	FORCEINLINE void setW(Vector4 w) noexcept;
	FORCEINLINE explicit operator DX::XMMATRIX() const noexcept;
	FORCEINLINE explicit operator float3x3() const noexcept;
	FORCEINLINE explicit operator float4x3() const noexcept;
	FORCEINLINE explicit operator float4x4() const noexcept;
	FORCEINLINE DX::XMMATRIX *operator&() noexcept;
	FORCEINLINE const DX::XMMATRIX *operator&() const noexcept;
	FORCEINLINE Vector4 operator*(const Vector3 &vec) const noexcept;
	FORCEINLINE Vector4 operator*(const Vector4 &vec) const noexcept;
	FORCEINLINE Matrix4 operator*(const Matrix4 &mat) const noexcept;
	static FORCEINLINE Matrix4 makeZRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix4 makeXRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix4 makeYRotationByRadian(float radian) noexcept;
	static FORCEINLINE Matrix4 makeZRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix4 makeXRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix4 makeYRotationByDegree(float angle) noexcept;
	static FORCEINLINE Matrix4 makeAxisRotationByDegree(const Vector3 &axis, float angle) noexcept;
	static FORCEINLINE Matrix4 makeAxisRotationByRadian(const Vector3 &axis, float radian) noexcept;
	static FORCEINLINE Matrix4 makeScale(float scale) noexcept;
	static FORCEINLINE Matrix4 makeScale(float sx, float sy, float sz) noexcept;
	static FORCEINLINE Matrix4 makeScale(const float3 &scale) noexcept;
	static FORCEINLINE Matrix4 makeScale(const Vector3 &scale) noexcept;
	static FORCEINLINE Matrix4 makeTranslation(const Vector3 &vec) noexcept;
	static FORCEINLINE Matrix4 makeTranslation(float ox, float oy, float oz) noexcept;
	static FORCEINLINE Matrix4 makeTranslation(float offset) noexcept;
	static FORCEINLINE Matrix4 identity() noexcept;
private:
	DX::XMMATRIX _mat;
};

class alignas(16) Quaternion {
public:
	FORCEINLINE Quaternion() noexcept;
	FORCEINLINE Quaternion(const Vector3 &axis, float radian) noexcept;
	FORCEINLINE Quaternion(const float3 &axis, float radian) noexcept;
	FORCEINLINE Quaternion(float pitch, float yaw, float roll) noexcept;
	FORCEINLINE Quaternion(float x, float y, float z, float w) noexcept;
	FORCEINLINE explicit Quaternion(const float4 &f4) noexcept;
	FORCEINLINE explicit Quaternion(const Matrix3 &matrix) noexcept;
	FORCEINLINE explicit Quaternion(DX::FXMVECTOR vec) noexcept;
	FORCEINLINE operator DX::XMVECTOR() const noexcept;
	FORCEINLINE explicit operator float4() const noexcept;
	FORCEINLINE explicit operator Matrix3() const noexcept;
	FORCEINLINE explicit operator Matrix4() const noexcept;
	FORCEINLINE Quaternion operator~() const noexcept;
	FORCEINLINE Quaternion operator*(const Quaternion &rhs) const noexcept;
	FORCEINLINE Vector3 operator*(const Vector3 &rhs) const noexcept;
	FORCEINLINE Quaternion &operator=(const Quaternion &rhs) noexcept;
	FORCEINLINE Quaternion &operator*=(const Quaternion &rhs) noexcept;
	FORCEINLINE DX::XMVECTOR *operator&() noexcept;
	friend BoolVector operator==(const Quaternion &, const Quaternion &) noexcept;
	friend BoolVector operator!=(const Quaternion &, const Quaternion &) noexcept;
	friend Quaternion normalize(const Quaternion &q) noexcept;
	friend Quaternion inverse(const Quaternion &q) noexcept;
	friend Quaternion slerp(const Quaternion &lhs, const Quaternion &rhs, float t) noexcept;
	friend Quaternion lerp(const Quaternion &lhs, const Quaternion &rhs, float t) noexcept;
	friend Quaternion conjugate(const Quaternion &q) noexcept;
	friend std::ostream &operator<<(std::ostream &os, const Quaternion &q) noexcept;
public:
	union {
		DX::XMVECTOR _vec;
#define VEC4
#include "VectorMember.ini"
#undef VEC4
	};
};

class BoundingBox;
class BoundingSphere;
class BoundingFrustum;

class BoundingBox {
public:
	friend class BoundingFrustum;
	static constexpr size_t kCornerCount = 8;
	FORCEINLINE BoundingBox() = default;
	FORCEINLINE BoundingBox(const Vector3 &min, const Vector3 &max) noexcept;
	FORCEINLINE BoundingBox(const BoundingBox &) noexcept = default;
	FORCEINLINE BoundingBox(const DX::BoundingBox &) noexcept;
	FORCEINLINE BoundingBox(const BoundingBox &lhs, const BoundingBox &rhs) noexcept;
	FORCEINLINE explicit BoundingBox(const BoundingSphere &boundingSphere) noexcept;
	FORCEINLINE explicit BoundingBox(const BoundingFrustum &boundingFrustum) noexcept;
	FORCEINLINE BoundingBox &operator=(const BoundingBox &) noexcept = default;
	FORCEINLINE BoundingBox(BoundingBox &&) noexcept = default;
	FORCEINLINE BoundingBox &operator=(BoundingBox &&) noexcept = default;
	FORCEINLINE BoundingBox &operator=(const DX::BoundingBox &) noexcept;
	FORCEINLINE BoundingBox transform(const Matrix4 &trans) const noexcept;
	FORCEINLINE BoundingBox transform(float scale, const Quaternion &rotate, const Vector3 &translation) const noexcept;
	FORCEINLINE DX::ContainmentType contains(const BoundingBox &other) const noexcept;
	FORCEINLINE std::array<float3, kCornerCount> getCorners() const noexcept;
	FORCEINLINE void getMinMax(Vector3 &min, Vector3 &max) const noexcept;
	FORCEINLINE std::pair<Vector3, Vector3> getMinMax() const noexcept;
	FORCEINLINE const float3 &getCenter() const noexcept;
	FORCEINLINE DX::BoundingBox &baseCast() noexcept;
	FORCEINLINE const DX::BoundingBox &baseCast() const noexcept;
	FORCEINLINE static BoundingBox createFromCenter(const float3 &center, const float3 &extents) noexcept;
	FORCEINLINE static BoundingBox createFromPoints(size_t count, const float3 *points, size_t stride) noexcept;
	FORCEINLINE static BoundingBox createMerged(const BoundingBox &b1, const BoundingBox &b2) noexcept;
private:
	DX::BoundingBox _boundingBox;
};


class BoundingSphere {
public:
	FORCEINLINE BoundingSphere() noexcept = default;
	FORCEINLINE BoundingSphere(BoundingSphere &&) noexcept = default;
	FORCEINLINE BoundingSphere &operator=(const BoundingSphere &) noexcept = default;
	FORCEINLINE BoundingSphere &operator=(BoundingSphere &&) noexcept = default;
	FORCEINLINE explicit BoundingSphere(const BoundingBox &boundingBox) noexcept;
	FORCEINLINE explicit BoundingSphere(const DX::BoundingBox &boundingBox) noexcept;
	FORCEINLINE explicit BoundingSphere(const DX::BoundingSphere &boundingSphere) noexcept;
	FORCEINLINE explicit BoundingSphere(const BoundingFrustum &fr) noexcept;
	FORCEINLINE BoundingSphere(const BoundingSphere &lhs, BoundingSphere &rhs) noexcept;
	FORCEINLINE const float3 &getCenter() const noexcept;
	FORCEINLINE const float &getRadius() const noexcept;
	FORCEINLINE void setCenter(const float3 &offset) noexcept;
	FORCEINLINE void setCenter(const Vector3 &offset) noexcept;
	FORCEINLINE void setRadius(float radius) noexcept;
	FORCEINLINE DX::BoundingSphere &baseCast() noexcept;
	FORCEINLINE const DX::BoundingSphere &baseCast() const noexcept;
private:
	DX::BoundingSphere _boundingSphere;
};

class BoundingFrustum {
public:
	static constexpr size_t kCornerCount = 8;
	FORCEINLINE BoundingFrustum() noexcept = default;
	FORCEINLINE BoundingFrustum(const BoundingFrustum &) noexcept = default;
	FORCEINLINE BoundingFrustum &operator=(const BoundingFrustum &) noexcept = default;
	FORCEINLINE BoundingFrustum(BoundingFrustum &&) noexcept = default;
	FORCEINLINE BoundingFrustum &operator=(BoundingFrustum &&) noexcept = default;
	FORCEINLINE BoundingFrustum(const float3 &origin, const float4 &orientation, 
		float rightSlope, float leftSlope, 
		float topSlope, float bottomSlope, 
		float near, float far
	) noexcept;
	FORCEINLINE BoundingFrustum(const Matrix4 &projection) noexcept;
	FORCEINLINE BoundingFrustum transform(const Matrix4 &trans) const noexcept;
	FORCEINLINE BoundingFrustum transform(float scale, const Quaternion &rotate, const Vector3 &translation) const noexcept;
	FORCEINLINE DX::BoundingFrustum &baseCast() noexcept;
	FORCEINLINE const DX::BoundingFrustum &baseCast() const noexcept;
	FORCEINLINE std::array<float3, kCornerCount> getCorners() const noexcept;
	FORCEINLINE void getPlanes(Vector4 &nearPlane, Vector4 &farPlane, 
		Vector4 &rightPlane, Vector4 &leftPlane, 
		Vector4 &topPlane, Vector4 &bottomPlane
	) const noexcept;
	FORCEINLINE DX::ContainmentType contains(_In_ const BoundingBox &box) const noexcept;
private:
	DX::BoundingFrustum _boundingFrustum;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/// FloatStore<2>
#include "Math/implement/FloatStore2.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// FloatStore<3>
#include "Math/implement/FloatStore3.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// FloatStore<4>
#include "Math/implement/FloatStore4.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// FloatStoreMatrix
#include "Math/implement/FloatStoreMatrix.inc"
/// Swizzle
#include "Math/implement/Swizzle.inc"

/////////////////////////////////////////////////////////////////////////////////////////////////
/// Scalar
#include "Math/implement/Scalar.inc"
////////////////////////////////////////////////////////////////////////////////////////////////////
/// Vector2
#include "Math/implement/Vector2.inc"
/// Vectror3
#include "Math/implement/Vector3.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// Vectror4
#include "Math/implement/Vector4.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// BoolVector
#if 1

FORCEINLINE BoolVector::BoolVector(DX::FXMVECTOR vec) noexcept : _vec(vec) {
}
FORCEINLINE BoolVector::operator DX::XMVECTOR() const {
	return _vec;
}

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////
/// Matrix3x3
#include "Math/implement/Matrix3.inc"
/////////////////////////////////////////////////////////////////////////////////////////////////
/// Matrix4x4
#include "Math/implement/Matrix4.inc"
/// Quaternion
#include "Math/implement/Quaternion.inc"
/// BoundingBox
#include "Math/implement/BoundingBox.inc"
/// BoundingFrustum 
#include "Math/implement/BoundingFrustum.inc"
/// BoundingSphere
#include "Math/implement/BoudingSphere.inc"
}


static_assert(sizeof(Math::float2) == sizeof(float)*2);
static_assert(sizeof(Math::float3) == sizeof(float)*3);
static_assert(sizeof(Math::float4) == sizeof(float)*4);

