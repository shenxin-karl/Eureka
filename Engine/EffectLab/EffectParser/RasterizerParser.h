#pragma once
#include "BaseParser.h"
#include <Dx12lib/Tool/D3Dx12.h>

namespace Eureka {

class RasterizerParser : public BaseParser {
public:
	RasterizerParser(std::string effectSourcePath);
	std::any visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) override;
	std::any visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) override;
	std::any visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) override;
	std::any visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) override;
private:
	struct RasterizerOffset {
		float bias;
		float slopeScaleDepthBias;
	};
private:
	std::string						    _effectSourcePath;
	LocAndObject<std::string>			_cullMode;
	LocAndObject<std::string>			_zClipMode;
	LocAndObject<RasterizerOffset>		_offset;
	D3D12_RASTERIZER_DESC				_rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
};

}
