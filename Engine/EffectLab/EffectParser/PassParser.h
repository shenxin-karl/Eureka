#pragma once
#include "BaseParser.h"

namespace Eureka {

class Pass;
class PassParser : public BaseParser {
public:
	PassParser(std::string effectSourcePath);
	auto parserPass(pd::EffectLabParser::PassContext *ctx) -> std::unique_ptr<Pass>;
	std::any visitPassVertexShader(pd::EffectLabParser::PassVertexShaderContext *context) override;
	std::any visitPassGeometryShader(pd::EffectLabParser::PassGeometryShaderContext *context) override;
	std::any visitPassHullShader(pd::EffectLabParser::PassHullShaderContext *context) override;
	std::any visitPassDomainShader(pd::EffectLabParser::PassDomainShaderContext *context) override;
	std::any visitPassPixelShader(pd::EffectLabParser::PassPixelShaderContext *context) override;
	std::any visitPassRenderQueue(pd::EffectLabParser::PassRenderQueueContext *context) override;
	std::any visitPassShaderFeature(pd::EffectLabParser::PassShaderFeatureContext *context) override;
	std::any visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) override;
	std::any visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) override;
	std::any visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) override;
	std::any visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) override;
	std::any visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) override;
	std::any visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) override;
	std::any visitPassBlend(pd::EffectLabParser::PassBlendContext *context) override;
	std::any visitPassBlendOp(pd::EffectLabParser::PassBlendOpContext *context) override;
	std::any visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) override;
	std::any visitPassStencil(pd::EffectLabParser::PassStencilContext *context) override;
private:
	std::string _effectSourcePath;
	
};


}
