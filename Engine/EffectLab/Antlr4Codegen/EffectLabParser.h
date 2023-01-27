
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"


namespace Eureka::ParserDetails {


class  EffectLabParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, BoolVal = 17, IntVal = 18, FloatVal = 19, String = 20, 
    Identity = 21, KWIdentity = 22, KWTrue = 23, KWFalse = 24, WhiteSpace = 25, 
    LineComment = 26, Comment = 27
  };

  enum {
    RuleEffect = 0, RuleSource_path = 1, RuleProperty_block = 2, RuleNumber_val = 3, 
    RuleProperty_bool_val = 4, RuleProperty_int_val = 5, RuleProperty_float_val = 6, 
    RuleProperty_float2_val = 7, RuleProperty_float3_val = 8, RuleProperty_float4_val = 9, 
    RuleProperty_texture_val = 10, RuleProperty_matrix = 11, RuleProperty_name = 12, 
    RuleProperty_description = 13, RuleProperty_item = 14
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
  class Property_matrixContext;
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
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_texture_valContext* property_texture_val();

  class  Property_matrixContext : public antlr4::ParserRuleContext {
  public:
    Property_matrixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KWIdentity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_matrixContext* property_matrix();

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
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_descriptionContext* property_description();

  class  Property_itemContext : public antlr4::ParserRuleContext {
  public:
    Property_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_nameContext *property_name();
    Property_descriptionContext *property_description();
    Property_bool_valContext *property_bool_val();
    Property_int_valContext *property_int_val();
    Property_float_valContext *property_float_val();

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
