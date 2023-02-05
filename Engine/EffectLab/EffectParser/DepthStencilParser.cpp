#include "DepthStencilParser.h"

namespace Eureka {


DepthStencilParser::DepthStencilParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath)) {
}

auto DepthStencilParser::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _depthStencilDesc;
}

std::any DepthStencilParser::visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) {
	return BaseParser::visitPassZWriteMode(context);
}

std::any DepthStencilParser::visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) {
	return BaseParser::visitPassZTestMode(context);
}

std::any DepthStencilParser::visitPassStencil(pd::EffectLabParser::PassStencilContext *context) {
	return BaseParser::visitPassStencil(context);
}

std::any DepthStencilParser::visitStencilRef(pd::EffectLabParser::StencilRefContext *context) {
	return BaseParser::visitStencilRef(context);
}

std::any DepthStencilParser::visitStencilReadMask(pd::EffectLabParser::StencilReadMaskContext *context) {
	return BaseParser::visitStencilReadMask(context);
}

std::any DepthStencilParser::visitStencilWriteMask(pd::EffectLabParser::StencilWriteMaskContext *context) {
	return BaseParser::visitStencilWriteMask(context);
}

std::any DepthStencilParser::visitStencilComp(pd::EffectLabParser::StencilCompContext *context) {
	return BaseParser::visitStencilComp(context);
}

std::any DepthStencilParser::visitStencilPassOp(pd::EffectLabParser::StencilPassOpContext *context) {
	return BaseParser::visitStencilPassOp(context);
}

std::any DepthStencilParser::visitStencilFailOp(pd::EffectLabParser::StencilFailOpContext *context) {
	return BaseParser::visitStencilFailOp(context);
}

std::any DepthStencilParser::visitStencilZFailOp(pd::EffectLabParser::StencilZFailOpContext *context) {
	return BaseParser::visitStencilZFailOp(context);
}

std::any DepthStencilParser::visitStencilCompBackOp(pd::EffectLabParser::StencilCompBackOpContext *context) {
	return BaseParser::visitStencilCompBackOp(context);
}

std::any DepthStencilParser::visitStencilPassBackOp(pd::EffectLabParser::StencilPassBackOpContext *context) {
	return BaseParser::visitStencilPassBackOp(context);
}

std::any DepthStencilParser::visitStencilFailBackOp(pd::EffectLabParser::StencilFailBackOpContext *context) {
	return BaseParser::visitStencilFailBackOp(context);
}

std::any DepthStencilParser::visitStencilZFailBackOp(pd::EffectLabParser::StencilZFailBackOpContext *context) {
	return BaseParser::visitStencilZFailBackOp(context);
}

std::any DepthStencilParser::visitStencilCompFrontOp(pd::EffectLabParser::StencilCompFrontOpContext *context) {
	return BaseParser::visitStencilCompFrontOp(context);
}

std::any DepthStencilParser::visitStencilPassFrontOp(pd::EffectLabParser::StencilPassFrontOpContext *context) {
	return BaseParser::visitStencilPassFrontOp(context);
}

std::any DepthStencilParser::visitStencilFailFrontOp(pd::EffectLabParser::StencilFailFrontOpContext *context) {
	return BaseParser::visitStencilFailFrontOp(context);
}

std::any DepthStencilParser::visitStencilZFailFrontOp(pd::EffectLabParser::StencilZFailFrontOpContext *context) {
	return BaseParser::visitStencilZFailFrontOp(context);
}

}
