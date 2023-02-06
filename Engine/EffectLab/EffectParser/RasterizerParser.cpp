#include "RasterizerParser.h"
#include "Foundation/Exception.h"

namespace Eureka {

RasterizerParser::RasterizerParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath))
{
}

std::any RasterizerParser::visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) {
	auto *token = context->getStart();
	if (_cullMode.hasValue()) {
		Exception::Throw("{} {}:{} keyword Cull redefinition at {}:{}, the last value is {}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_cullMode.line,
			_cullMode.column,
			_cullMode.get()
		);
	}

	auto cullLabel = context->pass_cull_mode()->CullModeLabel()->getText();
	_cullMode.set(cullLabel);
	_cullMode.setLocation(token);

	if (cullLabel == "Off") {
		_rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	} else if (cullLabel == "Front") {
		_rasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;
	} else {
		_rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	}
	return NullAny;
}

std::any RasterizerParser::visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) {
	auto *token = context->getStart();
	if (_zClipMode.hasValue()) {
		Exception::Throw("{} {}:{} keyword redefinition at {}:{}, the last value is {}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_zClipMode.line,
			_zClipMode.column,
			_zClipMode.get()
		);
	}

	auto zClipMode = visitBoolLiteral(context->pass_zclip_mode()->BooleanLiteral());
	_zClipMode.set(zClipMode);
	_zClipMode.setLocation(token);
	_rasterizerDesc.DepthClipEnable = _zClipMode.get();
	return NullAny;
}

std::any RasterizerParser::visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) {
	return BaseParser::visitPassOffset(context);
}

std::any RasterizerParser::visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) {
	return BaseParser::visitPassConservative(context);
}

bool RasterizerParser::visitBoolLiteral(const antlr4::tree::TerminalNode *node) {
	auto text = node->getSymbol()->getText();
	return (text == "true" || text == "True");
}

}
