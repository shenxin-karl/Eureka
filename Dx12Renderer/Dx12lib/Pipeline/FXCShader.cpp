#include "FXCShader.h"
#include "ShaderInclude.h"

namespace dx12lib {

class FXCShaderIncludeWrap : public ID3DInclude {
public:
	STDMETHOD(Open)(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override {
		auto pBlob = pInclude->loadSource(pFileName);
		if (pBlob == nullptr) {
			*ppData = nullptr;
			*pBytes = 0;
		} else {
			*ppData = pBlob->GetBufferPointer();
			*pBytes = pBlob->GetBufferSize();
		}
		return S_OK;
	}
	STDMETHOD(Close)(THIS_ LPCVOID pData) override {
		return S_OK;
	}
public:
	const ShaderInclude *pInclude;
};

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

	FXCShaderIncludeWrap pIncludeWrap;
	ID3DInclude *pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	if (desc.pInclude != nullptr) {
		pIncludeWrap.pInclude = desc.pInclude;
		pInclude = &pIncludeWrap;
	}

	HRESULT hr = S_OK;
	WRL::ComPtr<ID3DBlob> byteCode;
	WRL::ComPtr<ID3DBlob> errors;
	hr = D3DCompile(desc.pShaderSource,
		desc.sizeInByte,
		desc.hintName.c_str(),
		desc.pMacro,
		pInclude,
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
