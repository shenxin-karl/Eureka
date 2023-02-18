#pragma once
#include "BaseParser.h"
#include "EffectLab/Pass.h"
#include "RasterizerParser.h"
#include "BlendParser.h"
#include "DepthStencilParser.h"

namespace Eureka {

class Pass;
class PassParser : public BaseParser {
public:
	PassParser(std::string effectSourcePath);
	auto parse(pd::EffectLabParser::PassContext *ctx) -> std::unique_ptr<Pass>;
	std::any visitPass_tag(ParserDetails::EffectLabParser::Pass_tagContext *context) override;
	std::any visitPassSourcePath(ParserDetails::EffectLabParser::PassSourcePathContext *context) override;
	std::any visitPassVertexShader(pd::EffectLabParser::PassVertexShaderContext *context) override;
	std::any visitPassHullShader(pd::EffectLabParser::PassHullShaderContext *context) override;
	std::any visitPassDomainShader(pd::EffectLabParser::PassDomainShaderContext *context) override;
	std::any visitPassGeometryShader(pd::EffectLabParser::PassGeometryShaderContext *context) override;
	std::any visitPassPixelShader(pd::EffectLabParser::PassPixelShaderContext *context) override;
	std::any visitPassRenderQueue(pd::EffectLabParser::PassRenderQueueContext *context) override;
	std::any visitPassShaderFeature(pd::EffectLabParser::PassShaderFeatureContext *context) override;
	std::any visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) override;
	std::any visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) override;
	std::any visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) override;
	std::any visitPassZWriteMode(ParserDetails::EffectLabParser::PassZWriteModeContext *context) override;
	std::any visitPassOffset(ParserDetails::EffectLabParser::PassOffsetContext *context) override;
	std::any visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) override;
	std::any visitPassBlend(pd::EffectLabParser::PassBlendContext *context) override;
	std::any visitPassBlendOp(pd::EffectLabParser::PassBlendOpContext *context) override;
	std::any visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) override;
	std::any visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) override;
	std::any visitPassStencil(pd::EffectLabParser::PassStencilContext *context) override;
private:
	void parserShaderThrow(const LocAndObject<std::string> &shader, const antlr4::Token *pToken, std::string_view keyword) const;
private:
	std::string									_effectSourcePath;
	std::unique_ptr<Pass>						_pass;
	LocAndObject<std::string>					_sourcePath;
	LocAndObject<std::string>					_vertexShader;
	LocAndObject<std::string>					_hullShader;
	LocAndObject<std::string>					_domainShader;
	LocAndObject<std::string>					_geometryShader;
	LocAndObject<std::string>					_pixelShader;
	LocAndObject<RenderQueueLabel>				_renderQueueLabel;
	std::shared_ptr<ShaderKeywordSet>			_pKeywordSet;
	LocAndObject<std::string>					_zTestMode;
	LocAndObject<std::string>					_zWriteMode;
	std::unordered_map<std::string, Location>	_macroLocationMap; 
	RasterizerParser							_rasterizerParser;
	BlendParser									_blendParser;
	DepthStencilParser							_depthStencilParser;
};


}
