
FORCEINLINE const FloatStore<33> & FloatStore<33>::identity() noexcept {
	static FloatStore<33> object { static_cast<float3x3>(Matrix4::identity()) };
	return object;
}

FORCEINLINE const FloatStore<43> & FloatStore<43>::identity() noexcept {
	static FloatStore<43> object { static_cast<float4x3>(Matrix4::identity()) };
	return object;
}

FORCEINLINE const FloatStore<44> & FloatStore<44>::identity() noexcept {
	static FloatStore<44> object { static_cast<float4x4>(Matrix4::identity()) };
	return object;
}