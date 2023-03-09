#pragma once
#include <filesystem>
#include <d3d12.h>
#include <cstdint>
#include <Math/MathStd.hpp>

namespace Eureka {
	
inline DXGI_FORMAT kGBuffer0Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
inline DXGI_FORMAT kGBuffer1Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
inline DXGI_FORMAT kGBuffer2Format				= DXGI_FORMAT_R10G10B10A2_UNORM;
inline DXGI_FORMAT kLightingBufferFormat		= DXGI_FORMAT_R16G16B16A16_FLOAT;
inline DXGI_FORMAT kPostProcessingBufferFormat	= DXGI_FORMAT_R8G8B8A8_UNORM;
inline DXGI_FORMAT kSwapChainDepthStencilFormat	= DXGI_FORMAT_D24_UNORM_S8_UINT;
inline DXGI_FORMAT kSwapChainRenderTargetFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
inline DXGI_FORMAT kTemporalAAFormat			= DXGI_FORMAT_R16G16B16A16_FLOAT;
//inline DXGI_FORMAT kVelocityFormat				= DXGI_FORMAT_R10G10B10A2_UNORM;
inline DXGI_FORMAT kVelocityFormat				= DXGI_FORMAT_R16G16_FLOAT;

using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

#define StringName(ptr)							\
	[]() -> const std::string & {				\
		static std::string sName(ptr);			\
		return sName;							\
	}()

inline const Math::float2 kHalton23[8] = {
	Math::float2{ 0.0f / 8.0f, 0.0f / 9.0f }, Math::float2{ 4.0f / 8.0f, 3.0f / 9.0f },
	Math::float2{ 2.0f / 8.0f, 6.0f / 9.0f }, Math::float2{ 6.0f / 8.0f, 1.0f / 9.0f },
	Math::float2{ 1.0f / 8.0f, 4.0f / 9.0f }, Math::float2{ 5.0f / 8.0f, 7.0f / 9.0f },
	Math::float2{ 3.0f / 8.0f, 2.0f / 9.0f }, Math::float2{ 7.0f / 8.0f, 5.0f / 9.0f }
};

namespace stdfs = std::filesystem;

}