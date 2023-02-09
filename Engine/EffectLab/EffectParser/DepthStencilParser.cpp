#include "DepthStencilParser.h"
#include "Foundation/Exception.h"

namespace Eureka {


DepthStencilParser::DepthStencilParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath)) {
}

auto DepthStencilParser::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _depthStencilDesc;
}

std::any DepthStencilParser::visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) {
	auto *token = context->getStart();
	if (_zWriteMode.hasValue()) {
		Exception::Throw("{} {}:{} keyword 'ZWrite' redefinition the last location at {}:{}\n"
			"the last value is '{}'!",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_zWriteMode.line,
			_zWriteMode.column,
			_zWriteMode.get()
		);
	}

	std::string zWriteLabel = context->pass_zwrite_mode()->OnOffLabel()->getText();
	_zWriteMode.set(zWriteLabel);
	_zWriteMode.setLocation(token);
	if (zWriteLabel == "On") {
		_depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	} else {
		_depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	}
	return NullAny;
}

std::any DepthStencilParser::visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) {
	auto *token = context->getStart();
	if (_zTestMode.hasValue()) {
		Exception::Throw("{} {}:{} keyword 'ZTest' redefinition the last location at {}:{}\n"
			"the last value is '{}'!",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			_zTestMode.line,
			_zTestMode.column,
			_zTestMode.get()
		);
	}

	std::string zTestLabel = context->pass_ztest_mode()->ZTestModeLabel()->getText();
	_zTestMode.set(zTestLabel);
	_zTestMode.setLocation(token);
	if (zTestLabel == "Never") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_NEVER;
	} else if (zTestLabel == "Less") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	} else if (zTestLabel == "Equal") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_EQUAL;
	} else if (zTestLabel == "LEqual") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	} else if (zTestLabel == "GEqual") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_GREATER;
	} else if (zTestLabel == "NotEqual") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_NOT_EQUAL;
	} else if (zTestLabel == "Greater") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	} else if (zTestLabel == "Always") {
		_depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	}
	return NullAny;
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
