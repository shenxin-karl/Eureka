#pragma once
#include <d3dcommon.h>
#include <memory>
#include <string>
#include <string_view>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/IShader.h>
#include <Dx12lib/Pipeline/DXCShader.h>
#include "Foundation/UUIDRandomGenerator.h"


namespace dx12lib {
class ShaderInclude;
}

namespace Eureka {

namespace stdfs = std::filesystem;
class ShaderLoader : public Singletion<ShaderLoader> {
    static inline const stdfs::path outputDirectory = "shaderCache";
    static inline const UUID128 classUUID = UUID128::from_string("{CF296646-0975-41BB-9006-D0423E2479D4}").value();
    static const std::string CompileMode;
public:
    ShaderLoader();
    void initialize() override;
    static std::shared_ptr<dx12lib::DXCShader> dxc(const stdfs::path &filePath,
        const std::string &entryPoint,
        const std::string &target,
        const D3D_SHADER_MACRO *defines = nullptr);


    struct DxcCompileDesc1 {
        std::string_view              filePath;
        std::string_view              source;
        stdfs::file_time_type         lastWriteTime;
        std::string                   entryPoint;
        std::string                   target;
        const D3D_SHADER_MACRO *      defines = nullptr;
        const dx12lib::ShaderInclude *pInclude = nullptr;
    };
    static std::shared_ptr<dx12lib::DXCShader> dxc(const DxcCompileDesc1 &desc);
private:
    static bool checkShaderCacheValid(const stdfs::file_time_type &lastWriteTime, const dx12lib::ShaderCacheInfo &cacheInfo);
    static std::string calcShaderCacheKey(const stdfs::path &filePath,
        const D3D_SHADER_MACRO *defines,
        const std::string &entryPoint, 
        const std::string &target);
    static dx12lib::ShaderCacheInfo getShaderCacheInfo(const std::string &shaderCacheKey);
private:
    UUIDNameGenerator _uuidGenerator;
};

}
