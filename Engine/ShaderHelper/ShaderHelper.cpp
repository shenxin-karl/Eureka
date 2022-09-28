#include <d3dcompiler.h>
#include "ShaderHelper/ShaderHelper.h"
#include "Dx12lib/Common/Common.h"
#include "ShaderHelper/ShaderInclude.h"

namespace Eureka {

WRL::ComPtr<ID3DBlob> ShaderHelper::compile(
	const std::wstring &fileName, 
	const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint, 
	const std::string &target)
{
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	std::unique_ptr<ShaderInclude> pShaderInclude = std::make_unique<ShaderInclude>("", "");

	using Microsoft::WRL::ComPtr;
	HRESULT hr = S_OK;
	ComPtr<ID3DBlob> byteCode;
	ComPtr<ID3DBlob> errors;
	hr = D3DCompileFromFile(
		fileName.c_str(),
		defines,
		pShaderInclude.get(),
		entryPoint.c_str(),
		target.c_str(),
		compilesFlags,
		0,
		&byteCode,
		&errors
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<char *>(errors->GetBufferPointer()));
		ThrowIfFailed(hr);
	}
	return byteCode;
}

WRL::ComPtr<ID3DBlob> ShaderHelper::compile(
	const char *fileContext, 
	std::size_t sizeInByte,
	const D3D_SHADER_MACRO *defines, 
	const std::string &entryPoint, 
	const std::string &target)
{
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;
	WRL::ComPtr<ID3DBlob> byteCode;
	WRL::ComPtr<ID3DBlob> errors;
	hr = D3DCompile(fileContext,
		sizeInByte,
		nullptr,
		defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint.c_str(),
		target.c_str(),
		compilesFlags,
		0,
		&byteCode,
		&errors
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<char *>(errors->GetBufferPointer()));
		ThrowIfFailed(hr);
	}
	return byteCode;
}

}
