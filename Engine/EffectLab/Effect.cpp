#include "Effect.h"
#include "Pass.h"
#include "PropertyBlock.h"

namespace Eureka {

Effect::Effect() {

}

Effect::~Effect() {

}

auto Effect::getEffectSourcePath() const -> const stdfs::path & {
	return _effectSourcePath;
}

auto Effect::getPasses() const -> const std::vector<std::unique_ptr<Pass>> & {
	return _passes;
}

auto Effect::getPropertyBlock() const -> PropertyBlock * {
	return _propertyBlock.get();
}

auto Effect::getIncludeContent() const -> WRL::ComPtr<IDxcBlobEncoding> {
	return _pIncludeContent;
}

}
