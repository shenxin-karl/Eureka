
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabParser.h"


namespace Eureka::ParserDetails {

/**
 * This interface defines an abstract listener for a parse tree produced by EffectLabParser.
 */
class  EffectLabListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterEffect(EffectLabParser::EffectContext *ctx) = 0;
  virtual void exitEffect(EffectLabParser::EffectContext *ctx) = 0;

  virtual void enterSource_path(EffectLabParser::Source_pathContext *ctx) = 0;
  virtual void exitSource_path(EffectLabParser::Source_pathContext *ctx) = 0;

  virtual void enterProperty_block(EffectLabParser::Property_blockContext *ctx) = 0;
  virtual void exitProperty_block(EffectLabParser::Property_blockContext *ctx) = 0;

  virtual void enterNumber_val(EffectLabParser::Number_valContext *ctx) = 0;
  virtual void exitNumber_val(EffectLabParser::Number_valContext *ctx) = 0;

  virtual void enterProperty_range_type(EffectLabParser::Property_range_typeContext *ctx) = 0;
  virtual void exitProperty_range_type(EffectLabParser::Property_range_typeContext *ctx) = 0;

  virtual void enterProperty_range_val(EffectLabParser::Property_range_valContext *ctx) = 0;
  virtual void exitProperty_range_val(EffectLabParser::Property_range_valContext *ctx) = 0;

  virtual void enterProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) = 0;
  virtual void exitProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) = 0;

  virtual void enterProperty_int_val(EffectLabParser::Property_int_valContext *ctx) = 0;
  virtual void exitProperty_int_val(EffectLabParser::Property_int_valContext *ctx) = 0;

  virtual void enterProperty_float_val(EffectLabParser::Property_float_valContext *ctx) = 0;
  virtual void exitProperty_float_val(EffectLabParser::Property_float_valContext *ctx) = 0;

  virtual void enterProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) = 0;
  virtual void exitProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) = 0;

  virtual void enterProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) = 0;
  virtual void exitProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) = 0;

  virtual void enterProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) = 0;
  virtual void exitProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) = 0;

  virtual void enterProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) = 0;
  virtual void exitProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) = 0;

  virtual void enterProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) = 0;
  virtual void exitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) = 0;

  virtual void enterPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) = 0;
  virtual void exitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) = 0;

  virtual void enterPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) = 0;
  virtual void exitPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) = 0;

  virtual void enterPropertyItemRange(EffectLabParser::PropertyItemRangeContext *ctx) = 0;
  virtual void exitPropertyItemRange(EffectLabParser::PropertyItemRangeContext *ctx) = 0;

  virtual void enterPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) = 0;
  virtual void exitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) = 0;

  virtual void enterPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) = 0;
  virtual void exitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) = 0;

  virtual void enterPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) = 0;
  virtual void exitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) = 0;

  virtual void enterPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) = 0;
  virtual void exitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) = 0;

  virtual void enterPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) = 0;
  virtual void exitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) = 0;

  virtual void enterPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) = 0;
  virtual void exitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) = 0;


};

}  // namespace Eureka::ParserDetails
