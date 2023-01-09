#include "FXCShader.h"
#include <format>

namespace dx12lib {

auto FXCShader::getByteCode() const -> D3D12_SHADER_BYTECODE {
    if (_pByteCode == nullptr)
        return { nullptr, 0 };
    return { _pByteCode->GetBufferPointer(), _pByteCode->GetBufferSize() };
}

void FXCShader::compile(const ShaderCompileDesc &desc) {
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;
	WRL::ComPtr<ID3DBlob> byteCode;
	WRL::ComPtr<ID3DBlob> errors;
	hr = D3DCompile(desc.pShaderSource,
		desc.sizeInByte,
		desc.hintName.c_str(),
		desc.pMacro,
		desc.pInclude,
		desc.entryPoint.c_str(),
		desc.target.c_str(),
		compilesFlags,
		0,
		&_pByteCode,
		&errors
	);

	if (FAILED(hr)) {
		std::string errorMsg(static_cast<char *>(errors->GetBufferPointer()), errors->GetBufferSize());
		D3DException::Throw(hr, errorMsg);
	}

	ThrowIfFailed(D3DReflect(
		_pByteCode->GetBufferPointer(),
		_pByteCode->GetBufferSize(),
		IID_PPV_ARGS(&_pShaderReflection)
	));
}

}
