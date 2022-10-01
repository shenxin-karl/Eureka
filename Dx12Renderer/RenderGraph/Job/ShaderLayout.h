#pragma once

namespace rgph {

struct ShaderLayoutIndex {
enum IndexType {
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
constexpr ShaderLayoutIndex(const ShaderLayoutIndex &) noexcept = default;
ShaderLayoutIndex &operator=(const ShaderLayoutIndex &) noexcept = default;
constexpr ShaderLayoutIndex(const IndexType &indexType) noexcept : indexType(indexType) {
}
constexpr operator IndexType() const noexcept {
	return indexType;
}
constexpr explicit operator bool() const noexcept {
	return static_cast<bool>(indexType);
}
friend bool operator==(const ShaderLayoutIndex &lhs, const ShaderLayoutIndex &rhs) noexcept {
	return lhs.indexType == rhs.indexType;
}
friend bool operator!=(const ShaderLayoutIndex &lhs, const ShaderLayoutIndex &rhs) noexcept {
	return lhs.indexType != rhs.indexType;
}
public:
	IndexType indexType = Nothing;
};

struct ShaderLayoutMask {
enum LayoutType {
	Nothing		= (0),
	Position	= (1 << (ShaderLayoutIndex::Position	-1)),
	Normal		= (1 << (ShaderLayoutIndex::Normal		-1)),
	Tangent		= (1 << (ShaderLayoutIndex::Tangent		-1)),
	Color		= (1 << (ShaderLayoutIndex::Color		-1)),
	TexCoord0	= (1 << (ShaderLayoutIndex::TexCoord0	-1)),
	TexCoord1	= (1 << (ShaderLayoutIndex::TexCoord1	-1)),
	TexCoord2	= (1 << (ShaderLayoutIndex::TexCoord2	-1)),
	TexCoord3	= (1 << (ShaderLayoutIndex::TexCoord3	-1)),
	TexCoord4	= (1 << (ShaderLayoutIndex::TexCoord4	-1)),
	TexCoord5	= (1 << (ShaderLayoutIndex::TexCoord5	-1)),
	TexCoord6	= (1 << (ShaderLayoutIndex::TexCoord6	-1)),
	TexCoord7	= (1 << (ShaderLayoutIndex::TexCoord7	-1)),
	BoneIndices = (1 << (ShaderLayoutIndex::BoneIndices	-1)),
	BoneWeights = (1 << (ShaderLayoutIndex::BoneWeights	-1)),
};
public:
constexpr ShaderLayoutMask() noexcept = default;
constexpr ShaderLayoutMask(const ShaderLayoutMask &) noexcept = default;
ShaderLayoutMask &operator=(const ShaderLayoutMask &) noexcept = default;
constexpr ShaderLayoutMask(LayoutType layoutType) noexcept : layoutMask(layoutType) {
}
constexpr ShaderLayoutMask(const ShaderLayoutIndex &index) noexcept {
	layoutMask = ShaderLayoutMask(static_cast<LayoutType>(1 << (index.indexType-1)));
}
constexpr operator LayoutType() const noexcept {
	return layoutMask;
}
constexpr explicit operator bool() const noexcept {
	return static_cast<bool>(layoutMask);
}
constexpr friend bool operator==(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
	return lhs.layoutMask == rhs.layoutMask;
}
constexpr friend bool operator!=(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
	return lhs.layoutMask == rhs.layoutMask;
}
constexpr friend ShaderLayoutMask operator|(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
	return LayoutType(lhs.layoutMask | rhs.layoutMask);
}
constexpr friend ShaderLayoutMask &operator|=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
	return (lhs = lhs | rhs);
}
constexpr friend ShaderLayoutMask operator&(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
	return LayoutType(lhs.layoutMask & rhs.layoutMask);
}
constexpr friend ShaderLayoutMask &operator&=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
	return (lhs = lhs & rhs);
}
constexpr friend ShaderLayoutMask operator^(ShaderLayoutMask lhs, ShaderLayoutMask rhs) noexcept {
	return LayoutType(lhs.layoutMask ^ rhs.layoutMask);
}
constexpr friend ShaderLayoutMask &operator^=(ShaderLayoutMask &lhs, ShaderLayoutMask rhs) noexcept {
	return (lhs = lhs ^ rhs);
}
constexpr friend ShaderLayoutMask operator~(ShaderLayoutMask lhs) noexcept {
	return LayoutType(~lhs.layoutMask);
}
private:
LayoutType layoutMask = Nothing;
};


}