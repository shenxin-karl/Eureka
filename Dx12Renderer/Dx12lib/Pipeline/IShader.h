#pragma once 
#include <Dx12lib/dx12libStd.h>
#include <d3d12shader.h>
#include <d3dcommon.h>
#include <string>

namespace dx12lib {

class IShader {
public:
    struct Macro {
	    std::string name;
        std::string value;
    };
    IShader() = default;
    virtual ~IShader() = default;
    auto getFileName() const noexcept -> const std::string &;
    auto getTarget() const noexcept -> const std::string &;
    auto getEntryPoint() const noexcept -> const std::string &;
    auto getMacros() const noexcept -> const std::vector<Macro> &;
    void setFileName(std::string fileName);
    void setTarget(std::string target);
    void setEntryPoint(std::string entryPoint);
    void setMacros(std::vector<Macro> macros);
    void addMacro(Macro macro);
    auto getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection>;
    virtual void compileFormFile(ID3DInclude *pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE);
    virtual auto getByteCode() const -> D3D12_SHADER_BYTECODE = 0;
    virtual void compileFormMemory(const void *pData, size_t sizeInByte, ID3DInclude *pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE) = 0;
protected:
    std::string _fileName;
    std::string _target;
    std::string _entryPoint;
    std::vector<Macro> _macros;
    WRL::ComPtr<ID3D12ShaderReflection> _pShaderReflection;
};

}