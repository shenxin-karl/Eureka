#pragma once
#include "IShader.h"
#include <d3d12shader.h>
#include <dxcapi.h>
#include <dxcerrors.h>
#include <dxcisense.h>

namespace dx12lib {

class DXCShader : public IShader {
public:
    using IShader::IShader;
    auto getByteCode() const->D3D12_SHADER_BYTECODE  final;
    void compileFormMemory(const CompileFormMemoryArgs &args) final;
    void makeFromByteCode(const void *pData, size_t sizeInByte) override;
private:
    WRL::ComPtr<IDxcBlob> _pByteCode = nullptr;
};

}