#pragma once
#include <d3d12.h>
#include <stdint.h>

namespace Eureka {
	
constexpr DXGI_FORMAT kGBuffer0Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
constexpr DXGI_FORMAT kGBuffer1Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
constexpr DXGI_FORMAT kGBuffer2Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
constexpr DXGI_FORMAT kLightingBufferFormat			= DXGI_FORMAT_R16G16B16A16_FLOAT;
constexpr DXGI_FORMAT kPostProcessingBufferFormat			= DXGI_FORMAT_R10G10B10A2_UNORM;
constexpr DXGI_FORMAT kSwapChainDepthStencilFormat	= DXGI_FORMAT_D24_UNORM_S8_UINT;
constexpr DXGI_FORMAT kSwapChainRenderTargetFormat  = DXGI_FORMAT_R8G8B8A8_UNORM;

using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

}