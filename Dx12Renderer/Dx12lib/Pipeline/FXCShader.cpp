#include "FXCShader.h"
#include <format>

namespace dx12lib {

auto FXCShader::getByteCode() const -> D3D12_SHADER_BYTECODE {
    if (_pByteCode == nullptr)
        return { nullptr, 0 };
    return { _pByteCode->GetBufferPointer(), _pByteCode->GetBufferSize() };
}

void FXCShader::compileFormMemory(const CompileFormMemoryArgs &args) {
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	
	std::vector<D3D_SHADER_MACRO> defines;
	defines.reserve(args.macros.size() + 1);
	for (const auto &macro : args.macros)
		defines.push_back(D3D_SHADER_MACRO(macro.name.c_str(), macro.value.c_str()));
	defines.push_back(D3D_SHADER_MACRO(nullptr, nullptr));

	HRESULT hr = S_OK;
	WRL::ComPtr<ID3DBlob> byteCode;
	WRL::ComPtr<ID3DBlob> errors;
	hr = D3DCompile(args.pData,
		args.sizeInByte,
		args.fileName.c_str(),
		defines.data(),
		args.pInclude,
		args.entryPoint.c_str(),
		args.target.c_str(),
		compilesFlags,
		0,
		&_pByteCode,
		&errors
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<char *>(errors->GetBufferPointer()));
		ThrowIfFailed(hr);
	}

	ThrowIfFailed(D3DReflect(
		_pByteCode->GetBufferPointer(), 
		_pByteCode->GetBufferSize(), 
		IID_PPV_ARGS(&_pShaderReflection)
	));
}

void FXCShader::makeFromByteCode(const void *pData, size_t sizeInByte) {
	D3DCreateBlob(sizeInByte, &_pByteCode);
	std::memcpy(_pByteCode->GetBufferPointer(), pData, sizeInByte);
	ThrowIfFailed(D3DReflect(
		_pByteCode->GetBufferPointer(),
		_pByteCode->GetBufferSize(),
		IID_PPV_ARGS(&_pShaderReflection)
	));
}


}
