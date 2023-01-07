#pragma once
#define NOMINMAX
#include <Windows.h>
#include <source_location>
#include <sstream>
#include <locale>
#include <string>
#include <Dx12lib/Common/Exception.h>
#include <cassert>

inline void ThrowIfFailed(HRESULT hr, const std::source_location &sl = std::source_location::current()) {
	if (FAILED(hr)) {
		assert(false);
		throw dx12lib::D3DException(hr, sl.file_name(), sl.line());
	}
}

template<typename T>
constexpr decltype(auto) RVPtr(T &&val) {
	return &val;
}
