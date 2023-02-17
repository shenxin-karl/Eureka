#pragma once
#include <string>
#include <variant>
#include "Math/MathStd.hpp"

namespace Eureka {

enum class PropertyItemType {
	None,
	Bool,
	Int,
	Float,
	Range,
	Float2,
	Float3,
	Float4,
	Matrix,
	Texture2D,
};

enum class PropertyTexture {
	None,
	White,
	Black,
	Bump,
};

enum class PropertyMatrix {
	Identity,
};

struct PropertyRange {
	float min;
	float max;
	float val;
};

class PropertyItem {
	using PropertyItemValue = std::variant<
		bool,
		int,
		float,
		PropertyRange,
		Math::float2,
		Math::float3,
		Math::float4,
		PropertyTexture,
		PropertyMatrix
	>;
public:
	PropertyItem(std::string uniformName);
	void setDescription(std::string description);
	void setBool(bool bCond);
	void setInt(int val);
	void setFloat(float val);
	void setRange(const PropertyRange &range);
	void setFloat2(const Math::float2 &f2);
	void setFloat3(const Math::float3 &f3);
	void setFloat4(const Math::float4 &f4);
	void setTexture2D(PropertyTexture textureDefault);
	void setMatrix(PropertyMatrix matrixDefault);
	auto getUniformName() const -> const std::string &;
	auto getPropertyType() const -> PropertyItemType;
	auto getDescription() const -> const std::string &;
	auto getBool() const -> bool;
	auto getInt() const -> int;
	auto getFloat() const -> float;
	auto getRange() const -> PropertyRange;
	auto getFloat2() const -> Math::float2;
	auto getFloat3() const -> Math::float3;
	auto getFloat4() const -> Math::float4;
	auto getTexture2D() const -> PropertyTexture;
	auto getMatrix() const -> PropertyMatrix;
private:
	std::string _uniformName;
	std::string _description;
	PropertyItemType _propertyType;
	PropertyItemValue _propertyValue;
};

}
