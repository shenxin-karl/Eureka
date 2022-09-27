#pragma once
#include <Dx12lib/dx12libStd.h>
#include <d3dcommon.h>
#include <dxgi1_4.h>

namespace dx12lib {

class Adapter {
public:
	Adapter();
	IDXGIFactory4 *getDxgiFactory() const;
private:
	WRL::ComPtr<IDXGIFactory4>  _pDxgiFactory;
};

}