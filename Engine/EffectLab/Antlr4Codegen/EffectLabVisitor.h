
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabParser.h"


namespace Eureka::ParserDetails {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by EffectLabParser.
 */
class  EffectLabVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by EffectLabParser.
   */
    virtual std::any visitEffect(EffectLabParser::EffectContext *context) = 0;

    virtual std::any visitSource_path(EffectLabParser::Source_pathContext *context) = 0;

    virtual std::any visitProperty_block(EffectLabParser::Property_blockContext *context) = 0;

    virtual std::any visitNumber_val(EffectLabParser::Number_valContext *context) = 0;

    virtual std::any visitProperty_bool_type(EffectLabParser::Property_bool_typeContext *context) = 0;

    virtual std::any visitProperty_int_type(EffectLabParser::Property_int_typeContext *context) = 0;

    virtual std::any visitProperty_range_type(EffectLabParser::Property_range_typeContext *context) = 0;

    virtual std::any visitProperty_float_type(EffectLabParser::Property_float_typeContext *context) = 0;

    virtual std::any visitProperty_float2_type(EffectLabParser::Property_float2_typeContext *context) = 0;

    virtual std::any visitProperty_float3_type(EffectLabParser::Property_float3_typeContext *context) = 0;

    virtual std::any visitProperty_float4_type(EffectLabParser::Property_float4_typeContext *context) = 0;

    virtual std::any visitProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext *context) = 0;

    virtual std::any visitProperty_matrix_type(EffectLabParser::Property_matrix_typeContext *context) = 0;

    virtual std::any visitProperty_range_val(EffectLabParser::Property_range_valContext *context) = 0;

    virtual std::any visitProperty_bool_val(EffectLabParser::Property_bool_valContext *context) = 0;

    virtual std::any visitProperty_int_val(EffectLabParser::Property_int_valContext *context) = 0;

    virtual std::any visitProperty_float_val(EffectLabParser::Property_float_valContext *context) = 0;

    virtual std::any visitProperty_float2_val(EffectLabParser::Property_float2_valContext *context) = 0;

    virtual std::any visitProperty_float3_val(EffectLabParser::Property_float3_valContext *context) = 0;

    virtual std::any visitProperty_float4_val(EffectLabParser::Property_float4_valContext *context) = 0;

    virtual std::any visitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *context) = 0;

    virtual std::any visitProperty_texture_val(EffectLabParser::Property_texture_valContext *context) = 0;

    virtual std::any visitProperty_name(EffectLabParser::Property_nameContext *context) = 0;

    virtual std::any visitProperty_description(EffectLabParser::Property_descriptionContext *context) = 0;

    virtual std::any visitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *context) = 0;

    virtual std::any visitPropertyItemInt(EffectLabParser::PropertyItemIntContext *context) = 0;

    virtual std::any visitPropertyItemRange(EffectLabParser::PropertyItemRangeContext *context) = 0;

    virtual std::any visitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *context) = 0;

    virtual std::any visitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *context) = 0;

    virtual std::any visitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *context) = 0;

    virtual std::any visitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *context) = 0;

    virtual std::any visitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *context) = 0;

    virtual std::any visitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *context) = 0;


};

}  // namespace Eureka::ParserDetails
