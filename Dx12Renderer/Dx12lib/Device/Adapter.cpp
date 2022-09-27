#include <Dx12lib/Device/Adapter.h>

namespace dx12lib {

Adapter::Adapter() {
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&_pDxgiFactory)));
}

IDXGIFactory4 *Adapter::getDxgiFactory() const {
	return _pDxgiFactory.Get();
}

}