
FORCEINLINE Quaternion::Quaternion() noexcept {
	_vec = DX::XMQuaternionIdentity();
}

FORCEINLINE Quaternion::Quaternion(const Vector3 &axis, float radian) noexcept {
	_vec = DX::XMQuaternionRotationAxis(axis, radian);
}

FORCEINLINE Quaternion::Quaternion(const float3 &axis, float radian) noexcept : Quaternion(Vector3{ axis }, radian) {

}

FORCEINLINE Quaternion::Quaternion(float pitch, float yaw, float roll) noexcept {
	_vec = DX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
}

FORCEINLINE Quaternion::Quaternion(float x, float y, float z, float w) noexcept {
	_vec = DX::XMVectorSet(x, y, z, w);
}

FORCEINLINE Quaternion::Quaternion(const float4 &f4) noexcept {
	_vec = DX::XMLoadFloat4(&f4);
}

FORCEINLINE Quaternion::Quaternion(const Matrix3 &matrix) noexcept {
	_vec = XMQuaternionRotationMatrix(matrix.operator DX::XMMATRIX());
}

FORCEINLINE Quaternion::Quaternion(DX::FXMVECTOR vec) noexcept {
	_vec = vec;
}

FORCEINLINE Quaternion::operator DX::XMVECTOR() const noexcept {
	return _vec;
}

FORCEINLINE Quaternion::operator float4() const noexcept {
	return *reinterpret_cast<const float4 *>(this);
}

FORCEINLINE Quaternion::operator Matrix3() const noexcept {
	return Matrix3(DX::XMMatrixRotationQuaternion(_vec));
}

FORCEINLINE Quaternion::operator Matrix4() const noexcept {
	return Matrix4(DX::XMMatrixRotationQuaternion(_vec));
}

FORCEINLINE Quaternion Quaternion::operator~() const noexcept {
	return Quaternion(DX::XMQuaternionConjugate(_vec));
}

FORCEINLINE Quaternion Quaternion::operator*(const Quaternion &rhs) const noexcept {
	return Quaternion(DX::XMQuaternionMultiply(rhs._vec, _vec));
}

FORCEINLINE Vector3 Quaternion::operator*(const Vector3 &rhs) const noexcept {
	return Vector3(DX::XMVector3Rotate(rhs.vec, _vec));
}

FORCEINLINE Quaternion &Quaternion::operator=(const Quaternion &rhs) noexcept {
	_vec = rhs._vec;
	return *this;
}

FORCEINLINE Quaternion &Quaternion::operator*=(const Quaternion &rhs) noexcept {
	*this = *this * rhs;
	return *this;
}

FORCEINLINE DX::XMVECTOR * Quaternion::operator&() noexcept {
	return &_vec;
}

FORCEINLINE const Quaternion & Quaternion::identity() noexcept {
	static Quaternion object(0.f, 0.f, 0.f, 1.f);
	return object;
}

FORCEINLINE BoolVector operator==(const Quaternion &lhs, const Quaternion &rhs) noexcept {
	return BoolVector(DX::XMVectorEqual(lhs._vec, rhs._vec));
}

FORCEINLINE BoolVector operator!=(const Quaternion &lhs, const Quaternion &rhs) noexcept {
	return BoolVector(DX::XMVectorEqual(lhs._vec, rhs._vec));
}

FORCEINLINE Quaternion normalize(const Quaternion &q) noexcept {
	return Quaternion(DX::XMQuaternionNormalize(q._vec));
}

FORCEINLINE Quaternion inverse(const Quaternion &q) noexcept {
	return Quaternion(DX::XMQuaternionInverse(q._vec));
}

FORCEINLINE Quaternion slerp(const Quaternion &lhs, const Quaternion &rhs, float t) noexcept {
	return normalize(Quaternion(DX::XMQuaternionSlerp(lhs._vec, rhs._vec, t)));
}

FORCEINLINE Quaternion lerp(const Quaternion &lhs, const Quaternion &rhs, float t) noexcept {
	return normalize(Quaternion(DX::XMVectorLerp(lhs._vec, rhs._vec, t)));
}

FORCEINLINE Quaternion conjugate(const Quaternion &q) noexcept {
	return Quaternion(DX::XMQuaternionConjugate(q._vec));
}

FORCEINLINE std::ostream & operator<<(std::ostream &os, const Quaternion &q) noexcept {
	os << '(' << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ')';
	return os;
}