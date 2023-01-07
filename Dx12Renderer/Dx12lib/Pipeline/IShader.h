#pragma once 
#include <Dx12lib/dx12libStd.h>
#include <d3d12shader.h>
#include <d3dcommon.h>
#include <string>

namespace dx12lib {

struct CompileFormFileArgs {
    std::string filePath;
    std::string target;
    std::string entryPoint;
    std::string outputDirectory;
    ID3DInclude *pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
    const D3D_SHADER_MACRO *pMacro = nullptr;
};

struct CompileFormMemoryArgs : public CompileFormFileArgs {
    const void *pData = nullptr;
	size_t sizeInByte = 0;
};

class IShader {
public:
    IShader() = default;
    virtual ~IShader() = default;
    auto getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection>;
    virtual void compileFormFile(const CompileFormFileArgs &args);
    virtual auto getByteCode() const -> D3D12_SHADER_BYTECODE = 0;
    virtual void compileFormMemory(const CompileFormMemoryArgs &args) = 0;
    virtual void makeFromByteCode(const void *pData, size_t sizeInByte) = 0;
protected:
    struct ShaderCacheInfo {
	    std::string pdbFilePath; 
        std::string csoFilePath;
        std::string reFilePath;     
    };
    static ShaderCacheInfo calcShaderCacheInfo(const CompileFormFileArgs &args);
protected:
    WRL::ComPtr<ID3D12ShaderReflection> _pShaderReflection;
};

}