#pragma once
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace Eureka {

constexpr size_t kMaxKeyword = 128;
using KeywordBitMask = std::bitset<kMaxKeyword>;

enum class CBufferVarType {
	Float, Float2, Float3, Float4,
	Int, Int2, Int3, Int4,
	Uint, Uint2, Uint3, Uint4
};

struct CBufferVar {
	size_t offset;
	CBufferVarType size;
	dx12lib::ShaderRegister shaderRegister;
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


}