#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>

namespace dx12lib {

class SwapChain {
protected:
	SwapChain(std::weak_ptr<Device> pDevice, 
		HWND hwnd, 
		DXGI_FORMAT backBufferFormat,
		DXGI_FORMAT depthStencilFormat,
		size_t fps
	);
public:
	void resize(DirectContextProxy pDirectContext, uint32 width, uint32 height);
	DXGI_FORMAT getRenderTargetFormat() const;
	DXGI_FORMAT getDepthStencilFormat() const;
	std::shared_ptr<Texture> getRenderTarget2D() const;
	std::shared_ptr<Texture> getDepthStencil2D() const;
	Math::float2 getRenderTargetSize() const;
	Math::float2 getInvRenderTargetSize() const;
	void present();
	void setVerticalSync(bool bSync);
	bool getVerticalSync() const;
private:
	void updateBuffer(DirectContextProxy pDirectContext);
private:
	HWND	_hwnd;
	uint32	_width;
	uint32	_height;
	DXGI_FORMAT	_renderTargetFormat;
	DXGI_FORMAT	_depthStencilFormat;
	std::size_t	_currentBackBufferIndex;
	bool		_verticalSync = false;
	std::weak_ptr<Device>			_pDevice;
	WRL::ComPtr<IDXGISwapChain>		_pSwapChain;
	std::shared_ptr<Texture>		_pDepthStencil2D;
	std::shared_ptr<Texture>		_pSwapChainBuffer[kSwapChainBufferCount];
};

}