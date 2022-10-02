#pragma once
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <string_view>

namespace Eureka {

constexpr size_t kMaxKeyword = 128;
constexpr size_t kPrePassSpaceIndex = 8;
constexpr size_t kPreObjectSpaceIndex = 0;
constexpr size_t kStaticSamplerCount = 8;

constexpr std::string_view kCbPrePassName   = "CbPrePass";
constexpr std::string_view kCbPreObjectName = "CbPreObject";

using KeywordBitMask = std::bitset<kMaxKeyword>;

struct CBufferVar {
	D3D_SHADER_VARIABLE_TYPE type;
	UINT					 rows;
	UINT					 elements;
	size_t					 offset;
	dx12lib::ShaderRegister  shaderRegister;
};

struct CBufferDesc {
	std::string name;
	size_t bufferSize;
	std::unordered_map<std::string, CBufferVar> vars;
};

enum class BoundResourceType {
	CBuffer,
	Texture,
	Structured,
	RWTexture,
	RWStructured,
	Sampler,
};

struct BoundResourceDesc {
	std::string name;
	size_t arraySize = 1;
	BoundResourceType type;
	D3D_SRV_DIMENSION textureDimension;
	dx12lib::ShaderRegister shaderRegister;
};

CD3DX12_STATIC_SAMPLER_DESC getPointWrapStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getPointClampStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getLinearWrapStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getLinearClampStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getAnisotropicWrapStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getAnisotropicClampStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getLinearShadowCompareStaticSampler(UINT shaderRegister);
CD3DX12_STATIC_SAMPLER_DESC getPointShadowCompareStaticSampler(UINT shaderRegister);
const std::array<CD3DX12_STATIC_SAMPLER_DESC, 8> &getStaticSamplers();

}