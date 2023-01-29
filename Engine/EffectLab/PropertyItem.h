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

enum class PropertyTextureDefault {
	White,
	Black,
	Bump,
};

enum class PropertyMatrixDefault {
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
		PropertyTextureDefault,
		PropertyMatrixDefault
	>;
public:
	PropertyItem(std::string uniformName);
	void setBool(bool bCond);
	void setInt(int val);
	void setRange(const PropertyRange &range);
	void setFloat2(const Math::float2 &f2);
	void setFloat3(const Math::float3 &f3);
	void setFloat4(const Math::float3 &f4);
	void setTexture2D(PropertyTextureDefault textureDefault);
	void setMatrix(PropertyMatrixDefault matrixDefault);
private:
	std::string _uniformName;
	PropertyItemType _propertyType;
	PropertyItemValue _propertyValue;
};

}
