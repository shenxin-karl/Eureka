#pragma once
#include <d3d12.h>

namespace Eureka {
	
constexpr DXGI_FORMAT kGBuffer0Format				= DXGI_FORMAT_R16G16B16A16_FLOAT;
constexpr DXGI_FORMAT kGBuffer1Format				= DXGI_FORMAT_R16G16B16A16_FLOAT;
constexpr DXGI_FORMAT kGBuffer2Format				= DXGI_FORMAT_R16G16B16A16_FLOAT;
constexpr DXGI_FORMAT kSwapChainDepthStencilFormat	= DXGI_FORMAT_D24_UNORM_S8_UINT;

}