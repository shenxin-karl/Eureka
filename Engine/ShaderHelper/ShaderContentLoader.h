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
	struct Value {
		size_t length = 0;
		std::unique_ptr<char[]> ptr;
	};
	std::unordered_map<std::string, Value> _contentMap;
};

}
