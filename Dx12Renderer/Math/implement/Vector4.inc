#if 1
FORCEINLINE Vector4 operator+(const Vector4 &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorAdd(lhs, rhs);
}
FORCEINLINE Vector4 operator-(const Vector4 &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, rhs);
}
FORCEINLINE Vector4 operator*(const Vector4 &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, rhs);
}
FORCEINLINE Vector4 operator/(const Vector4 &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorDivide(lhs, rhs);
}
FORCEINLINE Vector4 operator+(const Vector4 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorAdd(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector4 operator-(const Vector4 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector4 operator*(const Vector4 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector4 operator/(const Vector4 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorDivide(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector4 operator+(const Scalar &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorAdd(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector4 operator-(const Scalar &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorSubtract(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector4 operator*(const Scalar &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorMultiply(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector4 operator/(const Scalar &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorDivide(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector4 operator+(const float &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorAdd(Vector4(lhs), rhs);
}
FORCEINLINE Vector4 operator-(const float &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorSubtract(Vector4(lhs), rhs);
}
FORCEINLINE Vector4 operator*(const float &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorMultiply(Vector4(lhs), rhs);
}
FORCEINLINE Vector4 operator/(const float &lhs, const Vector4 &rhs) noexcept {
	return DX::XMVectorDivide(Vector4(lhs), rhs);
}
FORCEINLINE Vector4 operator+(const Vector4 &lhs, const float &rhs) noexcept {
	return DX::XMVectorAdd(lhs, Vector4(rhs));
}
FORCEINLINE Vector4 operator-(const Vector4 &lhs, const float &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, Vector4(rhs));
}
FORCEINLINE Vector4 operator*(const Vector4 &lhs, const float &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, Vector4(rhs));
}
FORCEINLINE Vector4 operator/(const Vector4 &lhs, const float &rhs) noexcept {
	return DX::XMVectorDivide(lhs, Vector4(rhs));
}
FORCEINLINE Vector4 &operator+=(Vector4 &lhs, const Vector4 &rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator-=(Vector4 &lhs, const Vector4 &rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator*=(Vector4 &lhs, const Vector4 &rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator/=(Vector4 &lhs, const Vector4 &rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator+=(Vector4 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator-=(Vector4 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator*=(Vector4 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator/=(Vector4 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
}
FORCEINLINE Vector4 &operator+=(Vector4 &lhs, float rhs) noexcept {
	lhs = lhs + Vector4(rhs);
	return lhs;
}
FORCEINLINE Vector4 &operator-=(Vector4 &lhs, float rhs) noexcept {
	lhs = lhs - Vector4(rhs);
	return lhs;
}
FORCEINLINE Vector4 &operator*=(Vector4 &lhs, float rhs) noexcept {
	lhs = lhs * Vector4(rhs);
	return lhs;
}
FORCEINLINE Vector4 &operator/=(Vector4 &lhs, float rhs) noexcept {
	lhs = lhs / Vector4(rhs);
	return lhs;
}
FORCEINLINE Vector4 operator-(const Vector4 &v) noexcept {
	return DX::XMVectorNegate(v);
}
FORCEINLINE BoolVector operator<  (Vector4 lhs, Vector4 rhs) noexcept {
	return DX::XMVectorLess(lhs, rhs);
}
FORCEINLINE BoolVector operator<= (Vector4 lhs, Vector4 rhs) noexcept {
	return DX::XMVectorLessOrEqual(lhs, rhs);
}
FORCEINLINE BoolVector operator>  (Vector4 lhs, Vector4 rhs) noexcept {
	return DX::XMVectorGreater(lhs, rhs);
}
FORCEINLINE BoolVector operator>= (Vector4 lhs, Vector4 rhs) noexcept {
	return DX::XMVectorGreaterOrEqual(lhs, rhs);
}
FORCEINLINE BoolVector operator== (Vector4 lhs, Vector4 rhs) noexcept {
	return DX::XMVectorEqual(lhs, rhs);
}
FORCEINLINE Vector4 sqrt(Vector4 s) noexcept {
	return Vector4(DX::XMVectorSqrt(s));
}
FORCEINLINE Vector4 inverse(Vector4 s) noexcept {
	return Vector4(DX::XMVectorReciprocal(s));
}
FORCEINLINE Vector4 inverseSqrt(Vector4 s) noexcept {
	return Vector4(DX::XMVectorReciprocalSqrt(s));
}
FORCEINLINE Vector4 floor(Vector4 s) noexcept {
	return Vector4(DX::XMVectorFloor(s));
}
FORCEINLINE Vector4 ceil(Vector4 s) noexcept {
	return Vector4(DX::XMVectorCeiling(s));
}
FORCEINLINE Vector4 round(Vector4 s) noexcept {
	return Vector4(DX::XMVectorRound(s));
}
FORCEINLINE Vector4 abs(Vector4 s) noexcept {
	return Vector4(DX::XMVectorAbs(s));
}
FORCEINLINE Vector4 exp(Vector4 s) noexcept {
	return Vector4(DX::XMVectorExp(s));
}
FORCEINLINE Vector4 pow(Vector4 b, Vector4 e) noexcept {
	return Vector4(DX::XMVectorPow(b, e));
}
FORCEINLINE Vector4 log(Vector4 s) noexcept {
	return Vector4(DX::XMVectorLog(s));
}
FORCEINLINE Vector4 sin(Vector4 s) noexcept {
	return Vector4(DX::XMVectorSin(s));
}
FORCEINLINE Vector4 cos(Vector4 s) noexcept {
	return Vector4(DX::XMVectorCos(s));
}
FORCEINLINE Vector4 tan(Vector4 s) noexcept {
	return Vector4(DX::XMVectorTan(s));
}
FORCEINLINE Vector4 asin(Vector4 s) noexcept {
	return Vector4(DX::XMVectorASin(s));
}
FORCEINLINE Vector4 acos(Vector4 s) noexcept {
	return Vector4(DX::XMVectorACos(s));
}
FORCEINLINE Vector4 atan(Vector4 s) noexcept {
	return Vector4(DX::XMVectorATan(s));
}
FORCEINLINE Vector4 atan2(Vector4 y, Vector4 x) noexcept {
	return Vector4(DX::XMVectorATan2(y, x));
}
FORCEINLINE Vector4 lerp(Vector4 a, Vector4 b, Vector4 t) noexcept {
	return Vector4(DX::XMVectorLerpV(a, b, t));
}
FORCEINLINE Vector4 lerp(Vector4 a, Vector4 b, float t) noexcept {
	return Vector4(DX::XMVectorLerp(a, b, t));
}
FORCEINLINE Vector4 max(Vector4 a, Vector4 b) noexcept {
	return Vector4(DX::XMVectorMax(a, b));
}
FORCEINLINE Vector4 min(Vector4 a, Vector4 b) noexcept {
	return Vector4(DX::XMVectorMin(a, b));
}
FORCEINLINE Vector4 clamp(Vector4 v, Vector4 a, Vector4 b) noexcept {
	return min(max(v, a), b);
}
FORCEINLINE Scalar dot(const Vector4 & v1, const Vector4 & v2) noexcept {
	return Scalar(DX::XMVector4Dot(v1, v2));
}
FORCEINLINE Scalar length(const Vector4 & v) {
	return Scalar(DX::XMVector4Length(v));
}
FORCEINLINE Scalar lengthSquare(const Vector4 & v) {
	return Scalar(DX::XMVector4LengthSq(v));
}
FORCEINLINE Scalar inverseLength(const Vector4 & v) {
	return Scalar(DX::XMVector4ReciprocalLength(v));
}
FORCEINLINE Vector4::Vector4(const float3 &f3, float v) noexcept : Vector4(f3.x, f3.y, f3.z, v) {
}
FORCEINLINE Vector4::Vector4(const float4 &f4) noexcept : Vector4(f4.x, f4.y, f4.z, f4.w) {
}
FORCEINLINE Vector4::Vector4(DX::XMVECTOR vec) noexcept : vec(vec) {
}
FORCEINLINE Vector4::Vector4(const Scalar &s) noexcept {
	vec = DX::XMVECTOR(s);
}
FORCEINLINE Vector4::Vector4(float x, float y, float z, float w) noexcept {
	vec = DX::XMVectorSet(x, y, z, w);
}
FORCEINLINE Vector4::Vector4(float val) noexcept {
	vec = DX::XMVectorSet(val, val, val, val);
}
FORCEINLINE Vector4::Vector4(const Vector3 &v3, float w) noexcept : Vector4(v3.x, v3.y, v3.z, w) {
}
FORCEINLINE Vector4 &Vector4::operator=(const Vector4 &other) noexcept {
	vec = other.vec;
	return *this;
}
FORCEINLINE float &Vector4::operator[](size_t index) noexcept {
	assert(index < 4);
	return vec.m128_f32[index];
}
FORCEINLINE float Vector4::operator[](size_t index) const noexcept {
	assert(index < 4);
	return vec.m128_f32[index];
}
FORCEINLINE DX::XMVECTOR *Vector4::operator&() noexcept {
	return &vec;
}
FORCEINLINE const DX::XMVECTOR *Vector4::operator&() const noexcept {
	return &vec;
}
Vector4::operator DX::XMVECTOR() const noexcept {
	return vec;
}

FORCEINLINE Vector4::operator float2() const noexcept {
	return xy;
}

FORCEINLINE Vector4::operator float3() const noexcept {
	return xyz;
}
FORCEINLINE Vector4::operator float4() const noexcept {
	return xyzw;
}
FORCEINLINE std::ostream &operator<<(std::ostream &os, const Vector4 &v) noexcept {
	os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
	return os;
}
#endif