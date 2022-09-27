#if 1
FORCEINLINE Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorAdd(lhs, rhs);
}
FORCEINLINE Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, rhs);
}
FORCEINLINE Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, rhs);
}
FORCEINLINE Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorDivide(lhs, rhs);
}
FORCEINLINE Vector3 operator+(const Vector3 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorAdd(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector3 operator-(const Vector3 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector3 operator*(const Vector3 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector3 operator/(const Vector3 &lhs, const Scalar &rhs) noexcept {
	return DX::XMVectorDivide(lhs, DX::XMVECTOR(rhs));
}
FORCEINLINE Vector3 operator+(const Scalar &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorAdd(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector3 operator-(const Scalar &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorSubtract(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector3 operator*(const Scalar &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorMultiply(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector3 operator/(const Scalar &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorDivide(DX::XMVECTOR(lhs), rhs);
}
FORCEINLINE Vector3 operator+(const float &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorAdd(Vector3(lhs), rhs);
}
FORCEINLINE Vector3 operator-(const float &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorSubtract(Vector3(lhs), rhs);
}
FORCEINLINE Vector3 operator*(const float &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorMultiply(Vector3(lhs), rhs);
}
FORCEINLINE Vector3 operator/(const float &lhs, const Vector3 &rhs) noexcept {
	return DX::XMVectorDivide(Vector3(lhs), rhs);
}
FORCEINLINE Vector3 operator+(const Vector3 &lhs, const float &rhs) noexcept {
	return DX::XMVectorAdd(lhs, Vector3(rhs));
}
FORCEINLINE Vector3 operator-(const Vector3 &lhs, const float &rhs) noexcept {
	return DX::XMVectorSubtract(lhs, Vector3(rhs));
}
FORCEINLINE Vector3 operator*(const Vector3 &lhs, const float &rhs) noexcept {
	return DX::XMVectorMultiply(lhs, Vector3(rhs));
}
FORCEINLINE Vector3 operator/(const Vector3 &lhs, const float &rhs) noexcept {
	return DX::XMVectorDivide(lhs, Vector3(rhs));
}
FORCEINLINE Vector3 &operator+=(Vector3 &lhs, const Vector3 &rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator-=(Vector3 &lhs, const Vector3 &rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator*=(Vector3 &lhs, const Vector3 &rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator/=(Vector3 &lhs, const Vector3 &rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator+=(Vector3 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator-=(Vector3 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator*=(Vector3 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator/=(Vector3 &lhs, const Scalar &rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
}
FORCEINLINE Vector3 &operator+=(Vector3 &lhs, float rhs) noexcept {
	lhs = lhs + Vector3(rhs);
	return lhs;
}
FORCEINLINE Vector3 &operator-=(Vector3 &lhs, float rhs) noexcept {
	lhs = lhs - Vector3(rhs);
	return lhs;
}
FORCEINLINE Vector3 &operator*=(Vector3 &lhs, float rhs) noexcept {
	lhs = lhs * Vector3(rhs);
	return lhs;
}
FORCEINLINE Vector3 &operator/=(Vector3 &lhs, float rhs) noexcept {
	lhs = lhs / Vector3(rhs);
	return lhs;
}
FORCEINLINE Vector3 operator-(const Vector3 &v) noexcept {
	return DX::XMVectorNegate(v);
}
FORCEINLINE BoolVector operator<  (Vector3 lhs, Vector3 rhs) noexcept {
	return DX::XMVectorLess(lhs, rhs);
}
FORCEINLINE BoolVector operator<= (Vector3 lhs, Vector3 rhs) noexcept {
	return DX::XMVectorLessOrEqual(lhs, rhs);
}
FORCEINLINE BoolVector operator>  (Vector3 lhs, Vector3 rhs) noexcept {
	return DX::XMVectorGreater(lhs, rhs);
}
FORCEINLINE BoolVector operator>= (Vector3 lhs, Vector3 rhs) noexcept {
	return DX::XMVectorGreaterOrEqual(lhs, rhs);
}
FORCEINLINE BoolVector operator== (Vector3 lhs, Vector3 rhs) noexcept {
	return DX::XMVectorEqual(lhs, rhs);
}
FORCEINLINE Vector3 sqrt(Vector3 s) noexcept {
	return Vector3(DX::XMVectorSqrt(s));
}
FORCEINLINE Vector3 inverse(Vector3 s) noexcept {
	return Vector3(DX::XMVectorReciprocal(s));
}
FORCEINLINE Vector3 inverseSqrt(Vector3 s) noexcept {
	return Vector3(DX::XMVectorReciprocalSqrt(s));
}
FORCEINLINE Vector3 floor(Vector3 s) noexcept {
	return Vector3(DX::XMVectorFloor(s));
}
FORCEINLINE Vector3 ceil(Vector3 s) noexcept {
	return Vector3(DX::XMVectorCeiling(s));
}
FORCEINLINE Vector3 round(Vector3 s) noexcept {
	return Vector3(DX::XMVectorRound(s));
}
FORCEINLINE Vector3 abs(Vector3 s) noexcept {
	return Vector3(DX::XMVectorAbs(s));
}
FORCEINLINE Vector3 exp(Vector3 s) noexcept {
	return Vector3(DX::XMVectorExp(s));
}
FORCEINLINE Vector3 pow(Vector3 b, Vector3 e) noexcept {
	return Vector3(DX::XMVectorPow(b, e));
}
FORCEINLINE Vector3 log(Vector3 s) noexcept {
	return Vector3(DX::XMVectorLog(s));
}
FORCEINLINE Vector3 sin(Vector3 s) noexcept {
	return Vector3(DX::XMVectorSin(s));
}
FORCEINLINE Vector3 cos(Vector3 s) noexcept {
	return Vector3(DX::XMVectorCos(s));
}
FORCEINLINE Vector3 tan(Vector3 s) noexcept {
	return Vector3(DX::XMVectorTan(s));
}
FORCEINLINE Vector3 asin(Vector3 s) noexcept {
	return Vector3(DX::XMVectorASin(s));
}
FORCEINLINE Vector3 acos(Vector3 s) noexcept {
	return Vector3(DX::XMVectorACos(s));
}
FORCEINLINE Vector3 atan(Vector3 s) noexcept {
	return Vector3(DX::XMVectorATan(s));
}
FORCEINLINE Vector3 atan2(Vector3 y, Vector3 x) noexcept {
	return Vector3(DX::XMVectorATan2(y, x));
}
FORCEINLINE Vector3 lerp(Vector3 a, Vector3 b, Vector3 t) noexcept {
	return Vector3(DX::XMVectorLerpV(a, b, t));
}
FORCEINLINE Vector3 lerp(Vector3 a, Vector3 b, float t) noexcept {
	return Vector3(DX::XMVectorLerp(a, b, t));
}
FORCEINLINE Vector3 max(Vector3 a, Vector3 b) noexcept {
	return Vector3(DX::XMVectorMax(a, b));
}
FORCEINLINE Vector3 min(Vector3 a, Vector3 b) noexcept {
	return Vector3(DX::XMVectorMin(a, b));
}
FORCEINLINE Vector3 clamp(Vector3 v, Vector3 a, Vector3 b) noexcept {
	return min(max(v, a), b);
}
FORCEINLINE Vector3 normalize(const Vector3 &v) noexcept {
	return DX::XMVector3Normalize(v);
}
FORCEINLINE Scalar dot(const Vector3 &v1, const Vector3 &v2) noexcept {
	return Scalar(DX::XMVector3Dot(v1, v2));
}
FORCEINLINE Vector3 cross(const Vector3 &v0, const Vector3 &v1) {
	return Vector3(DX::XMVector3Cross(v0, v1));
}
FORCEINLINE Scalar length(const Vector3 &v) {
	return Scalar(DX::XMVector3Length(v));
}
FORCEINLINE Scalar lengthSquare(const Vector3 &v) {
	return Scalar(DX::XMVector3LengthSq(v));
}
FORCEINLINE Scalar inverseLength(const Vector3 &v) {
	return Scalar(DX::XMVector3ReciprocalLength(v));
}
FORCEINLINE Vector3::Vector3(const float2 &f2, float v) noexcept : Vector3(f2.x, f2.y, v) {
}

FORCEINLINE Vector3::Vector3(const float3 &f3) noexcept : Vector3(f3.x, f3.y, f3.z) {
}
FORCEINLINE Vector3::Vector3(DX::XMVECTOR vec) noexcept : vec(vec) {
}
FORCEINLINE Vector3::Vector3(const Scalar &s) noexcept : vec(s) {
}
FORCEINLINE Vector3::Vector3(float x, float y, float z) noexcept {
	vec = DX::XMVectorSet(x, y, z, 0.0);
}
FORCEINLINE Vector3::Vector3(const Vector4 &v4) noexcept {
	vec = v4.vec;
}
FORCEINLINE Vector3::Vector3(float val) noexcept {
	vec = DX::XMVectorSet(val, val, val, 0.0);
}
FORCEINLINE Vector3 &Vector3::operator=(const Vector3 &other) noexcept {
	vec = other.vec;
	return *this;
}
FORCEINLINE float &Vector3::operator[](size_t index) noexcept {
	assert(index < 3);
	return vec.m128_f32[index];
}
FORCEINLINE float Vector3::operator[](size_t index) const noexcept {
	assert(index < 3);
	return vec.m128_f32[index];
}
FORCEINLINE DX::XMVECTOR *Vector3::operator&() noexcept {
	return &vec;
}
FORCEINLINE const DX::XMVECTOR *Vector3::operator&() const noexcept {
	return &vec;
}
FORCEINLINE Vector3::operator DX::XMVECTOR() const noexcept {
	return vec;
}

FORCEINLINE Vector3::operator float2() const noexcept {
	return xy;
}

FORCEINLINE Vector3::operator float3() const noexcept {
	return xyz;
}

FORCEINLINE const Vector3 & Vector3::identity() noexcept {
	static Vector3 obj(1.f, 1.f, 1.f);
	return obj;
}

FORCEINLINE const Vector3 & Vector3::zero() noexcept {
	static Vector3 obj(0.f, 0.f, 0.f);
	return obj;
}

FORCEINLINE std::ostream &operator<<(std::ostream &os, const Vector3 &v) noexcept {
	os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return os;
}
#endif