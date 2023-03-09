#include "Pass.h"
#include "PassVariant.h"

namespace Eureka {

Pass::Pass(const Effect *pEffect) : _pEffect(pEffect) {

}

auto Pass::getEffect() const -> const Effect * {
	return _pEffect;
}

auto Pass::getTag() const -> const std::string & {
	return _tag;
}

auto Pass::getPassVariant(const ShaderKeyword &keyword) -> std::shared_ptr<PassVariant> {
	auto iter = _passVariantMap.find(keyword.getBitset());
	if (iter != _passVariantMap.end()) {
		return iter->second;
	}

	auto pPassVariant = std::make_shared<PassVariant>(this, keyword);
	_passVariantMap[keyword.getBitset()] = pPassVariant;
	return pPassVariant;
}

auto Pass::getKeywordSet() const -> std::shared_ptr<ShaderKeywordSet> {
	return _pKeywordSet;
}

auto Pass::getStencilRef() const -> int {
	return _stencilRef;
}

auto Pass::getRenderQueue() const -> RenderQueueLabel {
	return _renderQueue;
}

auto Pass::getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC & {
	return _rasterizerDesc;
}

auto Pass::getBlendDesc() const -> const D3D12_BLEND_DESC & {
	return _blendDesc;
}

auto Pass::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _depthStencilDesc;
}

auto Pass::getVertexEntryPoint() const -> const std::string & {
	return _vertexEntryPoint;
}

auto Pass::getHullEntryPoint() const -> const std::string & {
	return _hullEntryPoint;
}

auto Pass::getDomainEntryPoint() const -> const std::string & {
	return _domainEntryPoint;
}

auto Pass::getGeometryEntryPoint() const -> const std::string & {
	return _geometryEntryPoint;
}

auto Pass::getPixelEntryPoint() const -> const std::string & {
	return _pixelEntryPoint;
}

auto Pass::getSourceCode() const -> const WRL::ComPtr<IDxcBlobEncoding> & {
	return _pSourceCode;
}

}
