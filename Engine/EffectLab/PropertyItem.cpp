#include "PropertyItem.h"
#include "Foundation/Exception.h"

namespace Eureka {

PropertyItem::PropertyItem(std::string uniformName)
: _uniformName(std::move(uniformName)), _propertyType(PropertyItemType::None) {

}

void PropertyItem::setDescription(std::string description) {
	_description = std::move(description);
}

void PropertyItem::setBool(bool bCond) {
	_propertyType = PropertyItemType::Bool;
	_propertyValue = bCond;
}

void PropertyItem::setInt(int val) {
	_propertyType = PropertyItemType::Int;
	_propertyValue = val;
}

void PropertyItem::setFloat(float val) {
	_propertyType = PropertyItemType::Float;
	_propertyValue = val;
}

void PropertyItem::setRange(const PropertyRange &range) {
	_propertyType = PropertyItemType::Range;
	_propertyValue = range;
}

void PropertyItem::setFloat2(const Math::float2 &f2) {
	_propertyType = PropertyItemType::Float2;
	_propertyValue = f2;
}

void PropertyItem::setFloat3(const Math::float3 &f3) {
	_propertyType = PropertyItemType::Float3;
	_propertyValue = f3;
}

void PropertyItem::setFloat4(const Math::float4 &f4) {
	_propertyType = PropertyItemType::Float4;
	_propertyValue = f4;
}

void PropertyItem::setTexture2D(PropertyTexture textureDefault) {
	_propertyType = PropertyItemType::Texture2D;
	_propertyValue = textureDefault;
}

void PropertyItem::setMatrix(PropertyMatrix matrixDefault) {
	_propertyType = PropertyItemType::Matrix;
	_propertyValue = matrixDefault;
}

auto PropertyItem::getUniformName() const -> const std::string & {
	return _uniformName;
}

auto PropertyItem::getPropertyType() const -> PropertyItemType {
	return _propertyType;
}

auto PropertyItem::getDescription() const -> const std::string & {
	return _description;
}

auto PropertyItem::getBool() const -> bool {
	Exception::Throw(_propertyType == PropertyItemType::Bool, "PropertyItem::getBool invalid type");
	return std::get<bool>(_propertyValue);
}

auto PropertyItem::getInt() const -> int {
	Exception::Throw(_propertyType == PropertyItemType::Int, "PropertyItem::getInt invalid type");
	return std::get<int>(_propertyValue);
}

auto PropertyItem::getFloat() const -> float {
	Exception::Throw(_propertyType == PropertyItemType::Float, "PropertyItem::getFloat invalid type");
	return std::get<float>(_propertyValue);
}

auto PropertyItem::getRange() const -> PropertyRange {
	Exception::Throw(_propertyType == PropertyItemType::Range, "PropertyItem::getRange invalid type");
	return std::get<PropertyRange>(_propertyValue);
}

auto PropertyItem::getFloat2() const -> Math::float2 {
	Exception::Throw(_propertyType == PropertyItemType::Float2, "PropertyItem::getFloat2 invalid type");
	return std::get<Math::float2>(_propertyValue);
}

auto PropertyItem::getFloat3() const -> Math::float3 {
	Exception::Throw(_propertyType == PropertyItemType::Float3, "PropertyItem::getFloat3 invalid type");
	return std::get<Math::float3>(_propertyValue);
}

auto PropertyItem::getFloat4() const -> Math::float4 {
	Exception::Throw(_propertyType == PropertyItemType::Float4, "PropertyItem::getFloat4 invalid type");
	return std::get<Math::float4>(_propertyValue);
}

auto PropertyItem::getTexture2D() const -> PropertyTexture {
	Exception::Throw(_propertyType == PropertyItemType::Texture2D, "PropertyItem::getTexture2D invalid type");
	return std::get<PropertyTexture>(_propertyValue);
}

auto PropertyItem::getTexture2DPath() const -> std::string {
	Exception::Throw(_propertyType == PropertyItemType::Texture2D, "PropertyItem::getTexture2DPath invalid type");
	switch (getTexture2D()) {
	case PropertyTexture::White:
		return "White";
	case PropertyTexture::Black:
		return "Black";
	case PropertyTexture::Bump:
		return "Bump";
	case PropertyTexture::None:
	default: ;
		Exception::Throw("PropertyItem::getTexture2DPath invalid texture default value");
		return "";
	}
}

auto PropertyItem::getMatrix() const -> PropertyMatrix {
	Exception::Throw(_propertyType == PropertyItemType::Matrix, "PropertyItem::getMatrix invalid type");
	return std::get<PropertyMatrix>(_propertyValue);
}

}
