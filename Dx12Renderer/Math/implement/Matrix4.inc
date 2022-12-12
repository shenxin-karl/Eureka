#if 1
FORCEINLINE Matrix4::Matrix4(const DX::XMMATRIX &mat) noexcept : _mat(mat) {
}
FORCEINLINE Matrix4::Matrix4(const float4x4 &f4x4) noexcept {
	_mat = DX::XMLoadFloat4x4(&f4x4);
}
FORCEINLINE Matrix4::Matrix4(const Matrix3 &mat3) noexcept {
	_mat = mat3.operator DX::XMMATRIX();
}
FORCEINLINE Matrix4::Matrix4(const float *data) noexcept {
	_mat = DX::XMLoadFloat4x4(reinterpret_cast<const DX::XMFLOAT4X4 *>(data));
}
FORCEINLINE Matrix4::Matrix4(const Vector3 &x, const Vector3 &y, const Vector3 &z, const Vector3 &w) noexcept {
	_mat.r[0] = x;
	_mat.r[1] = y;
	_mat.r[2] = z;
	_mat.r[3] = w;
}
FORCEINLINE Matrix4::Matrix4(const Vector4 &x, const Vector4 &y, const Vector4 &z, const Vector4 &w) noexcept {
	_mat.r[0] = x;
	_mat.r[1] = y;
	_mat.r[2] = z;
	_mat.r[3] = w;
}
FORCEINLINE const Matrix3 &Matrix4::get3x3() const noexcept {
	return reinterpret_cast<const Matrix3 &>(*this);
}
FORCEINLINE void Matrix4::set3x3(const Matrix3 &xyz) noexcept {
	_mat.r[0] = xyz.getX();
	_mat.r[1] = xyz.getY();
	_mat.r[2] = xyz.getZ();
}
FORCEINLINE Vector4 Matrix4::getX() const noexcept {
	return _mat.r[0];
}
FORCEINLINE Vector4 Matrix4::getY() const noexcept {
	return _mat.r[1];
}
FORCEINLINE Vector4 Matrix4::getZ() const noexcept {
	return _mat.r[2];
}
FORCEINLINE Vector4 Matrix4::getW() const noexcept {
	return _mat.r[3];
}
FORCEINLINE void Matrix4::setX(Vector4 x) noexcept {
	_mat.r[0] = x;
}
FORCEINLINE void Matrix4::setY(Vector4 y) noexcept {
	_mat.r[1] = y;
}
FORCEINLINE void Matrix4::setZ(Vector4 z) noexcept {
	_mat.r[2] = z;
}
FORCEINLINE void Matrix4::setW(Vector4 w) noexcept {
	_mat.r[3] = w;
}
FORCEINLINE Matrix4::operator DirectX::XMMATRIX() const noexcept {
	return _mat;
}
FORCEINLINE Matrix4::operator float3x3() const noexcept {
	float3x3 res;
	DX::XMStoreFloat3x3(&res, _mat);
	return res;
}
FORCEINLINE Matrix4::operator float4x3() const noexcept {
	float4x3 res;
	DX::XMStoreFloat4x3(&res, _mat);
	return res;
}
FORCEINLINE Matrix4::operator float4x4() const noexcept {
	float4x4 res;
	DX::XMStoreFloat4x4(&res, _mat);
	return res;
}
FORCEINLINE DX::XMMATRIX *Matrix4::operator&() noexcept {
	return &_mat;
}
FORCEINLINE const DX::XMMATRIX *Matrix4::operator&() const noexcept {
	return &_mat;
}
FORCEINLINE Vector4 Matrix4::operator*(const Vector3 &vec) const noexcept {
	return Vector4(DX::XMVector3Transform(vec, _mat));
}
FORCEINLINE Vector4 Matrix4::operator*(const Vector4 &vec) const noexcept {
	return Vector4(DX::XMVector3Transform(vec, _mat));
}
FORCEINLINE Matrix4 Matrix4::operator*(const Matrix4 &mat) const noexcept {
	return Matrix4(DX::XMMatrixMultiply(static_cast<DX::XMMATRIX>(mat), _mat));
}
FORCEINLINE Matrix4 Matrix4::makeZRotationByRadian(float radian) noexcept {
	return Matrix4(DX::XMMatrixRotationZ(radian));
}
FORCEINLINE Matrix4 Matrix4::makeXRotationByRadian(float radian) noexcept {
	return Matrix4(DX::XMMatrixRotationX(radian));
}
FORCEINLINE Matrix4 Matrix4::makeYRotationByRadian(float radian) noexcept {
	return Matrix4(DX::XMMatrixRotationY(radian));
}
FORCEINLINE Matrix4 Matrix4::makeZRotationByDegree(float angle) noexcept {
	return Matrix4(DX::XMMatrixRotationZ(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix4 Matrix4::makeXRotationByDegree(float angle) noexcept {
	return Matrix4(DX::XMMatrixRotationX(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix4 Matrix4::makeYRotationByDegree(float angle) noexcept {
	return Matrix4(DX::XMMatrixRotationY(DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix4 Matrix4::makeAxisRotationByDegree(const Vector3 &axis, float angle) noexcept {
	return Matrix4(DX::XMMatrixRotationAxis(axis, DX::XMConvertToRadians(angle)));
}
FORCEINLINE Matrix4 Matrix4::makeAxisRotationByRadian(const Vector3 &axis, float radian) noexcept {
	return Matrix4(DX::XMMatrixRotationAxis(axis, radian));
}
FORCEINLINE Matrix4 Matrix4::makeScale(float scale) noexcept {
	return Matrix4(DX::XMMatrixScaling(scale, scale, scale));
}
FORCEINLINE Matrix4 Matrix4::makeScale(float sx, float sy, float sz) noexcept {
	return Matrix4(DX::XMMatrixScaling(sx, sy, sz));
}
FORCEINLINE Matrix4 Matrix4::makeScale(const float3 &scale) noexcept {
	return Matrix4(DX::XMMatrixScaling(scale.x, scale.y, scale.z));
}
FORCEINLINE Matrix4 Matrix4::makeScale(const Vector3 &scale) noexcept {
	return Matrix4(DX::XMMatrixScaling(scale.x, scale.y, scale.z));
}
FORCEINLINE Matrix4 Matrix4::makeTranslation(const Vector3 &vec) noexcept {
	return Matrix4(DX::XMMatrixTranslation(vec.x, vec.y, vec.z));
}
FORCEINLINE Matrix4 Matrix4::makeTranslation(float ox, float oy, float oz) noexcept {
	return Matrix4(DX::XMMatrixTranslation(ox, oy, oz));
}
FORCEINLINE Matrix4 Matrix4::makeTranslation(float offset) noexcept {
	return Matrix4(DX::XMMatrixTranslation(offset, offset, offset));
}
FORCEINLINE Matrix4 Matrix4::identity() noexcept {
	return DX::XMMatrixIdentity();
}
FORCEINLINE Matrix4 Matrix4::Affine(const Vector3 &translation, const Quaternion &rotateQuat, const Vector3 &scale) noexcept {
	static Vector4 origin(0.f, 0.f, 0.f, 1.f);
	return Matrix4(DX::XMMatrixAffineTransformation(
		scale,
		origin,
		rotateQuat,
		translation
	));
}
FORCEINLINE Matrix4 transpose(const Matrix4 &mat4) noexcept {
	return Matrix4(DX::XMMatrixTranspose(static_cast<DX::XMMATRIX>(mat4)));
}
FORCEINLINE Scalar determinant(const Matrix4 &mat4) noexcept {
	return DX::XMMatrixDeterminant(static_cast<DX::XMMATRIX>(mat4));
}
FORCEINLINE Matrix4 inverse(const Matrix4 &mat4, const Scalar &det) noexcept {
	Scalar d = det;
	return Matrix4(DX::XMMatrixInverse(&d, static_cast<DX::XMMATRIX>(mat4)));
}
FORCEINLINE Matrix4 inverse(const Matrix4 &mat4) noexcept {
	Scalar det = determinant(mat4);
	return Matrix4(DX::XMMatrixInverse(&det, static_cast<DX::XMMATRIX>(mat4)));
}
#endif