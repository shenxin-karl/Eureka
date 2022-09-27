#if 1
template <typename T, bool EnableAssign, size_t... I>
template <typename> requires (EnableAssign)
FORCEINLINE T &Swizzle<T, EnableAssign, I...>::operator=(const T &other) noexcept {
	constexpr size_t idx = indices[0];
	if constexpr(sizeof...(I) > 1)
		((at<I>() = other[I]), ...);
	else
		at<idx>() = other;

	return reinterpret_cast<T &>(at<idx>());
}
template <typename T, bool EnableAssign, size_t... I>
FORCEINLINE Swizzle<T, EnableAssign, I...>::operator T() const noexcept {
	return T(at<I>()...);
}
template<typename T, bool EnableAssign, size_t... I>
FORCEINLINE std::ostream &operator<<(std::ostream &os, const Swizzle<T, EnableAssign, I...> &sz) noexcept {
	os << static_cast<T>(sz);
	return os;
}
template <typename T, bool EnableAssign, size_t... I>
template <size_t Idx>
FORCEINLINE float &Swizzle<T, EnableAssign, I...>::at() noexcept {
	return reinterpret_cast<float *>(this)[Idx];
}
template <typename T, bool EnableAssign, size_t... I>
template <size_t Idx>
FORCEINLINE float Swizzle<T, EnableAssign, I...>::at() const noexcept {
	return reinterpret_cast<const float *>(this)[Idx];
}
#endif