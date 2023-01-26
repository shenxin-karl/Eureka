
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabParser.h"


namespace Eureka {

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

    virtual std::any visitProperty_bool_val(EffectLabParser::Property_bool_valContext *context) = 0;

    virtual std::any visitProperty_int_val(EffectLabParser::Property_int_valContext *context) = 0;

    virtual std::any visitProperty_float_val(EffectLabParser::Property_float_valContext *context) = 0;

    virtual std::any visitProperty_float2_val(EffectLabParser::Property_float2_valContext *context) = 0;

    virtual std::any visitProperty_float3_val(EffectLabParser::Property_float3_valContext *context) = 0;

    virtual std::any visitProperty_float4_val(EffectLabParser::Property_float4_valContext *context) = 0;

    virtual std::any visitProperty_texture_val(EffectLabParser::Property_texture_valContext *context) = 0;

    virtual std::any visitProperty_matrix(EffectLabParser::Property_matrixContext *context) = 0;

    virtual std::any visitProperty_name(EffectLabParser::Property_nameContext *context) = 0;

    virtual std::any visitProperty_description(EffectLabParser::Property_descriptionContext *context) = 0;

    virtual std::any visitProperty_item(EffectLabParser::Property_itemContext *context) = 0;


};

}  // namespace Eureka
