#pragma once
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include "ShaderHelper/StringInclude.h"

namespace Eureka {

namespace WRL = Microsoft::WRL;

class ShaderHelper {
public:
	static WRL::ComPtr<ID3DBlob> compile(
		const std::wstring &fileName,
		const D3D_SHADER_MACRO *defines,
		const std::string &entryPoint,
		const std::string &target
	);

	static WRL::ComPtr<ID3DBlob> compile(
		const char *fileContext,
		std::size_t	sizeInByte,
		const D3D_SHADER_MACRO *defines,
		const std::string &entryPoint,
		const std::string &target
	);
};

}
