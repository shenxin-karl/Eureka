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
		Exception::Throw("{} {}:{} keyword redefinition the last location at {}:{}, the last value is {}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_zClipMode.line,
			_zClipMode.column,
			_zClipMode.get()
		);
	}

	auto text = context->pass_zclip_mode()->BooleanLiteral()->getText();
	auto zClipMode = visitBoolLiteral(context->pass_zclip_mode()->BooleanLiteral());
	_zClipMode.set(text);
	_zClipMode.setLocation(token);
	_rasterizerDesc.DepthClipEnable = zClipMode;
	return NullAny;
}

std::any RasterizerParser::visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) {
	auto *token = context->getStart();
	if (_depthOffset.hasValue()) {
		Exception::Throw("{} {}:{} keyword redefinition the last location at {}:{},"
			"the last bias is {}, the last slope scale depth bias is {}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_depthOffset.line,
			_depthOffset.column,
			_depthOffset.get().bias,
			_depthOffset.get().slopeScaleDepthBias
		);
	}

	float bias = std::stof(context->pass_offset()->FloatLiteral(0)->getText());
	float slopeScaleDepthBias = std::stof(context->pass_offset()->FloatLiteral(1)->getText());
	_depthOffset.set(RasterizerOffset{ bias, slopeScaleDepthBias });
	_depthOffset.setLocation(token);

	_rasterizerDesc.DepthBias = static_cast<INT>(bias);
	_rasterizerDesc.SlopeScaledDepthBias = slopeScaleDepthBias;
	return NullAny;
}

std::any RasterizerParser::visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) {
	auto token = context->getStart();
	if (_conservative.hasValue()) {
		Exception::Throw("{} {}:{} keyword Conservative redefinition the last location at {}:{} "
			", the last value is {}",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_conservative.line,
			_conservative.column,
			_conservative.get()
		);
	}

	auto text = context->pass_conservative()->BooleanLiteral()->getText();
	bool enable = visitBoolLiteral(context->pass_conservative()->BooleanLiteral());
	_conservative.set(std::move(text));
	_conservative.setLocation(token);
	if (enable) {
		_rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON; 
	} else {
		_rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}
	return NullAny;
}

bool RasterizerParser::visitBoolLiteral(const antlr4::tree::TerminalNode *node) {
	auto text = node->getSymbol()->getText();
	return (text == "true" || text == "True");
}

}
