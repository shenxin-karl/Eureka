#pragma once
#include <d3d12.h>

namespace rgph {

struct ShaderLayoutIndex {
	enum : size_t {
		Nothing		= 0,
		Position	= 1,	// Vector3
		Normal		= 2,	// Vector3
		Tangent		= 3,	// Vector4
		Color		= 4,	// Vector4
		TexCoord0	= 5,	// Vector2
		TexCoord1	= 6,	// Vector2
		TexCoord2	= 7,	// Vector2
		TexCoord3	= 8,	// Vector2
		TexCoord4	= 9,	// Vector3
		TexCoord5	= 10,	// Vector3
		TexCoord6	= 11,	// Vector4
		TexCoord7	= 12,	// Vector4
		BoneIndices = 13,   // Vector4Uint8,
		BoneWeights = 14,   // Vector4
		Max			= 15,
	};
public:
	constexpr ShaderLayoutIndex() noexcept = default;
	constexpr ShaderLayoutIndex(size_t v) : _value(v) {}
	constexpr operator size_t() const noexcept {
		return _value;
	}

	static ShaderLayoutIndex stringToEnum(const std::string &str) {
		static std::unordered_map<std::string, int> map = {
			{ "POSITION0",		Position    },
			{ "NORMAL0",		Normal	    },
			{ "TANGENT0",		Tangent     },
			{ "COLOR0",			Color		},
			{ "TEXCOORD0",		TexCoord0   },
			{ "TEXCOORD1",		TexCoord1   },
			{ "TEXCOORD2",		TexCoord2   },
			{ "TEXCOORD3",		TexCoord3   },
			{ "TEXCOORD4",		TexCoord4   },
			{ "TEXCOORD5",		TexCoord5   },
			{ "TEXCOORD6",		TexCoord6   },
			{ "TEXCOORD7",		TexCoord7   },
			{ "BONEINDICES",	BoneIndices },
			{ "BONEWEIGHTS",	BoneWeights },
		};
		auto iter = map.find(str);
		if (iter != map.end())
			return iter->second;
		return Nothing;
	}

	static D3D12_INPUT_ELEMENT_DESC getInputLayoutByEnum(const ShaderLayoutIndex &layoutIndex) {
#define DEF_DESC(sem, idx, fmt, slot) \
		D3D12_INPUT_ELEMENT_DESC { sem, idx, fmt, slot, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		static D3D12_INPUT_ELEMENT_DESC descMap[] = {
			DEF_DESC("POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		 0),
			DEF_DESC("NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		 1),
			DEF_DESC("TANGENT",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	 2),
			DEF_DESC("COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	 3),
			DEF_DESC("TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		 4),
			DEF_DESC("TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,		 5),
			DEF_DESC("TEXCOORD",	2, DXGI_FORMAT_R32G32_FLOAT,		 6),
			DEF_DESC("TEXCOORD",	3, DXGI_FORMAT_R32G32_FLOAT,		 7),
			DEF_DESC("TEXCOORD",	4, DXGI_FORMAT_R32G32B32_FLOAT,		 8),
			DEF_DESC("TEXCOORD",	5, DXGI_FORMAT_R32G32B32_FLOAT,		 9),
			DEF_DESC("TEXCOORD",	6, DXGI_FORMAT_R32G32B32A32_FLOAT,	10),
			DEF_DESC("TEXCOORD",	7, DXGI_FORMAT_R32G32B32A32_FLOAT,	11),
			DEF_DESC("BONEINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,		12),
			DEF_DESC("BONEINDICES", 0, DXGI_FORMAT_R32G32B32_FLOAT,		13),
		};
#undef DEF_DESC
		size_t index = static_cast<size_t>(layoutIndex) - 1;
		assert(index < std::size(descMap));
		return descMap[index];
	}

	static constexpr size_t getLayoutSize() noexcept {
		return Max-1;
	}
private:
	size_t _value = Nothing;
};


struct ShaderLayoutMask {
	enum : size_t {
		Nothing	     = (0),
		Position	 = (1 << (ShaderLayoutIndex::Position	 -1)),
		Normal		 = (1 << (ShaderLayoutIndex::Normal		 -1)),
		Tangent	     = (1 << (ShaderLayoutIndex::Tangent	 -1)),
		Color		 = (1 << (ShaderLayoutIndex::Color		 -1)),
		TexCoord0	 = (1 << (ShaderLayoutIndex::TexCoord0	 -1)),
		TexCoord1	 = (1 << (ShaderLayoutIndex::TexCoord1	 -1)),
		TexCoord2	 = (1 << (ShaderLayoutIndex::TexCoord2	 -1)),
		TexCoord3	 = (1 << (ShaderLayoutIndex::TexCoord3	 -1)),
		TexCoord4	 = (1 << (ShaderLayoutIndex::TexCoord4	 -1)),
		TexCoord5	 = (1 << (ShaderLayoutIndex::TexCoord5	 -1)),
		TexCoord6	 = (1 << (ShaderLayoutIndex::TexCoord6	 -1)),
		TexCoord7	 = (1 << (ShaderLayoutIndex::TexCoord7	 -1)),
		BoneIndices  = (1 << (ShaderLayoutIndex::BoneIndices -1)),
		BoneWeights  = (1 << (ShaderLayoutIndex::BoneWeights -1)),
	};
public:
	constexpr ShaderLayoutMask() noexcept = default;
	constexpr ShaderLayoutMask(size_t v) : _value(v) {}
	constexpr ShaderLayoutMask(const ShaderLayoutIndex &index)
		: _value(static_cast<size_t>(1) << static_cast<size_t>(index - 1)) {}
	constexpr operator size_t() const noexcept {
		return _value;
	}
	constexpr friend bool operator==(const ShaderLayoutMask &lhs, const ShaderLayoutMask &rhs) noexcept {
		return lhs._value == rhs._value;
	}
	constexpr friend bool operator!=(const ShaderLayoutMask &lhs, const ShaderLayoutMask &rhs) noexcept {
		return lhs._value == rhs._value;
	}
	constexpr friend ShaderLayoutMask operator|(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
		return { lhs._value | rhs._value };
	}
	constexpr friend ShaderLayoutMask &operator|=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
		return (lhs = lhs | rhs);
	}
	constexpr friend ShaderLayoutMask operator&(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
		return { lhs._value & rhs._value };
	}
	constexpr friend ShaderLayoutMask &operator&=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
		return (lhs = lhs & rhs);
	}
	constexpr friend ShaderLayoutMask operator^(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
		return { lhs._value ^ rhs._value };
	}
	constexpr friend ShaderLayoutMask &operator^=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
		return (lhs = lhs ^ rhs);
	}
	constexpr friend ShaderLayoutMask operator~(ShaderLayoutMask lhs) noexcept {
		return { ~lhs._value };
	}
private:
	size_t _value = Nothing;
};

}