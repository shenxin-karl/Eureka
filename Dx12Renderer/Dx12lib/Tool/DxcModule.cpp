#include "DxcModule.h"

namespace dx12lib {

DxcModule::DxcModule() {
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&_pCompiler));
	DxcCreateInstance(CLSID_DxcLinker, IID_PPV_ARGS(&_pLinker));
	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&_pUtils));
}
auto DxcModule::getDxcCompiler3() const -> IDxcCompiler3 * {
	return _pCompiler.Get();
}
auto DxcModule::getDxcLinker() const -> IDxcLinker * {
	return _pLinker.Get();
}
auto DxcModule::getDxcUtils() const -> IDxcUtils * {
	return _pUtils.Get();

}

}
