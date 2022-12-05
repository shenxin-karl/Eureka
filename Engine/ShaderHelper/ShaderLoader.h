#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace Eureka {

class ShaderLoader {
public:
    static auto instance()->ShaderLoader *;
    auto open(const std::string &path)->std::string_view;
private:
    struct Item {
        size_t length;
        std::unique_ptr<char[]> pContent;
    };
    std::unordered_map<std::string, Item> _shaderContentCache;
};

}
