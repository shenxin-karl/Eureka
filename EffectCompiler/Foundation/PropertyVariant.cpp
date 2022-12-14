#include "PropertyVariant.h"
#include "Exception.h"

namespace EC {

void PropertyVariant::setVariantType(VariantType type) {
	_variantType = type;
}

void PropertyVariant::setTexture2D(Texture2D tex2d) {
	checkVariantType(VariantType::Texture2D, "");
}

void PropertyVariant::setColor(const Color &color) {
}

void PropertyVariant::setRangeMinMax(float min, float max) {
}

void PropertyVariant::setRangeDefaultValue(float value) {
}

void PropertyVariant::setFloat(float value) {
}

void PropertyVariant::setVector(const Vector &vector) {
}

void PropertyVariant::setUint(uint32_t value) {
}

void PropertyVariant::setInt(int value) {
}

auto PropertyVariant::getVariantType() const -> VariantType {
	return _variantType;
}

void PropertyVariant::checkVariantType(VariantType type, std::string_view message) const {
	Exception::Assert(type == _variantType, "line: {}, column: {} message: {}", 0, 0, message);
}

}
