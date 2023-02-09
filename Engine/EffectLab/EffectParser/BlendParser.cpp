#include "BlendParser.h"
#include "Foundation/Exception.h"

namespace Eureka {

BlendParser::BlendParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath))
{
}

std::any BlendParser::visitPassBlendRTOff(pd::EffectLabParser::PassBlendRTOffContext *context) {
	return BaseParser::visitPassBlendRTOff(context);
}

std::any BlendParser::visitPassBlendColor(pd::EffectLabParser::PassBlendColorContext *context) {
	return BaseParser::visitPassBlendColor(context);
}

std::any BlendParser::visitPassBlendRTColor(pd::EffectLabParser::PassBlendRTColorContext *context) {
	return BaseParser::visitPassBlendRTColor(context);
}

std::any BlendParser::visitPassBlendColorAlpha(pd::EffectLabParser::PassBlendColorAlphaContext *context) {
	return BaseParser::visitPassBlendColorAlpha(context);
}

std::any BlendParser::visitPassBlendRTColorAlpha(pd::EffectLabParser::PassBlendRTColorAlphaContext *context) {
	return BaseParser::visitPassBlendRTColorAlpha(context);
}

std::any BlendParser::visitPassAlphaToMask(ParserDetails::EffectLabParser::PassAlphaToMaskContext *context) {
	auto token = context->pass_alpha_to_mask()->getStart();
	if (_alphaToMask.valid()) {
		Exception::Throw("{} {}:{} keyword AlphaToMask redefinition in {} {}:{}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_effectSourcePath,
			_alphaToMask.line,
			_alphaToMask.column
		);
	}

	auto text = token->getText();
	bool enable = text == "On";
	_alphaToMask.setLocation(token);
	_blendDesc.AlphaToCoverageEnable = enable;
	return NullAny;
}

std::any BlendParser::visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) {
	size_t renderTargetId = 0;
	if (auto *pRtIdNode = context->pass_color_mask()->IntLiteral()) {
		renderTargetId = std::stoi(pRtIdNode->getSymbol()->getText());
	}

	auto token = context->pass_color_mask()->getStart();
	if (renderTargetId >= kMaxRenderTarget) {
		Exception::Throw("{} {}:{} ColorMask render target id {} out of range(0, 7)",
			_effectSourcePath,
			renderTargetId,
			token->getLine(),
			token->getCharPositionInLine()
		);

	}

	if (_renderTargetColorMask[renderTargetId].valid()) {
		Exception::Throw("{} {}:{} keyword ColorMask redefinition in {} {}:{}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_effectSourcePath,
			_renderTargetColorMask[renderTargetId].line,
			_renderTargetColorMask[renderTargetId].column
		);
	}

	_renderTargetColorMask[renderTargetId].setLocation(token);

	constexpr UINT8 kMasks[4] = {
		D3D12_COLOR_WRITE_ENABLE_RED,
		D3D12_COLOR_WRITE_ENABLE_GREEN,
		D3D12_COLOR_WRITE_ENABLE_BLUE,
		D3D12_COLOR_WRITE_ENABLE_ALPHA,
	};

	auto text = context->pass_color_mask()->ColorMaskChannel()->getText();
	bool maskFlags[4] = { false, false, false, false };
	UINT8 channelMask = 0;
	for (char c : text) {
		size_t j = 0;
		if (c == 'R') {
			j = 0;
		} else if (c == 'G') {
			j = 1;
		} else if (c == 'B') {
			j = 2;
		} else if (c == 'A') {
			j = 3;
		}
		if (maskFlags[j]) {
			Exception::Throw("{} {}:{} the ColorMask provides a duplicate channel {}",
				_effectSourcePath,
				token->getLine(),
				token->getCharPositionInLine(),
				c
			);
		}
		maskFlags[j] = true;
		channelMask |= kMasks[j];
	}

	_blendDesc.RenderTarget[renderTargetId].RenderTargetWriteMask = channelMask;
	return NullAny;
}

auto BlendParser::getBlendDesc() const -> const D3D12_BLEND_DESC & {
	return _blendDesc;
}

}
