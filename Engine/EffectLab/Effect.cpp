#include "Effect.h"
#include "Pass.h"
#include "PropertyBlock.h"

namespace Eureka {

Effect::Effect() {

}

Effect::~Effect() {

}

auto Effect::getSourcePath() const -> const fs::path & {
	return _sourcePath;
}

auto Effect::getPasses() const -> const std::vector<std::unique_ptr<Pass>> & {
	return _passes;
}

auto Effect::getPropertyBlock() const -> PropertyBlock * {
	return _propertyBlock.get();
}

}
