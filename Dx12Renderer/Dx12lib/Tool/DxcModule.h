#pragma once
#include <d3d12shader.h>
#include <d3dcommon.h>
#include <dxcapi.h>
#include <dxcerrors.h>
#include <dxcisense.h>
#include <memory>
#include <wrl/client.h>

namespace dx12lib {

class DxcModule {
public:
	DxcModule();
	DxcModule(const DxcModule &) = delete;
	DxcModule &operator=(const DxcModule &) = delete;
	auto getCompiler3() const -> IDxcCompiler3 *;
	auto getLinker() const -> IDxcLinker *;
	auto getUtils() const -> IDxcUtils *;
	auto getLibrary() const -> IDxcLibrary *;
	static auto instance() -> DxcModule *;
private:
	Microsoft::WRL::ComPtr<IDxcCompiler3> _pCompiler;
	Microsoft::WRL::ComPtr<IDxcLinker>	  _pLinker;
	Microsoft::WRL::ComPtr<IDxcUtils>	  _pUtils;
	Microsoft::WRL::ComPtr<IDxcLibrary>   _pLibrary;
	static thread_local std::unique_ptr<DxcModule> _pInstance;
};

}
