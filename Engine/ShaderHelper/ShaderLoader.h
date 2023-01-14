#pragma once
#include <d3dcommon.h>
#include <memory>
#include <string>
#include <string_view>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/IShader.h>
#include <Dx12lib/Pipeline/DXCShader.h>
#include "Foundation/UUIDRandomGenerator.h"

namespace Eureka {

namespace fs = std::filesystem;
class ShaderLoader {
    static inline const fs::path outputDirectory = ".shaderCache";
    static inline const UUID128 classUUID = UUID128::from_string("{CF296646-0975-41BB-9006-D0423E2479D4}").value();
public:
    ShaderLoader();
    static auto instance() -> ShaderLoader *;
    static std::shared_ptr<dx12lib::DXCShader> dxc(const fs::path &filePath,
        const std::string &entryPoint,
        const std::string &target,
        const D3D_SHADER_MACRO *defines = nullptr);
private:
    static bool checkShaderCacheValid(const fs::path &sourcePath, const dx12lib::ShaderCacheInfo &cacheInfo);
    static std::string calcShaderCacheKey(const fs::path &filePath,
        const D3D_SHADER_MACRO *defines,
        const std::string &entryPoint, 
        const std::string &target);
    static dx12lib::ShaderCacheInfo getShaderCacheInfo(const std::string &shaderCacheKey);
private:
    static std::unique_ptr<ShaderLoader> pInst;
    UUIDNameGenerator _uuidGenerator;
};

}
