#include "BlendParser.h"
#include "Foundation/Exception.h"

namespace Eureka {

BlendParser::BlendParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath))
{
}

std::any BlendParser::visitPassBlend(ParserDetails::EffectLabParser::PassBlendContext *context) {
	return context->pass_blend()->accept(this);
}

std::any BlendParser::visitPassBlendOff(ParserDetails::EffectLabParser::PassBlendOffContext *context) {
	auto *pToken = context->getStart();
	if (_renderTargetBlend[0].hasValue()) {
		redefinitionThrow("{} {}:{} the keyword 'Blend' redefinition, the last location at {}:{}\n"
			"the last value is {}",
			pToken,
			_renderTargetBlend[0]
		);
	}

	_renderTargetBlend[0].setLocation(pToken);
	_renderTargetBlend[0].set("Off");
	_blendDesc.RenderTarget[0].BlendEnable = false;
	return NullAny;
}

std::any BlendParser::visitPassBlendRTOff(pd::EffectLabParser::PassBlendRTOffContext *context) {
	auto *pToken = context->getStart();
	size_t renderTargetId = visitRenderTargetID(context->IntLiteral()->getText(), pToken);
	if (_renderTargetBlend[renderTargetId].hasValue()) {
		redefinitionThrow("{} {}:{} the keyword 'Blend' redefinition, the last location at {}:{}\n"
			"the last value is {}",
			pToken,
			_renderTargetBlend[renderTargetId]
		);
	}

	_renderTargetBlend[renderTargetId].setLocation(pToken);
	_renderTargetBlend[renderTargetId].set(fmt::format("Blend {} Off", renderTargetId));
	_blendDesc.RenderTarget[renderTargetId].BlendEnable = false;
	return NullAny;
}

std::any BlendParser::visitPassBlendColor(pd::EffectLabParser::PassBlendColorContext *context) {
	constexpr size_t renderTargetId = 0;
	auto *pToken = context->getStart();
	if (_renderTargetBlend[renderTargetId].hasValue()) {
		redefinitionThrow("{} {}:{} the keyword 'Blend' redefinition, the last location at {}:{}\n"
			"the last value is {}",
			pToken,
			_renderTargetBlend[renderTargetId]
		);
	}

	auto srcColorLabel = context->BlendFactorLabel(0)->getText();
	auto dstColorLabel = context->BlendFactorLabel(1)->getText();
	_renderTargetBlend[renderTargetId].setLocation(pToken);
	_renderTargetBlend[renderTargetId].set(fmt::format("Blend {} {}", srcColorLabel, dstColorLabel));
	_blendDesc.RenderTarget[renderTargetId].SrcBlend = visitBlendFactorLabel(srcColorLabel);
	_blendDesc.RenderTarget[renderTargetId].DestBlend = visitBlendFactorLabel(dstColorLabel);
	return NullAny;
}

std::any BlendParser::visitPassBlendRTColor(pd::EffectLabParser::PassBlendRTColorContext *context) {
	auto *pToken = context->getStart();
	size_t renderTargetId = visitRenderTargetID(context->IntLiteral()->getText(), pToken);
	if (_renderTargetBlend[renderTargetId].hasValue()) {
		redefinitionThrow("{} {}:{} the keyword 'Blend' redefinition, the last location at {}:{}\n"
			"the last value is {}",
			pToken,
			_renderTargetBlend[renderTargetId]
		);
	}

	auto srcColorLabel = context->BlendFactorLabel(0)->getText();
	auto dstColorLabel = context->BlendFactorLabel(1)->getText();
	_renderTargetBlend[renderTargetId].setLocation(pToken);
	_renderTargetBlend[renderTargetId].set(fmt::format("Blend {} {} {}", renderTargetId, srcColorLabel, dstColorLabel));
	_blendDesc.RenderTarget[renderTargetId].SrcBlend = visitBlendFactorLabel(srcColorLabel);
	_blendDesc.RenderTarget[renderTargetId].DestBlend = visitBlendFactorLabel(dstColorLabel);
	return NullAny;
}

std::any BlendParser::visitPassBlendColorAlpha(pd::EffectLabParser::PassBlendColorAlphaContext *context) {
	return BaseParser::visitPassBlendColorAlpha(context);
}

std::any BlendParser::visitPassBlendRTColorAlpha(pd::EffectLabParser::PassBlendRTColorAlphaContext *context) {
	auto *pToken = context->getStart();
	size_t renderTargetId = visitRenderTargetID(context->IntLiteral()->getText(), pToken);
	if (_renderTargetBlend[renderTargetId].hasValue()) {
		redefinitionThrow("{} {}:{} the keyword 'Blend' redefinition, the last location at {}:{}\n"
			"the last value is {}",
			pToken,
			_renderTargetBlend[renderTargetId]
		);
	}

	auto srcColorLabel = context->BlendFactorLabel(0)->getText();
	auto srcAlphaLabel = context->BlendFactorLabel(1)->getText();
	auto dstColorLabel = context->BlendFactorLabel(2)->getText();
	auto dstAlphaLabel = context->BlendFactorLabel(3)->getText();
	auto hitMsg = fmt::format("Blend {} {} {}, {} {}", 
		renderTargetId,
		srcColorLabel,
		srcAlphaLabel,
		dstColorLabel,
		dstAlphaLabel
	);
	_renderTargetBlend[renderTargetId].setLocation(pToken);
	_renderTargetBlend[renderTargetId].set(hitMsg);
	_blendDesc.RenderTarget[renderTargetId].SrcBlend = visitBlendFactorLabel(srcColorLabel);
	_blendDesc.RenderTarget[renderTargetId].SrcBlendAlpha = visitBlendFactorLabel(srcAlphaLabel);
	_blendDesc.RenderTarget[renderTargetId].DestBlend = visitBlendFactorLabel(dstColorLabel);
	_blendDesc.RenderTarget[renderTargetId].DestBlendAlpha = visitBlendFactorLabel(dstAlphaLabel);
	return NullAny;
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
	if (renderTargetId >= kMaxNumRenderTarget) {
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

void BlendParser::redefinitionThrow(std::string_view fmt, const antlr4::Token *pToken,
	const LocAndObject<std::string> &object) const
{
	Exception::Throw(fmt,
		_effectSourcePath,
		pToken->getLine(),
		pToken->getCharPositionInLine(),
		object.line,
		object.column,
		object.get()
	);
}

size_t BlendParser::visitRenderTargetID(const std::string &intLiteral, const antlr4::Token *pToken) const {
	int renderTargetId = std::stoi(intLiteral);
	if (renderTargetId < 0 || renderTargetId >= static_cast<int>(kMaxNumRenderTarget)) {
		Exception::Throw("{} {}:{} the blend render target id out of range(0, 8), the value is {}",
			_effectSourcePath,
			pToken->getLine(),
			pToken->getCharPositionInLine(),
			renderTargetId
		);
	}
	return static_cast<size_t>(renderTargetId);
}

auto BlendParser::visitBlendFactorLabel(const std::string &stringLiteral) -> D3D12_BLEND {
	if (stringLiteral == "Zero") {
		return D3D12_BLEND_ZERO;
	} else if (stringLiteral == "SrcColor") {
        return D3D12_BLEND_SRC_COLOR;
    } else if (stringLiteral == "SrcAlpha") {
        return D3D12_BLEND_SRC_ALPHA;
    } else if (stringLiteral == "DstColor") {
        return D3D12_BLEND_DEST_COLOR;
    } else if (stringLiteral == "DstAlpha") {
        return D3D12_BLEND_DEST_ALPHA;
    } else if (stringLiteral == "OneMinusSrcColor") {
        return D3D12_BLEND_INV_SRC_COLOR;
    } else if (stringLiteral == "OneMinusSrcAlpha") {
        return D3D12_BLEND_INV_SRC_ALPHA;
    } else if (stringLiteral == "OneMinusDstColor") {
        return D3D12_BLEND_INV_DEST_COLOR;
    } else if (stringLiteral == "OneMinusDstAlpha") { 
        return D3D12_BLEND_INV_DEST_ALPHA;
    }
	return D3D12_BLEND_ZERO;
}

}
