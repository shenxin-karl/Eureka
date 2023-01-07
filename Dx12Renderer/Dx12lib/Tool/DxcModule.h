#pragma once
#include <d3d12shader.h>
#include <d3dcommon.h>
#include <dxcapi.h>
#include <dxcerrors.h>
#include <dxcisense.h>
#include <wrl/client.h>

namespace dx12lib {

class DxcModule {
public:
	DxcModule();
	DxcModule(const DxcModule &) = delete;
	DxcModule &operator=(const DxcModule &) = delete;
	auto getDxcCompiler3() const -> IDxcCompiler3 *;
	auto getDxcLinker() const -> IDxcLinker *;
	auto getDxcUtils() const -> IDxcUtils *;
private:
	Microsoft::WRL::ComPtr<IDxcCompiler3> _pCompiler;
	Microsoft::WRL::ComPtr<IDxcLinker> _pLinker;
	Microsoft::WRL::ComPtr<IDxcUtils> _pUtils;
};

}
