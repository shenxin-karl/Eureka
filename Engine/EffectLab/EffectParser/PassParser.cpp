#include "PassParser.h"
#include "EffectLab/Pass.h"

namespace Eureka {

PassParser::PassParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath)) {
}

auto PassParser::parserPass(pd::EffectLabParser::PassContext *ctx) -> std::unique_ptr<Pass> {
	return nullptr;
}

std::any PassParser::visitPassVertexShader(pd::EffectLabParser::PassVertexShaderContext *context) {
	return BaseParser::visitPassVertexShader(context);
}

std::any PassParser::visitPassGeometryShader(pd::EffectLabParser::PassGeometryShaderContext *context) {
	return BaseParser::visitPassGeometryShader(context);
}

std::any PassParser::visitPassHullShader(pd::EffectLabParser::PassHullShaderContext *context) {
	return BaseParser::visitPassHullShader(context);
}

std::any PassParser::visitPassDomainShader(pd::EffectLabParser::PassDomainShaderContext *context) {
	return BaseParser::visitPassDomainShader(context);
}

std::any PassParser::visitPassPixelShader(pd::EffectLabParser::PassPixelShaderContext *context) {
	return BaseParser::visitPassPixelShader(context);
}

std::any PassParser::visitPassRenderQueue(pd::EffectLabParser::PassRenderQueueContext *context) {
	return BaseParser::visitPassRenderQueue(context);
}

std::any PassParser::visitPassShaderFeature(pd::EffectLabParser::PassShaderFeatureContext *context) {
	return BaseParser::visitPassShaderFeature(context);
}

std::any PassParser::visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) {
	return BaseParser::visitPassCullMode(context);
}

std::any PassParser::visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) {
	return BaseParser::visitPassZClipMode(context);
}

std::any PassParser::visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) {
	return BaseParser::visitPassZTestMode(context);
}

std::any PassParser::visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) {
	return BaseParser::visitPassZWriteMode(context);
}

std::any PassParser::visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) {
	return BaseParser::visitPassOffset(context);
}

std::any PassParser::visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) {
	return BaseParser::visitPassColorMask(context);
}

std::any PassParser::visitPassBlend(pd::EffectLabParser::PassBlendContext *context) {
	return BaseParser::visitPassBlend(context);
}

std::any PassParser::visitPassBlendOp(pd::EffectLabParser::PassBlendOpContext *context) {
	return BaseParser::visitPassBlendOp(context);
}

std::any PassParser::visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) {
	return BaseParser::visitPassAlphaToMask(context);
}

std::any PassParser::visitPassStencil(pd::EffectLabParser::PassStencilContext *context) {
	return BaseParser::visitPassStencil(context);
}

}
