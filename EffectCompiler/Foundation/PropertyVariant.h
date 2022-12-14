#pragma once
#include "PropertyFundation.hpp"

namespace EC {

class PropertyVariant {
public:
	enum class VariantType {
		None		= 0,
		Texture2D	= 1,
		Color		= 2,
		Range		= 3,
		Float		= 4,
		Vector		= 5,
		Uint		= 6,
		Int			= 7,
	};
public:
	void setVariantType(VariantType type);
	void setTexture2D(Texture2D tex2d);
	void setColor(const Color &color);
	void setRangeMinMax(float min, float max);
	void setRangeDefaultValue(float value);
	void setFloat(float value);
	void setVector(const Vector &vector);
	void setUint(uint32_t value);
	void setInt(int value);
	auto getVariantType() const -> VariantType;
private:
	void checkVariantType(VariantType type, std::string_view message) const;
private:
	VariantType		_variantType = VariantType::None;
	PropertyValue	_variantValue;
};

}
