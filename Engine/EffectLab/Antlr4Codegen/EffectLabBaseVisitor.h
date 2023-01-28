
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabVisitor.h"


namespace Eureka::ParserDetails {

/**
 * This class provides an empty implementation of EffectLabVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  EffectLabBaseVisitor : public EffectLabVisitor {
public:

  virtual std::any visitEffect(EffectLabParser::EffectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_path(EffectLabParser::Source_pathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_block(EffectLabParser::Property_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_val(EffectLabParser::Number_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_int_val(EffectLabParser::Property_int_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float_val(EffectLabParser::Property_float_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Eureka::ParserDetails
