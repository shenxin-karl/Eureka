#pragma once
#include "BaseParser.h"
#include <Dx12lib/Tool/D3Dx12.h>

namespace Eureka {

class BlendParser : public BaseParser {
	constexpr static size_t kMaxRenderTarget = 7;
public:
	explicit BlendParser(std::string effectSourcePath);
	std::any visitPassBlendRTOff(pd::EffectLabParser::PassBlendRTOffContext *context) override;
	std::any visitPassBlendColor(pd::EffectLabParser::PassBlendColorContext *context) override;
	std::any visitPassBlendRTColor(pd::EffectLabParser::PassBlendRTColorContext *context) override;
	std::any visitPassBlendColorAlpha(pd::EffectLabParser::PassBlendColorAlphaContext *context) override;
	std::any visitPassBlendRTColorAlpha(pd::EffectLabParser::PassBlendRTColorAlphaContext *context) override;
	std::any visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) override;
	std::any visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) override;
	auto getBlendDesc() const -> const D3D12_BLEND_DESC &;
private:
	std::string			_effectSourcePath;
	Location			_renderTargetBlend[kMaxRenderTarget];
	Location			_renderTargetColorMask[kMaxRenderTarget];
	Location			_alphaToMask;
	D3D12_BLEND_DESC	_blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
};

}
