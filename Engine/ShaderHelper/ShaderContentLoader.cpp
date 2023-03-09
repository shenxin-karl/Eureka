#include "ShaderContentLoader.h"
#include "Foundation/Exception.h"
#include <fstream>

namespace Eureka {

auto ShaderContentLoader::open(const stdfs::path &filePath) -> std::string_view {
	auto strFilePath = filePath.string();
	auto iter = _contentMap.find(strFilePath);
	if (iter != _contentMap.end()) {
		return { iter->second.ptr.get(), iter->second.length };
	}

	if (!stdfs::exists(filePath)) {
		Exception::Throw("ShaderContentLoader::open filePath {} not exist!", filePath.string());
	}

	std::fstream fin(filePath);
	Exception::Throw(fin.is_open(), "can't not open the file {}", filePath.string());

	std::stringstream sbuf;
	sbuf << fin.rdbuf();
	fin.close();
	auto content = sbuf.str();

	auto pContent = std::make_unique<char[]>(content.length());
	auto *pResult = pContent.get();
	std::memcpy(pResult, content.c_str(), content.length());
	_contentMap[strFilePath] = { content.length(), std::move(pContent) };
	return { pResult, content.length() };
}

}
