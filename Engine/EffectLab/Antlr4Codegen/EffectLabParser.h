
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
    T__32 = 33, T__33 = 34, IntLiteral = 35, FloatLiteral = 36, BooleanLiteral = 37, 
    StringLiteral = 38, Identity = 39, WhiteSpace = 40, LineComment = 41, 
    BlockComment = 42
  };

  enum {
    RuleEffect = 0, RuleSource_path = 1, RuleProperty_block = 2, RuleNumber_val = 3, 
    RuleProperty_bool_type = 4, RuleProperty_int_type = 5, RuleProperty_range_type = 6, 
    RuleProperty_float_type = 7, RuleProperty_float2_type = 8, RuleProperty_float3_type = 9, 
    RuleProperty_float4_type = 10, RuleProperty_texture_2d_type = 11, RuleProperty_matrix_type = 12, 
    RuleProperty_range_val = 13, RuleProperty_bool_val = 14, RuleProperty_int_val = 15, 
    RuleProperty_float_val = 16, RuleProperty_float2_val = 17, RuleProperty_float3_val = 18, 
    RuleProperty_float4_val = 19, RuleProperty_matrix_val = 20, RuleProperty_texture_val = 21, 
    RuleProperty_name = 22, RuleProperty_description = 23, RuleProperty_item = 24
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

  class  EffectContext : public antlr4::ParserRuleContext {
  public:
    EffectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Source_pathContext *source_path();
    Property_blockContext *property_block();

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


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace Eureka::ParserDetails
