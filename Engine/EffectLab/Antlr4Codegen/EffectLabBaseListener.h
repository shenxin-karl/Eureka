
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabListener.h"


namespace Eureka {

/**
 * This class provides an empty implementation of EffectLabListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  EffectLabBaseListener : public EffectLabListener {
public:

  virtual void enterEffect(EffectLabParser::EffectContext * /*ctx*/) override { }
  virtual void exitEffect(EffectLabParser::EffectContext * /*ctx*/) override { }

  virtual void enterSource_path(EffectLabParser::Source_pathContext * /*ctx*/) override { }
  virtual void exitSource_path(EffectLabParser::Source_pathContext * /*ctx*/) override { }

  virtual void enterProperty_block(EffectLabParser::Property_blockContext * /*ctx*/) override { }
  virtual void exitProperty_block(EffectLabParser::Property_blockContext * /*ctx*/) override { }

  virtual void enterNumber_val(EffectLabParser::Number_valContext * /*ctx*/) override { }
  virtual void exitNumber_val(EffectLabParser::Number_valContext * /*ctx*/) override { }

  virtual void enterProperty_bool_val(EffectLabParser::Property_bool_valContext * /*ctx*/) override { }
  virtual void exitProperty_bool_val(EffectLabParser::Property_bool_valContext * /*ctx*/) override { }

  virtual void enterProperty_int_val(EffectLabParser::Property_int_valContext * /*ctx*/) override { }
  virtual void exitProperty_int_val(EffectLabParser::Property_int_valContext * /*ctx*/) override { }

  virtual void enterProperty_float_val(EffectLabParser::Property_float_valContext * /*ctx*/) override { }
  virtual void exitProperty_float_val(EffectLabParser::Property_float_valContext * /*ctx*/) override { }

  virtual void enterProperty_float2_val(EffectLabParser::Property_float2_valContext * /*ctx*/) override { }
  virtual void exitProperty_float2_val(EffectLabParser::Property_float2_valContext * /*ctx*/) override { }

  virtual void enterProperty_float3_val(EffectLabParser::Property_float3_valContext * /*ctx*/) override { }
  virtual void exitProperty_float3_val(EffectLabParser::Property_float3_valContext * /*ctx*/) override { }

  virtual void enterProperty_float4_val(EffectLabParser::Property_float4_valContext * /*ctx*/) override { }
  virtual void exitProperty_float4_val(EffectLabParser::Property_float4_valContext * /*ctx*/) override { }

  virtual void enterProperty_texture_val(EffectLabParser::Property_texture_valContext * /*ctx*/) override { }
  virtual void exitProperty_texture_val(EffectLabParser::Property_texture_valContext * /*ctx*/) override { }

  virtual void enterProperty_matrix(EffectLabParser::Property_matrixContext * /*ctx*/) override { }
  virtual void exitProperty_matrix(EffectLabParser::Property_matrixContext * /*ctx*/) override { }

  virtual void enterProperty_name(EffectLabParser::Property_nameContext * /*ctx*/) override { }
  virtual void exitProperty_name(EffectLabParser::Property_nameContext * /*ctx*/) override { }

  virtual void enterProperty_description(EffectLabParser::Property_descriptionContext * /*ctx*/) override { }
  virtual void exitProperty_description(EffectLabParser::Property_descriptionContext * /*ctx*/) override { }

  virtual void enterProperty_item(EffectLabParser::Property_itemContext * /*ctx*/) override { }
  virtual void exitProperty_item(EffectLabParser::Property_itemContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace Eureka
