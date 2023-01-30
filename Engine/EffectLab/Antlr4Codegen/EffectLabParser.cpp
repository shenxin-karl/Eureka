
// Generated from EffectLab.g4 by ANTLR 4.11.1


#include "EffectLabListener.h"
#include "EffectLabVisitor.h"

#include "EffectLabParser.h"


using namespace antlrcpp;
using namespace Eureka::ParserDetails;

using namespace antlr4;

namespace {

struct EffectLabParserStaticData final {
  EffectLabParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  EffectLabParserStaticData(const EffectLabParserStaticData&) = delete;
  EffectLabParserStaticData(EffectLabParserStaticData&&) = delete;
  EffectLabParserStaticData& operator=(const EffectLabParserStaticData&) = delete;
  EffectLabParserStaticData& operator=(EffectLabParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag effectlabParserOnceFlag;
EffectLabParserStaticData *effectlabParserStaticData = nullptr;

void effectlabParserInitialize() {
  assert(effectlabParserStaticData == nullptr);
  auto staticData = std::make_unique<EffectLabParserStaticData>(
    std::vector<std::string>{
      "effect", "source_path", "property_block", "number_val", "property_range_type", 
      "property_range_val", "property_bool_val", "property_int_val", "property_float_val", 
      "property_float2_val", "property_float3_val", "property_float4_val", 
      "property_texture_val", "property_matrix_val", "property_item"
    },
    std::vector<std::string>{
      "", "'SourcePath'", "':'", "'Properties'", "'{'", "'}'", "'range'", 
      "'Range'", "'('", "','", "')'", "'bool'", "'Bool'", "'='", "'int'", 
      "'Int'", "'float'", "'Float'", "'float2'", "'Float2'", "'float3'", 
      "'Float3'", "'float4'", "'Float4'", "'2d'", "'2D'", "'matrix'", "'Matrix'", 
      "", "", "", "", "", "'identity'", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "BoolVal", "IntVal", "FloatVal", 
      "String", "Identity", "KWIdentity", "KWTrue", "KWFalse", "KWWhite", 
      "KWBlack", "KWBump", "WhiteSpace", "LineComment", "Comment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,41,168,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,1,0,3,0,33,8,0,1,1,1,1,1,1,1,1,1,2,1,2,1,2,4,2,42,8,2,11,2,12,
  	2,43,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,1,6,1,7,
  	1,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,13,
  	1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,3,14,166,8,14,1,14,0,0,15,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,0,11,1,0,29,30,1,0,6,7,1,0,36,38,1,0,11,12,1,0,14,15,1,
  	0,16,17,1,0,18,19,1,0,20,21,1,0,22,23,1,0,24,25,1,0,26,27,162,0,30,1,
  	0,0,0,2,34,1,0,0,0,4,38,1,0,0,0,6,47,1,0,0,0,8,49,1,0,0,0,10,56,1,0,0,
  	0,12,58,1,0,0,0,14,60,1,0,0,0,16,62,1,0,0,0,18,64,1,0,0,0,20,70,1,0,0,
  	0,22,78,1,0,0,0,24,88,1,0,0,0,26,90,1,0,0,0,28,165,1,0,0,0,30,32,3,2,
  	1,0,31,33,3,4,2,0,32,31,1,0,0,0,32,33,1,0,0,0,33,1,1,0,0,0,34,35,5,1,
  	0,0,35,36,5,2,0,0,36,37,5,31,0,0,37,3,1,0,0,0,38,39,5,3,0,0,39,41,5,4,
  	0,0,40,42,3,28,14,0,41,40,1,0,0,0,42,43,1,0,0,0,43,41,1,0,0,0,43,44,1,
  	0,0,0,44,45,1,0,0,0,45,46,5,5,0,0,46,5,1,0,0,0,47,48,7,0,0,0,48,7,1,0,
  	0,0,49,50,7,1,0,0,50,51,5,8,0,0,51,52,3,6,3,0,52,53,5,9,0,0,53,54,3,6,
  	3,0,54,55,5,10,0,0,55,9,1,0,0,0,56,57,3,6,3,0,57,11,1,0,0,0,58,59,5,28,
  	0,0,59,13,1,0,0,0,60,61,5,29,0,0,61,15,1,0,0,0,62,63,3,6,3,0,63,17,1,
  	0,0,0,64,65,5,8,0,0,65,66,3,6,3,0,66,67,5,9,0,0,67,68,3,6,3,0,68,69,5,
  	10,0,0,69,19,1,0,0,0,70,71,5,8,0,0,71,72,3,6,3,0,72,73,5,9,0,0,73,74,
  	3,6,3,0,74,75,5,9,0,0,75,76,3,6,3,0,76,77,5,10,0,0,77,21,1,0,0,0,78,79,
  	5,8,0,0,79,80,3,6,3,0,80,81,5,9,0,0,81,82,3,6,3,0,82,83,5,9,0,0,83,84,
  	3,6,3,0,84,85,5,9,0,0,85,86,3,6,3,0,86,87,5,10,0,0,87,23,1,0,0,0,88,89,
  	7,2,0,0,89,25,1,0,0,0,90,91,5,33,0,0,91,27,1,0,0,0,92,93,5,32,0,0,93,
  	94,5,8,0,0,94,95,5,31,0,0,95,96,5,9,0,0,96,97,7,3,0,0,97,98,5,10,0,0,
  	98,99,5,13,0,0,99,166,3,12,6,0,100,101,5,32,0,0,101,102,5,8,0,0,102,103,
  	5,31,0,0,103,104,5,9,0,0,104,105,7,4,0,0,105,106,5,10,0,0,106,107,5,13,
  	0,0,107,166,3,14,7,0,108,109,5,32,0,0,109,110,5,8,0,0,110,111,5,31,0,
  	0,111,112,5,9,0,0,112,113,3,8,4,0,113,114,5,10,0,0,114,115,5,13,0,0,115,
  	116,3,10,5,0,116,166,1,0,0,0,117,118,5,32,0,0,118,119,5,8,0,0,119,120,
  	5,31,0,0,120,121,5,9,0,0,121,122,7,5,0,0,122,123,5,10,0,0,123,124,5,13,
  	0,0,124,166,3,16,8,0,125,126,5,32,0,0,126,127,5,8,0,0,127,128,5,31,0,
  	0,128,129,5,9,0,0,129,130,7,6,0,0,130,131,5,10,0,0,131,132,5,13,0,0,132,
  	166,3,18,9,0,133,134,5,32,0,0,134,135,5,8,0,0,135,136,5,31,0,0,136,137,
  	5,9,0,0,137,138,7,7,0,0,138,139,5,10,0,0,139,140,5,13,0,0,140,166,3,20,
  	10,0,141,142,5,32,0,0,142,143,5,8,0,0,143,144,5,31,0,0,144,145,5,9,0,
  	0,145,146,7,8,0,0,146,147,5,10,0,0,147,148,5,13,0,0,148,166,3,22,11,0,
  	149,150,5,32,0,0,150,151,5,8,0,0,151,152,5,31,0,0,152,153,5,9,0,0,153,
  	154,7,9,0,0,154,155,5,10,0,0,155,156,5,13,0,0,156,166,3,24,12,0,157,158,
  	5,32,0,0,158,159,5,8,0,0,159,160,5,31,0,0,160,161,5,9,0,0,161,162,7,10,
  	0,0,162,163,5,10,0,0,163,164,5,13,0,0,164,166,3,26,13,0,165,92,1,0,0,
  	0,165,100,1,0,0,0,165,108,1,0,0,0,165,117,1,0,0,0,165,125,1,0,0,0,165,
  	133,1,0,0,0,165,141,1,0,0,0,165,149,1,0,0,0,165,157,1,0,0,0,166,29,1,
  	0,0,0,3,32,43,165
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  effectlabParserStaticData = staticData.release();
}

}

EffectLabParser::EffectLabParser(TokenStream *input) : EffectLabParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

EffectLabParser::EffectLabParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  EffectLabParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *effectlabParserStaticData->atn, effectlabParserStaticData->decisionToDFA, effectlabParserStaticData->sharedContextCache, options);
}

EffectLabParser::~EffectLabParser() {
  delete _interpreter;
}

const atn::ATN& EffectLabParser::getATN() const {
  return *effectlabParserStaticData->atn;
}

std::string EffectLabParser::getGrammarFileName() const {
  return "EffectLab.g4";
}

const std::vector<std::string>& EffectLabParser::getRuleNames() const {
  return effectlabParserStaticData->ruleNames;
}

const dfa::Vocabulary& EffectLabParser::getVocabulary() const {
  return effectlabParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView EffectLabParser::getSerializedATN() const {
  return effectlabParserStaticData->serializedATN;
}


//----------------- EffectContext ------------------------------------------------------------------

EffectLabParser::EffectContext::EffectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EffectLabParser::Source_pathContext* EffectLabParser::EffectContext::source_path() {
  return getRuleContext<EffectLabParser::Source_pathContext>(0);
}

EffectLabParser::Property_blockContext* EffectLabParser::EffectContext::property_block() {
  return getRuleContext<EffectLabParser::Property_blockContext>(0);
}


size_t EffectLabParser::EffectContext::getRuleIndex() const {
  return EffectLabParser::RuleEffect;
}

void EffectLabParser::EffectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEffect(this);
}

void EffectLabParser::EffectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEffect(this);
}


std::any EffectLabParser::EffectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitEffect(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::EffectContext* EffectLabParser::effect() {
  EffectContext *_localctx = _tracker.createInstance<EffectContext>(_ctx, getState());
  enterRule(_localctx, 0, EffectLabParser::RuleEffect);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    source_path();
    setState(32);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EffectLabParser::T__2) {
      setState(31);
      property_block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Source_pathContext ------------------------------------------------------------------

EffectLabParser::Source_pathContext::Source_pathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Source_pathContext::String() {
  return getToken(EffectLabParser::String, 0);
}


size_t EffectLabParser::Source_pathContext::getRuleIndex() const {
  return EffectLabParser::RuleSource_path;
}

void EffectLabParser::Source_pathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSource_path(this);
}

void EffectLabParser::Source_pathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSource_path(this);
}


std::any EffectLabParser::Source_pathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitSource_path(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Source_pathContext* EffectLabParser::source_path() {
  Source_pathContext *_localctx = _tracker.createInstance<Source_pathContext>(_ctx, getState());
  enterRule(_localctx, 2, EffectLabParser::RuleSource_path);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    match(EffectLabParser::T__0);
    setState(35);
    match(EffectLabParser::T__1);
    setState(36);
    match(EffectLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_blockContext ------------------------------------------------------------------

EffectLabParser::Property_blockContext::Property_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Property_itemContext *> EffectLabParser::Property_blockContext::property_item() {
  return getRuleContexts<EffectLabParser::Property_itemContext>();
}

EffectLabParser::Property_itemContext* EffectLabParser::Property_blockContext::property_item(size_t i) {
  return getRuleContext<EffectLabParser::Property_itemContext>(i);
}


size_t EffectLabParser::Property_blockContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_block;
}

void EffectLabParser::Property_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_block(this);
}

void EffectLabParser::Property_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_block(this);
}


std::any EffectLabParser::Property_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_block(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_blockContext* EffectLabParser::property_block() {
  Property_blockContext *_localctx = _tracker.createInstance<Property_blockContext>(_ctx, getState());
  enterRule(_localctx, 4, EffectLabParser::RuleProperty_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    match(EffectLabParser::T__2);
    setState(39);
    match(EffectLabParser::T__3);
    setState(41); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(40);
      property_item();
      setState(43); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EffectLabParser::Identity);
    setState(45);
    match(EffectLabParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Number_valContext ------------------------------------------------------------------

EffectLabParser::Number_valContext::Number_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Number_valContext::IntVal() {
  return getToken(EffectLabParser::IntVal, 0);
}

tree::TerminalNode* EffectLabParser::Number_valContext::FloatVal() {
  return getToken(EffectLabParser::FloatVal, 0);
}


size_t EffectLabParser::Number_valContext::getRuleIndex() const {
  return EffectLabParser::RuleNumber_val;
}

void EffectLabParser::Number_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber_val(this);
}

void EffectLabParser::Number_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber_val(this);
}


std::any EffectLabParser::Number_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitNumber_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Number_valContext* EffectLabParser::number_val() {
  Number_valContext *_localctx = _tracker.createInstance<Number_valContext>(_ctx, getState());
  enterRule(_localctx, 6, EffectLabParser::RuleNumber_val);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::IntVal

    || _la == EffectLabParser::FloatVal)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_range_typeContext ------------------------------------------------------------------

EffectLabParser::Property_range_typeContext::Property_range_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Number_valContext *> EffectLabParser::Property_range_typeContext::number_val() {
  return getRuleContexts<EffectLabParser::Number_valContext>();
}

EffectLabParser::Number_valContext* EffectLabParser::Property_range_typeContext::number_val(size_t i) {
  return getRuleContext<EffectLabParser::Number_valContext>(i);
}


size_t EffectLabParser::Property_range_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_range_type;
}

void EffectLabParser::Property_range_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_range_type(this);
}

void EffectLabParser::Property_range_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_range_type(this);
}


std::any EffectLabParser::Property_range_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_range_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_range_typeContext* EffectLabParser::property_range_type() {
  Property_range_typeContext *_localctx = _tracker.createInstance<Property_range_typeContext>(_ctx, getState());
  enterRule(_localctx, 8, EffectLabParser::RuleProperty_range_type);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__5

    || _la == EffectLabParser::T__6)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(50);
    match(EffectLabParser::T__7);
    setState(51);
    number_val();
    setState(52);
    match(EffectLabParser::T__8);
    setState(53);
    number_val();
    setState(54);
    match(EffectLabParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_range_valContext ------------------------------------------------------------------

EffectLabParser::Property_range_valContext::Property_range_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EffectLabParser::Number_valContext* EffectLabParser::Property_range_valContext::number_val() {
  return getRuleContext<EffectLabParser::Number_valContext>(0);
}


size_t EffectLabParser::Property_range_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_range_val;
}

void EffectLabParser::Property_range_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_range_val(this);
}

void EffectLabParser::Property_range_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_range_val(this);
}


std::any EffectLabParser::Property_range_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_range_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_range_valContext* EffectLabParser::property_range_val() {
  Property_range_valContext *_localctx = _tracker.createInstance<Property_range_valContext>(_ctx, getState());
  enterRule(_localctx, 10, EffectLabParser::RuleProperty_range_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    number_val();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_bool_valContext ------------------------------------------------------------------

EffectLabParser::Property_bool_valContext::Property_bool_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_bool_valContext::BoolVal() {
  return getToken(EffectLabParser::BoolVal, 0);
}


size_t EffectLabParser::Property_bool_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_bool_val;
}

void EffectLabParser::Property_bool_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_bool_val(this);
}

void EffectLabParser::Property_bool_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_bool_val(this);
}


std::any EffectLabParser::Property_bool_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_bool_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_bool_valContext* EffectLabParser::property_bool_val() {
  Property_bool_valContext *_localctx = _tracker.createInstance<Property_bool_valContext>(_ctx, getState());
  enterRule(_localctx, 12, EffectLabParser::RuleProperty_bool_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(EffectLabParser::BoolVal);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_int_valContext ------------------------------------------------------------------

EffectLabParser::Property_int_valContext::Property_int_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_int_valContext::IntVal() {
  return getToken(EffectLabParser::IntVal, 0);
}


size_t EffectLabParser::Property_int_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_int_val;
}

void EffectLabParser::Property_int_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_int_val(this);
}

void EffectLabParser::Property_int_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_int_val(this);
}


std::any EffectLabParser::Property_int_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_int_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_int_valContext* EffectLabParser::property_int_val() {
  Property_int_valContext *_localctx = _tracker.createInstance<Property_int_valContext>(_ctx, getState());
  enterRule(_localctx, 14, EffectLabParser::RuleProperty_int_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    match(EffectLabParser::IntVal);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_float_valContext ------------------------------------------------------------------

EffectLabParser::Property_float_valContext::Property_float_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EffectLabParser::Number_valContext* EffectLabParser::Property_float_valContext::number_val() {
  return getRuleContext<EffectLabParser::Number_valContext>(0);
}


size_t EffectLabParser::Property_float_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float_val;
}

void EffectLabParser::Property_float_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float_val(this);
}

void EffectLabParser::Property_float_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float_val(this);
}


std::any EffectLabParser::Property_float_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float_valContext* EffectLabParser::property_float_val() {
  Property_float_valContext *_localctx = _tracker.createInstance<Property_float_valContext>(_ctx, getState());
  enterRule(_localctx, 16, EffectLabParser::RuleProperty_float_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    number_val();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_float2_valContext ------------------------------------------------------------------

EffectLabParser::Property_float2_valContext::Property_float2_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Number_valContext *> EffectLabParser::Property_float2_valContext::number_val() {
  return getRuleContexts<EffectLabParser::Number_valContext>();
}

EffectLabParser::Number_valContext* EffectLabParser::Property_float2_valContext::number_val(size_t i) {
  return getRuleContext<EffectLabParser::Number_valContext>(i);
}


size_t EffectLabParser::Property_float2_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float2_val;
}

void EffectLabParser::Property_float2_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float2_val(this);
}

void EffectLabParser::Property_float2_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float2_val(this);
}


std::any EffectLabParser::Property_float2_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float2_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float2_valContext* EffectLabParser::property_float2_val() {
  Property_float2_valContext *_localctx = _tracker.createInstance<Property_float2_valContext>(_ctx, getState());
  enterRule(_localctx, 18, EffectLabParser::RuleProperty_float2_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(EffectLabParser::T__7);
    setState(65);
    number_val();
    setState(66);
    match(EffectLabParser::T__8);
    setState(67);
    number_val();
    setState(68);
    match(EffectLabParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_float3_valContext ------------------------------------------------------------------

EffectLabParser::Property_float3_valContext::Property_float3_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Number_valContext *> EffectLabParser::Property_float3_valContext::number_val() {
  return getRuleContexts<EffectLabParser::Number_valContext>();
}

EffectLabParser::Number_valContext* EffectLabParser::Property_float3_valContext::number_val(size_t i) {
  return getRuleContext<EffectLabParser::Number_valContext>(i);
}


size_t EffectLabParser::Property_float3_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float3_val;
}

void EffectLabParser::Property_float3_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float3_val(this);
}

void EffectLabParser::Property_float3_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float3_val(this);
}


std::any EffectLabParser::Property_float3_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float3_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float3_valContext* EffectLabParser::property_float3_val() {
  Property_float3_valContext *_localctx = _tracker.createInstance<Property_float3_valContext>(_ctx, getState());
  enterRule(_localctx, 20, EffectLabParser::RuleProperty_float3_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70);
    match(EffectLabParser::T__7);
    setState(71);
    number_val();
    setState(72);
    match(EffectLabParser::T__8);
    setState(73);
    number_val();
    setState(74);
    match(EffectLabParser::T__8);
    setState(75);
    number_val();
    setState(76);
    match(EffectLabParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_float4_valContext ------------------------------------------------------------------

EffectLabParser::Property_float4_valContext::Property_float4_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Number_valContext *> EffectLabParser::Property_float4_valContext::number_val() {
  return getRuleContexts<EffectLabParser::Number_valContext>();
}

EffectLabParser::Number_valContext* EffectLabParser::Property_float4_valContext::number_val(size_t i) {
  return getRuleContext<EffectLabParser::Number_valContext>(i);
}


size_t EffectLabParser::Property_float4_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float4_val;
}

void EffectLabParser::Property_float4_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float4_val(this);
}

void EffectLabParser::Property_float4_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float4_val(this);
}


std::any EffectLabParser::Property_float4_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float4_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float4_valContext* EffectLabParser::property_float4_val() {
  Property_float4_valContext *_localctx = _tracker.createInstance<Property_float4_valContext>(_ctx, getState());
  enterRule(_localctx, 22, EffectLabParser::RuleProperty_float4_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(EffectLabParser::T__7);
    setState(79);
    number_val();
    setState(80);
    match(EffectLabParser::T__8);
    setState(81);
    number_val();
    setState(82);
    match(EffectLabParser::T__8);
    setState(83);
    number_val();
    setState(84);
    match(EffectLabParser::T__8);
    setState(85);
    number_val();
    setState(86);
    match(EffectLabParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_texture_valContext ------------------------------------------------------------------

EffectLabParser::Property_texture_valContext::Property_texture_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_texture_valContext::KWWhite() {
  return getToken(EffectLabParser::KWWhite, 0);
}

tree::TerminalNode* EffectLabParser::Property_texture_valContext::KWBlack() {
  return getToken(EffectLabParser::KWBlack, 0);
}

tree::TerminalNode* EffectLabParser::Property_texture_valContext::KWBump() {
  return getToken(EffectLabParser::KWBump, 0);
}


size_t EffectLabParser::Property_texture_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_texture_val;
}

void EffectLabParser::Property_texture_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_texture_val(this);
}

void EffectLabParser::Property_texture_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_texture_val(this);
}


std::any EffectLabParser::Property_texture_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_texture_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_texture_valContext* EffectLabParser::property_texture_val() {
  Property_texture_valContext *_localctx = _tracker.createInstance<Property_texture_valContext>(_ctx, getState());
  enterRule(_localctx, 24, EffectLabParser::RuleProperty_texture_val);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 481036337152) != 0)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_matrix_valContext ------------------------------------------------------------------

EffectLabParser::Property_matrix_valContext::Property_matrix_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_matrix_valContext::KWIdentity() {
  return getToken(EffectLabParser::KWIdentity, 0);
}


size_t EffectLabParser::Property_matrix_valContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_matrix_val;
}

void EffectLabParser::Property_matrix_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_matrix_val(this);
}

void EffectLabParser::Property_matrix_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_matrix_val(this);
}


std::any EffectLabParser::Property_matrix_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_matrix_val(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_matrix_valContext* EffectLabParser::property_matrix_val() {
  Property_matrix_valContext *_localctx = _tracker.createInstance<Property_matrix_valContext>(_ctx, getState());
  enterRule(_localctx, 26, EffectLabParser::RuleProperty_matrix_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(EffectLabParser::KWIdentity);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_itemContext ------------------------------------------------------------------

EffectLabParser::Property_itemContext::Property_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_itemContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_item;
}

void EffectLabParser::Property_itemContext::copyFrom(Property_itemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PropertyItemIntContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemIntContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemIntContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_int_valContext* EffectLabParser::PropertyItemIntContext::property_int_val() {
  return getRuleContext<EffectLabParser::Property_int_valContext>(0);
}

EffectLabParser::PropertyItemIntContext::PropertyItemIntContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemIntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemInt(this);
}
void EffectLabParser::PropertyItemIntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemInt(this);
}

std::any EffectLabParser::PropertyItemIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemFloat4Context ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemFloat4Context::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemFloat4Context::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_float4_valContext* EffectLabParser::PropertyItemFloat4Context::property_float4_val() {
  return getRuleContext<EffectLabParser::Property_float4_valContext>(0);
}

EffectLabParser::PropertyItemFloat4Context::PropertyItemFloat4Context(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemFloat4Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemFloat4(this);
}
void EffectLabParser::PropertyItemFloat4Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemFloat4(this);
}

std::any EffectLabParser::PropertyItemFloat4Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemFloat4(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemBoolContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemBoolContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemBoolContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_bool_valContext* EffectLabParser::PropertyItemBoolContext::property_bool_val() {
  return getRuleContext<EffectLabParser::Property_bool_valContext>(0);
}

EffectLabParser::PropertyItemBoolContext::PropertyItemBoolContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemBoolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemBool(this);
}
void EffectLabParser::PropertyItemBoolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemBool(this);
}

std::any EffectLabParser::PropertyItemBoolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemBool(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemMatrixContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemMatrixContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemMatrixContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_matrix_valContext* EffectLabParser::PropertyItemMatrixContext::property_matrix_val() {
  return getRuleContext<EffectLabParser::Property_matrix_valContext>(0);
}

EffectLabParser::PropertyItemMatrixContext::PropertyItemMatrixContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemMatrixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemMatrix(this);
}
void EffectLabParser::PropertyItemMatrixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemMatrix(this);
}

std::any EffectLabParser::PropertyItemMatrixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemMatrix(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemRangeContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemRangeContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemRangeContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_range_typeContext* EffectLabParser::PropertyItemRangeContext::property_range_type() {
  return getRuleContext<EffectLabParser::Property_range_typeContext>(0);
}

EffectLabParser::Property_range_valContext* EffectLabParser::PropertyItemRangeContext::property_range_val() {
  return getRuleContext<EffectLabParser::Property_range_valContext>(0);
}

EffectLabParser::PropertyItemRangeContext::PropertyItemRangeContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemRangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemRange(this);
}
void EffectLabParser::PropertyItemRangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemRange(this);
}

std::any EffectLabParser::PropertyItemRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemRange(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemFloat2Context ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemFloat2Context::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemFloat2Context::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_float2_valContext* EffectLabParser::PropertyItemFloat2Context::property_float2_val() {
  return getRuleContext<EffectLabParser::Property_float2_valContext>(0);
}

EffectLabParser::PropertyItemFloat2Context::PropertyItemFloat2Context(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemFloat2Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemFloat2(this);
}
void EffectLabParser::PropertyItemFloat2Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemFloat2(this);
}

std::any EffectLabParser::PropertyItemFloat2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemFloat2(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemFloat3Context ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemFloat3Context::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemFloat3Context::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_float3_valContext* EffectLabParser::PropertyItemFloat3Context::property_float3_val() {
  return getRuleContext<EffectLabParser::Property_float3_valContext>(0);
}

EffectLabParser::PropertyItemFloat3Context::PropertyItemFloat3Context(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemFloat3Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemFloat3(this);
}
void EffectLabParser::PropertyItemFloat3Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemFloat3(this);
}

std::any EffectLabParser::PropertyItemFloat3Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemFloat3(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemFloatContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemFloatContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemFloatContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_float_valContext* EffectLabParser::PropertyItemFloatContext::property_float_val() {
  return getRuleContext<EffectLabParser::Property_float_valContext>(0);
}

EffectLabParser::PropertyItemFloatContext::PropertyItemFloatContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemFloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemFloat(this);
}
void EffectLabParser::PropertyItemFloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemFloat(this);
}

std::any EffectLabParser::PropertyItemFloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemFloat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyItemTextureContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PropertyItemTextureContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}

tree::TerminalNode* EffectLabParser::PropertyItemTextureContext::String() {
  return getToken(EffectLabParser::String, 0);
}

EffectLabParser::Property_texture_valContext* EffectLabParser::PropertyItemTextureContext::property_texture_val() {
  return getRuleContext<EffectLabParser::Property_texture_valContext>(0);
}

EffectLabParser::PropertyItemTextureContext::PropertyItemTextureContext(Property_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PropertyItemTextureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyItemTexture(this);
}
void EffectLabParser::PropertyItemTextureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyItemTexture(this);
}

std::any EffectLabParser::PropertyItemTextureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPropertyItemTexture(this);
  else
    return visitor->visitChildren(this);
}
EffectLabParser::Property_itemContext* EffectLabParser::property_item() {
  Property_itemContext *_localctx = _tracker.createInstance<Property_itemContext>(_ctx, getState());
  enterRule(_localctx, 28, EffectLabParser::RuleProperty_item);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemBoolContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(92);
      match(EffectLabParser::Identity);
      setState(93);
      match(EffectLabParser::T__7);
      setState(94);
      match(EffectLabParser::String);
      setState(95);
      match(EffectLabParser::T__8);
      setState(96);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__10

      || _la == EffectLabParser::T__11)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(97);
      match(EffectLabParser::T__9);
      setState(98);
      match(EffectLabParser::T__12);
      setState(99);
      property_bool_val();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemIntContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(100);
      match(EffectLabParser::Identity);
      setState(101);
      match(EffectLabParser::T__7);
      setState(102);
      match(EffectLabParser::String);
      setState(103);
      match(EffectLabParser::T__8);
      setState(104);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__13

      || _la == EffectLabParser::T__14)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(105);
      match(EffectLabParser::T__9);
      setState(106);
      match(EffectLabParser::T__12);
      setState(107);
      property_int_val();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemRangeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(108);
      match(EffectLabParser::Identity);
      setState(109);
      match(EffectLabParser::T__7);
      setState(110);
      match(EffectLabParser::String);
      setState(111);
      match(EffectLabParser::T__8);
      setState(112);
      property_range_type();
      setState(113);
      match(EffectLabParser::T__9);
      setState(114);
      match(EffectLabParser::T__12);
      setState(115);
      property_range_val();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloatContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(117);
      match(EffectLabParser::Identity);
      setState(118);
      match(EffectLabParser::T__7);
      setState(119);
      match(EffectLabParser::String);
      setState(120);
      match(EffectLabParser::T__8);
      setState(121);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__15

      || _la == EffectLabParser::T__16)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(122);
      match(EffectLabParser::T__9);
      setState(123);
      match(EffectLabParser::T__12);
      setState(124);
      property_float_val();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(125);
      match(EffectLabParser::Identity);
      setState(126);
      match(EffectLabParser::T__7);
      setState(127);
      match(EffectLabParser::String);
      setState(128);
      match(EffectLabParser::T__8);
      setState(129);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__17

      || _la == EffectLabParser::T__18)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(130);
      match(EffectLabParser::T__9);
      setState(131);
      match(EffectLabParser::T__12);
      setState(132);
      property_float2_val();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat3Context>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(133);
      match(EffectLabParser::Identity);
      setState(134);
      match(EffectLabParser::T__7);
      setState(135);
      match(EffectLabParser::String);
      setState(136);
      match(EffectLabParser::T__8);
      setState(137);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__19

      || _la == EffectLabParser::T__20)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(138);
      match(EffectLabParser::T__9);
      setState(139);
      match(EffectLabParser::T__12);
      setState(140);
      property_float3_val();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat4Context>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(141);
      match(EffectLabParser::Identity);
      setState(142);
      match(EffectLabParser::T__7);
      setState(143);
      match(EffectLabParser::String);
      setState(144);
      match(EffectLabParser::T__8);
      setState(145);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__21

      || _la == EffectLabParser::T__22)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(146);
      match(EffectLabParser::T__9);
      setState(147);
      match(EffectLabParser::T__12);
      setState(148);
      property_float4_val();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemTextureContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(149);
      match(EffectLabParser::Identity);
      setState(150);
      match(EffectLabParser::T__7);
      setState(151);
      match(EffectLabParser::String);
      setState(152);
      match(EffectLabParser::T__8);
      setState(153);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__23

      || _la == EffectLabParser::T__24)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(154);
      match(EffectLabParser::T__9);
      setState(155);
      match(EffectLabParser::T__12);
      setState(156);
      property_texture_val();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemMatrixContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(157);
      match(EffectLabParser::Identity);
      setState(158);
      match(EffectLabParser::T__7);
      setState(159);
      match(EffectLabParser::String);
      setState(160);
      match(EffectLabParser::T__8);
      setState(161);
      _la = _input->LA(1);
      if (!(_la == EffectLabParser::T__25

      || _la == EffectLabParser::T__26)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(162);
      match(EffectLabParser::T__9);
      setState(163);
      match(EffectLabParser::T__12);
      setState(164);
      property_matrix_val();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void EffectLabParser::initialize() {
  ::antlr4::internal::call_once(effectlabParserOnceFlag, effectlabParserInitialize);
}
