#include "ShaderLoader.h"
#include <fstream>
#include "BuildInShader.h"

namespace Eureka {

ShaderLoader::ShaderLoader() {

}

auto ShaderLoader::instance() -> ShaderLoader * {
    static ShaderLoader sInstance;
    return &sInstance;
}

auto ShaderLoader::open(const std::string &path) -> std::string_view {
    auto buildFile = BuildIn::filesystem::open(path);
    if (buildFile != std::nullopt)
	    return { reinterpret_cast<const char *>(buildFile->data()), buildFile->size() };

    auto iter = _shaderContentCache.find(path);
    if (iter != _shaderContentCache.end()) {
        auto &item = iter->second;
        return { item.pContent.get(), item.length };
    }

    std::ifstream includeFile(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (includeFile.is_open()) {
        auto &item = _shaderContentCache[path];
        item.length = static_cast<size_t>(includeFile.tellg());
        item.pContent = std::make_unique<char[]>(item.length + 1);
        includeFile.seekg(0, std::ios::beg);
        includeFile.read(item.pContent.get(), item.length);
        item.pContent[item.length] = '\0';
        return { item.pContent.get(), item.length };
    }
    return {};
}

}
