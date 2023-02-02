#pragma once
#include "BaseParser.h"
#include "EffectLab/PropertyBlock.h"
#include "EffectLab/PropertyItem.h"

namespace Eureka {

class PropertyBlock;
class PropertyBlockParser : public BaseParser {
public:
	explicit PropertyBlockParser(std::string effectSourcePath);
	auto parserPropertyBlock(pd::EffectLabParser::Property_blockContext *ctx) -> std::unique_ptr<PropertyBlock>;
	std::any visitNumber_val(pd::EffectLabParser::Number_valContext *context) override;
	std::any visitProperty_range_type(ParserDetails::EffectLabParser::Property_range_typeContext *context) override;
	std::any visitProperty_range_val(ParserDetails::EffectLabParser::Property_range_valContext *context) override;
	std::any visitProperty_bool_val(pd::EffectLabParser::Property_bool_valContext *context) override;
	std::any visitProperty_int_val(pd::EffectLabParser::Property_int_valContext *context) override;
	std::any visitProperty_float_val(pd::EffectLabParser::Property_float_valContext *context) override;
	std::any visitProperty_float2_val(pd::EffectLabParser::Property_float2_valContext *context) override;
	std::any visitProperty_float3_val(pd::EffectLabParser::Property_float3_valContext *context) override;
	std::any visitProperty_float4_val(pd::EffectLabParser::Property_float4_valContext *context) override;
	std::any visitProperty_texture_val(pd::EffectLabParser::Property_texture_valContext *context) override;
	std::any visitProperty_matrix_val(pd::EffectLabParser::Property_matrix_valContext *context) override;
	std::any visitProperty_name(ParserDetails::EffectLabParser::Property_nameContext *context) override;
	std::any visitProperty_description(ParserDetails::EffectLabParser::Property_descriptionContext *context) override;
	std::any visitPropertyItemBool(ParserDetails::EffectLabParser::PropertyItemBoolContext *context) override;
	std::any visitPropertyItemInt(ParserDetails::EffectLabParser::PropertyItemIntContext *context) override;
	std::any visitPropertyItemRange(ParserDetails::EffectLabParser::PropertyItemRangeContext *context) override;
	std::any visitPropertyItemFloat(ParserDetails::EffectLabParser::PropertyItemFloatContext *context) override;
	std::any visitPropertyItemFloat2(ParserDetails::EffectLabParser::PropertyItemFloat2Context *context) override;
	std::any visitPropertyItemFloat3(ParserDetails::EffectLabParser::PropertyItemFloat3Context *context) override;
	std::any visitPropertyItemFloat4(ParserDetails::EffectLabParser::PropertyItemFloat4Context *context) override;
	std::any visitPropertyItemTexture(ParserDetails::EffectLabParser::PropertyItemTextureContext *context) override;
	std::any visitPropertyItemMatrix(ParserDetails::EffectLabParser::PropertyItemMatrixContext *context) override;
private:
	struct PropertyVar {
		size_t line = 0;
		size_t column = 0;
	};
private:
	std::string _effectSourcePath;
	std::unordered_map<std::string, PropertyVar> _propertyVars;
};

}
