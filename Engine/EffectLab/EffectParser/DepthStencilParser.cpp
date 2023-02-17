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
	auto *pToken = context->getStart();
	if (_stencilCompOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'Comp' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilCompOp
		);
	}

	auto compareLabel = context->stencil_comp()->StencilCompareLabel()->getText();
	auto compareState = visitStencilCompareLabel(compareLabel);
	_stencilCompOp.setLocation(pToken);
	_stencilCompOp.set(compareLabel);
	_depthStencilDesc.FrontFace.StencilFunc = compareState;
	_depthStencilDesc.BackFace.StencilFunc = compareState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilPassOp(pd::EffectLabParser::StencilPassOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilPassOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'Pass' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilPassOp
		);
	}

	auto stencilOpLabel = context->stencil_pass_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilPassOp.setLocation(pToken);
	_stencilPassOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilPassOp = stencilOpState;
	_depthStencilDesc.BackFace.StencilPassOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilFailOp(pd::EffectLabParser::StencilFailOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilFailOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'Fail' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilFailOp
		);
	}

	auto stencilOpLabel = context->stencil_fail_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilFailOp.setLocation(pToken);
	_stencilFailOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilFailOp = stencilOpState;
	_depthStencilDesc.BackFace.StencilFailOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilZFailOp(pd::EffectLabParser::StencilZFailOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilZFailOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'ZFail' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilZFailOp
		);
	}

	auto stencilOpLabel = context->stencil_zfail_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilZFailOp.setLocation(pToken);
	_stencilZFailOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilDepthFailOp = stencilOpState;
	_depthStencilDesc.BackFace.StencilDepthFailOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilCompBackOp(pd::EffectLabParser::StencilCompBackOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilCompBackOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'CompBack' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilCompBackOp
		);
	}

	auto compareLabel = context->stencil_comp_back_op()->StencilCompareLabel()->getText();
	auto compareState = visitStencilCompareLabel(compareLabel);
	_stencilCompBackOp.setLocation(pToken);
	_stencilCompBackOp.set(compareLabel);
	_depthStencilDesc.BackFace.StencilFunc = compareState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilPassBackOp(pd::EffectLabParser::StencilPassBackOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilPassBackOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'PassBack' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilPassBackOp
		);
	}

	auto stencilOpLabel = context->stancil_pass_back_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilPassBackOp.setLocation(pToken);
	_stencilPassBackOp.set(stencilOpLabel);
	_depthStencilDesc.BackFace.StencilPassOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilFailBackOp(pd::EffectLabParser::StencilFailBackOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilFailBackOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'FailBack' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilFailBackOp
		);
	}

	auto stencilOpLabel = context->stencil_fail_back_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilFailBackOp.setLocation(pToken);
	_stencilFailBackOp.set(stencilOpLabel);
	_depthStencilDesc.BackFace.StencilFailOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilZFailBackOp(pd::EffectLabParser::StencilZFailBackOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilZFailBackOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'ZFailBack' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilZFailBackOp
		);
	}

	auto stencilOpLabel = context->stencil_zfail_back_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilZFailBackOp.setLocation(pToken);
	_stencilZFailBackOp.set(stencilOpLabel);
	_depthStencilDesc.BackFace.StencilDepthFailOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilCompFrontOp(pd::EffectLabParser::StencilCompFrontOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilCompFrontOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'CompFont' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilCompFrontOp
		);
	}

	auto compareLabel = context->stencil_comp_front_op()->StencilCompareLabel()->getText();
	auto compareState = visitStencilCompareLabel(compareLabel);
	_stencilCompFrontOp.setLocation(pToken);
	_stencilCompFrontOp.set(compareLabel);
	_depthStencilDesc.FrontFace.StencilFunc = compareState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilPassFrontOp(pd::EffectLabParser::StencilPassFrontOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilPassFrontOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'PassFront' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilPassFrontOp
		);
	}

	auto stencilOpLabel = context->stancil_pass_front_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilPassFrontOp.setLocation(pToken);
	_stencilPassFrontOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilPassOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilFailFrontOp(pd::EffectLabParser::StencilFailFrontOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilFailFrontOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'FailFront' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilFailFrontOp
		);
	}

	auto stencilOpLabel = context->stencil_fail_front_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilFailFrontOp.setLocation(pToken);
	_stencilFailFrontOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilFailOp = stencilOpState;
	return NullAny;
}

std::any DepthStencilParser::visitStencilZFailFrontOp(pd::EffectLabParser::StencilZFailFrontOpContext *context) {
	auto *pToken = context->getStart();
	if (_stencilZFailFrontOp.hasValue()) {
		redefinitionThrow("{} {}:{} Stencil keyword 'ZFailFront' redefinition, the last location at {}:{},\n"
			" the last value is {}",
			pToken,
			_stencilZFailFrontOp
		);
	}

	auto stencilOpLabel = context->stencil_zfail_front_op()->StencilOpLabel()->getText();
	auto stencilOpState = visitStencilOpLabel(stencilOpLabel);
	_stencilZFailFrontOp.setLocation(pToken);
	_stencilZFailFrontOp.set(stencilOpLabel);
	_depthStencilDesc.FrontFace.StencilDepthFailOp = stencilOpState;
	return NullAny;
}

auto DepthStencilParser::visitStencilOpLabel(const std::string &stencilOpLabel) -> D3D12_STENCIL_OP {
	if (stencilOpLabel == "Keep") {
		return D3D12_STENCIL_OP_KEEP;
	} else if (stencilOpLabel == "Zero") {
		return D3D12_STENCIL_OP_ZERO;
	} else if (stencilOpLabel == "Replace") {
		return D3D12_STENCIL_OP_REPLACE;
	} else if (stencilOpLabel == "IncrSat") {
		return D3D12_STENCIL_OP_INCR_SAT;
	} else if (stencilOpLabel == "DecrSat") {
		return D3D12_STENCIL_OP_DECR_SAT;
	} else if (stencilOpLabel == "Invert") {
		return D3D12_STENCIL_OP_INVERT;
	} else if (stencilOpLabel == "IncrWrap") {
		return D3D12_STENCIL_OP_INCR;
	} else if (stencilOpLabel == "DecrWrap") {
		return D3D12_STENCIL_OP_DECR;
	}
	return D3D12_STENCIL_OP_KEEP;
}

auto DepthStencilParser::visitStencilCompareLabel(const std::string &stencilCompareLabel) -> D3D12_COMPARISON_FUNC {
	if (stencilCompareLabel == "Never") {
		return D3D12_COMPARISON_FUNC_NEVER;
	} else if (stencilCompareLabel == "Less") {
		return D3D12_COMPARISON_FUNC_LESS;
	} else if (stencilCompareLabel == "Equal") {
		return D3D12_COMPARISON_FUNC_EQUAL;
	} else if (stencilCompareLabel == "LEqaul") {
		return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	} else if (stencilCompareLabel == "Greater") {
		return D3D12_COMPARISON_FUNC_GREATER;
	} else if (stencilCompareLabel == "NotEqual") {
		return D3D12_COMPARISON_FUNC_NOT_EQUAL;
	} else if (stencilCompareLabel == "GEqual") {
		return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	} else if (stencilCompareLabel == "Always") {
		return D3D12_COMPARISON_FUNC_ALWAYS;
	}
	return D3D12_COMPARISON_FUNC_NEVER;
}

}
