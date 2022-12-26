#pragma once
#include "IShader.h"
#include <wrl/client.h>

namespace dx12lib {

class FXCShader : public IShader {
public:
    using IShader::IShader;
    auto getByteCode() const -> D3D12_SHADER_BYTECODE final;
    void compileFormMemory(const void *pData, size_t sizeInByte, ID3DInclude *pInclude) final;
private:
    WRL::ComPtr<ID3DBlob> _pByteCode;
};

}