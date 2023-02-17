#pragma once
#include "BaseParser.h"
#include <Dx12lib/Tool/D3Dx12.h>

namespace Eureka {

class BlendParser : public BaseParser {
	constexpr static size_t kMaxNumRenderTarget = 8;
public:
	explicit BlendParser(std::string effectSourcePath);
	std::any visitPassBlend(ParserDetails::EffectLabParser::PassBlendContext *context) override;
	std::any visitPassBlendOff(ParserDetails::EffectLabParser::PassBlendOffContext *context) override;
	std::any visitPassBlendRTOff(pd::EffectLabParser::PassBlendRTOffContext *context) override;
	std::any visitPassBlendColor(pd::EffectLabParser::PassBlendColorContext *context) override;
	std::any visitPassBlendRTColor(pd::EffectLabParser::PassBlendRTColorContext *context) override;
	std::any visitPassBlendColorAlpha(pd::EffectLabParser::PassBlendColorAlphaContext *context) override;
	std::any visitPassBlendRTColorAlpha(pd::EffectLabParser::PassBlendRTColorAlphaContext *context) override;
	std::any visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) override;
	std::any visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) override;
	auto getBlendDesc() const -> const D3D12_BLEND_DESC &;
private:
	void redefinitionThrow(std::string_view fmt, 
		const antlr4::Token *pToken, 
		const LocAndObject<std::string> &object) const;
	size_t visitRenderTargetID(const std::string &intLiteral, const antlr4::Token *pToken) const;
	static auto visitBlendFactorLabel(const std::string &stringLiteral) -> D3D12_BLEND;
private:
	std::string					_effectSourcePath;
	LocAndObject<std::string>	_renderTargetBlend[kMaxNumRenderTarget];
	Location					_renderTargetColorMask[kMaxNumRenderTarget];
	Location					_alphaToMask;
	D3D12_BLEND_DESC			_blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
};

}
