FORCEINLINE FloatStore<2>::FloatStore(DX::FXMVECTOR v) noexcept {
	x = DX::XMVectorGetX(v);
	y = DX::XMVectorGetY(v);
}
FORCEINLINE FloatStore<2>::FloatStore(const Vector3 &vec) noexcept {
	x = vec.x;
	y = vec.y;
}
FORCEINLINE FloatStore<2>::FloatStore(const Vector4 &vec) noexcept {
	x = vec.x;
	y = vec.y;
}
FORCEINLINE float &FloatStore<2>::operator[](size_t n) noexcept {
	assert(n < 2);
	return reinterpret_cast<float *>(this)[n];
}
FORCEINLINE float FloatStore<2>::operator[](size_t n) const noexcept {
	assert(n < 2);
	return reinterpret_cast<const float *>(this)[n];
}
FORCEINLINE std::ostream &operator<<(std::ostream &os, const FloatStore<2> &v) noexcept {
	os << '(' << v.x << ", " << v.y << ')';
	return os;
}
FORCEINLINE FloatStore<2> FloatStore<2>::operator-() const noexcept {
	return FloatStore(-x, -y);
}
FORCEINLINE FloatStore<2>::operator DX::XMVECTOR() const noexcept {
	return DX::XMVectorSet(x, y, 0.f, 0.f);
}
template<typename T> requires(std::is_convertible_v<T, float>)
FORCEINLINE FloatStore<2>::FloatStore(T v) noexcept : DX::XMFLOAT2(static_cast<float>(v), static_cast<float>(v)) {
}
template<typename T1, typename T2>
	requires(std::is_convertible_v<T1, float> &&std::is_convertible_v<T2, float>)
FORCEINLINE FloatStore<2>::FloatStore(T1 x, T2 y) noexcept : DX::XMFLOAT2(float(x), float(y)) {
}

FORCEINLINE const FloatStore<2> &FloatStore<2>::identity() noexcept {
	static FloatStore<2> object(1.f);
	return object;
}

FORCEINLINE const FloatStore<2> &FloatStore<2>::zero() noexcept {
	static FloatStore<2> object(0.f);
	return object;
}