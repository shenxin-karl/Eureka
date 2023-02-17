#pragma once
#include "BaseParser.h"
#include <Dx12lib/Tool/D3Dx12.h>

#include "EffectLab/Pass.h"

namespace Eureka {

class DepthStencilParser : public BaseParser {
public:
	DepthStencilParser(std::string effectSourcePath);
	auto getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &;
	auto getStencilRef() -> int;
	/// depth
	std::any visitPassZWriteMode(pd::EffectLabParser::PassZWriteModeContext *context) override;
	std::any visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) override;
	/// stencil
	std::any visitPassStencil(pd::EffectLabParser::PassStencilContext *context) override;
	std::any visitStencilRef(pd::EffectLabParser::StencilRefContext *context) override;
	std::any visitStencilReadMask(pd::EffectLabParser::StencilReadMaskContext *context) override;
	std::any visitStencilWriteMask(pd::EffectLabParser::StencilWriteMaskContext *context) override;
	/// stencil all face
	std::any visitStencilComp(pd::EffectLabParser::StencilCompContext *context) override;
	std::any visitStencilPassOp(pd::EffectLabParser::StencilPassOpContext *context) override;
	std::any visitStencilFailOp(pd::EffectLabParser::StencilFailOpContext *context) override;
	std::any visitStencilZFailOp(pd::EffectLabParser::StencilZFailOpContext *context) override;
	/// stencil back face
	std::any visitStencilCompBackOp(pd::EffectLabParser::StencilCompBackOpContext *context) override;
	std::any visitStencilPassBackOp(pd::EffectLabParser::StencilPassBackOpContext *context) override;
	std::any visitStencilFailBackOp(pd::EffectLabParser::StencilFailBackOpContext *context) override;
	std::any visitStencilZFailBackOp(pd::EffectLabParser::StencilZFailBackOpContext *context) override;
	/// stencil front face
	std::any visitStencilCompFrontOp(pd::EffectLabParser::StencilCompFrontOpContext *context) override;
	std::any visitStencilPassFrontOp(pd::EffectLabParser::StencilPassFrontOpContext *context) override;
	std::any visitStencilFailFrontOp(pd::EffectLabParser::StencilFailFrontOpContext *context) override;
	std::any visitStencilZFailFrontOp(pd::EffectLabParser::StencilZFailFrontOpContext *context) override;

private:
	template<typename T>
	void redefinitionThrow(std::string_view fmt, const antlr4::Token *token, const LocAndObject<T> &object) const {
		Exception::Throw(fmt,
			_effectSourcePath,
			token->getLine(), 
			token->getCharPositionInLine(), 
			object.line,
			object.column,
			object.get()
		);
	}
	static auto visitStencilOpLabel(const std::string &stencilOpLabel) -> D3D12_STENCIL_OP;
	static auto visitStencilCompareLabel(const std::string &stencilCompareLabel) -> D3D12_COMPARISON_FUNC;
private:
	std::string					_effectSourcePath;
	LocAndObject<std::string>	_zWriteMode;
	LocAndObject<std::string>	_zTestMode;
	LocAndObject<int>			_stencilRef;
	LocAndObject<int>			_stencilReadMask;
	LocAndObject<int>			_stencilWriteMask;
	LocAndObject<std::string>	_stencilCompOp;
	LocAndObject<std::string>	_stencilPassOp;
	LocAndObject<std::string>	_stencilFailOp;
	LocAndObject<std::string>	_stencilZFailOp;
	LocAndObject<std::string>	_stencilCompBackOp;
	LocAndObject<std::string>	_stencilPassBackOp;
	LocAndObject<std::string>	_stencilFailBackOp;
	LocAndObject<std::string>	_stencilZFailBackOp;
	LocAndObject<std::string>	_stencilCompFrontOp;
	LocAndObject<std::string>	_stencilPassFrontOp;
	LocAndObject<std::string>	_stencilFailFrontOp;
	LocAndObject<std::string>	_stencilZFailFrontOp;
	D3D12_DEPTH_STENCIL_DESC	_depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
};

}
