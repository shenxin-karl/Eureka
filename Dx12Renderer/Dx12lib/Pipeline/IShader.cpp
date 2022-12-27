#include "IShader.h"
#include <fstream>
#include <ios>

namespace dx12lib {

auto IShader::getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection> {
    return _pShaderReflection;
}

void IShader::compileFormFile(const CompileFormFileArgs &args) {
    std::ifstream fin(args.fileName, std::ios::in);
    if (!fin.is_open())
        return;

	std::stringstream sbuf;
	sbuf << fin.rdbuf();
    auto content = sbuf.str();

    CompileFormMemoryArgs memoryArgs;
	static_cast<CompileFormFileArgs &>(memoryArgs) = args;
    memoryArgs.pData = content.data();
    memoryArgs.sizeInByte = content.length();
    compileFormMemory(memoryArgs);
    fin.close();
}

}