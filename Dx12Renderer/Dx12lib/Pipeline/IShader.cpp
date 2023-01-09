#include "IShader.h"

#include <filesystem>
#include <fstream>

namespace dx12lib {

auto IShader::getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection> {
    return _pShaderReflection;
}



}
