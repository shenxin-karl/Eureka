#include "DxcModule.h"

namespace dx12lib {

thread_local std::unique_ptr<DxcModule> DxcModule::_pInstance = std::make_unique<DxcModule>();

DxcModule::DxcModule() {
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&_pCompiler));
	DxcCreateInstance(CLSID_DxcLinker, IID_PPV_ARGS(&_pLinker));
	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&_pUtils));
	DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&_pLibrary));
}
auto DxcModule::getCompiler3() const -> IDxcCompiler3 * {
	return _pCompiler.Get();
}
auto DxcModule::getLinker() const -> IDxcLinker * {
	return _pLinker.Get();
}
auto DxcModule::getUtils() const -> IDxcUtils * {
	return _pUtils.Get();

}
auto DxcModule::getLibrary() const -> IDxcLibrary * {
	return _pLibrary.Get();
}

auto DxcModule::instance() -> DxcModule * {
	return _pInstance.get();
}

}
