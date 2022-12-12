FORCEINLINE FloatStore<4>::FloatStore(DX::FXMVECTOR v) noexcept {
	x = DX::XMVectorGetX(v);
	y = DX::XMVectorGetY(v);
	z = DX::XMVectorGetZ(v);
	w = DX::XMVectorGetW(v);
}
FORCEINLINE FloatStore<4>::FloatStore(const Vector4 &v4) noexcept {
	x = v4.x;
	y = v4.y;
	z = v4.z;
	w = v4.w;
}
FORCEINLINE FloatStore<4>::FloatStore(const FloatStore<2> &f2, float z, float w) noexcept : FloatStore(f2.x, f2.y, z, w) {
}
FORCEINLINE FloatStore<4>::FloatStore(const FloatStore<3> &f3, float w) noexcept : DX::XMFLOAT4(f3.x, f3.y, f3.z, w) {
}
FORCEINLINE float &FloatStore<4>::operator[](size_t n) noexcept {
	assert(n < 4);
	return reinterpret_cast<float *>(this)[n];
}
FORCEINLINE float FloatStore<4>::operator[](size_t n) const noexcept {
	assert(n < 4);
	return reinterpret_cast<const float *>(this)[n];
}

FORCEINLINE FloatStore<4>::FloatStore(const DX::XMVECTORF32 &color) noexcept
: FloatStore(color.operator DirectX::XMVECTOR()) {
}

FORCEINLINE FloatStore<4>::FloatStore(const Quaternion &q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

FORCEINLINE std::ostream &operator<<(std::ostream &os, const FloatStore<4> &v) noexcept {
	os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
	return os;
}
FORCEINLINE FloatStore<4> FloatStore<4>::operator-() const noexcept {
	return FloatStore(-x, -y, -z, -w);
}
FORCEINLINE FloatStore<4>::operator DX::XMVECTOR() const noexcept {
	return DX::XMLoadFloat4(this);
}
template<typename T> requires(std::is_convertible_v<T, float>)
FORCEINLINE FloatStore<4>::FloatStore(T v) noexcept : DX::XMFLOAT4(float(v), float(v), float(v), float(v)) {
}
template<typename T1, typename T2, typename T3, typename T4>
	requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float> &&
std::is_convertible_v<T3, float> &&std::is_convertible_v<T4, float>)
FORCEINLINE FloatStore<4>::FloatStore(T1 x, T2 y, T3 z, T4 w) noexcept : DX::XMFLOAT4(float(x), float(y), float(z), float(w)) {
}
template<size_t N> requires(N <= 4)
FORCEINLINE FloatStore<4>::operator FloatStore<N> &() noexcept {
	return reinterpret_cast<FloatStore<N> &>(*this);
}
template<size_t N> requires(N <= 4)
FORCEINLINE FloatStore<4>::operator const FloatStore<N> &() const noexcept {
	return reinterpret_cast<const FloatStore<N> &>(*this);
}

FORCEINLINE const FloatStore<4> & FloatStore<4>::one() noexcept {
	static FloatStore<4> object(1.f);
	return object;
}

FORCEINLINE const FloatStore<4> & FloatStore<4>::zero() noexcept {
	static FloatStore<4> object(0.f);
	return object;
}

FORCEINLINE const FloatStore<4> & FloatStore<4>::QuaternionIdentity() noexcept {
	static float4 object(0.f, 0.f, 0.f, 1.f);
	return object;
}

FORCEINLINE bool operator==(const FloatStore<4> &lhs, const FloatStore<4> &rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

FORCEINLINE bool operator!=(const FloatStore<4> &lhs, const FloatStore<4> &rhs) {
	return !(lhs == rhs);
}