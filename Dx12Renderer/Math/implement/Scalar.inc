#if 1
FORCEINLINE Scalar::Scalar(DX::XMVECTOR vec) noexcept : _vec(vec) {
}
FORCEINLINE Scalar::Scalar(float v) noexcept : _vec(DX::XMVectorSet(v, v, v, v)) {
}
FORCEINLINE Scalar::operator float() const noexcept {
	return  DX::XMVectorGetX(_vec);
}
FORCEINLINE DX::XMVECTOR *Scalar::operator&() noexcept {
	return &_vec;
}
FORCEINLINE const DX::XMVECTOR *Scalar::operator&() const noexcept {
	return &_vec;
}
FORCEINLINE Scalar::operator DX::XMVECTOR() const noexcept {
	return _vec;
}
FORCEINLINE Scalar operator- (Scalar s) noexcept {
	return Scalar(DX::XMVectorNegate(s));
}
FORCEINLINE Scalar operator+ (Scalar s1, Scalar s2) noexcept {
	return Scalar(DX::XMVectorAdd(s1, s2));
}
FORCEINLINE Scalar operator- (Scalar s1, Scalar s2) noexcept {
	return Scalar(DX::XMVectorSubtract(s1, s2));
}
FORCEINLINE Scalar operator* (Scalar s1, Scalar s2) noexcept {
	return Scalar(DX::XMVectorMultiply(s1, s2));
}
FORCEINLINE Scalar operator/ (Scalar s1, Scalar s2) noexcept {
	return Scalar(DX::XMVectorDivide(s1, s2));
}
FORCEINLINE Scalar operator+ (Scalar s1, float s2) noexcept {
	return s1 + Scalar(s2);
}
FORCEINLINE Scalar operator- (Scalar s1, float s2) noexcept {
	return s1 - Scalar(s2);
}
FORCEINLINE Scalar operator* (Scalar s1, float s2) noexcept {
	return s1 * Scalar(s2);
}
FORCEINLINE Scalar operator/ (Scalar s1, float s2) noexcept {
	return s1 / Scalar(s2);
}
FORCEINLINE Scalar operator+ (float s1, Scalar s2) noexcept {
	return Scalar(s1) + s2;
}
FORCEINLINE Scalar operator- (float s1, Scalar s2) noexcept {
	return Scalar(s1) - s2;
}
FORCEINLINE Scalar operator* (float s1, Scalar s2) noexcept {
	return Scalar(s1) * s2;
}
FORCEINLINE Scalar operator/ (float s1, Scalar s2) noexcept {
	return Scalar(s1) / s2;
}
#endif