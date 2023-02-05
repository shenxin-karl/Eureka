
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"


namespace Eureka::ParserDetails {


class  EffectLabParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, T__69 = 70, IntLiteral = 71, FloatLiteral = 72, BooleanLiteral = 73, 
    CullModeLabel = 74, ZTestModeLabel = 75, ZWriteModeLabel = 76, ColorMaskChannel = 77, 
    RenderTargetID = 78, BlendFactorLabel = 79, BlendOPLabel = 80, AlphaToMaskLabel = 81, 
    StencilCompareLabel = 82, StencilOpLabel = 83, KWOff = 84, KWOn = 85, 
    KWNever = 86, KWLess = 87, KWEqual = 88, KWLEqaul = 89, KWGreater = 90, 
    KWNotEqual = 91, KWGEqual = 92, KWAlways = 93, KWKeep = 94, KWZero = 95, 
    KWReplace = 96, KWIncrSat = 97, KWDecrSat = 98, KWInvert = 99, KWIncrWrap = 100, 
    KWDecrWrap = 101, KWTrue = 102, KWFalse = 103, StringLiteral = 104, 
    Identity = 105, WhiteSpace = 106, LineComment = 107, BlockComment = 108
  };

  enum {
    RuleEffect = 0, RuleSource_path = 1, RuleProperty_block = 2, RuleNumber_val = 3, 
    RuleProperty_bool_type = 4, RuleProperty_int_type = 5, RuleProperty_range_type = 6, 
    RuleProperty_float_type = 7, RuleProperty_float2_type = 8, RuleProperty_float3_type = 9, 
    RuleProperty_float4_type = 10, RuleProperty_texture_2d_type = 11, RuleProperty_matrix_type = 12, 
    RuleProperty_range_val = 13, RuleProperty_bool_val = 14, RuleProperty_int_val = 15, 
    RuleProperty_float_val = 16, RuleProperty_float2_val = 17, RuleProperty_float3_val = 18, 
    RuleProperty_float4_val = 19, RuleProperty_matrix_val = 20, RuleProperty_texture_val = 21, 
    RuleProperty_name = 22, RuleProperty_description = 23, RuleProperty_item = 24, 
    RulePass_tag = 25, RulePass = 26, RulePass_vertex_shader = 27, RulePass_geometry_shader = 28, 
    RulePass_hull_shader = 29, RulePass_domain_shader = 30, RulePass_pixel_shader = 31, 
    RulePass_render_queue = 32, RulePass_shader_feature = 33, RulePass_cull_mode = 34, 
    RulePass_zclip_mode = 35, RulePass_ztest_mode = 36, RulePass_zwrite_mode = 37, 
    RulePass_offset = 38, RulePass_color_mask = 39, RulePass_blend = 40, 
    RulePass_blend_op = 41, RulePass_alpha_to_mask = 42, RulePass_conservative = 43, 
    RulePass_stencil = 44, RulePass_block_item = 45, RuleStencil_ref = 46, 
    RuleStencil_read_mask = 47, RuleStencil_write_mask = 48, RuleStencil_comp = 49, 
    RuleStencil_pass_op = 50, RuleStencil_fail_op = 51, RuleStencil_zfail_op = 52, 
    RuleStencil_comp_back_op = 53, RuleStancil_pass_back_op = 54, RuleStencil_fail_back_op = 55, 
    RuleStencil_zfail_back_op = 56, RuleStencil_comp_front_op = 57, RuleStancil_pass_front_op = 58, 
    RuleStencil_fail_front_op = 59, RuleStencil_zfail_front_op = 60, RuleStencil_item = 61
  };

  explicit EffectLabParser(antlr4::TokenStream *input);

  EffectLabParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~EffectLabParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class EffectContext;
  class Source_pathContext;
  class Property_blockContext;
  class Number_valContext;
  class Property_bool_typeContext;
  class Property_int_typeContext;
  class Property_range_typeContext;
  class Property_float_typeContext;
  class Property_float2_typeContext;
  class Property_float3_typeContext;
  class Property_float4_typeContext;
  class Property_texture_2d_typeContext;
  class Property_matrix_typeContext;
  class Property_range_valContext;
  class Property_bool_valContext;
  class Property_int_valContext;
  class Property_float_valContext;
  class Property_float2_valContext;
  class Property_float3_valContext;
  class Property_float4_valContext;
  class Property_matrix_valContext;
  class Property_texture_valContext;
  class Property_nameContext;
  class Property_descriptionContext;
  class Property_itemContext;
  class Pass_tagContext;
  class PassContext;
  class Pass_vertex_shaderContext;
  class Pass_geometry_shaderContext;
  class Pass_hull_shaderContext;
  class Pass_domain_shaderContext;
  class Pass_pixel_shaderContext;
  class Pass_render_queueContext;
  class Pass_shader_featureContext;
  class Pass_cull_modeContext;
  class Pass_zclip_modeContext;
  class Pass_ztest_modeContext;
  class Pass_zwrite_modeContext;
  class Pass_offsetContext;
  class Pass_color_maskContext;
  class Pass_blendContext;
  class Pass_blend_opContext;
  class Pass_alpha_to_maskContext;
  class Pass_conservativeContext;
  class Pass_stencilContext;
  class Pass_block_itemContext;
  class Stencil_refContext;
  class Stencil_read_maskContext;
  class Stencil_write_maskContext;
  class Stencil_compContext;
  class Stencil_pass_opContext;
  class Stencil_fail_opContext;
  class Stencil_zfail_opContext;
  class Stencil_comp_back_opContext;
  class Stancil_pass_back_opContext;
  class Stencil_fail_back_opContext;
  class Stencil_zfail_back_opContext;
  class Stencil_comp_front_opContext;
  class Stancil_pass_front_opContext;
  class Stencil_fail_front_opContext;
  class Stencil_zfail_front_opContext;
  class Stencil_itemContext; 

  class  EffectContext : public antlr4::ParserRuleContext {
  public:
    EffectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Source_pathContext *source_path();
    Property_blockContext *property_block();
    std::vector<PassContext *> pass();
    PassContext* pass(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EffectContext* effect();

  class  Source_pathContext : public antlr4::ParserRuleContext {
  public:
    Source_pathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Source_pathContext* source_path();

  class  Property_blockContext : public antlr4::ParserRuleContext {
  public:
    Property_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Property_itemContext *> property_item();
    Property_itemContext* property_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_blockContext* property_block();

  class  Number_valContext : public antlr4::ParserRuleContext {
  public:
    Number_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntLiteral();
    antlr4::tree::TerminalNode *FloatLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Number_valContext* number_val();

  class  Property_bool_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_bool_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_bool_typeContext* property_bool_type();

  class  Property_int_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_int_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_int_typeContext* property_int_type();

  class  Property_range_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_range_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Number_valContext *> number_val();
    Number_valContext* number_val(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_range_typeContext* property_range_type();

  class  Property_float_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_float_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float_typeContext* property_float_type();

  class  Property_float2_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_float2_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float2_typeContext* property_float2_type();

  class  Property_float3_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_float3_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float3_typeContext* property_float3_type();

  class  Property_float4_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_float4_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float4_typeContext* property_float4_type();

  class  Property_texture_2d_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_texture_2d_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_texture_2d_typeContext* property_texture_2d_type();

  class  Property_matrix_typeContext : public antlr4::ParserRuleContext {
  public:
    Property_matrix_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_matrix_typeContext* property_matrix_type();

  class  Property_range_valContext : public antlr4::ParserRuleContext {
  public:
    Property_range_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Number_valContext *number_val();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_range_valContext* property_range_val();

  class  Property_bool_valContext : public antlr4::ParserRuleContext {
  public:
    Property_bool_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BooleanLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_bool_valContext* property_bool_val();

  class  Property_int_valContext : public antlr4::ParserRuleContext {
  public:
    Property_int_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_int_valContext* property_int_val();

  class  Property_float_valContext : public antlr4::ParserRuleContext {
  public:
    Property_float_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Number_valContext *number_val();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float_valContext* property_float_val();

  class  Property_float2_valContext : public antlr4::ParserRuleContext {
  public:
    Property_float2_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Number_valContext *> number_val();
    Number_valContext* number_val(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float2_valContext* property_float2_val();

  class  Property_float3_valContext : public antlr4::ParserRuleContext {
  public:
    Property_float3_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Number_valContext *> number_val();
    Number_valContext* number_val(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float3_valContext* property_float3_val();

  class  Property_float4_valContext : public antlr4::ParserRuleContext {
  public:
    Property_float4_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Number_valContext *> number_val();
    Number_valContext* number_val(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_float4_valContext* property_float4_val();

  class  Property_matrix_valContext : public antlr4::ParserRuleContext {
  public:
    Property_matrix_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_matrix_valContext* property_matrix_val();

  class  Property_texture_valContext : public antlr4::ParserRuleContext {
  public:
    Property_texture_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_texture_valContext* property_texture_val();

  class  Property_nameContext : public antlr4::ParserRuleContext {
  public:
    Property_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_nameContext* property_name();

  class  Property_descriptionContext : public antlr4::ParserRuleContext {
  public:
    Property_descriptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_descriptionContext* property_description();

  class  Property_itemContext : public antlr4::ParserRuleContext {
  public:
    Property_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Property_itemContext() = default;
    void copyFrom(Property_itemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PropertyItemIntContext : public Property_itemContext {
  public:
    PropertyItemIntContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_int_typeContext *property_int_type();
    Property_int_valContext *property_int_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat4Context : public Property_itemContext {
  public:
    PropertyItemFloat4Context(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_float4_typeContext *property_float4_type();
    Property_float4_valContext *property_float4_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemBoolContext : public Property_itemContext {
  public:
    PropertyItemBoolContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_bool_typeContext *property_bool_type();
    Property_bool_valContext *property_bool_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemMatrixContext : public Property_itemContext {
  public:
    PropertyItemMatrixContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_matrix_typeContext *property_matrix_type();
    Property_matrix_valContext *property_matrix_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemRangeContext : public Property_itemContext {
  public:
    PropertyItemRangeContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_range_typeContext *property_range_type();
    Property_range_valContext *property_range_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat2Context : public Property_itemContext {
  public:
    PropertyItemFloat2Context(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_float2_typeContext *property_float2_type();
    Property_float2_valContext *property_float2_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat3Context : public Property_itemContext {
  public:
    PropertyItemFloat3Context(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_float3_typeContext *property_float3_type();
    Property_float3_valContext *property_float3_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloatContext : public Property_itemContext {
  public:
    PropertyItemFloatContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_float_typeContext *property_float_type();
    Property_float_valContext *property_float_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemTextureContext : public Property_itemContext {
  public:
    PropertyItemTextureContext(Property_itemContext *ctx);

    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_texture_2d_typeContext *property_texture_2d_type();
    Property_texture_valContext *property_texture_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Property_itemContext* property_item();

  class  Pass_tagContext : public antlr4::ParserRuleContext {
  public:
    Pass_tagContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_tagContext* pass_tag();

  class  PassContext : public antlr4::ParserRuleContext {
  public:
    PassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pass_tagContext *pass_tag();
    std::vector<Pass_block_itemContext *> pass_block_item();
    Pass_block_itemContext* pass_block_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PassContext* pass();

  class  Pass_vertex_shaderContext : public antlr4::ParserRuleContext {
  public:
    Pass_vertex_shaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_vertex_shaderContext* pass_vertex_shader();

  class  Pass_geometry_shaderContext : public antlr4::ParserRuleContext {
  public:
    Pass_geometry_shaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_geometry_shaderContext* pass_geometry_shader();

  class  Pass_hull_shaderContext : public antlr4::ParserRuleContext {
  public:
    Pass_hull_shaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_hull_shaderContext* pass_hull_shader();

  class  Pass_domain_shaderContext : public antlr4::ParserRuleContext {
  public:
    Pass_domain_shaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_domain_shaderContext* pass_domain_shader();

  class  Pass_pixel_shaderContext : public antlr4::ParserRuleContext {
  public:
    Pass_pixel_shaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_pixel_shaderContext* pass_pixel_shader();

  class  Pass_render_queueContext : public antlr4::ParserRuleContext {
  public:
    Pass_render_queueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_render_queueContext* pass_render_queue();

  class  Pass_shader_featureContext : public antlr4::ParserRuleContext {
  public:
    Pass_shader_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> StringLiteral();
    antlr4::tree::TerminalNode* StringLiteral(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_shader_featureContext* pass_shader_feature();

  class  Pass_cull_modeContext : public antlr4::ParserRuleContext {
  public:
    Pass_cull_modeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CullModeLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_cull_modeContext* pass_cull_mode();

  class  Pass_zclip_modeContext : public antlr4::ParserRuleContext {
  public:
    Pass_zclip_modeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BooleanLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_zclip_modeContext* pass_zclip_mode();

  class  Pass_ztest_modeContext : public antlr4::ParserRuleContext {
  public:
    Pass_ztest_modeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ZTestModeLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_ztest_modeContext* pass_ztest_mode();

  class  Pass_zwrite_modeContext : public antlr4::ParserRuleContext {
  public:
    Pass_zwrite_modeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ZWriteModeLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_zwrite_modeContext* pass_zwrite_mode();

  class  Pass_offsetContext : public antlr4::ParserRuleContext {
  public:
    Pass_offsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> FloatLiteral();
    antlr4::tree::TerminalNode* FloatLiteral(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_offsetContext* pass_offset();

  class  Pass_color_maskContext : public antlr4::ParserRuleContext {
  public:
    Pass_color_maskContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ColorMaskChannel();
    antlr4::tree::TerminalNode *RenderTargetID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_color_maskContext* pass_color_mask();

  class  Pass_blendContext : public antlr4::ParserRuleContext {
  public:
    Pass_blendContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Pass_blendContext() = default;
    void copyFrom(Pass_blendContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PassBlendRTOffContext : public Pass_blendContext {
  public:
    PassBlendRTOffContext(Pass_blendContext *ctx);

    antlr4::tree::TerminalNode *RenderTargetID();
    antlr4::tree::TerminalNode *KWOff();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendOffContext : public Pass_blendContext {
  public:
    PassBlendOffContext(Pass_blendContext *ctx);

    antlr4::tree::TerminalNode *KWOff();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendRTColorAlphaContext : public Pass_blendContext {
  public:
    PassBlendRTColorAlphaContext(Pass_blendContext *ctx);

    antlr4::tree::TerminalNode *RenderTargetID();
    std::vector<antlr4::tree::TerminalNode *> BlendFactorLabel();
    antlr4::tree::TerminalNode* BlendFactorLabel(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendColorContext : public Pass_blendContext {
  public:
    PassBlendColorContext(Pass_blendContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> BlendFactorLabel();
    antlr4::tree::TerminalNode* BlendFactorLabel(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendColorAlphaContext : public Pass_blendContext {
  public:
    PassBlendColorAlphaContext(Pass_blendContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> BlendFactorLabel();
    antlr4::tree::TerminalNode* BlendFactorLabel(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendRTColorContext : public Pass_blendContext {
  public:
    PassBlendRTColorContext(Pass_blendContext *ctx);

    antlr4::tree::TerminalNode *RenderTargetID();
    std::vector<antlr4::tree::TerminalNode *> BlendFactorLabel();
    antlr4::tree::TerminalNode* BlendFactorLabel(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Pass_blendContext* pass_blend();

  class  Pass_blend_opContext : public antlr4::ParserRuleContext {
  public:
    Pass_blend_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BlendOPLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_blend_opContext* pass_blend_op();

  class  Pass_alpha_to_maskContext : public antlr4::ParserRuleContext {
  public:
    Pass_alpha_to_maskContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AlphaToMaskLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_alpha_to_maskContext* pass_alpha_to_mask();

  class  Pass_conservativeContext : public antlr4::ParserRuleContext {
  public:
    Pass_conservativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BooleanLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_conservativeContext* pass_conservative();

  class  Pass_stencilContext : public antlr4::ParserRuleContext {
  public:
    Pass_stencilContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Stencil_itemContext *> stencil_item();
    Stencil_itemContext* stencil_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pass_stencilContext* pass_stencil();

  class  Pass_block_itemContext : public antlr4::ParserRuleContext {
  public:
    Pass_block_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Pass_block_itemContext() = default;
    void copyFrom(Pass_block_itemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PassStencilContext : public Pass_block_itemContext {
  public:
    PassStencilContext(Pass_block_itemContext *ctx);

    Pass_stencilContext *pass_stencil();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassColorMaskContext : public Pass_block_itemContext {
  public:
    PassColorMaskContext(Pass_block_itemContext *ctx);

    Pass_color_maskContext *pass_color_mask();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassPixelShaderContext : public Pass_block_itemContext {
  public:
    PassPixelShaderContext(Pass_block_itemContext *ctx);

    Pass_pixel_shaderContext *pass_pixel_shader();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassZClipModeContext : public Pass_block_itemContext {
  public:
    PassZClipModeContext(Pass_block_itemContext *ctx);

    Pass_zclip_modeContext *pass_zclip_mode();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassGeometryShaderContext : public Pass_block_itemContext {
  public:
    PassGeometryShaderContext(Pass_block_itemContext *ctx);

    Pass_geometry_shaderContext *pass_geometry_shader();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassShaderFeatureContext : public Pass_block_itemContext {
  public:
    PassShaderFeatureContext(Pass_block_itemContext *ctx);

    Pass_shader_featureContext *pass_shader_feature();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassConservativeContext : public Pass_block_itemContext {
  public:
    PassConservativeContext(Pass_block_itemContext *ctx);

    Pass_conservativeContext *pass_conservative();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassDomainShaderContext : public Pass_block_itemContext {
  public:
    PassDomainShaderContext(Pass_block_itemContext *ctx);

    Pass_domain_shaderContext *pass_domain_shader();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassRenderQueueContext : public Pass_block_itemContext {
  public:
    PassRenderQueueContext(Pass_block_itemContext *ctx);

    Pass_render_queueContext *pass_render_queue();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassZWriteModeContext : public Pass_block_itemContext {
  public:
    PassZWriteModeContext(Pass_block_itemContext *ctx);

    Pass_zwrite_modeContext *pass_zwrite_mode();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendContext : public Pass_block_itemContext {
  public:
    PassBlendContext(Pass_block_itemContext *ctx);

    Pass_blendContext *pass_blend();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassOffsetContext : public Pass_block_itemContext {
  public:
    PassOffsetContext(Pass_block_itemContext *ctx);

    Pass_offsetContext *pass_offset();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassHullShaderContext : public Pass_block_itemContext {
  public:
    PassHullShaderContext(Pass_block_itemContext *ctx);

    Pass_hull_shaderContext *pass_hull_shader();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassCullModeContext : public Pass_block_itemContext {
  public:
    PassCullModeContext(Pass_block_itemContext *ctx);

    Pass_cull_modeContext *pass_cull_mode();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassZTestModeContext : public Pass_block_itemContext {
  public:
    PassZTestModeContext(Pass_block_itemContext *ctx);

    Pass_ztest_modeContext *pass_ztest_mode();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassVertexShaderContext : public Pass_block_itemContext {
  public:
    PassVertexShaderContext(Pass_block_itemContext *ctx);

    Pass_vertex_shaderContext *pass_vertex_shader();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassBlendOpContext : public Pass_block_itemContext {
  public:
    PassBlendOpContext(Pass_block_itemContext *ctx);

    Pass_blend_opContext *pass_blend_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassAlphaToMaskContext : public Pass_block_itemContext {
  public:
    PassAlphaToMaskContext(Pass_block_itemContext *ctx);

    Pass_alpha_to_maskContext *pass_alpha_to_mask();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Pass_block_itemContext* pass_block_item();

  class  Stencil_refContext : public antlr4::ParserRuleContext {
  public:
    Stencil_refContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_refContext* stencil_ref();

  class  Stencil_read_maskContext : public antlr4::ParserRuleContext {
  public:
    Stencil_read_maskContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_read_maskContext* stencil_read_mask();

  class  Stencil_write_maskContext : public antlr4::ParserRuleContext {
  public:
    Stencil_write_maskContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_write_maskContext* stencil_write_mask();

  class  Stencil_compContext : public antlr4::ParserRuleContext {
  public:
    Stencil_compContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilCompareLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_compContext* stencil_comp();

  class  Stencil_pass_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_pass_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_pass_opContext* stencil_pass_op();

  class  Stencil_fail_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_fail_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_fail_opContext* stencil_fail_op();

  class  Stencil_zfail_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_zfail_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_zfail_opContext* stencil_zfail_op();

  class  Stencil_comp_back_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_comp_back_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_comp_back_opContext* stencil_comp_back_op();

  class  Stancil_pass_back_opContext : public antlr4::ParserRuleContext {
  public:
    Stancil_pass_back_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stancil_pass_back_opContext* stancil_pass_back_op();

  class  Stencil_fail_back_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_fail_back_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_fail_back_opContext* stencil_fail_back_op();

  class  Stencil_zfail_back_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_zfail_back_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_zfail_back_opContext* stencil_zfail_back_op();

  class  Stencil_comp_front_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_comp_front_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_comp_front_opContext* stencil_comp_front_op();

  class  Stancil_pass_front_opContext : public antlr4::ParserRuleContext {
  public:
    Stancil_pass_front_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stancil_pass_front_opContext* stancil_pass_front_op();

  class  Stencil_fail_front_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_fail_front_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_fail_front_opContext* stencil_fail_front_op();

  class  Stencil_zfail_front_opContext : public antlr4::ParserRuleContext {
  public:
    Stencil_zfail_front_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StencilOpLabel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stencil_zfail_front_opContext* stencil_zfail_front_op();

  class  Stencil_itemContext : public antlr4::ParserRuleContext {
  public:
    Stencil_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Stencil_itemContext() = default;
    void copyFrom(Stencil_itemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StencilCompBackOpContext : public Stencil_itemContext {
  public:
    StencilCompBackOpContext(Stencil_itemContext *ctx);

    Stencil_comp_back_opContext *stencil_comp_back_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilReadMaskContext : public Stencil_itemContext {
  public:
    StencilReadMaskContext(Stencil_itemContext *ctx);

    Stencil_read_maskContext *stencil_read_mask();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilRefContext : public Stencil_itemContext {
  public:
    StencilRefContext(Stencil_itemContext *ctx);

    Stencil_refContext *stencil_ref();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilPassOpContext : public Stencil_itemContext {
  public:
    StencilPassOpContext(Stencil_itemContext *ctx);

    Stencil_pass_opContext *stencil_pass_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilFailOpContext : public Stencil_itemContext {
  public:
    StencilFailOpContext(Stencil_itemContext *ctx);

    Stencil_fail_opContext *stencil_fail_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilCompFrontOpContext : public Stencil_itemContext {
  public:
    StencilCompFrontOpContext(Stencil_itemContext *ctx);

    Stencil_comp_front_opContext *stencil_comp_front_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilPassBackOpContext : public Stencil_itemContext {
  public:
    StencilPassBackOpContext(Stencil_itemContext *ctx);

    Stancil_pass_back_opContext *stancil_pass_back_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilWriteMaskContext : public Stencil_itemContext {
  public:
    StencilWriteMaskContext(Stencil_itemContext *ctx);

    Stencil_write_maskContext *stencil_write_mask();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilFailBackOpContext : public Stencil_itemContext {
  public:
    StencilFailBackOpContext(Stencil_itemContext *ctx);

    Stencil_fail_back_opContext *stencil_fail_back_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilPassFrontOpContext : public Stencil_itemContext {
  public:
    StencilPassFrontOpContext(Stencil_itemContext *ctx);

    Stancil_pass_front_opContext *stancil_pass_front_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilFailFrontOpContext : public Stencil_itemContext {
  public:
    StencilFailFrontOpContext(Stencil_itemContext *ctx);

    Stencil_fail_front_opContext *stencil_fail_front_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilZFailOpContext : public Stencil_itemContext {
  public:
    StencilZFailOpContext(Stencil_itemContext *ctx);

    Stencil_zfail_opContext *stencil_zfail_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilCompContext : public Stencil_itemContext {
  public:
    StencilCompContext(Stencil_itemContext *ctx);

    Stencil_compContext *stencil_comp();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilZFailBackOpContext : public Stencil_itemContext {
  public:
    StencilZFailBackOpContext(Stencil_itemContext *ctx);

    Stencil_zfail_back_opContext *stencil_zfail_back_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StencilZFailFrontOpContext : public Stencil_itemContext {
  public:
    StencilZFailFrontOpContext(Stencil_itemContext *ctx);

    Stencil_zfail_front_opContext *stencil_zfail_front_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Stencil_itemContext* stencil_item();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace Eureka::ParserDetails
