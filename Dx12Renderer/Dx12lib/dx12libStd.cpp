#include "dx12libStd.h"
#ifndef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif
#include <codecvt>

namespace dx12lib {

static std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter;
std::wstring to_wstring(const std::string &str) {
	return converter.from_bytes(str);
}

std::string to_string(const std::wstring &str) {
	return converter.to_bytes(str);
}

}
