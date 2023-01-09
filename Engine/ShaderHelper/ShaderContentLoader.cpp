#include "ShaderContentLoader.h"
#include "Foundation/Exception.h"
#include <fstream>

namespace Eureka {

auto ShaderContentLoader::instance() -> ShaderContentLoader * {
	static ShaderContentLoader inst;
	return &inst;
}

auto ShaderContentLoader::open(const fs::path &filePath) -> std::string_view {
	auto iter = _contentMap.find(filePath);
	if (iter != _contentMap.end()) {
		return { std::get<0>(iter->second).get(), std::get<1>(iter->second) };
	}

	if (!fs::exists(filePath)) {
		Exception::Throw("ShaderContentLoader::open filePath {} not exist!", filePath.string());
	}

	std::fstream fin(filePath);
	Exception::Throw(!fin.is_open(), "can't not open the file {}", filePath.string());

	std::stringstream sbuf;
	sbuf << fin.rdbuf();
	fin.close();
	auto content = sbuf.str();

	auto pContent = std::make_unique<char[]>(content.length());
	auto *pResult = pContent.get();
	std::memcpy(pResult, content.c_str(), content.length());
	_contentMap[filePath] = std::make_tuple(std::move(pContent), content.size());
	return { pResult, content.length() };
}

}
