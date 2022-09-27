#include "Material.h"

namespace rgph {

Material::Material(std::string name) : _materialName(std::move(name)) {
	// 在派生类中构建 Technique
}

const std::string & Material::getMaterialName() const {
	return _materialName;
}

size_t Material::getNumTechnique() const {
	return _techniques.size();
}

std::shared_ptr<Technique> Material::getTechnique(size_t idx) const {
	assert(idx < _techniques.size());
	return _techniques[idx];
}

VertexInputSlots Material::getVertexInputSlots() const {
	return _vertexInputSlots;
}

Material::~Material() {
}

}
