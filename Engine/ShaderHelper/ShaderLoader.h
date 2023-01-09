#pragma once
#include <d3dcommon.h>
#include <memory>
#include <string>
#include <string_view>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/IShader.h>
#include <Dx12lib/Pipeline/DXCShader.h>

namespace Eureka {

namespace fs = std::filesystem;
class ShaderLoader {
public:
    static auto instance() -> ShaderLoader *;
    static std::shared_ptr<dx12lib::DXCShader> dxc(const fs::path &filePath,
        const std::string &entryPoint,
        const std::string &target,
        const D3D_SHADER_MACRO *defines = nullptr);
};

}
