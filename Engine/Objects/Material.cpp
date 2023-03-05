#include "Material.h"
#include "MaterialKeyword.h"
#include "MaterialProperty.h"
#include "EffectLab/Effect.h"
#include "Foundation/Exception.h"

namespace Eureka {

Material::Material(std::shared_ptr<Effect> pEffect) : _pEffect(std::move(pEffect)) {
	Exception::Throw(_pEffect != nullptr, "pEffect is nullptr");
	_pMaterialProperty = std::make_unique<MaterialProperty>(this);
	_pMaterialKeyword = std::make_unique<MaterialKeyword>(this);
	_passMask.flip();
}

Material::~Material() {
}

bool Material::setBool(const std::string &name, bool val) {
	return _pMaterialProperty->setBool(name, val);
}

bool Material::setInt(const std::string &name, int val) {
	return _pMaterialProperty->setInt(name, val);
}

bool Material::setFloat(const std::string &name, float val) {
	return _pMaterialProperty->setFloat(name, val);
}

bool Material::setFloat2(const std::string &name, const Math::float2 &val) {
	return _pMaterialProperty->setFloat2(name, val);
}

bool Material::setFloat3(const std::string &name, const Math::float3 &val) {
	return _pMaterialProperty->setFloat3(name, val);
}

bool Material::setFloat4(const std::string &name, const Math::float4 &val) {
	return _pMaterialProperty->setFloat4(name, val);
}

bool Material::setMatrix(const std::string &name, const Math::float4x4 &val) {
	return _pMaterialProperty->setMatrix(name, val);
}

bool Material::setTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> pTexture) {
	return _pMaterialProperty->setTexture(name, std::move(pTexture));
}

bool Material::getBool(const std::string &name, bool &outVal) const {
	return _pMaterialProperty->getBool(name, outVal);
}

bool Material::getInt(const std::string &name, int &outVal) const {
	return _pMaterialProperty->getInt(name, outVal);
}

bool Material::getFloat(const std::string &name, float &outVal) const {
	return _pMaterialProperty->getFloat(name, outVal);
}

bool Material::getFloat2(const std::string &name, Math::float2 &outVal) const {
	return _pMaterialProperty->getFloat2(name, outVal);
}

bool Material::getFloat3(const std::string &name, Math::float3 &outVal) const {
	return _pMaterialProperty->getFloat3(name, outVal);
}

bool Material::getFloat4(const std::string &name, Math::float4 &outVal) const {
	return _pMaterialProperty->getFloat4(name, outVal);
}

bool Material::getMatrix(const std::string &name, Math::float4x4 &outMatrix) const {
	return _pMaterialProperty->getMatrix(name, outMatrix);
}

bool Material::getTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> &outTexture) const {
	return _pMaterialProperty->getTexture(name, outTexture);
}

bool Material::isKeywordEnable(const std::string &keyword) const {
	return _pMaterialKeyword->isKeywordEnable(keyword);
}

bool Material::disableKeyword(const std::string &keyword, bool flushPassVariant) {
	auto toReturn = _pMaterialKeyword->disableKeyword(keyword, flushPassVariant);
	_renderObjectDirty |= toReturn;
	return toReturn;
}

bool Material::enableKeyword(const std::string &keyword, bool flushPassVariant) {
	auto toReturn = _pMaterialKeyword->enableKeyword(keyword, flushPassVariant);
	_renderObjectDirty |= toReturn;
	return toReturn;
}

void Material::flushPassVariant() {
	_pMaterialKeyword->flushPassVariant();
}

bool Material::isRenderObjectDirty() const {
	return _renderObjectDirty;
}

void Material::resetRenderObjectDirty() {
	_renderObjectDirty = false;
}

bool Material::isPassEnable(size_t index) const {
	if (index >= _pEffect->getPasses().size()) {
		return false;
	}
	return _passMask.test(index);
}

bool Material::enablePass(size_t index) {
	if (index >= _pEffect->getPasses().size()) {
		return false;
	}
	if (_passMask.test(index)) {
		return true;
	}
	_passMask.set(index, true);
	_renderObjectDirty = true;
	return true;
}

bool Material::disablePass(size_t index) {
	if (index >= _pEffect->getPasses().size()) {
		return false;
	}
	if (!_passMask.test(index)) {
		return true;
	}
	_passMask.set(index, false);
	_renderObjectDirty = true;
	return true;
}
}
