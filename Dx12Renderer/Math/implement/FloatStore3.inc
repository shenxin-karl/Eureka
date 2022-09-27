FORCEINLINE FloatStore<3>::FloatStore(const Vector3 &vec) noexcept {
	*this = vec.operator float3();
}
FORCEINLINE FloatStore<3>::FloatStore(const Vector4 &vec) noexcept {
	*this = vec.operator float3();
}
FORCEINLINE FloatStore<3>::FloatStore(const FloatStore<2> &f2, float z) noexcept : FloatStore(f2.x, f2.y, z) {
}
FORCEINLINE FloatStore<3>::FloatStore(DX::FXMVECTOR v) noexcept {
	x = DX::XMVectorGetX(v);
	y = DX::XMVectorGetY(v);
	z = DX::XMVectorGetZ(v);
}
template<typename T> requires(std::is_convertible_v<T, float>)
FORCEINLINE FloatStore<3>::FloatStore(T v)
	: XMFLOAT3(float(v), float(v), float(v)) {

}
template<typename T1, typename T2, typename T3>
	requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float> &&
std::is_convertible_v<T3, float>)
FORCEINLINE FloatStore<3>::FloatStore(T1 x, T2 y, T3 z) noexcept
	: DX::XMFLOAT3(float(x), float(y), float(z)) {

}
template<size_t N> requires(N <= 3)
FORCEINLINE FloatStore<3>::operator FloatStore<N> &() noexcept {
	return reinterpret_cast<FloatStore<N> &>(*this);
}
template<size_t N> requires(N <= 3)
FORCEINLINE FloatStore<3>::operator const FloatStore<N> &() const noexcept {
	return reinterpret_cast<const FloatStore<N> &>(*this);
}
FORCEINLINE FloatStore<3>::FloatStore(const DX::XMFLOAT3 &f3) noexcept : DX::XMFLOAT3(f3) {
}
FORCEINLINE float &FloatStore<3>::operator[](size_t n) noexcept {
	assert(n < 3);
	return reinterpret_cast<float *>(this)[n];
}
FORCEINLINE float FloatStore<3>::operator[](size_t n) const noexcept {
	assert(n < 3);
	return reinterpret_cast<const float *>(this)[n];
}
FORCEINLINE FloatStore<3>::FloatStore(const DX::XMVECTORF32 &color) noexcept
: FloatStore(color.operator DirectX::XMVECTOR()) {
}
FORCEINLINE std::ostream &operator<<(std::ostream &os, const FloatStore<3> &v) noexcept {
	os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return os;
}
FloatStore<3> FloatStore<3>::operator-() const noexcept {
	return FloatStore(-x, -y, -z);
}
FORCEINLINE FloatStore<3>::operator DX::XMVECTOR() const noexcept {
	return DX::XMVectorSet(x, y, z, 0.f);
}

FORCEINLINE const FloatStore<3> & FloatStore<3>::identity() noexcept {
	static FloatStore<3> object(1.f);
	return object;
}

FORCEINLINE const FloatStore<3> & FloatStore<3>::zero() noexcept {
	static FloatStore<3> object(0.f);
	return object;
}