
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

  virtual void enterProperty_matrix(EffectLabParser::Property_matrixContext *ctx) = 0;
  virtual void exitProperty_matrix(EffectLabParser::Property_matrixContext *ctx) = 0;

  virtual void enterProperty_name(EffectLabParser::Property_nameContext *ctx) = 0;
  virtual void exitProperty_name(EffectLabParser::Property_nameContext *ctx) = 0;

  virtual void enterProperty_description(EffectLabParser::Property_descriptionContext *ctx) = 0;
  virtual void exitProperty_description(EffectLabParser::Property_descriptionContext *ctx) = 0;

  virtual void enterProperty_item(EffectLabParser::Property_itemContext *ctx) = 0;
  virtual void exitProperty_item(EffectLabParser::Property_itemContext *ctx) = 0;


};

}  // namespace Eureka::ParserDetails
