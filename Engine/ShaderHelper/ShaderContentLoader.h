#pragma once
#include <unordered_map>
#include <filesystem>
#include "Foundation/Singletion.hpp"

namespace Eureka {

namespace fs = std::filesystem;

class ShaderContentLoader : public Singletion<ShaderContentLoader> {
public:
	auto open(const fs::path &filePath) -> std::string_view;
private:
	using ContentMap = std::unordered_map<fs::path, std::tuple<std::unique_ptr<char[]>, size_t>>;
	ContentMap _contentMap;
};

}
