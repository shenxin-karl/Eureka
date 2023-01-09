#pragma once
#include "IShader.h"
#include <wrl/client.h>

namespace dx12lib {

class FXCShader : public IShader {
public:
    using IShader::IShader;
    auto getByteCode() const -> D3D12_SHADER_BYTECODE override;
    void compile(const ShaderCompileDesc &desc) override;
private:
    WRL::ComPtr<ID3DBlob> _pByteCode;
};

}