FORCEINLINE BoundingFrustum::BoundingFrustum(const float3 &origin, const float4 &orientation, float rightSlope,
	float leftSlope, float topSlope, float bottomSlope, float _near, float _far) noexcept
: _boundingFrustum(origin, orientation,
	rightSlope, leftSlope,
	topSlope, bottomSlope,
	_near, _far)
{
}

FORCEINLINE BoundingFrustum::BoundingFrustum(const Matrix4 &projection) noexcept
: _boundingFrustum(static_cast<DX::XMMATRIX>(projection))
{
}

FORCEINLINE BoundingFrustum BoundingFrustum::transform(const Matrix4 &trans) const noexcept {
	BoundingFrustum ret;
	_boundingFrustum.Transform(ret.baseCast(), static_cast<DX::XMMATRIX>(trans));
	return ret;
}

FORCEINLINE BoundingFrustum BoundingFrustum::transform(float scale, const Quaternion &rotate,
	const Vector3 &translation) const noexcept {
}

FORCEINLINE DX::BoundingFrustum &BoundingFrustum::baseCast() noexcept {
	return _boundingFrustum;
}

FORCEINLINE const DX::BoundingFrustum &BoundingFrustum::baseCast() const noexcept {
	return _boundingFrustum;
}

FORCEINLINE std::array<float3, BoundingFrustum::kCornerCount> BoundingFrustum::getCorners() const noexcept {
	std::array<float3, BoundingFrustum::kCornerCount> corners;
	_boundingFrustum.GetCorners(corners.data());
	return corners;
}

FORCEINLINE void BoundingFrustum::getPlanes(Vector4 &nearPlane, Vector4 &farPlane, Vector4 &rightPlane, Vector4 &leftPlane,
	Vector4 &topPlane, Vector4 &bottomPlane) const noexcept
{
	_boundingFrustum.GetPlanes(&nearPlane, &farPlane, 
		&rightPlane, &leftPlane, 
		&topPlane, &bottomPlane
	);
}

FORCEINLINE DX::ContainmentType BoundingFrustum::contains(const BoundingBox &box) const noexcept {
	return _boundingFrustum.Contains(box.baseCast());
}