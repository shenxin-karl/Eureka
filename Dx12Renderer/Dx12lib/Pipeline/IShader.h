#pragma once 
#include <Dx12lib/dx12libStd.h>
#include <d3d12shader.h>
#include <d3dcommon.h>
#include <string>
#include <filesystem>

namespace dx12lib {

namespace stdfs = std::filesystem;

class ShaderInclude;

struct ShaderCacheInfo {
    stdfs::path pdbFilePath;           // program database data
    stdfs::path csoFilePath;           // byte code data
    stdfs::path refFilePath;           // reflection data
};


struct ShaderCompileDesc {
    std::string                 entryPoint;
    std::string                 target;
    const ShaderInclude *       pInclude           = nullptr;
    const D3D_SHADER_MACRO *    pMacro             = nullptr;
    const void *                pShaderSource      = nullptr;
    size_t                      sizeInByte         = 0;
    const ShaderCacheInfo *     pShaderCacheInfo   = nullptr;
    std::string                 hintName;
};

class IShader {
public:
    IShader() = default;
    virtual ~IShader() = default;
    auto getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection>;
    virtual auto getByteCode() const -> D3D12_SHADER_BYTECODE = 0;
    virtual void compile(const ShaderCompileDesc &desc) = 0;
protected:
    WRL::ComPtr<ID3D12ShaderReflection> _pShaderReflection;
};

}