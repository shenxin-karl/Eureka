
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
    BoolVal = 27, IntVal = 28, FloatVal = 29, String = 30, Identity = 31, 
    KWIdentity = 32, KWTrue = 33, KWFalse = 34, KWWhite = 35, KWBlack = 36, 
    KWBump = 37, WhiteSpace = 38, LineComment = 39, Comment = 40
  };

  enum {
    RuleEffect = 0, RuleSource_path = 1, RuleProperty_block = 2, RuleNumber_val = 3, 
    RuleProperty_bool_val = 4, RuleProperty_int_val = 5, RuleProperty_float_val = 6, 
    RuleProperty_float2_val = 7, RuleProperty_float3_val = 8, RuleProperty_float4_val = 9, 
    RuleProperty_texture_val = 10, RuleProperty_matrix_val = 11, RuleProperty_item = 12
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
  class Property_bool_valContext;
  class Property_int_valContext;
  class Property_float_valContext;
  class Property_float2_valContext;
  class Property_float3_valContext;
  class Property_float4_valContext;
  class Property_texture_valContext;
  class Property_matrix_valContext;
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
    antlr4::tree::TerminalNode *String();

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
    antlr4::tree::TerminalNode *IntVal();
    antlr4::tree::TerminalNode *FloatVal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Number_valContext* number_val();

  class  Property_bool_valContext : public antlr4::ParserRuleContext {
  public:
    Property_bool_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BoolVal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_bool_valContext* property_bool_val();

  class  Property_int_valContext : public antlr4::ParserRuleContext {
  public:
    Property_int_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntVal();

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

  class  Property_texture_valContext : public antlr4::ParserRuleContext {
  public:
    Property_texture_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KWWhite();
    antlr4::tree::TerminalNode *KWBlack();
    antlr4::tree::TerminalNode *KWBump();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_texture_valContext* property_texture_val();

  class  Property_matrix_valContext : public antlr4::ParserRuleContext {
  public:
    Property_matrix_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KWIdentity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_matrix_valContext* property_matrix_val();

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

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_int_valContext *property_int_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat4Context : public Property_itemContext {
  public:
    PropertyItemFloat4Context(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_float4_valContext *property_float4_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemBoolContext : public Property_itemContext {
  public:
    PropertyItemBoolContext(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_bool_valContext *property_bool_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemMatrixContext : public Property_itemContext {
  public:
    PropertyItemMatrixContext(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_matrix_valContext *property_matrix_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat2Context : public Property_itemContext {
  public:
    PropertyItemFloat2Context(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_float2_valContext *property_float2_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloat3Context : public Property_itemContext {
  public:
    PropertyItemFloat3Context(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_float3_valContext *property_float3_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemFloatContext : public Property_itemContext {
  public:
    PropertyItemFloatContext(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
    Property_float_valContext *property_float_val();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PropertyItemTextureContext : public Property_itemContext {
  public:
    PropertyItemTextureContext(Property_itemContext *ctx);

    antlr4::tree::TerminalNode *Identity();
    antlr4::tree::TerminalNode *String();
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
