#if 1
FORCEINLINE Matrix3::Matrix3(const float3x3 &f3x3) noexcept {
	_mat[0] = Vector3(f3x3.m[0][0], f3x3.m[0][1], f3x3.m[0][2]);
	_mat[1] = Vector3(f3x3.m[1][0], f3x3.m[1][1], f3x3.m[1][2]);
	_mat[2] = Vector3(f3x3.m[2][0], f3x3.m[2][1], f3x3.m[2][2]);
}

FORCEINLINE Matrix3::Matrix3(const DX::XMMATRIX &mat) noexcept {
	_mat[0] = Vector3(mat.r[0]);
	_mat[1] = Vector3(mat.r[1]);
	_mat[2] = Vector3(mat.r[2]);
}
FORCEINLINE Matrix3::Matrix3(const Matrix4 &mat4) noexcept : Matrix3(static_cast<DX::XMMATRIX>(mat4)) {
}
FORCEINLINE Matrix3::Matrix3(const Vector3 &x, const Vector3 &y, const Vector3 &z) noexcept {
	_mat[0] = x;
	_mat[1] = y;
	_mat[2] = z;
}
FORCEINLINE void Matrix3::setX(const Vector3 &x) noexcept {
	_mat[0] = x;
}
FORCEINLINE void Matrix3::setY(const Vector3 &y) noexcept {
	_mat[1] = y;
}
FORCEINLINE void Matrix3::setZ(const Vector3 &z) noexcept {
	_mat[2] = z;
}
FORCEINLINE Vector3 Matrix3::getX() const noexcept {
	return _mat[0];
}
FORCEINLINE Vector3 Matrix3::getY() const noexcept {
	return _mat[1];
}
FORCEINLINE Vector3 Matrix3::getZ() const noexcept {
	return _mat[2];
}
FORCEINLINE Matrix3::operator DX::XMMATRIX() const noexcept {
	return DX::XMMATRIX(getX(), getY(), getZ(), Vector4(0.f, 0.f, 0.f, 1.f));
}
FORCEINLINE Matrix3::operator Matrix4() const noexcept {
	return Matrix4(static_cast<DX::XMMATRIX>(*this));
}
FORCEINLINE Matrix3::operator float3x3() const noexcept {
	return float3x3(
		_mat[0].x, _mat[0].y, _mat[0].z,
		_mat[1].x, _mat[1].y, _mat[1].z,
		_mat[2].x, _mat[2].y, _mat[2].z
	);
}
FORCEINLINE Vector3 &Matrix3::operator[](size_t index) noexcept {
	assert(index < 3);
	return _mat[index];
}
FORCEINLINE const Vector3 &Matrix3::operator[](size_t index) const noexcept {
	assert(index < 3);
	return _mat[index];
}
FORCEINLINE Matrix3 Matrix3::operator*(const Scalar &s) const noexcept {
	return Matrix3(
		getX() * s,
		getY() * s,
		getZ() * s
	);
}
FORCEINLINE Vector3 Matrix3::operator*(const Vector3 &v) const noexcept {
	return Vector3(DX::XMVector3TransformNormal(v, this->operator DX::XMMATRIX()));
}
FORCEINLINE Matrix3 Matrix3::operator*(const Matrix3 &mat) const noexcept {
	return Matrix3(
		*this * mat.getX(), 
		*this * mat.getY(), 
		*this * mat.getZ()
	);
}
FORCEINLINE Matrix3 Matrix3::makeZRotationByRadian(float radian) noexcept {
	return Matrix3(DX::XMMatrixRotationZ(radian));
}
FORCEINLINE Matrix3 Matrix3::makeXRotationByRadian(float radian) noexcept {
	return Matrix3(DX::XMMatrixRotationX(radian));
}
FORCEINLINE Matrix3 Matrix3::makeYRotationByRadian(float radian) noexcept {
	return Matrix3(DX::XMMatrixRotationY(radian));
}
FORCEINLINE Matrix3 Matrix3::makeZRotationByDegree(float angle) noexcept {
	return Matrix3(DX::XMMatrixRotationZ(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix3 Matrix3::makeXRotationByDegree(float angle) noexcept {
	return Matrix3(DX::XMMatrixRotationX(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix3 Matrix3::makeYRotationByDegree(float angle) noexcept {
	return Matrix3(DX::XMMatrixRotationY(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix3 Matrix3::makeAxisRotationByDegree(const Vector3 &axis, float angle) noexcept {
	return Matrix3(DX::XMMatrixRotationAxis(axis, DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix3 Matrix3::makeAxisRotationByRadian(const Vector3 &axis, float radian) noexcept {
	return Matrix3(DX::XMMatrixRotationAxis(axis, radian));
}
FORCEINLINE Matrix3 Matrix3::makeScale(float scale) noexcept {
	return Matrix3(DX::XMMatrixScaling(scale, scale, scale));
}
FORCEINLINE Matrix3 Matrix3::makeScale(float sx, float sy, float sz) noexcept {
	return Matrix3(DX::XMMatrixScaling(sx, sy, sz));
}
FORCEINLINE Matrix3 Matrix3::makeScale(const float3 &scale) noexcept {
	return Matrix3(DX::XMMatrixScaling(scale.x, scale.y, scale.z));
}
FORCEINLINE Matrix3 Matrix3::makeScale(const Vector3 &scale) noexcept {
	return Matrix3(DX::XMMatrixScaling(scale.x, scale.y, scale.z));
}
FORCEINLINE Matrix3 Matrix3::identity() noexcept {
	static Matrix3 identity(Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f));
	return identity;
}
FORCEINLINE Matrix3 transpose(const Matrix3 &mat3) noexcept {
	return Matrix3(DX::XMMatrixTranspose(static_cast<DX::XMMATRIX>(mat3)));
}
FORCEINLINE Scalar determinant(const Matrix3 &mat3) noexcept {
	return DX::XMMatrixDeterminant(static_cast<DX::XMMATRIX>(mat3));
}
FORCEINLINE Matrix3 inverse(const Matrix3 &mat3, const Scalar &det) noexcept {
	Scalar d = det;
	return Matrix3(DX::XMMatrixInverse(&d, static_cast<DX::XMMATRIX>(mat3)));
}
FORCEINLINE Matrix3 inverse(const Matrix3 &mat3) noexcept {
	Scalar det = determinant(mat3);
	return Matrix3(DX::XMMatrixInverse(&det, static_cast<DX::XMMATRIX>(mat3)));
}
#endif