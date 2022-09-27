FORCEINLINE BoundingSphere::BoundingSphere(const BoundingBox &boundingBox) noexcept {
	DX::BoundingSphere::CreateFromBoundingBox(_boundingSphere, boundingBox.baseCast());
}

FORCEINLINE BoundingSphere::BoundingSphere(const BoundingSphere &lhs, BoundingSphere &rhs) noexcept {
	DX::BoundingSphere::CreateMerged(_boundingSphere, lhs.baseCast(), rhs.baseCast());
}

FORCEINLINE BoundingSphere::BoundingSphere(const BoundingFrustum &fr) noexcept {
	DX::BoundingSphere::CreateFromFrustum(_boundingSphere, fr.baseCast());
}

FORCEINLINE const float3 &BoundingSphere::getCenter() const noexcept {
	return reinterpret_cast<const float3 &>(baseCast().Center);
}

FORCEINLINE const float &BoundingSphere::getRadius() const noexcept {
	return baseCast().Radius;
}

FORCEINLINE void BoundingSphere::setCenter(const float3 &offset) noexcept {
	setCenter(Vector3(offset));
}

FORCEINLINE void BoundingSphere::setCenter(const Vector3 &offset) noexcept {
	baseCast().Center = float3(Vector3(getCenter()) + offset);
}

FORCEINLINE void BoundingSphere::setRadius(float radius) noexcept {
	baseCast().Radius = radius;
}

FORCEINLINE DX::BoundingSphere & BoundingSphere::baseCast() noexcept {
	return _boundingSphere;
}

FORCEINLINE const DX::BoundingSphere & BoundingSphere::baseCast() const noexcept {
	return _boundingSphere;
}