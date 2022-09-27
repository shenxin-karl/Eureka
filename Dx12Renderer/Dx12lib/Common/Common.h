#pragma once
#define NOMINMAX
#include <Windows.h>
#include <source_location>
#include <sstream>
#include <locale>
#include <string>
#include <Dx12lib/Common/D3DException.h>

inline void ThrowIfFailed(HRESULT hr, const std::source_location &sl = std::source_location::current()) {
	if (FAILED(hr)) {
		assert(false);
		throw d3d::D3DException(hr, sl.file_name(), sl.line());
	}
}

template<typename T>
constexpr decltype(auto) RVPtr(T &&val) {
	return &val;
}
