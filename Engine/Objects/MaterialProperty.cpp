#include "MaterialProperty.h"
#include "Material.h"
#include "EffectLab/Effect.h"
#include "EffectLab/PropertyBlock.h"

namespace Eureka {

MaterialProperty::MaterialProperty(Material *pMaterial) : _pMaterial(pMaterial) {
	//_pConstantBuffer = pMaterial->_pEffect->getPropertyBlock()
}

bool MaterialProperty::setBool(const std::string &name, bool val) {
}

bool MaterialProperty::setInt(const std::string &name, int val) {
}

bool MaterialProperty::setFloat(const std::string &name, float val) {
}

bool MaterialProperty::setFloat2(const std::string &name, const Math::float2 &val) {
}

bool MaterialProperty::setFloat3(const std::string &name, const Math::float3 &val) {
}

bool MaterialProperty::setFloat4(const std::string &name, const Math::float4 &val) {
}

bool MaterialProperty::setMatrix(const std::string &name, const Math::float4x4 &val) {
}

bool MaterialProperty::setTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> pTexture) {
}

bool MaterialProperty::getBool(const std::string &name, bool &outVal) const {
}

bool MaterialProperty::getInt(const std::string &name, int &outVal) const {
}

bool MaterialProperty::getFloat(const std::string &name, float &outVal) const {
}

bool MaterialProperty::getFloat2(const std::string &name, Math::float2 &outVal) const {
}

bool MaterialProperty::getFloat3(const std::string &name, Math::float3 &outVal) const {
}

bool MaterialProperty::getFloat4(const std::string &name, Math::float4 &outVal) const {
}

bool MaterialProperty::getMatrix(const std::string &name, Math::float4x4 &outMatrix) const {
}

bool MaterialProperty::getTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> &outTexture) const {
}
}
