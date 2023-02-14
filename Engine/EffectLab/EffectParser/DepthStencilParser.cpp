#include "DepthStencilParser.h"
#include "Foundation/Exception.h"

namespace Eureka {


DepthStencilParser::DepthStencilParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath)) {
}

auto DepthStencilParser::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _depthStencilDesc;
}

auto DepthStencilParser::getStencilRef() -> int {
	return _stencilRef.hasValue() ? _stencilRef.get() : 0;
}

std::any DepthStencilParser::visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) {
	auto *token = context->getStart();
	if (_zWriteMode.hasValue()) {
		redefinitionThrow("{} {}:{} keyword 'ZWrite' redefinition the last location at {}:{}\n"
			"the last value is '{}'!",
			token,
			_zWriteMode
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
		redefinitionThrow("{} {}:{} keyword 'ZTest' redefinition the last location at {}:{}\n"
			"the last value is '{}'!",
			token,
			_zTestMode
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
	_depthStencilDesc.StencilEnable = !context->pass_stencil()->stencil_item().empty();
	for (auto *stencilItem : context->pass_stencil()->stencil_item()) {
		stencilItem->accept(this);
	}
	return NullAny;
}

std::any DepthStencilParser::visitStencilRef(pd::EffectLabParser::StencilRefContext *context) {
	auto *token = context->stencil_ref()->getStart();
	if (_stencilRef.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'Ref' redefinition, the last location at {}:{}\n"
			"the last value is '{}'",
			token,
			_stencilRef
		);
	}

	int refValue = std::stoi(context->stencil_ref()->IntLiteral()->getText());
	if (refValue < 0 || refValue > 255) {
		Exception::Throw("{} {}:{} the Stencil Ref value '{}' out of range(0, 255)",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			refValue
		);
	}

	_stencilRef.set(refValue);
	_stencilRef.setLocation(token);
	return NullAny;
}

std::any DepthStencilParser::visitStencilReadMask(pd::EffectLabParser::StencilReadMaskContext *context) {
	auto *token = context->stencil_read_mask()->getStart();
	if (_stencilReadMask.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'ReadMask' redefinition,"
			"the last location at {}:{}\n the last value is '{}'",
			token,
			_stencilReadMask
		);
	}

	int readMaskValue = std::stoi(context->stencil_read_mask()->IntLiteral()->getText());
	if (readMaskValue < 0 || readMaskValue > 255) {
		Exception::Throw("{} {}:{} the Stencil ReadMask value '{}' out of range(0, 255)",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			readMaskValue
		);
	}

	_stencilReadMask.set(readMaskValue);
	_stencilReadMask.setLocation(token);
	_depthStencilDesc.StencilReadMask = static_cast<UINT8>(readMaskValue);
	return NullAny;
}

std::any DepthStencilParser::visitStencilWriteMask(pd::EffectLabParser::StencilWriteMaskContext *context) {
	auto *token = context->stencil_write_mask()->getStart();
	if (_stencilWriteMask.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'WriteMask' redefinition,"
			"the last location at {}:{}\n the last value is '{}'",
			token,
			_stencilWriteMask
		);
	}

	int readMaskValue = std::stoi(context->stencil_write_mask()->IntLiteral()->getText());
	if (readMaskValue < 0 || readMaskValue > 255) {
		Exception::Throw("{} {}:{} the Stencil keyword 'WriteMask' value '{}' out of range(0, 255)",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine(),
			readMaskValue
		);
	}

	_stencilWriteMask.set(readMaskValue);
	_stencilWriteMask.setLocation(token);
	_depthStencilDesc.StencilWriteMask = static_cast<UINT8>(readMaskValue);
	return NullAny;
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
