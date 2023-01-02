build_in_code_gen = build_in_code_gen or {}

-- string.format(build_in_code_gen.header_format, namespace_name)
function get_header_format() 
    return 
[[
#pragma once
#include <cstddef>
#include <optional>
#include <unordered_map>

namespace %s {

class file {
public:
    file(const file &) noexcept = default;
    file(file &&) noexcept = default;
    file &operator=(const file &) noexcept = default;
    file &operator=(file &&) noexcept = default;

    template<size_t N>
    file(const unsigned char(&arr)[N]) noexcept : _length(N), _pData(arr) {
        
    }
    size_t length() const noexcept {
        return _length;
    }
    size_t size() const noexcept {
        return _length;
    }
    auto data() const noexcept -> const unsigned char * {
        return _pData;
    }
    auto begin() const noexcept -> const unsigned char * {
        return data();
    }
    auto end() const noexcept -> const unsigned char * {
        return data() + length();
    }
private:
    std::size_t _length;
    const unsigned char *_pData;
};


class filesystem {
public:
    static std::optional<file> open(const std::string &path) noexcept {
        if (auto iter = _fileMap.find(path); iter != _fileMap.end())
            return iter->second;
        return {};
    }
private:
    static std::unordered_map<std::string, file> _fileMap;
};	

}  
]] 
end


-- string.format(build_in_code_gen.global_var_format, var_name, byte_string)
function get_global_var_format()
    return 
[[
static const unsigned char g%s[] = {
    %s
};
]]
end

-- string.format(build_in_code_gen.map_item_format, path, var_name)
function get_map_item_format()
    return 
[[
    { "%s", file(g%s) },
]]
end

-- string.format(build_in_code_gen.source_format, namespace_name, global_vars_format,  map_items_format)
function get_source_format() 
    return 
[[
#include "BuildInShader.h"

namespace %s {

// static variant defination
%s

// map variant defination
std::unordered_map<std::string, file> filesystem::_fileMap = {
%s
};

}
]]
end 

return build_in_code_gen