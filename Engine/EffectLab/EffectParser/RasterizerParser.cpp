#include "RasterizerParser.h"

namespace Eureka {

RasterizerParser::RasterizerParser(std::string effectSourcePath)
: _effectSourcePath(std::move(effectSourcePath))
{
}

std::any RasterizerParser::visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) {
	return BaseParser::visitPassCullMode(context);
}

std::any RasterizerParser::visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) {
	return BaseParser::visitPassZClipMode(context);
}

std::any RasterizerParser::visitPassOffset(pd::EffectLabParser::PassOffsetContext *context) {
	return BaseParser::visitPassOffset(context);
}

std::any RasterizerParser::visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) {
	return BaseParser::visitPassConservative(context);
}

}
