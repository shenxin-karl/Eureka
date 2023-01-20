#pragma once
#include <algorithm>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <cmath>
#include <ostream>

namespace Eureka {

#define FORCEINLINE __forceinline

class float2;
class float3;
class float4;
class Vector2;
class Vector3;
class Vector4;
class Matrix;
class Plane;
class Quaternion;
class BoundingBox;
class BoundingSphere;
class BoundingFrustum;

#pragma region Float2Declared

	class float2 : public DirectX::XMFLOAT2 {
	public:
		float2(const float2 &) = default;
		float2(float2 &&) = default;
		float2 &operator=(const float2 &) = default;
		float2 &operator=(float2 &&) = default;
		~float2() = default;
		FORCEINLINE float2(float v = 0.f);
		FORCEINLINE float2(float x, float y);
		FORCEINLINE explicit float2(const Vector2 &v2);
		FORCEINLINE explicit float2(const Vector3 &v3);
		FORCEINLINE explicit float2(const Vector4 &v4);
		FORCEINLINE Vector2 load() const noexcept;
		FORCEINLINE auto operator[](size_t index) -> float &;
		FORCEINLINE auto operator[](size_t index) const -> const float &;
		FORCEINLINE friend bool operator==(const float2 &lhs, const float2 &rhs);
		FORCEINLINE friend bool operator!=(const float2 &lhs, const float2 &rhs);
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const float2 &f2) noexcept;
		static const float2 Zero;
		static const float2 One;
		static const float2 UnitX;
		static const float2 UnitY;
	};

#pragma endregion

#pragma region Float3Declared

	class float3 : public DirectX::XMFLOAT3 {
	public:
		float3(const float3 &) = default;
		float3(float3 &&) = default;
		float3 &operator=(const float3 &) = default;
		float3 &operator=(float3 &&) = default;
		~float3() = default;
		FORCEINLINE float3(float v = 0.f);
		FORCEINLINE float3(float x, float y, float z);
		FORCEINLINE float3(const float2 &f2, float z);
		FORCEINLINE explicit float3(const Vector3 &v3);
		FORCEINLINE explicit float3(const Vector4 &v4);
		FORCEINLINE Vector3 load() const noexcept;
		FORCEINLINE auto operator[](size_t index) -> float &;
		FORCEINLINE auto operator[](size_t index) const -> const float &;
		FORCEINLINE friend bool operator==(const float3 &lhs, const float3 &rhs);
		FORCEINLINE friend bool operator!=(const float3 &lhs, const float3 &rhs);
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const float3 &f3) noexcept;
		static const float3 Zero;
		static const float3 One;
		static const float3 UnitX;
		static const float3 UnitY;
		static const float3 UnitZ;
		static const float3 Up;
		static const float3 Down;
		static const float3 Right;
		static const float3 Left;
		static const float3 Forward;
		static const float3 Backward;
	};

#pragma endregion

#pragma region Float4Declared

	class float4 : public DirectX::XMFLOAT4 {
	public:
		float4(const float4 &) = default;
		float4(float4 &&) = default;
		float4 &operator=(const float4 &) = default;
		float4 &operator=(float4 &&) = default;
		~float4() = default;
		FORCEINLINE float4(float v = 0.f);
		FORCEINLINE float4(float x, float y, float z, float w);
		FORCEINLINE float4(const float2 &f2, float z, float w);
		FORCEINLINE float4(const float3 &f3, float w);
		FORCEINLINE Vector4 load() const noexcept;
		FORCEINLINE auto operator[](size_t index) -> float &;
		FORCEINLINE auto operator[](size_t index) const -> const float &;
		FORCEINLINE friend bool operator==(const float4 &lhs, const float4 &rhs);
		FORCEINLINE friend bool operator!=(const float4 &lhs, const float4 &rhs);
		static const float4 Zero;
		static const float4 One;
		static const float4 UnitX;
		static const float4 UnitY;
		static const float4 UnitZ;
		static const float4 UnitW;
	};

#pragma endregion

#pragma region ColorDeclared

	class Color {
	public:
		Color(const Color &) = default;
		Color &operator=(const Color &) = default;

		FORCEINLINE Color();
		FORCEINLINE Color(float r, float g, float b, float a = 1.f);
		FORCEINLINE Color(const float3 &f3, float a = 1.f);
		FORCEINLINE Color(const float4 &f4);
		FORCEINLINE explicit Color(const DirectX::XMVECTORF32 &c);

		// Comparison operators
		FORCEINLINE bool operator == (const Color &c) const noexcept;
		FORCEINLINE bool operator != (const Color &c) const noexcept;

		FORCEINLINE Color &operator= (const DirectX::XMVECTORF32 &F) noexcept { r = F.f[0]; g = F.f[1]; b = F.f[2]; a = F.f[3]; return *this; }
		FORCEINLINE Color &operator+= (const Color &c) noexcept;
		FORCEINLINE Color &operator-= (const Color &c) noexcept;
		FORCEINLINE Color &operator*= (const Color &c) noexcept;
		FORCEINLINE Color &operator*= (float S) noexcept;
		FORCEINLINE Color &operator/= (const Color &c) noexcept;

		// Unary operators
		FORCEINLINE Color operator+ () const noexcept { return *this; }
		FORCEINLINE Color operator- () const noexcept;

		FORCEINLINE float3 toFloat3() const noexcept;
		FORCEINLINE float4 toFloat4() const noexcept;

		// Binary operators
		FORCEINLINE friend Color operator+ (const Color &C1, const Color &C2)	noexcept;
		FORCEINLINE friend Color operator- (const Color &C1, const Color &C2)	noexcept;
		FORCEINLINE friend Color operator* (const Color &C1, const Color &C2)	noexcept;
		FORCEINLINE friend Color operator* (const Color &C, float S)			noexcept;
		FORCEINLINE friend Color operator/ (const Color &C1, const Color &C2)	noexcept;
		FORCEINLINE friend Color operator* (float S, const Color &C)			noexcept;

		FORCEINLINE friend Color negate(const Color &inputColor);
		FORCEINLINE friend Color saturate(const Color &inputColor);
		FORCEINLINE friend Color adjustSaturation(const Color &inputColor, float sat);
		FORCEINLINE friend Color adjustContrast(const Color &inputColor, float contrast);
		FORCEINLINE friend Color lerp(const Color &lhs, const Color &rhs, float t);
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Color &c) noexcept;
	public:
		union {
			struct {
				float r, g, b, a;
			};
			float4 f4;
		};
	};

#pragma endregion

#pragma region Float4x4Declared

	class float4x4 : public DirectX::XMFLOAT4X4 {
	public:
		float4x4();
		float4x4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33) noexcept;
		float4x4(const float3 &r0, const float3 &r1, const float3 &r2) noexcept;
		float4x4(const float4 &r0, const float4 &r1, const float4 &r2, const float4 &r3) noexcept;
		float4x4(const DirectX::XMFLOAT4X4 &M) noexcept;
		float4x4(const DirectX::XMFLOAT3X3 &M) noexcept;
		float4x4(const DirectX::XMFLOAT4X3 &M) noexcept;
		explicit float4x4(_In_reads_(16) const float *pArray) noexcept;
		friend bool operator == (const float4x4 &lhs, const float4x4 &rhs) noexcept;
		friend bool operator != (const float4x4 &lhs, const float4x4 &rhs) noexcept;
		float3 getUp() const;
		float3 getDown() const;
		float3 getRight() const;
		float3 getLeft() const;
		float3 getForward() const;
		float3 getBackward() const;
		float3 getTranslation() const;
		static const float4x4 Identity;
	};

#pragma endregion

#pragma region SwizzleDeclared

	template<typename T, bool EnableAssign, size_t...I>
	struct Swizzle {
		constexpr static size_t indices[] = { I... };

		Swizzle() noexcept = default;
		Swizzle(const Swizzle &) = delete;
		template<typename = void> requires(EnableAssign)
		FORCEINLINE T &operator=(const T &other) noexcept;
		FORCEINLINE operator T() const noexcept;
		FORCEINLINE decltype(auto) store() const noexcept {
			return (operator T()).store();
		}
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Swizzle &sz) noexcept {
			os << (sz.operator T());
			return os;
		}
	private:
		template<size_t Idx>
		FORCEINLINE float &at() noexcept;

		template<size_t Idx>
		FORCEINLINE float at() const noexcept;
	};

#pragma endregion 

#pragma region Vector2Declared

	class Vector2 {
	public:
		FORCEINLINE Vector2() noexcept = default;
		FORCEINLINE Vector2(float x, float y) noexcept;
		FORCEINLINE Vector2(const Vector2 &other) noexcept;
		FORCEINLINE explicit Vector2(float val) noexcept;
		FORCEINLINE explicit Vector2(const float2 &f2) noexcept;
		FORCEINLINE explicit Vector2(const Vector3 &v3) noexcept;
		FORCEINLINE explicit Vector2(const Vector4 &v4) noexcept;
		FORCEINLINE Vector2 &operator=(const Vector2 &other) noexcept;
		FORCEINLINE float2   store() const noexcept;
		FORCEINLINE float   &operator[](size_t index) noexcept;
		FORCEINLINE float    operator[](size_t index) const noexcept;

		FORCEINLINE Vector2 &operator+=(const Vector2 &rhs) noexcept;
		FORCEINLINE Vector2 &operator-=(const Vector2 &rhs) noexcept;
		FORCEINLINE Vector2 &operator*=(const Vector2 &rhs) noexcept;
		FORCEINLINE Vector2 &operator/=(const Vector2 &rhs) noexcept;

		FORCEINLINE Vector2 &operator+=(float rhs) noexcept;
		FORCEINLINE Vector2 &operator-=(float rhs) noexcept;
		FORCEINLINE Vector2 &operator*=(float rhs) noexcept;
		FORCEINLINE Vector2 &operator/=(float rhs) noexcept;

		FORCEINLINE Vector2 operator+() const noexcept;
		FORCEINLINE Vector2 operator-() const noexcept;

		FORCEINLINE friend Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs) noexcept;

		FORCEINLINE friend Vector2 operator+(const Vector2 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector2 operator-(const Vector2 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector2 operator*(const Vector2 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector2 operator/(const Vector2 &lhs, float rhs) noexcept;

		FORCEINLINE friend Vector2 operator+(float lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator-(float lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator*(float lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 operator/(float lhs, const Vector2 &rhs) noexcept;

		FORCEINLINE friend Vector2 sqrt(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 inverse(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 inverseSqrt(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 floor(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 ceil(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 round(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 abs(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 exp(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 pow(const Vector2 &self, float e) noexcept;
		FORCEINLINE friend Vector2 pow(const Vector2 &self, const Vector2 &e) noexcept;
		FORCEINLINE friend Vector2 log(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 sin(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 cos(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 tan(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 asin(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 acos(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 atan(const Vector2 &self) noexcept;
		FORCEINLINE friend Vector2 lerp(const Vector2 &lhs, const Vector2 &rhs, float t) noexcept;
		FORCEINLINE friend Vector2 lerp(const Vector2 &lhs, const Vector2 &rhs, const Vector2 &t) noexcept;
		FORCEINLINE friend Vector2 min(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 max(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend Vector2 clamp(const Vector2 &v, const Vector2 &a, const Vector2 &b) noexcept;
		FORCEINLINE friend Vector2 normalize(const Vector2 &self) noexcept;
		FORCEINLINE friend float   dot(const Vector2 &lhs, const Vector2 &rhs) noexcept;
		FORCEINLINE friend float   lengthSquare(const Vector2 &self) noexcept;
		FORCEINLINE friend float   length(const Vector2 &self) noexcept;
		FORCEINLINE friend float   inverseLength(const Vector2 &self) noexcept;
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector2 &v2) noexcept;
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
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

#pragma endregion

#pragma region Vector3Declared

	class alignas(16) Vector3 {
	public:
		FORCEINLINE Vector3() noexcept = default;
		FORCEINLINE Vector3(float x, float y, float z) noexcept;
		FORCEINLINE Vector3(const float2 &f2, float z) noexcept;
		FORCEINLINE Vector3(const Vector2 &v2, float z) noexcept;
		FORCEINLINE Vector3(const Vector3 &v3) noexcept;
		FORCEINLINE explicit Vector3(float val) noexcept;
		FORCEINLINE explicit Vector3(const Vector4 &v4) noexcept;
		FORCEINLINE Vector3 &operator=(const Vector3 &other) noexcept;
		FORCEINLINE float3   store() const noexcept;
		FORCEINLINE float   &operator[](size_t index) noexcept;
		FORCEINLINE float    operator[](size_t index) const noexcept;

		FORCEINLINE Vector3 &operator+=(const Vector3 &rhs) noexcept;
		FORCEINLINE Vector3 &operator-=(const Vector3 &rhs) noexcept;
		FORCEINLINE Vector3 &operator*=(const Vector3 &rhs) noexcept;
		FORCEINLINE Vector3 &operator/=(const Vector3 &rhs) noexcept;

		FORCEINLINE Vector3 &operator+=(float rhs) noexcept;
		FORCEINLINE Vector3 &operator-=(float rhs) noexcept;
		FORCEINLINE Vector3 &operator*=(float rhs) noexcept;
		FORCEINLINE Vector3 &operator/=(float rhs) noexcept;

		FORCEINLINE Vector3 operator+() const noexcept;
		FORCEINLINE Vector3 operator-() const noexcept;

		FORCEINLINE friend Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs) noexcept;

		FORCEINLINE friend Vector3 operator+(const Vector3 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector3 operator-(const Vector3 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector3 operator*(const Vector3 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector3 operator/(const Vector3 &lhs, float rhs) noexcept;

		FORCEINLINE friend Vector3 operator+(float lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator-(float lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator*(float lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 operator/(float lhs, const Vector3 &rhs) noexcept;

		FORCEINLINE friend Vector3 sqrt(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 inverse(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 inverseSqrt(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 floor(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 ceil(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 round(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 abs(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 exp(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 pow(const Vector3 &self, float e) noexcept;
		FORCEINLINE friend Vector3 pow(const Vector3 &self, const Vector3 &e) noexcept;
		FORCEINLINE friend Vector3 log(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 sin(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 cos(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 tan(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 asin(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 acos(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 atan(const Vector3 &self) noexcept;
		FORCEINLINE friend Vector3 lerp(const Vector3 &lhs, const Vector3 &rhs, float t) noexcept;
		FORCEINLINE friend Vector3 lerp(const Vector3 &lhs, const Vector3 &rhs, const Vector3 &t) noexcept;
		FORCEINLINE friend Vector3 min(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 max(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend Vector3 clamp(const Vector3 &v, const Vector3 &a, const Vector3 &b) noexcept;
		FORCEINLINE friend Vector3 normalize(const Vector3 &self) noexcept;
		FORCEINLINE friend float   dot(const Vector3 &lhs, const Vector3 &rhs) noexcept;
		FORCEINLINE friend float   lengthSquare(const Vector3 &self) noexcept;
		FORCEINLINE friend float   length(const Vector3 &self) noexcept;
		FORCEINLINE friend float   inverseLength(const Vector3 &self) noexcept;
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector3 &v3) noexcept;
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Forward;
		static const Vector3 Backward;
	public:
		union {
			struct {
				float x;
				float y;
				float z;
			};
			DirectX::XMVECTOR vec;

			#define VEC3
			#include "VectorMember.ini"
			#undef VEC3
		};
	};

#pragma endregion

#pragma region Vector4Declared

	class alignas(16) Vector4 {
	public:
		FORCEINLINE Vector4() noexcept = default;
		FORCEINLINE Vector4(float x, float y, float z, float w) noexcept;
		FORCEINLINE Vector4(const float2 &f2, float z, float w) noexcept;
		FORCEINLINE Vector4(const Vector2 &v2, float z, float w) noexcept;
		FORCEINLINE Vector4(const float3 &f3, float w) noexcept;
		FORCEINLINE Vector4(const Vector3 &v3, float w) noexcept;
		FORCEINLINE explicit Vector4(float val) noexcept;
		FORCEINLINE Vector4(const Vector4 &v4) noexcept;
		FORCEINLINE Vector4 &operator=(const Vector4 &other) noexcept;
		FORCEINLINE float4   store() const noexcept;
		FORCEINLINE float   &operator[](size_t index) noexcept;
		FORCEINLINE float    operator[](size_t index) const noexcept;

		FORCEINLINE Vector4 &operator+=(const Vector4 &rhs) noexcept;
		FORCEINLINE Vector4 &operator-=(const Vector4 &rhs) noexcept;
		FORCEINLINE Vector4 &operator*=(const Vector4 &rhs) noexcept;
		FORCEINLINE Vector4 &operator/=(const Vector4 &rhs) noexcept;

		FORCEINLINE Vector4 &operator+=(float rhs) noexcept;
		FORCEINLINE Vector4 &operator-=(float rhs) noexcept;
		FORCEINLINE Vector4 &operator*=(float rhs) noexcept;
		FORCEINLINE Vector4 &operator/=(float rhs) noexcept;

		FORCEINLINE Vector4 operator+() const noexcept;
		FORCEINLINE Vector4 operator-() const noexcept;

		FORCEINLINE friend Vector4 operator+(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator-(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator*(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator/(const Vector4 &lhs, const Vector4 &rhs) noexcept;

		FORCEINLINE friend Vector4 operator+(const Vector4 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector4 operator-(const Vector4 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector4 operator*(const Vector4 &lhs, float rhs) noexcept;
		FORCEINLINE friend Vector4 operator/(const Vector4 &lhs, float rhs) noexcept;

		FORCEINLINE friend Vector4 operator+(float lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator-(float lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator*(float lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 operator/(float lhs, const Vector4 &rhs) noexcept;

		FORCEINLINE friend Vector4 sqrt(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 inverse(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 inverseSqrt(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 floor(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 ceil(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 round(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 abs(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 exp(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 pow(const Vector4 &self, float e) noexcept;
		FORCEINLINE friend Vector4 pow(const Vector4 &self, const Vector4 &e) noexcept;
		FORCEINLINE friend Vector4 log(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 sin(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 cos(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 tan(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 asin(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 acos(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 atan(const Vector4 &self) noexcept;
		FORCEINLINE friend Vector4 lerp(const Vector4 &lhs, const Vector4 &rhs, float t) noexcept;
		FORCEINLINE friend Vector4 lerp(const Vector4 &lhs, const Vector4 &rhs, const Vector4 &t) noexcept;
		FORCEINLINE friend Vector4 min(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 max(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend Vector4 clamp(const Vector4 &v, const Vector4 &a, const Vector4 &b) noexcept;
		FORCEINLINE friend Vector4 normalize(const Vector4 &self) noexcept;
		FORCEINLINE friend float   dot(const Vector4 &lhs, const Vector4 &rhs) noexcept;
		FORCEINLINE friend float   lengthSquare(const Vector4 &self) noexcept;
		FORCEINLINE friend float   length(const Vector4 &self) noexcept;
		FORCEINLINE friend float   inverseLength(const Vector4 &self) noexcept;
		FORCEINLINE friend std::ostream &operator<<(std::ostream &os, const Vector4 &v4) noexcept;
		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 UnitX;
		static const Vector4 UnitY;
		static const Vector4 UnitZ;
		static const Vector4 UnitW;
	public:
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			DirectX::XMVECTOR vec;

			#define VEC4
			#include "VectorMember.ini"
			#undef VEC4
		};
	};

#pragma endregion

#pragma region QuaternionDeclared

	class Quaternion {
	public:
		Quaternion(const Quaternion &) = default;
		Quaternion &operator=(const Quaternion &) = default;
		Quaternion(Quaternion &&) = default;
		Quaternion &operator=(Quaternion &&) = default;

		FORCEINLINE Quaternion() noexcept;
		FORCEINLINE Quaternion(float ix, float iy, float iz, float iw) noexcept;
		FORCEINLINE Quaternion(const float4 &f4) noexcept;

		FORCEINLINE float4 store() const noexcept;

		// Comparison operators
		FORCEINLINE bool operator == (const Quaternion &q) const noexcept;
		FORCEINLINE bool operator != (const Quaternion &q) const noexcept;

		// Assignment operators
		FORCEINLINE Quaternion &operator+= (const Quaternion &q) noexcept;
		FORCEINLINE Quaternion &operator-= (const Quaternion &q) noexcept;
		FORCEINLINE Quaternion &operator*= (const Quaternion &q) noexcept;
		FORCEINLINE Quaternion &operator*= (float S) noexcept;
		FORCEINLINE Quaternion &operator/= (const Quaternion &q) noexcept;

		// Unary operators
		FORCEINLINE Quaternion operator+ () const  noexcept { return *this; }
		FORCEINLINE Quaternion operator- () const noexcept;

		FORCEINLINE friend float length(const Quaternion &self) noexcept;
		FORCEINLINE friend float lengthSquare(const Quaternion &self) noexcept;
		FORCEINLINE friend float dot(const Quaternion &lhs, const Quaternion &rhs) noexcept;
		FORCEINLINE friend Quaternion lerp(const Quaternion &q1, const Quaternion &q2, float t) noexcept;
		FORCEINLINE friend Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) noexcept;
		FORCEINLINE friend Quaternion normalize(const Quaternion &self) noexcept;
		FORCEINLINE friend Quaternion conjugate(const Quaternion &self) noexcept;
		FORCEINLINE friend Quaternion inverse(const Quaternion &self) noexcept;
		FORCEINLINE friend Vector3    toEuler(const Quaternion &self) noexcept;

		FORCEINLINE static Quaternion CreateFromAxisAngle(const Vector3 &axis, float angle) noexcept;
		FORCEINLINE static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;
		FORCEINLINE static Quaternion CreateFromYawPitchRoll(const Vector3 &angles) noexcept;
		FORCEINLINE static Quaternion CreateFromRotationMatrix(const Matrix &M) noexcept;
		FORCEINLINE static float Angle(const Quaternion &q1, const Quaternion &q2) noexcept;

		static const Quaternion Identity;
	public:
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			DirectX::XMVECTOR vec;
		};
	};

#pragma endregion

#pragma region MatrixDeclared

	class alignas(16) Matrix {
	public:
		FORCEINLINE Matrix(const Matrix &) = default;
		FORCEINLINE Matrix &operator=(const Matrix &) = default;
		FORCEINLINE Matrix(Matrix &&) = default;
		FORCEINLINE Matrix &operator=(Matrix &&) = default;

		FORCEINLINE Matrix();
		FORCEINLINE Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		FORCEINLINE Matrix(const Vector3 &r0, const Vector3 &r1, const Vector3 &r2);
		FORCEINLINE Matrix(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3);
		FORCEINLINE explicit Matrix(_In_reads_(16) const float *pArray) noexcept;
		FORCEINLINE bool operator == (const Matrix &M) const noexcept;
		FORCEINLINE bool operator != (const Matrix &M) const noexcept;
		FORCEINLINE Matrix &operator+= (const Matrix &M) noexcept;
		FORCEINLINE Matrix &operator-= (const Matrix &M) noexcept;
		FORCEINLINE Matrix &operator*= (const Matrix &M) noexcept;
		FORCEINLINE Matrix &operator/= (const Matrix &M) noexcept;
		FORCEINLINE Matrix &operator*= (float S) noexcept;
		FORCEINLINE Matrix &operator/= (float S) noexcept;
		FORCEINLINE Matrix operator+ () const noexcept;
		FORCEINLINE Matrix operator- () const noexcept;
		FORCEINLINE friend bool    decompose(const Matrix &m, Vector3 &scale, Quaternion &rotation, Vector3 &translation) noexcept;
		FORCEINLINE friend Matrix  transpose(const Matrix &m);
		FORCEINLINE friend Matrix  inverse(const Matrix &m);
		FORCEINLINE friend float   determinant(const Matrix &m);
		FORCEINLINE friend Vector3 toEuler(const Matrix &m);
		FORCEINLINE static Matrix CreateBillboard(
			const Vector3 &objectPos, 
			const Vector3 &cameraPos,
			const Vector3 &cameraUp,
			_In_opt_ const Vector3 *cameraForward = nullptr) noexcept;
		FORCEINLINE static Matrix CreateConstrainedBillboard(
			const Vector3 &objectPos,
			const Vector3 &cameraPosition,
			const Vector3 &rotateAxis,
			_In_opt_ const Vector3 *cameraForward = nullptr,
			_In_opt_ const Vector3 *objectForward = nullptr) noexcept;

		FORCEINLINE static Matrix CreateTranslation(const Vector3 &position) noexcept;
		FORCEINLINE static Matrix CreateTranslation(float x, float y, float z) noexcept;

		FORCEINLINE static Matrix CreateScale(const Vector3 &scales) noexcept;
		FORCEINLINE static Matrix CreateScale(float xs, float ys, float zs) noexcept;
		FORCEINLINE static Matrix CreateScale(float scale) noexcept;

		FORCEINLINE static Matrix CreateRotationX(float radians) noexcept;
		FORCEINLINE static Matrix CreateRotationY(float radians) noexcept;
		FORCEINLINE static Matrix CreateRotationZ(float radians) noexcept;

		FORCEINLINE static Matrix CreateFromAxisAngle(const Vector3 &axis, float angle) noexcept;
		FORCEINLINE static Matrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane) noexcept;
		FORCEINLINE static Matrix CreatePerspective(float width, float height, float nearPlane, float farPlane) noexcept;
		FORCEINLINE static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane) noexcept;
		FORCEINLINE static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept;
		FORCEINLINE static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane) noexcept;

		FORCEINLINE static Matrix CreateLookAt(const Vector3 &position, const Vector3 &target, const Vector3 &up) noexcept;
		FORCEINLINE static Matrix CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up) noexcept;

		FORCEINLINE static Matrix CreateFromQuaternion(const Quaternion &quat) noexcept;

		FORCEINLINE static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;
		FORCEINLINE static Matrix CreateFromYawPitchRoll(const Vector3 &angles) noexcept;

		//FORCEINLINE static Matrix CreateShadow(const Vector3 &lightDir, const Plane &plane) noexcept;
		//FORCEINLINE static Matrix CreateReflection(const Plane &plane) noexcept;

		FORCEINLINE static Matrix Transform(const Matrix &M, const Quaternion &rotation) noexcept;

		FORCEINLINE friend Matrix lerp(const Matrix &M1, const Matrix &M2, float t) noexcept;
		// Binary operators
		FORCEINLINE friend Matrix operator+ (const Matrix &M1, const Matrix &M2) noexcept;
		FORCEINLINE friend Matrix operator- (const Matrix &M1, const Matrix &M2) noexcept;
		FORCEINLINE friend Matrix operator* (const Matrix &M1, const Matrix &M2) noexcept;
		FORCEINLINE friend Matrix operator/ (const Matrix &M1, const Matrix &M2) noexcept;
		// Element-wise divide
		FORCEINLINE friend Matrix operator/ (const Matrix &M, float S) noexcept;
		FORCEINLINE friend Matrix operator* (const Matrix &M, float S) noexcept;
		FORCEINLINE friend Matrix operator* (float S, const Matrix &M) noexcept;

		FORCEINLINE friend Vector4 operator*(const Matrix &m, const Vector4 &v4) noexcept;

		static const Matrix Identity;
	public:
		DirectX::XMMATRIX mat;
	};

#pragma endregion

#pragma region BoundingBoxDeclared

	class BoundingBox : public DirectX::BoundingBox {
	public:
		using Base = DirectX::BoundingBox;
		static constexpr size_t kCornerCount = 8;
		// compiler generate code
		FORCEINLINE BoundingBox() = default;
		FORCEINLINE BoundingBox(const BoundingBox &) noexcept = default;
		FORCEINLINE BoundingBox(BoundingBox &&) noexcept = default;
		FORCEINLINE BoundingBox &operator=(const BoundingBox &) noexcept = default;
		FORCEINLINE BoundingBox &operator=(BoundingBox &&) noexcept = default;

		FORCEINLINE BoundingBox(const Vector3 &min, const Vector3 &max) noexcept;
		FORCEINLINE BoundingBox(const BoundingBox &lhs, const BoundingBox &rhs) noexcept;
		FORCEINLINE explicit BoundingBox(const BoundingSphere &boundingSphere) noexcept;
		FORCEINLINE Vector3  getCenter() const noexcept;
		FORCEINLINE Vector3  getExtents() const noexcept;
		FORCEINLINE void	 setCenter(const Vector3 &center);
		FORCEINLINE void	 setExtents(const Vector3 &extents);
		FORCEINLINE BoundingBox transform(const Matrix &trans) const noexcept;
		FORCEINLINE BoundingBox transform(float scale, const Quaternion &rotate, const Vector3 &translation) const noexcept;
		FORCEINLINE DirectX::ContainmentType contains(const BoundingBox &other) const noexcept;
		FORCEINLINE std::array<float3, kCornerCount> getCorners() const noexcept;
		FORCEINLINE void getMinMax(Vector3 &min, Vector3 &max) const noexcept;
		FORCEINLINE std::pair<Vector3, Vector3> getMinMax() const noexcept;
		FORCEINLINE static BoundingBox CreateFromCenter(const float3 &center, const float3 &extents) noexcept;
		FORCEINLINE static BoundingBox CreateFromPoints(size_t count, const float3 *points, size_t stride) noexcept;
		FORCEINLINE static BoundingBox CreateMerged(const BoundingBox &b1, const BoundingBox &b2) noexcept;
	};

#pragma endregion

#pragma region BoundingSphereDeclared

	class BoundingSphere : public DirectX::BoundingSphere {
	public:
		using Base = DirectX::BoundingSphere;
		// compiler generate code
		FORCEINLINE BoundingSphere() = default;
		FORCEINLINE BoundingSphere(const BoundingSphere &) noexcept = default;
		FORCEINLINE BoundingSphere(BoundingSphere &&) noexcept = default;
		FORCEINLINE BoundingSphere &operator=(const BoundingSphere &) noexcept = default;
		FORCEINLINE BoundingSphere &operator=(BoundingSphere &&) noexcept = default;

		FORCEINLINE BoundingSphere(const Vector3 &center, float radius) noexcept;
		FORCEINLINE BoundingSphere(const BoundingSphere &lhs, const BoundingSphere &rhs) noexcept;
		FORCEINLINE BoundingSphere(size_t count, const float3 *points, size_t stride) noexcept;
		FORCEINLINE explicit BoundingSphere(const BoundingBox &boundingBox) noexcept;
		FORCEINLINE explicit BoundingSphere(const BoundingFrustum &boundingFrustum) noexcept;
		FORCEINLINE Vector3  getCenter() const noexcept;
		FORCEINLINE float    getRadius() const noexcept;
		FORCEINLINE void     setCenter(const Vector3 &center) noexcept;
		FORCEINLINE void     setRadius(float radius) noexcept;
	};

#pragma endregion

#pragma region BoundingFrustumDeclared

	class BoundingFrustum : public DirectX::BoundingFrustum {
	public:
		using Base = DirectX::BoundingFrustum;
		static constexpr size_t kCornerCount = 8;
		// compiler generate code
		FORCEINLINE BoundingFrustum() noexcept = default;
		FORCEINLINE BoundingFrustum(const BoundingFrustum &) noexcept = default;
		FORCEINLINE BoundingFrustum &operator=(const BoundingFrustum &) noexcept = default;
		FORCEINLINE BoundingFrustum(BoundingFrustum &&) noexcept = default;
		FORCEINLINE BoundingFrustum &operator=(BoundingFrustum &&) noexcept = default;

		FORCEINLINE BoundingFrustum(const Vector3 &origin, const Quaternion &orientation,
			float rightSlope, float leftSlope,
			float topSlope, float bottomSlope,
			float zNear, float zFar
		) noexcept;
		FORCEINLINE explicit BoundingFrustum(const Matrix &projection) noexcept;
		FORCEINLINE BoundingFrustum transform(const Matrix &trans) const noexcept;
		FORCEINLINE BoundingFrustum transform(float scale, const Quaternion &rotate, const Vector3 &translation) const noexcept;
		FORCEINLINE std::array<float3, kCornerCount> getCorners() const noexcept;
		FORCEINLINE DirectX::ContainmentType contains(const BoundingBox &box) const noexcept;
	};

#pragma endregion

/*----------------------------------Implement-----------------------------------*/

#pragma region Float2Implement

	FORCEINLINE float2::float2(float v) : XMFLOAT2(v, v) {

	}
	FORCEINLINE float2::float2(float x, float y) : XMFLOAT2(x, y) {

	}
	FORCEINLINE float2::float2(const Vector2 &v2) : XMFLOAT2(v2.x, v2.y) {

	}
	FORCEINLINE float2::float2(const Vector3 &v3) : XMFLOAT2(v3.x, v3.y) {

	}
	FORCEINLINE float2::float2(const Vector4 &v4) : XMFLOAT2(v4.x, v4.y) {

	}
	FORCEINLINE Vector2 float2::load() const noexcept {
		return { x, y };
	}
	FORCEINLINE auto float2::operator[](size_t index) -> float & {
		assert(index < 2);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE auto float2::operator[](size_t index) const -> const float & {
		assert(index < 2);
		return reinterpret_cast<const float *>(this)[index];
	}
	FORCEINLINE bool operator==(const float2 &lhs, const float2 &rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}
	FORCEINLINE bool operator!=(const float2 &lhs, const float2 &rhs) {
		return !(lhs == rhs);
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const float2 &f2) noexcept {
		os << "(" << f2.x << ", " << f2.y << ")";
		return os;
	}
	inline const float2 float2::Zero { 0.f, 0.f };
	inline const float2 float2::One  { 1.f, 1.f };
	inline const float2 float2::UnitX{ 1.f, 0.f };
	inline const float2 float2::UnitY{ 0.f, 1.f };

#pragma endregion

#pragma region Float3Implement

	FORCEINLINE float3::float3(float v) : DirectX::XMFLOAT3(v, v, v) {

	}
	FORCEINLINE float3::float3(float x, float y, float z) : DirectX::XMFLOAT3(x, y, z) {

	}
	FORCEINLINE float3::float3(const float2 &f2, float z) : DirectX::XMFLOAT3(f2.x, f2.y, z) {

	}
	FORCEINLINE float3::float3(const Vector3 &v3) : XMFLOAT3(v3.x, v3.y, v3.z) {
	}
	FORCEINLINE float3::float3(const Vector4 &v4) : XMFLOAT3(v4.x, v4.y, v4.z) {
	}
	FORCEINLINE Vector3 float3::load() const noexcept {
		return { x, y, z };
	}
	FORCEINLINE auto float3::operator[](size_t index) -> float & {
		assert(index < 3);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE auto float3::operator[](size_t index) const -> const float & {
		assert(index < 3);
		return reinterpret_cast<const float *>(this)[index];
	}
	FORCEINLINE bool operator==(const float3 &lhs, const float3 &rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
	}
	FORCEINLINE bool operator!=(const float3 &lhs, const float3 &rhs) {
		return !(lhs == rhs);
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const float3 &f3) noexcept {
		os << "(" << f3.x << ", " << f3.y << ", " << f3.z << ")";
		return os;
	}
	inline const float3 float3::Zero { 0.f, 0.f, 0.f };
	inline const float3 float3::One  { 1.f, 1.f, 1.f };
	inline const float3 float3::UnitX{ 1.f, 0.f, 0.f };
	inline const float3 float3::UnitY{ 0.f, 1.f, 0.f };
	inline const float3 float3::UnitZ{ 0.f, 0.f, 1.f };

	inline const float3 float3::Up   { 0.f, +1.f, 0.f };
	inline const float3 float3::Down { 0.f, -1.f, 0.f };

	inline const float3 float3::Right{ +1.f, 0.f, 0.f };
	inline const float3 float3::Left { -1.f, 0.f, 0.f };

	inline const float3 float3::Forward { 0.f, 0.f, +1.f };
	inline const float3 float3::Backward{ 0.f, 0.f, -1.f };

#pragma endregion

#pragma region Float4Implement

	FORCEINLINE float4::float4(float v) : DirectX::XMFLOAT4(v, v, v, v) {

	}
	FORCEINLINE float4::float4(float x, float y, float z, float w) : DirectX::XMFLOAT4(x, y, z, w) {

	}
	FORCEINLINE float4::float4(const float2 &f2, float z, float w) : DirectX::XMFLOAT4(f2.x, f2.y, z, w) {

	}
	FORCEINLINE float4::float4(const float3 &f3, float w) : DirectX::XMFLOAT4(f3.x, f3.y, f3.z, w) {

	}
	FORCEINLINE Vector4 float4::load() const noexcept {
		return { x, y, z, w };
	}
	FORCEINLINE auto float4::operator[](size_t index) -> float & {
		assert(index < 4);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE auto float4::operator[](size_t index) const -> const float & {
		assert(index < 4);
		return reinterpret_cast<const float *>(this)[index];
	}

	FORCEINLINE bool operator==(const float4 &lhs, const float4 &rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
	}
	FORCEINLINE bool operator!=(const float4 &lhs, const float4 &rhs) {
		return !(lhs == rhs);
	}
	inline const float4 float4::Zero { 0.f, 0.f, 0.f, 0.f };
	inline const float4 float4::One  { 1.f, 1.f, 1.f, 1.f };
	inline const float4 float4::UnitX{ 1.f, 0.f, 0.f, 0.f };
	inline const float4 float4::UnitY{ 0.f, 1.f, 0.f, 0.f };
	inline const float4 float4::UnitZ{ 0.f, 0.f, 1.f, 0.f };
	inline const float4 float4::UnitW{ 0.f, 0.f, 0.f, 1.f };

#pragma endregion

#pragma region ColorImplement

	FORCEINLINE Color::Color() : r(0.f), g(0.f), b(0.f), a(1.f) {
	}
	FORCEINLINE Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
	}
	FORCEINLINE Color::Color(const float3 &f3, float a) : f4(f3, a) {
	}
	FORCEINLINE Color::Color(const float4 &f4) : f4(f4) {
	}
	FORCEINLINE Color::Color(const DirectX::XMVECTORF32 &c) {
		r = c.f[0];
		g = c.f[1];
		b = c.f[2];
		a = c.f[3];
	}
	FORCEINLINE bool Color::operator==(const Color &c) const noexcept {
		return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
	}
	FORCEINLINE bool Color::operator!=(const Color &c) const noexcept {
		return !(*this == c);
	}
	FORCEINLINE Color &Color::operator+=(const Color &c) noexcept {
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&this->f4);
		const XMVECTOR c2 = XMLoadFloat4(&c.f4);
		XMStoreFloat4(&this->f4, XMVectorAdd(c1, c2));
		return *this;
	}
	FORCEINLINE Color & Color::operator-=(const Color &c) noexcept {
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&this->f4);
		const XMVECTOR c2 = XMLoadFloat4(&c.f4);
		XMStoreFloat4(&this->f4, XMVectorSubtract(c1, c2));
		return *this;
	}
	FORCEINLINE Color & Color::operator*=(const Color &c) noexcept {
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&this->f4);
		const XMVECTOR c2 = XMLoadFloat4(&c.f4);
		XMStoreFloat4(&this->f4, XMVectorMultiply(c1, c2));
		return *this;
	}
	FORCEINLINE Color & Color::operator*=(float S) noexcept {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&this->f4);
		XMStoreFloat4(&this->f4, XMVectorScale(c, S));
		return *this;
	}
	FORCEINLINE Color & Color::operator/=(const Color &c) noexcept {
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&this->f4);
		const XMVECTOR c2 = XMLoadFloat4(&c.f4);
		XMStoreFloat4(&this->f4, XMVectorDivide(c1, c2));
		return *this;
	}
	FORCEINLINE Color Color::operator-() const noexcept {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&this->f4);
		Color R;
		XMStoreFloat4(&R.f4, XMVectorNegate(c));
		return R;
	}
	FORCEINLINE float3 Color::toFloat3() const noexcept {
		return { f4.x, f4.y, f4.z };
	}
	FORCEINLINE float4 Color::toFloat4() const noexcept {
		return f4;
	}
	FORCEINLINE Color operator+(const Color &C1, const Color &C2) noexcept {
		Color c1(C1);
		return c1 += C2;
	}
	FORCEINLINE Color operator-(const Color &C1, const Color &C2) noexcept {
		Color c1(C1);
		return c1 -= C2;
	}
	FORCEINLINE Color operator*(const Color &C1, const Color &C2) noexcept {
		Color c1(C1);
		return c1 *= C2;
	}
	FORCEINLINE Color operator*(const Color &C, float S) noexcept {
		Color c(C);
		return c *= S;
	}
	FORCEINLINE Color operator/(const Color &C1, const Color &C2) noexcept {
		Color c1(C1);
		return c1 /= C2;
	}
	FORCEINLINE Color operator*(float S, const Color &C) noexcept {
		return C * S;
	}
	FORCEINLINE Color negate(const Color &inputColor) {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&inputColor.f4);
		Color toReturn;
		XMStoreFloat4(&toReturn.f4, XMColorNegative(c));
		return toReturn;
	}
	FORCEINLINE Color saturate(const Color &inputColor) {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&inputColor.f4);
		Color toReturn;
		XMStoreFloat4(&toReturn.f4, XMVectorSaturate(c));
		return toReturn;
	}
	FORCEINLINE Color adjustSaturation(const Color &inputColor, float sat) {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&inputColor.f4);
		Color toReturn;
		XMStoreFloat4(&toReturn.f4, XMColorAdjustSaturation(c, sat));
		return toReturn;
	}
	FORCEINLINE Color adjustContrast(const Color &inputColor, float contrast) {
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&inputColor.f4);
		Color toReturn;
		XMStoreFloat4(&toReturn.f4, XMColorAdjustContrast(c, contrast));
		return toReturn;
	}
	FORCEINLINE Color lerp(const Color &lhs, const Color &rhs, float t) {
		using namespace DirectX;
		const XMVECTOR C0 = XMLoadFloat4(&lhs.f4);
		const XMVECTOR C1 = XMLoadFloat4(&rhs.f4);
		Color toReturn;
		XMStoreFloat4(&toReturn.f4, XMVectorLerp(C0, C1, t));
		return toReturn;
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const Color &c) noexcept {
		os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
		return os;
	}

#pragma endregion

#pragma region Float4x4Implement

	FORCEINLINE float4x4::float4x4()
	: XMFLOAT4X4(float4x4::Identity)
	{
	}
	FORCEINLINE float4x4::float4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) noexcept
	: XMFLOAT4X4(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33)
	{
	}
	FORCEINLINE float4x4::float4x4(const float3 &r0, const float3 &r1, const float3 &r2) noexcept
	: XMFLOAT4X4(r0.x, r0.y, r0.z, 0.f,
		r1.x, r1.y, r1.z, 0.f,
		r2.x, r2.y, r2.z, 0.f,
		0.f, 0.f, 0.f, 1.f)
	{
	}
	FORCEINLINE float4x4::float4x4(const float4 &r0, const float4 &r1, const float4 &r2, const float4 &r3) noexcept
	: XMFLOAT4X4(r0.x, r0.y, r0.z, r0.w,
		r1.x, r1.y, r1.z, r1.w,
		r2.x, r2.y, r2.z, r2.w,
		r3.x, r3.y, r3.z, r3.w)
	{
	}
	FORCEINLINE float4x4::float4x4(const DirectX::XMFLOAT4X4 &M) noexcept
	: XMFLOAT4X4(M) {

	}
	FORCEINLINE float4x4::float4x4(const DirectX::XMFLOAT3X3 &M) noexcept {
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
	}
	FORCEINLINE float4x4::float4x4(const DirectX::XMFLOAT4X3 &M) noexcept {
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
	}
	FORCEINLINE float4x4::float4x4(const float *pArray) noexcept : XMFLOAT4X4(pArray) {

	}
	FORCEINLINE bool operator==(const float4x4 &lhs, const float4x4 &rhs) noexcept {
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._41));

		return (XMVector4Equal(x1, y1)
			&& XMVector4Equal(x2, y2)
			&& XMVector4Equal(x3, y3)
			&& XMVector4Equal(x4, y4)) != 0;
	}
	FORCEINLINE bool operator!=(const float4x4 &lhs, const float4x4 &rhs) noexcept {
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&lhs._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&rhs._41));

		return (XMVector4NotEqual(x1, y1)
			|| XMVector4NotEqual(x2, y2)
			|| XMVector4NotEqual(x3, y3)
			|| XMVector4NotEqual(x4, y4)) != 0;
	}
	FORCEINLINE float3 float4x4::getUp() const {
		return { _21, _22, _23 };
	}
	FORCEINLINE float3 float4x4::getDown() const {
		return { -_21, -_22, -_23 };
	}
	FORCEINLINE float3 float4x4::getRight() const {
		return { _11, _12, _13 };
	}
	FORCEINLINE float3 float4x4::getLeft() const {
		return { -_11, -_12, -_13 };
	}
	FORCEINLINE float3 float4x4::getForward() const {
		return { -_31, -_32, -_33 };
	}
	FORCEINLINE float3 float4x4::getBackward() const {
		return { _31, _32, _33 };
	}
	FORCEINLINE float3 float4x4::getTranslation() const {
		return { _41, _42, _43 };
	}
	inline const float4x4 float4x4::Identity {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};

#pragma endregion

#pragma region SwizzleImplement

	template<typename T, bool EnableAssign, size_t... I>
	template<typename> requires (EnableAssign)
	FORCEINLINE T &Swizzle<T, EnableAssign, I...>::operator=(const T &other) noexcept {
		constexpr size_t idx = indices[0];
		if constexpr (sizeof...(I) > 1)
			((at<I>() = other[I]), ...);
		else
			at<idx>() = other;
		return reinterpret_cast<T &>(at<idx>());
	}

	template<typename T, bool EnableAssign, size_t... I>
	FORCEINLINE Swizzle<T, EnableAssign, I...>::operator T() const noexcept {
		return T(at<I>()...);
	}

	template<typename T, bool EnableAssign, size_t... I>
	template<size_t Idx>
	float & Swizzle<T, EnableAssign, I...>::at() noexcept {
		return reinterpret_cast<float *>(this)[Idx];
	}

	template<typename T, bool EnableAssign, size_t... I>
	template<size_t Idx>
	float Swizzle<T, EnableAssign, I...>::at() const noexcept {
		return reinterpret_cast<const float *>(this)[Idx];
	}

#pragma endregion

#pragma region Vector2Implement

	FORCEINLINE Vector2::Vector2(float x, float y) noexcept : x(x), y(y) {
	}
	FORCEINLINE Vector2::Vector2(const Vector2 &other) noexcept : x(other.x), y(other.y) {
	}
	FORCEINLINE Vector2::Vector2(float val) noexcept : x(val), y(val) {
	}
	FORCEINLINE Vector2::Vector2(const float2 &f2) noexcept : x(f2.x), y(f2.y) {
	}
	FORCEINLINE Vector2::Vector2(const Vector3 &v3) noexcept : x(v3.x), y(v3.y) {
	}
	FORCEINLINE Vector2::Vector2(const Vector4 &v4) noexcept : x(v4.x), y(v4.y) {
	}
	FORCEINLINE Vector2 &Vector2::operator=(const Vector2 &other) noexcept {
		x = other.x;
		y = other.y;
		return *this;
	}
	FORCEINLINE float2 Vector2::store() const noexcept {
		return { x, y };
	}
	FORCEINLINE float &Vector2::operator[](size_t index) noexcept {
		assert(index < 2);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE float Vector2::operator[](size_t index) const noexcept {
		assert(index < 2);
		return reinterpret_cast<const float *>(this)[index];
	}
	FORCEINLINE Vector2 &Vector2::operator+=(const Vector2 &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator-=(const Vector2 &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator*=(const Vector2 &rhs) noexcept {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator/=(const Vector2 &rhs) noexcept {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator+=(float rhs) noexcept {
		x += rhs;
		y += rhs;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator-=(float rhs) noexcept {
		x -= rhs;
		y -= rhs;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator*=(float rhs) noexcept {
		x *= rhs;
		y *= rhs;
		return *this;
	}
	FORCEINLINE Vector2 &Vector2::operator/=(float rhs) noexcept {
		x /= rhs;
		y /= rhs;
		return *this;
	}
	FORCEINLINE Vector2 Vector2::operator+() const noexcept {
		return *this;
	}
	FORCEINLINE Vector2 Vector2::operator-() const noexcept {
		return { -x, -y };
	}
	FORCEINLINE Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector2 operator+(const Vector2 &lhs, float rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector2 operator-(const Vector2 &lhs, float rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector2 operator*(const Vector2 &lhs, float rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector2 operator/(const Vector2 &lhs, float rhs) noexcept {
		Vector2 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector2 operator+(float lhs, const Vector2 &rhs) noexcept {
		return { lhs + rhs.x, lhs + rhs.y };
	}
	FORCEINLINE Vector2 operator-(float lhs, const Vector2 &rhs) noexcept {
		return { lhs - rhs.x, lhs - rhs.y };
	}
	FORCEINLINE Vector2 operator*(float lhs, const Vector2 &rhs) noexcept {
		return { lhs * rhs.x, lhs * rhs.y };
	}
	FORCEINLINE Vector2 operator/(float lhs, const Vector2 &rhs) noexcept {
		return { lhs / rhs.x, lhs / rhs.y };
	}
	FORCEINLINE Vector2 sqrt(const Vector2 &self) noexcept {
		return { std::sqrt(self.x), std::sqrt(self.y) };
	}
	FORCEINLINE Vector2 inverse(const Vector2 &self) noexcept {
		return { 1.f / self.x, 1.f / self.y };
	}
	FORCEINLINE Vector2 inverseSqrt(const Vector2 &self) noexcept {
		return { 1.f / std::sqrt(self.x), 1.f / std::sqrt(self.y) };
	}
	FORCEINLINE Vector2 floor(const Vector2 &self) noexcept {
		return { std::floor(self.x), std::floor(self.y) };
	}
	FORCEINLINE Vector2 ceil(const Vector2 &self) noexcept {
		return { std::ceil(self.x), std::ceil(self.y) };
	}
	FORCEINLINE Vector2 round(const Vector2 &self) noexcept {
		return { std::round(self.x), std::round(self.y) };
	}
	FORCEINLINE Vector2 abs(const Vector2 &self) noexcept {
		return { std::abs(self.x), std::abs(self.y) };
	}
	FORCEINLINE Vector2 exp(const Vector2 &self) noexcept {
		using namespace DirectX;
		return { std::exp(self.x), std::exp(self.y) };
	}
	FORCEINLINE Vector2 pow(const Vector2 &self, float e) noexcept {
		return { std::pow(self.x, e), std::pow(self.y, e) };
	}
	FORCEINLINE Vector2 pow(const Vector2 &self, const Vector2 &e) noexcept {
		return { std::pow(self.x, e.x), std::pow(self.y, e.y) };
	}
	FORCEINLINE Vector2 log(const Vector2 &self) noexcept {
		return { std::log(self.x), std::log(self.y) };
	}
	FORCEINLINE Vector2 sin(const Vector2 &self) noexcept {
		return { std::sin(self.x), std::sin(self.y) };
	}
	FORCEINLINE Vector2 cos(const Vector2 &self) noexcept {
		return { std::cos(self.x), std::cos(self.y) };
	}
	FORCEINLINE Vector2 tan(const Vector2 &self) noexcept {
		return { std::tan(self.x), std::tan(self.y) };
	}
	FORCEINLINE Vector2 asin(const Vector2 &self) noexcept {
		return { std::asin(self.x), std::asin(self.y) };
	}
	FORCEINLINE Vector2 acos(const Vector2 &self) noexcept {
		return { std::acos(self.x), std::acos(self.y) };
	}
	FORCEINLINE Vector2 atan(const Vector2 &self) noexcept {
		return { std::atan(self.x), std::atan(self.y) };
	}
	FORCEINLINE Vector2 lerp(const Vector2 &lhs, const Vector2 &rhs, float t) noexcept {
		return { std::lerp(lhs.x, rhs.x, t), std::lerp(lhs.y, rhs.y, t) };
	}
	FORCEINLINE Vector2 lerp(const Vector2 &lhs, const Vector2 &rhs, const Vector2 &t) noexcept {
		return { std::lerp(lhs.x, rhs.x, t.x), std::lerp(lhs.y, rhs.y, t.y) };
	}
	FORCEINLINE Vector2 min(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		return { std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y) };
	}
	FORCEINLINE Vector2 max(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		return { std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y) };
	}
	FORCEINLINE Vector2 clamp(const Vector2 &v, const Vector2 &a, const Vector2 &b) noexcept {
		return {
			std::clamp(v.x, a.x, b.x),
			std::clamp(v.y, a.y, b.y),
		};
	}
	FORCEINLINE Vector2 normalize(const Vector2 &self) noexcept {
		auto len = length(self);
		return (len > 0.f) ? self / len : Vector2::Zero;
	}
	FORCEINLINE float dot(const Vector2 &lhs, const Vector2 &rhs) noexcept {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	FORCEINLINE float lengthSquare(const Vector2 &self) noexcept {
		return self.x * self.x + self.y * self.y;
	}
	FORCEINLINE float length(const Vector2 &self) noexcept {
		return std::sqrt(lengthSquare(self));
	}
	FORCEINLINE float inverseLength(const Vector2 &self) noexcept {
		auto len = length(self);
		return (len > 0.f) ? 1.f / len : 0.f;
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const Vector2 &v2) noexcept {
		os << "(" << v2.x << ", " << v2.y << ")";
		return os;
	}

	inline const Vector2 Vector2::Zero  { 0.f, 0.f };
	inline const Vector2 Vector2::One   { 1.f, 1.f };
	inline const Vector2 Vector2::UnitX { 1.f, 0.f };
	inline const Vector2 Vector2::UnitY { 0.f, 1.f };

#pragma endregion

#pragma region Vector3Implement

	FORCEINLINE Vector3::Vector3(float x, float y, float z) noexcept {
		vec = DirectX::XMVectorSet(x, y, z, 0.f);
	}
	FORCEINLINE Vector3::Vector3(const float2 &f2, float z) noexcept {
		vec = DirectX::XMVectorSet(f2.x, f2.y, z, 0.f);
	}
	FORCEINLINE Vector3::Vector3(const Vector2 &v2, float z) noexcept {
		vec = DirectX::XMVectorSet(v2.x, v2.y, z, 0.f);
	}
	FORCEINLINE Vector3::Vector3(const Vector3 &v3) noexcept {
		vec = DirectX::XMVectorSet(v3.x, v3.y, v3.z, 0.f);
	}
	FORCEINLINE Vector3::Vector3(float val) noexcept {
		vec = DirectX::XMVectorSet(val, val, val, 0.f);
	}
	FORCEINLINE Vector3::Vector3(const Vector4 &v4) noexcept {
		vec = DirectX::XMVectorSet(v4.x, v4.y, v4.z, 0.f);
	}
	FORCEINLINE Vector3 &Vector3::operator=(const Vector3 &other) noexcept {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	FORCEINLINE float3 Vector3::store() const noexcept {
		return { x, y, z };
	}
	FORCEINLINE float &Vector3::operator[](size_t index) noexcept {
		assert(index < 3);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE float Vector3::operator[](size_t index) const noexcept {
		assert(index < 3);
		return reinterpret_cast<const float *>(this)[index];
	}
	FORCEINLINE Vector3 &Vector3::operator+=(const Vector3 &rhs) noexcept {
		vec = DirectX::XMVectorAdd(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator-=(const Vector3 &rhs) noexcept {
		vec = DirectX::XMVectorSubtract(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator*=(const Vector3 &rhs) noexcept {
		vec = DirectX::XMVectorMultiply(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator/=(const Vector3 &rhs) noexcept {
		vec = DirectX::XMVectorDivide(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator+=(float rhs) noexcept {
		vec = DirectX::XMVectorAdd(vec, DirectX::XMVectorSet(rhs, rhs, rhs, rhs));
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator-=(float rhs) noexcept {
		vec = DirectX::XMVectorSubtract(vec, DirectX::XMVectorSet(rhs, rhs, rhs, rhs));
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator*=(float rhs) noexcept {
		vec = DirectX::XMVectorScale(vec, rhs);
		return *this;
	}
	FORCEINLINE Vector3 &Vector3::operator/=(float rhs) noexcept {
		vec = DirectX::XMVectorScale(vec, 1.f / rhs);
		return *this;
	}
	FORCEINLINE Vector3 Vector3::operator+() const noexcept {
		return *this;
	}
	FORCEINLINE Vector3 Vector3::operator-() const noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorNegate(vec);
		return toReturn;
	}
	FORCEINLINE Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector3 operator+(const Vector3 &lhs, float rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector3 operator-(const Vector3 &lhs, float rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector3 operator*(const Vector3 &lhs, float rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector3 operator/(const Vector3 &lhs, float rhs) noexcept {
		Vector3 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector3 operator+(float lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn(lhs);
		return toReturn += rhs;
	}
	FORCEINLINE Vector3 operator-(float lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn(lhs);
		return toReturn -= rhs;
	}
	FORCEINLINE Vector3 operator*(float lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn(lhs);
		return toReturn *= rhs;
	}
	FORCEINLINE Vector3 operator/(float lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn(lhs);
		return toReturn /= rhs;
	}
	FORCEINLINE Vector3 sqrt(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorSqrt(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 inverse(const Vector3 &self) noexcept {
		Vector3 toReturn(self);
		return 1.f / toReturn;
	}
	FORCEINLINE Vector3 inverseSqrt(const Vector3 &self) noexcept {
		auto toReturn = sqrt(self);
		return 1.f / toReturn;
	}
	FORCEINLINE Vector3 floor(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorFloor(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 ceil(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorCeiling(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 round(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorRound(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 abs(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorAbs(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 exp(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorExp(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 pow(const Vector3 &self, float e) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorPow(self.vec, DirectX::XMVectorSet(e, e, e, 0.f));
		return toReturn;
	}
	FORCEINLINE Vector3 pow(const Vector3 &self, const Vector3 &e) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorPow(self.vec, e.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 log(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorLog(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 sin(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorSin(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 cos(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorCos(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 tan(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorTan(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 asin(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorASin(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 acos(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorACos(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 atan(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorATan(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 lerp(const Vector3 &lhs, const Vector3 &rhs, float t) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorLerp(lhs.vec, rhs.vec, t);
		return toReturn;
	}
	FORCEINLINE Vector3 lerp(const Vector3 &lhs, const Vector3 &rhs, const Vector3 &t) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorLerpV(lhs.vec, rhs.vec, t.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 min(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorMin(lhs.vec, rhs.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 max(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorMax(lhs.vec, rhs.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 clamp(const Vector3 &v, const Vector3 &a, const Vector3 &b) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVectorClamp(v.vec, a.vec, b.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 normalize(const Vector3 &self) noexcept {
		Vector3 toReturn;
		toReturn.vec = DirectX::XMVector3Normalize(self.vec);
		return toReturn;
	}
	FORCEINLINE float dot(const Vector3 &lhs, const Vector3 &rhs) noexcept {
		auto vec = DirectX::XMVector3Dot(lhs.vec, rhs.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float lengthSquare(const Vector3 &self) noexcept {
		auto vec = DirectX::XMVector3LengthSq(self.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float length(const Vector3 &self) noexcept {
		auto vec = DirectX::XMVector3Length(self.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float inverseLength(const Vector3 &self) noexcept {
		auto vec = DirectX::XMVector3Length(self.vec);
		auto len = DirectX::XMVectorGetX(vec);
		return (len > 0.f) ? 1.f / len : 0.f;
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const Vector3 &v3) noexcept {
		os << "(" << v3.x << ", " << v3.y << ", " << v3.z << ")";
		return os;
	}

	inline const Vector3 Vector3::Zero { 0.f, 0.f, 0.f };
	inline const Vector3 Vector3::One  { 1.f, 1.f, 1.f };
	inline const Vector3 Vector3::UnitX{ 1.f, 0.f, 0.f };
	inline const Vector3 Vector3::UnitY{ 0.f, 1.f, 0.f };
	inline const Vector3 Vector3::UnitZ{ 0.f, 0.f, 1.f };

	inline const Vector3 Vector3::Up   { 0.f, +1.f, 0.f };
	inline const Vector3 Vector3::Down { 0.f, -1.f, 0.f };

	inline const Vector3 Vector3::Right{ +1.f, 0.f, 0.f };
	inline const Vector3 Vector3::Left { -1.f, 0.f, 0.f };

	inline const Vector3 Vector3::Forward { 0.f, 0.f, +1.f };
	inline const Vector3 Vector3::Backward{ 0.f, 0.f, -1.f };

#pragma endregion

#pragma region Vector4Implement

	FORCEINLINE Vector4::Vector4(float x, float y, float z, float w) noexcept {
		vec = DirectX::XMVectorSet(x, y, z, w);
	}
	FORCEINLINE Vector4::Vector4(const float2 &f2, float z, float w) noexcept {
		vec = DirectX::XMVectorSet(f2.x, f2.y, z, w);
	}
	FORCEINLINE Vector4::Vector4(const Vector2 &v2, float z, float w) noexcept {
		vec = DirectX::XMVectorSet(v2.x, v2.y, z, w);
	}
	FORCEINLINE Vector4::Vector4(const float3 &f3, float w) noexcept {
		vec = DirectX::XMVectorSet(f3.x, f3.y, f3.z, w);
	}
	FORCEINLINE Vector4::Vector4(const Vector3 &v3, float w) noexcept {
		vec = DirectX::XMVectorSet(v3.x, v3.y, v3.z, w);
	}
	FORCEINLINE Vector4::Vector4(float val) noexcept {
		vec = DirectX::XMVectorSet(val, val, val, val);
	}
	FORCEINLINE Vector4::Vector4(const Vector4 &v4) noexcept {
		vec = v4.vec;
	}
	FORCEINLINE Vector4 &Vector4::operator=(const Vector4 &other) noexcept {
		vec = other.vec;
		return *this;
	}
	FORCEINLINE float4 Vector4::store() const noexcept {
		return { x, y, z, w };
	}
	FORCEINLINE float &Vector4::operator[](size_t index) noexcept {
		assert(index < 4);
		return reinterpret_cast<float *>(this)[index];
	}
	FORCEINLINE float  Vector4::operator[](size_t index) const noexcept {
		assert(index < 4);
		return reinterpret_cast<const float *>(this)[index];
	}
	FORCEINLINE Vector4 &Vector4::operator+=(const Vector4 &rhs) noexcept {
		vec = DirectX::XMVectorAdd(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator-=(const Vector4 &rhs) noexcept {
		vec = DirectX::XMVectorSubtract(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator*=(const Vector4 &rhs) noexcept {
		vec = DirectX::XMVectorMultiply(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator/=(const Vector4 &rhs) noexcept {
		vec = DirectX::XMVectorDivide(vec, rhs.vec);
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator+=(float rhs) noexcept {
		vec = DirectX::XMVectorAdd(vec, DirectX::XMVectorSet(rhs, rhs, rhs, rhs));
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator-=(float rhs) noexcept {
		vec = DirectX::XMVectorSubtract(vec, DirectX::XMVectorSet(rhs, rhs, rhs, rhs));
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator*=(float rhs) noexcept {
		vec = DirectX::XMVectorScale(vec, rhs);
		return *this;
	}
	FORCEINLINE Vector4 &Vector4::operator/=(float rhs) noexcept {
		vec = DirectX::XMVectorScale(vec, 1.f / rhs);
		return *this;
	}
	FORCEINLINE Vector4 Vector4::operator+() const noexcept {
		return *this;
	}
	FORCEINLINE Vector4 Vector4::operator-() const noexcept {
		using namespace DirectX;
		Vector4 toReturn;
		toReturn.vec = XMVectorNegate(vec);
		return toReturn;
	}
	FORCEINLINE Vector4 operator+(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector4 operator-(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector4 operator*(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector4 operator/(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector4 operator+(const Vector4 &lhs, float rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 += rhs;
	}
	FORCEINLINE Vector4 operator-(const Vector4 &lhs, float rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 -= rhs;
	}
	FORCEINLINE Vector4 operator*(const Vector4 &lhs, float rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 *= rhs;
	}
	FORCEINLINE Vector4 operator/(const Vector4 &lhs, float rhs) noexcept {
		Vector4 lhs1(lhs);
		return lhs1 /= rhs;
	}
	FORCEINLINE Vector4 operator+(float lhs, const Vector4 &rhs) noexcept {
		return Vector4(lhs) += rhs;
	}
	FORCEINLINE Vector4 operator-(float lhs, const Vector4 &rhs) noexcept {
		return Vector4(lhs) -= rhs;
	}
	FORCEINLINE Vector4 operator*(float lhs, const Vector4 &rhs) noexcept {
		return Vector4(lhs) *= rhs;
	}
	FORCEINLINE Vector4 operator/(float lhs, const Vector4 &rhs) noexcept {
		return Vector4(lhs) /= rhs;
	}
	FORCEINLINE Vector4 sqrt(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorSqrt(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 inverse(const Vector4 &self) noexcept {
		return 1.f / self;
	}
	FORCEINLINE Vector4 inverseSqrt(const Vector4 &self) noexcept {
		auto toReturn = sqrt(self);
		return 1.f / toReturn;
	}
	FORCEINLINE Vector4 floor(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorFloor(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 ceil(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorCeiling(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 round(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorRound(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 abs(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorAbs(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 exp(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorExp(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 pow(const Vector4 &self, float e) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorPow(self.vec, DirectX::XMVectorSet(e, e, e, e));
		return toReturn;
	}
	FORCEINLINE Vector4 pow(const Vector4 &self, const Vector4 &e) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorPow(self.vec, e.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 log(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorLog(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 sin(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorSin(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 cos(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorCos(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 tan(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorTan(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 asin(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorASin(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 acos(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorACos(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 atan(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorATan(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 lerp(const Vector4 &lhs, const Vector4 &rhs, float t) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorLerp(lhs.vec, rhs.vec, t);
		return toReturn;
	}
	FORCEINLINE Vector4 lerp(const Vector4 &lhs, const Vector4 &rhs, const Vector4 &t) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorLerpV(lhs.vec, rhs.vec, t.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 min(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorMin(lhs.vec, rhs.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 max(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorMax(lhs.vec, rhs.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 clamp(const Vector4 &v, const Vector4 &a, const Vector4 &b) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVectorClamp(v.vec, a.vec, b.vec);
		return toReturn;
	}
	FORCEINLINE Vector4 normalize(const Vector4 &self) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVector4Normalize(self.vec);
		return toReturn;
	}
	FORCEINLINE float dot(const Vector4 &lhs, const Vector4 &rhs) noexcept {
		auto vec = DirectX::XMVector4Dot(lhs.vec, rhs.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float lengthSquare(const Vector4 &self) noexcept {
		auto vec = DirectX::XMVector4LengthSq(self.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float length(const Vector4 &self) noexcept {
		auto vec = DirectX::XMVector4Length(self.vec);
		return DirectX::XMVectorGetX(vec);
	}
	FORCEINLINE float inverseLength(const Vector4 &self) noexcept {
		auto vec = DirectX::XMVector4Length(self.vec);
		auto len = DirectX::XMVectorGetX(vec);
		return (len > 0.f) ? 1.f / len : 0.f;
	}
	FORCEINLINE std::ostream & operator<<(std::ostream &os, const Vector4 &v4) noexcept {
		os << "(" << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.w << ")";
		return os;
	}

	inline const Vector4 Vector4::Zero { 0.f, 0.f, 0.f, 0.f };
	inline const Vector4 Vector4::One  { 1.f, 1.f, 1.f, 0.f };
	inline const Vector4 Vector4::UnitX{ 1.f, 0.f, 0.f, 0.f };
	inline const Vector4 Vector4::UnitY{ 0.f, 1.f, 0.f, 0.f };
	inline const Vector4 Vector4::UnitZ{ 0.f, 0.f, 1.f, 0.f };
	inline const Vector4 Vector4::UnitW{ 0.f, 0.f, 0.f, 1.f };

#pragma endregion

#pragma region QuaternionImplement

	FORCEINLINE Quaternion::Quaternion() noexcept {
		vec = DirectX::XMVectorSet(0.f, 0.f, 0.f, 1.f);
	}
	FORCEINLINE Quaternion::Quaternion(float ix, float iy, float iz, float iw) noexcept {
		vec = DirectX::XMVectorSet(ix, iy, iz, iw);
	}
	FORCEINLINE Quaternion::Quaternion(const float4 &f4) noexcept {
		vec = DirectX::XMVectorSet(f4.x, f4.y, f4.z, f4.w);
	}
	FORCEINLINE float4 Quaternion::store() const noexcept {
		return { x, y, z, w };
	}
	FORCEINLINE bool Quaternion::operator==(const Quaternion &q) const noexcept {
		return DirectX::XMQuaternionEqual(vec, q.vec);
	}
	FORCEINLINE bool Quaternion::operator!=(const Quaternion &q) const noexcept {
		return DirectX::XMQuaternionNotEqual(vec, q.vec);
	}
	FORCEINLINE Quaternion &Quaternion::operator+=(const Quaternion &q) noexcept {
		vec = DirectX::XMVectorAdd(vec, q.vec);
		return *this;
	}
	FORCEINLINE Quaternion &Quaternion::operator-=(const Quaternion &q) noexcept {
		vec = DirectX::XMVectorSubtract(vec, q.vec);
		return *this;
	}
	FORCEINLINE Quaternion &Quaternion::operator*=(const Quaternion &q) noexcept {
		vec = DirectX::XMVectorMultiply(vec, q.vec);
		return *this;
	}
	FORCEINLINE Quaternion &Quaternion::operator*=(float S) noexcept {
		vec = DirectX::XMVectorScale(vec, S);
		return *this;
	}
	FORCEINLINE Quaternion &Quaternion::operator/=(const Quaternion &q) noexcept {
		auto q2 = DirectX::XMQuaternionInverse(q.vec);
		q2 = DirectX::XMQuaternionInverse(q2);
		vec = DirectX::XMQuaternionMultiply(vec, q2);
		return *this;
	}
	FORCEINLINE Quaternion Quaternion::operator-() const noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMVectorNegate(vec);
		return toReturn;
	}
	FORCEINLINE float length(const Quaternion &self) noexcept {
		using namespace DirectX;
		auto vec = XMQuaternionLength(self.vec);
		return XMVectorGetX(vec);
	}
	FORCEINLINE float lengthSquare(const Quaternion &self) noexcept {
		using namespace DirectX;
		auto vec = XMQuaternionLengthSq(self.vec);
		return XMVectorGetX(vec);
	}
	FORCEINLINE float dot(const Quaternion &lhs, const Quaternion &rhs) noexcept {
		using namespace DirectX;
		auto vec = XMQuaternionDot(lhs.vec, rhs.vec);
		return XMVectorGetX(vec);
	}
	FORCEINLINE Quaternion lerp(const Quaternion &q1, const Quaternion &q2, float t) noexcept {
		using namespace DirectX;
		const XMVECTOR &Q0 = q1.vec;
		const XMVECTOR &Q1 = q2.vec;
		const XMVECTOR dot = XMVector4Dot(Q0, Q1);
		Quaternion toReturn;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero())) {
			toReturn.vec = XMVectorLerp(Q0, Q1, t);
		}
		else {
			const XMVECTOR tv = XMVectorReplicate(t);
			const XMVECTOR t1v = XMVectorReplicate(1.f - t);
			const XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
			const XMVECTOR X1 = XMVectorMultiply(Q1, tv);
			toReturn.vec = XMVectorSubtract(X0, X1);
		}
		toReturn.vec = XMQuaternionNormalize(toReturn.vec);
		return toReturn;
	}
	FORCEINLINE Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionSlerp(q1.vec, q2.vec, t);
		return toReturn;
	}
	FORCEINLINE Quaternion normalize(const Quaternion &self) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionNormalize(self.vec);
		return toReturn;
	}
	FORCEINLINE Quaternion conjugate(const Quaternion &self) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionConjugate(self.vec);
		return toReturn;
	}
	FORCEINLINE Quaternion inverse(const Quaternion &self) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionInverse(self.vec);
		return toReturn;
	}
	FORCEINLINE Vector3 toEuler(const Quaternion &self) noexcept {
		const float x = self.x;
		const float y = self.y;
		const float z = self.z;
		const float w = self.w;
		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;

		const float m31 = 2.f * x * z + 2.f * y * w;
		const float m32 = 2.f * y * z - 2.f * x * w;
		const float m33 = 1.f - 2.f * xx - 2.f * yy;

		const float cy = sqrtf(m33 * m33 + m31 * m31);
		const float cx = atan2f(-m32, cy);
		if (cy > 16.f * FLT_EPSILON) {
			const float m12 = 2.f * x * y + 2.f * z * w;
			const float m22 = 1.f - 2.f * xx - 2.f * zz;
			return Vector3(cx, atan2f(m31, m33), atan2f(m12, m22));
		} else {
			const float m11 = 1.f - 2.f * yy - 2.f * zz;
			const float m21 = 2.f * x * y - 2.f * z * w;
			return Vector3(cx, 0.f, atan2f(-m21, m11));
		}
	}
	FORCEINLINE Quaternion Quaternion::CreateFromAxisAngle(const Vector3 &axis, float angle) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionRotationAxis(axis.vec, angle);
		return toReturn;
	}
	FORCEINLINE Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
		return toReturn;
	}
	FORCEINLINE Quaternion Quaternion::CreateFromYawPitchRoll(const Vector3 &angles) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionRotationRollPitchYawFromVector(angles.vec);
			return toReturn;
	}
	FORCEINLINE Quaternion Quaternion::CreateFromRotationMatrix(const Matrix &M) noexcept {
		Quaternion toReturn;
		toReturn.vec = DirectX::XMQuaternionRotationMatrix(M.mat);
		return toReturn;
	}
	FORCEINLINE float Quaternion::Angle(const Quaternion &q1, const Quaternion &q2) noexcept {
		using namespace DirectX;
		XMVECTOR R = XMQuaternionMultiply(XMQuaternionConjugate(q1.vec), q2.vec);
		const float rs = XMVectorGetW(R);
		R = XMVector3Length(R);
		return 2.f * atan2f(XMVectorGetX(R), rs);
	}
	inline const Quaternion Quaternion::Identity{ 0.f, 0.f, 0.f, 1.f };

#pragma endregion

#pragma region MatrixImplement

	FORCEINLINE Matrix::Matrix() {
		mat = Matrix::Identity.mat;
	}
	FORCEINLINE Matrix::Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
	{
		mat = DirectX::XMMatrixSet(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33);
	}
	FORCEINLINE Matrix::Matrix(const Vector3 &r0, const Vector3 &r1, const Vector3 &r2) {
		mat = DirectX::XMMatrixSet(r0.x, r0.y, r0.z, 0.f,
			r1.x, r1.y, r1.z, 0.f,
			r2.x, r2.y, r2.z, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}
	FORCEINLINE Matrix::Matrix(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3) {
		mat.r[0] = r0.vec;
		mat.r[1] = r1.vec;
		mat.r[2] = r2.vec;
		mat.r[3] = r3.vec;
	}
	FORCEINLINE Matrix::Matrix(const float *pArray) noexcept {
		auto m = DirectX::XMFLOAT4X4(pArray);
		mat = DirectX::XMLoadFloat4x4(&m);
	}
	FORCEINLINE bool Matrix::operator==(const Matrix &M) const noexcept {
		float4x4 m0;
		float4x4 m1;
		DirectX::XMStoreFloat4x4(&m0, mat);
		DirectX::XMStoreFloat4x4(&m1, M.mat);
		return m0 == m1;
	}
	FORCEINLINE bool Matrix::operator!=(const Matrix &M) const noexcept {
		float4x4 m0;
		float4x4 m1;
		DirectX::XMStoreFloat4x4(&m0, mat);
		DirectX::XMStoreFloat4x4(&m1, M.mat);
		return m0 != m1;
	}
	FORCEINLINE Matrix &Matrix::operator+=(const Matrix &M) noexcept {
		using namespace DirectX;
		float4x4 m0;
		float4x4 m1;
		DirectX::XMStoreFloat4x4(&m0, mat);
		DirectX::XMStoreFloat4x4(&m1, M.mat);
		Vector4 x1, x2, x3, x4;

		x1.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._11));
		x2.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._21));
		x3.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._31));
		x4.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._41));

		x1.vec = XMVectorAdd(x1.vec, y1);
		x2.vec = XMVectorAdd(x2.vec, y2);
		x3.vec = XMVectorAdd(x3.vec, y3);
		x4.vec = XMVectorAdd(x4.vec, y4);

		*this = Matrix(x1, x2, x3, x4);
		return *this;
	}
	FORCEINLINE Matrix &Matrix::operator-=(const Matrix &M) noexcept {
		using namespace DirectX;
		float4x4 m0;
		float4x4 m1;
		DirectX::XMStoreFloat4x4(&m0, mat);
		DirectX::XMStoreFloat4x4(&m1, M.mat);
		Vector4 x1, x2, x3, x4;

		x1.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._11));
		x2.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._21));
		x3.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._31));
		x4.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m1._41));

		x1.vec = XMVectorSubtract(x1.vec, y1);
		x2.vec = XMVectorSubtract(x2.vec, y2);
		x3.vec = XMVectorSubtract(x3.vec, y3);
		x4.vec = XMVectorSubtract(x4.vec, y4);

		*this = Matrix(x1, x2, x3, x4);
		return *this;
	}
	FORCEINLINE Matrix &Matrix::operator*=(const Matrix &M) noexcept {
		using namespace DirectX;
		mat = XMMatrixMultiply(M.mat, mat);
		return *this;
	}
	FORCEINLINE Matrix &Matrix::operator/=(const Matrix &M) noexcept {
		*this *= inverse(M);
		return *this;
	}
	FORCEINLINE Matrix &Matrix::operator*=(float S) noexcept {
		using namespace DirectX;
		float4x4 m0;
		DirectX::XMStoreFloat4x4(&m0, mat);
		Vector4 x1, x2, x3, x4;

		x1.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._11));
		x2.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._21));
		x3.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._31));
		x4.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._41));

		x1.vec = XMVectorScale(x1.vec, S);
		x2.vec = XMVectorScale(x2.vec, S);
		x3.vec = XMVectorScale(x3.vec, S);
		x4.vec = XMVectorScale(x4.vec, S);
		*this = Matrix(x1, x2, x3, x4);
		return *this;
	}
	FORCEINLINE Matrix &Matrix::operator/=(float S) noexcept {
		using namespace DirectX;
		float4x4 m0;
		DirectX::XMStoreFloat4x4(&m0, mat);
		Vector4 x1, x2, x3, x4;

		x1.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._11));
		x2.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._21));
		x3.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._31));
		x4.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._41));

		float invS = 1.f / S;
		x1.vec = XMVectorScale(x1.vec, invS);
		x2.vec = XMVectorScale(x2.vec, invS);
		x3.vec = XMVectorScale(x3.vec, invS);
		x4.vec = XMVectorScale(x4.vec, invS);
		*this = Matrix(x1, x2, x3, x4);
		return *this;
	}
	FORCEINLINE Matrix Matrix::operator+() const noexcept {
		return *this;
	}
	FORCEINLINE Matrix Matrix::operator-() const noexcept {
		using namespace DirectX;
		float4x4 m0;
		DirectX::XMStoreFloat4x4(&m0, mat);
		Vector4 x1, x2, x3, x4;

		x1.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._11));
		x2.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._21));
		x3.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._31));
		x4.vec = XMLoadFloat4(reinterpret_cast<const XMFLOAT4 *>(&m0._41));

		x1.vec = XMVectorNegate(x1.vec);
		x2.vec = XMVectorNegate(x2.vec);
		x3.vec = XMVectorNegate(x3.vec);
		x4.vec = XMVectorNegate(x4.vec);
		return Matrix(x1, x2, x3, x4);
	}
	FORCEINLINE bool decompose(const Matrix &m, Vector3 &scale, Quaternion &rotation, Vector3 &translation) noexcept {
		if (!DirectX::XMMatrixDecompose(
			&scale.vec,
			&rotation.vec,
			&translation.vec,
			m.mat))
		{
			return false;
		}
		return true;
	}
	FORCEINLINE Matrix transpose(const Matrix &m) {
		Matrix toReturn;
		toReturn.mat = DirectX::XMMatrixTranspose(m.mat);
		return toReturn;
	}
	FORCEINLINE Matrix inverse(const Matrix &m) {
		Matrix toReturn;
		auto det = DirectX::XMMatrixDeterminant(m.mat);
		toReturn.mat = DirectX::XMMatrixInverse(&det, m.mat);
		return toReturn;
	}
	FORCEINLINE float determinant(const Matrix &m) {
		auto det = DirectX::XMMatrixDeterminant(m.mat);
		return DirectX::XMVectorGetX(det);
	}
	FORCEINLINE Vector3 toEuler(const Matrix &m) {
		float4x4 m0;
		DirectX::XMStoreFloat4x4(&m0, m.mat);

		const float cy = sqrtf(m0._33 * m0._33 + m0._31 * m0._31);
		const float cx = atan2f(-m0._32, cy);
		if (cy > 16.f * FLT_EPSILON) {
			return Vector3(cx, atan2f(m0._31, m0._33), atan2f(m0._12, m0._22));
		}
		return Vector3(cx, 0.f, atan2f(-m0._21, m0._11));
	}
	FORCEINLINE Matrix Matrix::CreateBillboard(const Vector3 &objectPos,
		const Vector3 &cameraPos,
		const Vector3 &cameraUp,
		const Vector3 *cameraForward) noexcept
	{
		using namespace DirectX;
		const XMVECTOR &O = objectPos.vec;
		const XMVECTOR &C = cameraPos.vec;
		XMVECTOR Z = XMVectorSubtract(O, C);

		const XMVECTOR N = XMVector3LengthSq(Z);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward) {
				const XMVECTOR &F = cameraForward->vec;
				Z = XMVectorNegate(F);
			}
			else {
				Z = g_XMNegIdentityR2;
			}
		}
		else {
			Z = XMVector3Normalize(Z);
		}

		const XMVECTOR &up = cameraUp.vec;
		XMVECTOR X = XMVector3Cross(up, Z);
		X = XMVector3Normalize(X);

		const XMVECTOR Y = XMVector3Cross(Z, X);

		Matrix toReturn;
		toReturn.mat.r[0] = X;
		toReturn.mat.r[1] = Y;
		toReturn.mat.r[2] = Z;
		toReturn.mat.r[3] = XMVectorSetW(O, 1.f);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateConstrainedBillboard(
		const Vector3 &objectPos,
		const Vector3 &cameraPosition,
		const Vector3 &rotateAxis,
		const Vector3 *cameraForward,
		const Vector3 *objectForward) noexcept
	{
		using namespace DirectX;

		static const XMVECTORF32 s_minAngle = { { { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f } } }; // 1.0 - XMConvertToRadians( 0.1f );

		const XMVECTOR &O = objectPos.vec;
		const XMVECTOR &C = cameraPosition.vec;
		XMVECTOR faceDir = XMVectorSubtract(O, C);

		const XMVECTOR N = XMVector3LengthSq(faceDir);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward) {
				const XMVECTOR &F = cameraForward->vec;
				faceDir = XMVectorNegate(F);
			}
			else {
				faceDir = g_XMNegIdentityR2;
			}
		}
		else {
			faceDir = XMVector3Normalize(faceDir);
		}

		const XMVECTOR &Y = rotateAxis.vec;
		XMVECTOR X, Z;

		XMVECTOR dot = XMVectorAbs(XMVector3Dot(Y, faceDir));
		if (XMVector3Greater(dot, s_minAngle)) {
			if (objectForward) {
				Z = objectForward->vec;
				dot = XMVectorAbs(XMVector3Dot(Y, Z));
				if (XMVector3Greater(dot, s_minAngle)) {
					dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
					Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
				}
			}
			else {
				dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
				Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
			}

			X = XMVector3Cross(Y, Z);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}
		else {
			X = XMVector3Cross(Y, faceDir);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}

		Matrix toReturn;
		toReturn.mat.r[0] = X;
		toReturn.mat.r[1] = Y;
		toReturn.mat.r[2] = Z;
		toReturn.mat.r[3] = XMVectorSetW(O, 1.f);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateTranslation(const Vector3 &position) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixTranslation(position.x, position.y, position.z);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateTranslation(float x, float y, float z) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixTranslation(x, y, z);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateScale(const Vector3 &scales) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixScaling(scales.x, scales.y, scales.z);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateScale(float xs, float ys, float zs) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixScaling(xs, ys, zs);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateScale(float scale) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixScaling(scale, scale, scale);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateRotationX(float radians) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixRotationX(radians);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateRotationY(float radians) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixRotationY(radians);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateRotationZ(float radians) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixRotationZ(radians);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateFromAxisAngle(const Vector3 &axis, float angle) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixRotationAxis(axis.vec, angle);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreatePerspectiveFieldOfView(
		float fov,
		float aspectRatio,
		float nearPlane,
		float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreatePerspective(
		float width,
		float height,
		float nearPlane,
		float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixPerspectiveLH(width, height, nearPlane, farPlane);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreatePerspectiveOffCenter(
		float left,
		float right,
		float bottom,
		float top,
		float nearPlane,
		float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixPerspectiveOffCenterLH(
			left,
			right,
			bottom,
			top,
			nearPlane,
			farPlane
		);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateOrthographic(
		float width,
		float height,
		float zNearPlane,
		float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixOrthographicLH(
			width,
			height,
			zNearPlane,
			zFarPlane
		);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateOrthographicOffCenter(
		float left,
		float right,
		float bottom,
		float top,
		float zNearPlane,
		float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix toReturn;
		toReturn.mat = XMMatrixOrthographicOffCenterLH(
			left,
			right,
			bottom,
			top,
			zNearPlane,
			zFarPlane
		);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateLookAt(
		const Vector3 &position,
		const Vector3 &target,
		const Vector3 &up) noexcept
	{
		Matrix toReturn;
		toReturn.mat = DirectX::XMMatrixLookAtLH(position.vec, target.vec, up.vec);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up) noexcept {
		using namespace DirectX;
		const XMVECTOR zaxis = XMVector3Normalize(XMVectorNegate(forward.vec));
		XMVECTOR yaxis = up.vec;
		const XMVECTOR xaxis = XMVector3Normalize(XMVector3Cross(yaxis, zaxis));
		yaxis = XMVector3Cross(zaxis, xaxis);

		Matrix toReturn;
		toReturn.mat.r[0] = xaxis;
		toReturn.mat.r[1] = yaxis;
		toReturn.mat.r[2] = zaxis;
		toReturn.mat.r[3] = XMVectorSet(position.x, position.y, position.z, 1.f);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateFromQuaternion(const Quaternion &quat) noexcept {
		Matrix toReturn;
		toReturn.mat = DirectX::XMMatrixRotationQuaternion(quat.vec);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept {
		Matrix toReturn;
		toReturn.mat = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::CreateFromYawPitchRoll(const Vector3 &angles) noexcept {
		Matrix toReturn;
		toReturn.mat = DirectX::XMMatrixRotationRollPitchYawFromVector(angles.vec);
		return toReturn;
	}
	FORCEINLINE Matrix Matrix::Transform(const Matrix &M, const Quaternion &rotation) noexcept {
		using namespace DirectX;
		Matrix toReturn;
		const XMMATRIX M1 = XMMatrixRotationQuaternion(rotation.vec);
		toReturn.mat = XMMatrixMultiply(M.mat, M1);
		return toReturn;
	}
	FORCEINLINE Matrix lerp(const Matrix &M1, const Matrix &M2, float t) noexcept {
		Matrix toReturn;
		toReturn.mat.r[0] = DirectX::XMVectorLerp(M1.mat.r[0], M2.mat.r[0], t);
		toReturn.mat.r[1] = DirectX::XMVectorLerp(M1.mat.r[1], M2.mat.r[1], t);
		toReturn.mat.r[2] = DirectX::XMVectorLerp(M1.mat.r[2], M2.mat.r[2], t);
		toReturn.mat.r[3] = DirectX::XMVectorLerp(M1.mat.r[3], M2.mat.r[3], t);
		return toReturn;
	}
	FORCEINLINE Matrix operator+(const Matrix &M1, const Matrix &M2) noexcept {
		Matrix m1(M1);
		return m1 += M2;
	}
	FORCEINLINE Matrix operator-(const Matrix &M1, const Matrix &M2) noexcept {
		Matrix m1(M1);
		return m1 -= M2;
	}
	FORCEINLINE Matrix operator*(const Matrix &M1, const Matrix &M2) noexcept {
		Matrix m1(M1);
		return m1 *= M2;
	}
	FORCEINLINE Matrix operator/(const Matrix &M1, const Matrix &M2) noexcept {
		Matrix m1(M1);
		return m1 /= M2;
	}
	FORCEINLINE Matrix operator/(const Matrix &M, float S) noexcept {
		Matrix m(M);
		return m /= S;
	}
	FORCEINLINE Matrix operator*(const Matrix &M, float S) noexcept {
		Matrix m(M);
		return m *= S;
	}
	FORCEINLINE Matrix operator*(float S, const Matrix &M) noexcept {
		return M * S;
	}
	FORCEINLINE Vector4 operator*(const Matrix &m, const Vector4 &v4) noexcept {
		Vector4 toReturn;
		toReturn.vec = DirectX::XMVector4Transform(v4.vec, m.mat);
		return toReturn;
	}

	inline const Matrix Matrix::Identity{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};

#pragma endregion

#pragma region BoundingBoxImplement

	FORCEINLINE BoundingBox::BoundingBox(const Vector3 &min, const Vector3 &max) noexcept {
		auto extent = max - min;
		auto center = min + (extent / 2.f);
		static_cast<Base &>(*this) = Base(center.store(), extent.store());
	}
	FORCEINLINE BoundingBox::BoundingBox(const BoundingBox &lhs, const BoundingBox &rhs) noexcept {
		Base::CreateMerged(*this, lhs, rhs);
	}
	FORCEINLINE BoundingBox::BoundingBox(const BoundingSphere &boundingSphere) noexcept {
		Base::CreateFromSphere(*this, boundingSphere);
	}
	FORCEINLINE Vector3 BoundingBox::getCenter() const noexcept {
		return { Center.x, Center.y, Center.y };
	}
	FORCEINLINE Vector3 BoundingBox::getExtents() const noexcept {
		return { Extents.x, Extents.y, Extents.y };
	}
	FORCEINLINE void BoundingBox::setCenter(const Vector3 &center) {
		Center = center.store();
	}
	FORCEINLINE void BoundingBox::setExtents(const Vector3 &extents) {
		Extents = extents.store();
	}
	FORCEINLINE BoundingBox BoundingBox::transform(const Matrix &trans) const noexcept {
		BoundingBox toReturn;
		Base::Transform(toReturn, trans.mat);
		return toReturn;
	}
	FORCEINLINE BoundingBox BoundingBox::transform(
		float scale, 
		const Quaternion &rotate,
		const Vector3 &translation) const noexcept
	{
		BoundingBox toReturn;
		Base::Transform(toReturn, scale, rotate.vec, translation.vec);
		return toReturn;
	}
	FORCEINLINE DirectX::ContainmentType BoundingBox::contains(const BoundingBox &other) const noexcept {
		return Base::Contains(other);
	}
	FORCEINLINE std::array<float3, BoundingBox::kCornerCount> BoundingBox::getCorners() const noexcept {
		std::array<float3, BoundingBox::kCornerCount> toReturn;
		Base::GetCorners(toReturn.data());
		return toReturn;
	}
	FORCEINLINE void BoundingBox::getMinMax(Vector3 &min, Vector3 &max) const noexcept {
		auto center = getCenter();
		auto extents = getExtents();
		min = center - extents;
		max = center + extents;
	}
	FORCEINLINE std::pair<Vector3, Vector3> BoundingBox::getMinMax() const noexcept {
		std::pair<Vector3, Vector3> toReturn;
		getMinMax(toReturn.first, toReturn.second);
		return toReturn;
	}
	FORCEINLINE BoundingBox BoundingBox::CreateFromCenter(const float3 &center, const float3 &extents) noexcept {
		BoundingBox toReturn;
		toReturn.Center = center;
		toReturn.Extents = extents;
		return toReturn;
	}
	FORCEINLINE BoundingBox BoundingBox::CreateFromPoints(size_t count, const float3 *points, size_t stride) noexcept {
		BoundingBox toReturn;
		Base::CreateFromPoints(toReturn, count, points, stride);
		return toReturn;
	}
	FORCEINLINE BoundingBox BoundingBox::CreateMerged(const BoundingBox &b1, const BoundingBox &b2) noexcept {
		BoundingBox toReturn;
		Base::CreateMerged(toReturn, b1, b2);
		return toReturn;
	}
#pragma endregion

#pragma region BoundingSphereImplement

	FORCEINLINE BoundingSphere::BoundingSphere(const Vector3 &center, float radius) noexcept : Base(center.store(), radius) {
	}
	FORCEINLINE BoundingSphere::BoundingSphere(const BoundingSphere &lhs, const BoundingSphere &rhs) noexcept {
		Base::CreateMerged(*this, lhs, rhs);
	}
	FORCEINLINE BoundingSphere::BoundingSphere(size_t count, const float3 *points, size_t stride) noexcept {
		Base::CreateFromPoints(*this, count, points, stride);
	}
	FORCEINLINE BoundingSphere::BoundingSphere(const BoundingBox &boundingBox) noexcept {
		Base::CreateFromBoundingBox(*this, boundingBox);
	}
	FORCEINLINE BoundingSphere::BoundingSphere(const BoundingFrustum &boundingFrustum) noexcept {
		Base::CreateFromFrustum(*this, boundingFrustum);
	}
	FORCEINLINE Vector3 BoundingSphere::getCenter() const noexcept {
		return { Center.x, Center.y, Center.z };
	}
	FORCEINLINE float BoundingSphere::getRadius() const noexcept {
		return Radius;
	}
	FORCEINLINE void BoundingSphere::setCenter(const Vector3 &center) noexcept {
		Center = center.store();
	}
	FORCEINLINE void BoundingSphere::setRadius(float radius) noexcept {
		Radius = radius;
	}

#pragma endregion

#pragma region BoundingFrustumImplement

	FORCEINLINE BoundingFrustum::BoundingFrustum(const Vector3 &origin, const Quaternion &orientation, float rightSlope,
		float leftSlope, float topSlope, float bottomSlope, float zNear, float zFar) noexcept
	: Base(origin.store(), orientation.store(), rightSlope, leftSlope, topSlope, bottomSlope, zNear, zFar)
	{
	}
	FORCEINLINE BoundingFrustum::BoundingFrustum(const Matrix &projection) noexcept : Base(projection.mat) {
	}
	FORCEINLINE BoundingFrustum BoundingFrustum::transform(const Matrix &trans) const noexcept {
		BoundingFrustum toReturn;
		Base::Transform(toReturn, trans.mat);
		return toReturn;
	}
	FORCEINLINE BoundingFrustum BoundingFrustum::transform(
		float scale, 
		const Quaternion &rotate,
		const Vector3 &translation) const noexcept
	{
		BoundingFrustum toReturn;
		Base::Transform(toReturn, scale, rotate.vec, translation.vec);
		return toReturn;
	}
	FORCEINLINE std::array<float3, BoundingFrustum::kCornerCount> BoundingFrustum::getCorners() const noexcept {
		std::array<float3, BoundingFrustum::kCornerCount> toReturn;
		Base::GetCorners(toReturn.data());
		return toReturn;
	}
	FORCEINLINE DirectX::ContainmentType BoundingFrustum::contains(const BoundingBox &box) const noexcept {
		return Base::Contains(box);
	}

#pragma endregion

}
