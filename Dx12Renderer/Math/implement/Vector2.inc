#if 1
FORCEINLINE Vector2::Vector2(float x, float y) noexcept : x(x), y(y) {
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
FORCEINLINE float &Vector2::operator[](size_t index) noexcept {
	assert(index < 2);
	return reinterpret_cast<float *>(this)[index];
}
FORCEINLINE float Vector2::operator[](size_t index) const noexcept {
	assert(index < 2);
	return reinterpret_cast<const float *>(this)[index];
}

FORCEINLINE Vector2::operator float2() const noexcept {
	return xy;
}
FORCEINLINE std::ostream &operator<<(std::ostream &os, const Vector2 &v) noexcept {
	os << '(' << v.x << ", " << v.y << ')';
	return os;
}
FORCEINLINE Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}
FORCEINLINE Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}
FORCEINLINE Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}
FORCEINLINE Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
}
FORCEINLINE Vector2 operator+(const float &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs + rhs.x, lhs + rhs.y);
}
FORCEINLINE Vector2 operator-(const float &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs - rhs.x, lhs - rhs.y);
}
FORCEINLINE Vector2 operator*(const float &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}
FORCEINLINE Vector2 operator/(const float &lhs, const Vector2 &rhs) noexcept {
	return Vector2(lhs / rhs.x, lhs / rhs.y);
}
FORCEINLINE Vector2 operator+(const Vector2 &lhs, const float &rhs) noexcept {
	return Vector2(lhs.x + rhs, lhs.y + rhs);
}
FORCEINLINE Vector2 operator-(const Vector2 &lhs, const float &rhs) noexcept {
	return Vector2(lhs.x - rhs, lhs.y - rhs);
}
FORCEINLINE Vector2 operator*(const Vector2 &lhs, const float &rhs) noexcept {
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}
FORCEINLINE Vector2 operator/(const Vector2 &lhs, const float &rhs) noexcept {
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}
FORCEINLINE Vector2 &operator+=(Vector2 &lhs, const Vector2 &rhs) noexcept {
	lhs = lhs + rhs;
	return lhs;
}
FORCEINLINE Vector2 &operator-=(Vector2 &lhs, const Vector2 &rhs) noexcept {
	lhs = lhs - rhs;
	return lhs;
}
FORCEINLINE Vector2 &operator*=(Vector2 &lhs, const Vector2 &rhs) noexcept {
	lhs = lhs * rhs;
	return lhs;
}
FORCEINLINE Vector2 &operator/=(Vector2 &lhs, const Vector2 &rhs) noexcept {
	lhs = lhs / rhs;
	return lhs;
}
FORCEINLINE Vector2 &operator+=(Vector2 &lhs, float rhs) noexcept {
	lhs = lhs + Vector2(rhs);
	return lhs;
}
FORCEINLINE Vector2 &operator-=(Vector2 &lhs, float rhs) noexcept {
	lhs = lhs - Vector2(rhs);
	return lhs;
}
FORCEINLINE Vector2 &operator*=(Vector2 &lhs, float rhs) noexcept {
	lhs = lhs * Vector2(rhs);
	return lhs;
}
FORCEINLINE Vector2 &operator/=(Vector2 &lhs, float rhs) noexcept {
	lhs = lhs / Vector2(rhs);
	return lhs;
}
FORCEINLINE Vector2 operator-(const Vector2 &v) noexcept {
	return Vector2(-v.x, -v.y);
}
FORCEINLINE Vector2 sqrt(const Vector2 &v) noexcept {
	return Vector2(std::sqrt(v.x), std::sqrt(v.y));
}
FORCEINLINE Vector2 inverse(const Vector2 &v) noexcept {
	return Vector2(1.f / v.x, 1.f / v.y);
}
FORCEINLINE Vector2 inverseSqrt(const Vector2 &v) noexcept {
	return Vector2(1.f / std::sqrt(v.x), 1.f / std::sqrt(v.y));
}
FORCEINLINE Vector2 floor(const Vector2 &v) noexcept {
	return Vector2(std::floor(v.x), std::floor(v.y));
}
FORCEINLINE Vector2 ceil(const Vector2 &v) noexcept {
	return Vector2(std::ceil(v.x), std::ceil(v.y));
}
FORCEINLINE Vector2 round(const Vector2 &v) noexcept {
	return Vector2(std::round(v.x), std::round(v.y));
}
FORCEINLINE Vector2 abs(const Vector2 &v) noexcept {
	return Vector2(std::abs(v.x), std::abs(v.y));
}
FORCEINLINE Vector2 exp(const Vector2 &v) noexcept {
	return Vector2(std::exp(v.x), std::exp(v.y));
}
FORCEINLINE Vector2 pow(const Vector2 &b, const Vector2 &e) noexcept {
	return Vector2(std::pow(b.x, e.x), std::pow(b.y, e.y));
}
FORCEINLINE Vector2 log(const Vector2 &v) noexcept {
	return Vector2(std::log(v.x), std::log(v.y));
}
FORCEINLINE Vector2 sin(const Vector2 &v) noexcept {
	return Vector2(std::sin(v.x), std::sin(v.y));
}
FORCEINLINE Vector2 cos(const Vector2 &v) noexcept {
	return Vector2(std::cos(v.x), std::cos(v.y));
}
FORCEINLINE Vector2 tan(const Vector2 &v) noexcept {
	return Vector2(std::tan(v.x), std::tan(v.y));
}
FORCEINLINE Vector2 asin(const Vector2 &v) noexcept {
	return Vector2(std::asin(v.x), std::asin(v.y));
}
FORCEINLINE Vector2 acos(const Vector2 &v) noexcept {
	return Vector2(std::acos(v.x), std::acos(v.y));
}
FORCEINLINE Vector2 atan(const Vector2 &v) noexcept {
	return Vector2(std::atan(v.x), std::atan(v.y));
}
FORCEINLINE Vector2 atan2(const Vector2 y, const Vector2 x) noexcept {
	return Vector2(std::atan2(y.x, x.x), std::atan2(y.y, x.y));
}
FORCEINLINE Vector2 lerp(const Vector2 &a, const Vector2 &b, const Vector2 &t) noexcept {
	return Vector2(
		(a.x * (1.f - t.x)) + b.x * t.x,
		(a.y * (1.f - t.y)) + b.y * t.y
	);
}
FORCEINLINE Vector2 lerp(const Vector2 &a, const Vector2 &b, float t) noexcept {
	return Vector2(
		(a.x * (1.f - t)) + b.x * t,
		(a.y * (1.f - t)) + b.y * t
	);
}
FORCEINLINE Vector2 max(const Vector2 &a, const Vector2 &b) noexcept {
	return Vector2(
		std::max(a.x, b.x),
		std::max(a.y, b.y)
	);
}
FORCEINLINE Vector2 min(const Vector2 &a, const Vector2 &b) noexcept {
	return Vector2(
		std::min(a.x, b.x),
		std::min(a.y, b.y)
	);
}
FORCEINLINE Vector2 clamp(const Vector2 &v, const Vector2 &a, const Vector2 &b) noexcept {
	return Vector2(
		std::clamp(v.x, a.x, b.x),
		std::clamp(v.y, a.y, b.y)
	);
}
FORCEINLINE float dot(const Vector2 &v1, const Vector2 &v2) noexcept {
	return v1.x * v2.x + v1.y * v2.y;
}
FORCEINLINE float lengthSquare(const Vector2 &v) {
	return v.x * v.x + v.y * v.y;
}
FORCEINLINE float length(const Vector2 &v) {
	float lengthSqr = lengthSquare(v);
	if (lengthSqr > 0.f)
		return std::sqrt(lengthSqr);
	else
		return 0.f;
}
FORCEINLINE float inverseLength(const Vector2 &v) {
	return 1.f / length(v);
}
FORCEINLINE Vector2 normalize(const Vector2 &v) noexcept {
	float lengthSqr = lengthSquare(v);;
	if (lengthSqr > 0.f)
		return v / std::sqrt(lengthSqr);
	else
		return Vector2(0.f);
}
#endif