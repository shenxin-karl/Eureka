
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
      "effect", "source_path", "property_block", "number_val", "property_bool_type", 
      "property_int_type", "property_range_type", "property_float_type", 
      "property_float2_type", "property_float3_type", "property_float4_type", 
      "property_texture_2d_type", "property_matrix_type", "property_range_val", 
      "property_bool_val", "property_int_val", "property_float_val", "property_float2_val", 
      "property_float3_val", "property_float4_val", "property_matrix_val", 
      "property_texture_val", "property_name", "property_description", "property_item"
    },
    std::vector<std::string>{
      "", "'SourcePath'", "':'", "'Properties'", "'{'", "'}'", "'bool'", 
      "'Bool'", "'int'", "'Int'", "'range'", "'Range'", "'('", "','", "')'", 
      "'float'", "'Float'", "'float2'", "'Float2'", "'float3'", "'Float3'", 
      "'float4'", "'Float4'", "'2d'", "'2D'", "'matrix'", "'Matrix'", "'identity'", 
      "'white'", "'White'", "'black'", "'Black'", "'bump'", "'Bump'", "'='"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "IntLiteral", "FloatLiteral", "BooleanLiteral", "StringLiteral", 
      "Identity", "WhiteSpace", "LineComment", "BlockComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,42,219,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,3,0,53,8,0,1,1,1,1,1,1,1,1,1,
  	2,1,2,1,2,4,2,62,8,2,11,2,12,2,63,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,
  	12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,21,1,21,1,21,3,21,130,8,21,1,
  	22,1,22,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,3,24,217,8,24,1,24,0,0,25,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,0,13,1,0,35,36,1,0,6,7,1,0,8,9,1,0,10,11,
  	1,0,15,16,1,0,17,18,1,0,19,20,1,0,21,22,1,0,23,24,1,0,25,26,1,0,28,29,
  	1,0,30,31,1,0,32,33,205,0,50,1,0,0,0,2,54,1,0,0,0,4,58,1,0,0,0,6,67,1,
  	0,0,0,8,69,1,0,0,0,10,71,1,0,0,0,12,73,1,0,0,0,14,80,1,0,0,0,16,82,1,
  	0,0,0,18,84,1,0,0,0,20,86,1,0,0,0,22,88,1,0,0,0,24,90,1,0,0,0,26,92,1,
  	0,0,0,28,94,1,0,0,0,30,96,1,0,0,0,32,98,1,0,0,0,34,100,1,0,0,0,36,106,
  	1,0,0,0,38,114,1,0,0,0,40,124,1,0,0,0,42,129,1,0,0,0,44,131,1,0,0,0,46,
  	133,1,0,0,0,48,216,1,0,0,0,50,52,3,2,1,0,51,53,3,4,2,0,52,51,1,0,0,0,
  	52,53,1,0,0,0,53,1,1,0,0,0,54,55,5,1,0,0,55,56,5,2,0,0,56,57,5,38,0,0,
  	57,3,1,0,0,0,58,59,5,3,0,0,59,61,5,4,0,0,60,62,3,48,24,0,61,60,1,0,0,
  	0,62,63,1,0,0,0,63,61,1,0,0,0,63,64,1,0,0,0,64,65,1,0,0,0,65,66,5,5,0,
  	0,66,5,1,0,0,0,67,68,7,0,0,0,68,7,1,0,0,0,69,70,7,1,0,0,70,9,1,0,0,0,
  	71,72,7,2,0,0,72,11,1,0,0,0,73,74,7,3,0,0,74,75,5,12,0,0,75,76,3,6,3,
  	0,76,77,5,13,0,0,77,78,3,6,3,0,78,79,5,14,0,0,79,13,1,0,0,0,80,81,7,4,
  	0,0,81,15,1,0,0,0,82,83,7,5,0,0,83,17,1,0,0,0,84,85,7,6,0,0,85,19,1,0,
  	0,0,86,87,7,7,0,0,87,21,1,0,0,0,88,89,7,8,0,0,89,23,1,0,0,0,90,91,7,9,
  	0,0,91,25,1,0,0,0,92,93,3,6,3,0,93,27,1,0,0,0,94,95,5,37,0,0,95,29,1,
  	0,0,0,96,97,5,35,0,0,97,31,1,0,0,0,98,99,3,6,3,0,99,33,1,0,0,0,100,101,
  	5,12,0,0,101,102,3,6,3,0,102,103,5,13,0,0,103,104,3,6,3,0,104,105,5,14,
  	0,0,105,35,1,0,0,0,106,107,5,12,0,0,107,108,3,6,3,0,108,109,5,13,0,0,
  	109,110,3,6,3,0,110,111,5,13,0,0,111,112,3,6,3,0,112,113,5,14,0,0,113,
  	37,1,0,0,0,114,115,5,12,0,0,115,116,3,6,3,0,116,117,5,13,0,0,117,118,
  	3,6,3,0,118,119,5,13,0,0,119,120,3,6,3,0,120,121,5,13,0,0,121,122,3,6,
  	3,0,122,123,5,14,0,0,123,39,1,0,0,0,124,125,5,27,0,0,125,41,1,0,0,0,126,
  	130,7,10,0,0,127,130,7,11,0,0,128,130,7,12,0,0,129,126,1,0,0,0,129,127,
  	1,0,0,0,129,128,1,0,0,0,130,43,1,0,0,0,131,132,5,39,0,0,132,45,1,0,0,
  	0,133,134,5,38,0,0,134,47,1,0,0,0,135,136,3,44,22,0,136,137,5,12,0,0,
  	137,138,3,46,23,0,138,139,5,13,0,0,139,140,3,8,4,0,140,141,5,14,0,0,141,
  	142,5,34,0,0,142,143,3,28,14,0,143,217,1,0,0,0,144,145,3,44,22,0,145,
  	146,5,12,0,0,146,147,3,46,23,0,147,148,5,13,0,0,148,149,3,10,5,0,149,
  	150,5,14,0,0,150,151,5,34,0,0,151,152,3,30,15,0,152,217,1,0,0,0,153,154,
  	3,44,22,0,154,155,5,12,0,0,155,156,3,46,23,0,156,157,5,13,0,0,157,158,
  	3,12,6,0,158,159,5,14,0,0,159,160,5,34,0,0,160,161,3,26,13,0,161,217,
  	1,0,0,0,162,163,3,44,22,0,163,164,5,12,0,0,164,165,3,46,23,0,165,166,
  	5,13,0,0,166,167,3,14,7,0,167,168,5,14,0,0,168,169,5,34,0,0,169,170,3,
  	32,16,0,170,217,1,0,0,0,171,172,3,44,22,0,172,173,5,12,0,0,173,174,3,
  	46,23,0,174,175,5,13,0,0,175,176,3,16,8,0,176,177,5,14,0,0,177,178,5,
  	34,0,0,178,179,3,34,17,0,179,217,1,0,0,0,180,181,3,44,22,0,181,182,5,
  	12,0,0,182,183,3,46,23,0,183,184,5,13,0,0,184,185,3,18,9,0,185,186,5,
  	14,0,0,186,187,5,34,0,0,187,188,3,36,18,0,188,217,1,0,0,0,189,190,3,44,
  	22,0,190,191,5,12,0,0,191,192,3,46,23,0,192,193,5,13,0,0,193,194,3,20,
  	10,0,194,195,5,14,0,0,195,196,5,34,0,0,196,197,3,38,19,0,197,217,1,0,
  	0,0,198,199,3,44,22,0,199,200,5,12,0,0,200,201,3,46,23,0,201,202,5,13,
  	0,0,202,203,3,22,11,0,203,204,5,14,0,0,204,205,5,34,0,0,205,206,3,42,
  	21,0,206,217,1,0,0,0,207,208,3,44,22,0,208,209,5,12,0,0,209,210,3,46,
  	23,0,210,211,5,13,0,0,211,212,3,24,12,0,212,213,5,14,0,0,213,214,5,34,
  	0,0,214,215,3,40,20,0,215,217,1,0,0,0,216,135,1,0,0,0,216,144,1,0,0,0,
  	216,153,1,0,0,0,216,162,1,0,0,0,216,171,1,0,0,0,216,180,1,0,0,0,216,189,
  	1,0,0,0,216,198,1,0,0,0,216,207,1,0,0,0,217,49,1,0,0,0,4,52,63,129,216
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
    setState(50);
    source_path();
    setState(52);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EffectLabParser::T__2) {
      setState(51);
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

tree::TerminalNode* EffectLabParser::Source_pathContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
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
    setState(54);
    match(EffectLabParser::T__0);
    setState(55);
    match(EffectLabParser::T__1);
    setState(56);
    match(EffectLabParser::StringLiteral);
   
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
    setState(58);
    match(EffectLabParser::T__2);
    setState(59);
    match(EffectLabParser::T__3);
    setState(61); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(60);
      property_item();
      setState(63); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EffectLabParser::Identity);
    setState(65);
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

tree::TerminalNode* EffectLabParser::Number_valContext::IntLiteral() {
  return getToken(EffectLabParser::IntLiteral, 0);
}

tree::TerminalNode* EffectLabParser::Number_valContext::FloatLiteral() {
  return getToken(EffectLabParser::FloatLiteral, 0);
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
    setState(67);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::IntLiteral

    || _la == EffectLabParser::FloatLiteral)) {
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

//----------------- Property_bool_typeContext ------------------------------------------------------------------

EffectLabParser::Property_bool_typeContext::Property_bool_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_bool_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_bool_type;
}

void EffectLabParser::Property_bool_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_bool_type(this);
}

void EffectLabParser::Property_bool_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_bool_type(this);
}


std::any EffectLabParser::Property_bool_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_bool_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_bool_typeContext* EffectLabParser::property_bool_type() {
  Property_bool_typeContext *_localctx = _tracker.createInstance<Property_bool_typeContext>(_ctx, getState());
  enterRule(_localctx, 8, EffectLabParser::RuleProperty_bool_type);
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
    setState(69);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__5

    || _la == EffectLabParser::T__6)) {
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

//----------------- Property_int_typeContext ------------------------------------------------------------------

EffectLabParser::Property_int_typeContext::Property_int_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_int_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_int_type;
}

void EffectLabParser::Property_int_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_int_type(this);
}

void EffectLabParser::Property_int_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_int_type(this);
}


std::any EffectLabParser::Property_int_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_int_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_int_typeContext* EffectLabParser::property_int_type() {
  Property_int_typeContext *_localctx = _tracker.createInstance<Property_int_typeContext>(_ctx, getState());
  enterRule(_localctx, 10, EffectLabParser::RuleProperty_int_type);
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
    setState(71);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__7

    || _la == EffectLabParser::T__8)) {
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
  enterRule(_localctx, 12, EffectLabParser::RuleProperty_range_type);
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
    setState(73);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__9

    || _la == EffectLabParser::T__10)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(74);
    match(EffectLabParser::T__11);
    setState(75);
    number_val();
    setState(76);
    match(EffectLabParser::T__12);
    setState(77);
    number_val();
    setState(78);
    match(EffectLabParser::T__13);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_float_typeContext ------------------------------------------------------------------

EffectLabParser::Property_float_typeContext::Property_float_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_float_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float_type;
}

void EffectLabParser::Property_float_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float_type(this);
}

void EffectLabParser::Property_float_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float_type(this);
}


std::any EffectLabParser::Property_float_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float_typeContext* EffectLabParser::property_float_type() {
  Property_float_typeContext *_localctx = _tracker.createInstance<Property_float_typeContext>(_ctx, getState());
  enterRule(_localctx, 14, EffectLabParser::RuleProperty_float_type);
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
    setState(80);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__14

    || _la == EffectLabParser::T__15)) {
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

//----------------- Property_float2_typeContext ------------------------------------------------------------------

EffectLabParser::Property_float2_typeContext::Property_float2_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_float2_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float2_type;
}

void EffectLabParser::Property_float2_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float2_type(this);
}

void EffectLabParser::Property_float2_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float2_type(this);
}


std::any EffectLabParser::Property_float2_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float2_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float2_typeContext* EffectLabParser::property_float2_type() {
  Property_float2_typeContext *_localctx = _tracker.createInstance<Property_float2_typeContext>(_ctx, getState());
  enterRule(_localctx, 16, EffectLabParser::RuleProperty_float2_type);
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
    setState(82);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__16

    || _la == EffectLabParser::T__17)) {
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

//----------------- Property_float3_typeContext ------------------------------------------------------------------

EffectLabParser::Property_float3_typeContext::Property_float3_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_float3_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float3_type;
}

void EffectLabParser::Property_float3_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float3_type(this);
}

void EffectLabParser::Property_float3_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float3_type(this);
}


std::any EffectLabParser::Property_float3_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float3_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float3_typeContext* EffectLabParser::property_float3_type() {
  Property_float3_typeContext *_localctx = _tracker.createInstance<Property_float3_typeContext>(_ctx, getState());
  enterRule(_localctx, 18, EffectLabParser::RuleProperty_float3_type);
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
    setState(84);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__18

    || _la == EffectLabParser::T__19)) {
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

//----------------- Property_float4_typeContext ------------------------------------------------------------------

EffectLabParser::Property_float4_typeContext::Property_float4_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_float4_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_float4_type;
}

void EffectLabParser::Property_float4_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float4_type(this);
}

void EffectLabParser::Property_float4_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float4_type(this);
}


std::any EffectLabParser::Property_float4_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float4_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_float4_typeContext* EffectLabParser::property_float4_type() {
  Property_float4_typeContext *_localctx = _tracker.createInstance<Property_float4_typeContext>(_ctx, getState());
  enterRule(_localctx, 20, EffectLabParser::RuleProperty_float4_type);
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
    setState(86);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__20

    || _la == EffectLabParser::T__21)) {
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

//----------------- Property_texture_2d_typeContext ------------------------------------------------------------------

EffectLabParser::Property_texture_2d_typeContext::Property_texture_2d_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_texture_2d_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_texture_2d_type;
}

void EffectLabParser::Property_texture_2d_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_texture_2d_type(this);
}

void EffectLabParser::Property_texture_2d_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_texture_2d_type(this);
}


std::any EffectLabParser::Property_texture_2d_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_texture_2d_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_texture_2d_typeContext* EffectLabParser::property_texture_2d_type() {
  Property_texture_2d_typeContext *_localctx = _tracker.createInstance<Property_texture_2d_typeContext>(_ctx, getState());
  enterRule(_localctx, 22, EffectLabParser::RuleProperty_texture_2d_type);
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
    if (!(_la == EffectLabParser::T__22

    || _la == EffectLabParser::T__23)) {
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

//----------------- Property_matrix_typeContext ------------------------------------------------------------------

EffectLabParser::Property_matrix_typeContext::Property_matrix_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Property_matrix_typeContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_matrix_type;
}

void EffectLabParser::Property_matrix_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_matrix_type(this);
}

void EffectLabParser::Property_matrix_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_matrix_type(this);
}


std::any EffectLabParser::Property_matrix_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_matrix_type(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_matrix_typeContext* EffectLabParser::property_matrix_type() {
  Property_matrix_typeContext *_localctx = _tracker.createInstance<Property_matrix_typeContext>(_ctx, getState());
  enterRule(_localctx, 24, EffectLabParser::RuleProperty_matrix_type);
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
    setState(90);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__24

    || _la == EffectLabParser::T__25)) {
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
  enterRule(_localctx, 26, EffectLabParser::RuleProperty_range_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
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

tree::TerminalNode* EffectLabParser::Property_bool_valContext::BooleanLiteral() {
  return getToken(EffectLabParser::BooleanLiteral, 0);
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
  enterRule(_localctx, 28, EffectLabParser::RuleProperty_bool_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    match(EffectLabParser::BooleanLiteral);
   
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

tree::TerminalNode* EffectLabParser::Property_int_valContext::IntLiteral() {
  return getToken(EffectLabParser::IntLiteral, 0);
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
  enterRule(_localctx, 30, EffectLabParser::RuleProperty_int_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(EffectLabParser::IntLiteral);
   
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
  enterRule(_localctx, 32, EffectLabParser::RuleProperty_float_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
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
  enterRule(_localctx, 34, EffectLabParser::RuleProperty_float2_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(EffectLabParser::T__11);
    setState(101);
    number_val();
    setState(102);
    match(EffectLabParser::T__12);
    setState(103);
    number_val();
    setState(104);
    match(EffectLabParser::T__13);
   
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
  enterRule(_localctx, 36, EffectLabParser::RuleProperty_float3_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(EffectLabParser::T__11);
    setState(107);
    number_val();
    setState(108);
    match(EffectLabParser::T__12);
    setState(109);
    number_val();
    setState(110);
    match(EffectLabParser::T__12);
    setState(111);
    number_val();
    setState(112);
    match(EffectLabParser::T__13);
   
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
  enterRule(_localctx, 38, EffectLabParser::RuleProperty_float4_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(EffectLabParser::T__11);
    setState(115);
    number_val();
    setState(116);
    match(EffectLabParser::T__12);
    setState(117);
    number_val();
    setState(118);
    match(EffectLabParser::T__12);
    setState(119);
    number_val();
    setState(120);
    match(EffectLabParser::T__12);
    setState(121);
    number_val();
    setState(122);
    match(EffectLabParser::T__13);
   
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
  enterRule(_localctx, 40, EffectLabParser::RuleProperty_matrix_val);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    match(EffectLabParser::T__26);
   
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
  enterRule(_localctx, 42, EffectLabParser::RuleProperty_texture_val);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EffectLabParser::T__27:
      case EffectLabParser::T__28: {
        enterOuterAlt(_localctx, 1);
        setState(126);
        _la = _input->LA(1);
        if (!(_la == EffectLabParser::T__27

        || _la == EffectLabParser::T__28)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case EffectLabParser::T__29:
      case EffectLabParser::T__30: {
        enterOuterAlt(_localctx, 2);
        setState(127);
        _la = _input->LA(1);
        if (!(_la == EffectLabParser::T__29

        || _la == EffectLabParser::T__30)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case EffectLabParser::T__31:
      case EffectLabParser::T__32: {
        enterOuterAlt(_localctx, 3);
        setState(128);
        _la = _input->LA(1);
        if (!(_la == EffectLabParser::T__31

        || _la == EffectLabParser::T__32)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_nameContext ------------------------------------------------------------------

EffectLabParser::Property_nameContext::Property_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_nameContext::Identity() {
  return getToken(EffectLabParser::Identity, 0);
}


size_t EffectLabParser::Property_nameContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_name;
}

void EffectLabParser::Property_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_name(this);
}

void EffectLabParser::Property_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_name(this);
}


std::any EffectLabParser::Property_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_name(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_nameContext* EffectLabParser::property_name() {
  Property_nameContext *_localctx = _tracker.createInstance<Property_nameContext>(_ctx, getState());
  enterRule(_localctx, 44, EffectLabParser::RuleProperty_name);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(EffectLabParser::Identity);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_descriptionContext ------------------------------------------------------------------

EffectLabParser::Property_descriptionContext::Property_descriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Property_descriptionContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Property_descriptionContext::getRuleIndex() const {
  return EffectLabParser::RuleProperty_description;
}

void EffectLabParser::Property_descriptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_description(this);
}

void EffectLabParser::Property_descriptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_description(this);
}


std::any EffectLabParser::Property_descriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitProperty_description(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::property_description() {
  Property_descriptionContext *_localctx = _tracker.createInstance<Property_descriptionContext>(_ctx, getState());
  enterRule(_localctx, 46, EffectLabParser::RuleProperty_description);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(EffectLabParser::StringLiteral);
   
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemIntContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemIntContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_int_typeContext* EffectLabParser::PropertyItemIntContext::property_int_type() {
  return getRuleContext<EffectLabParser::Property_int_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemFloat4Context::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemFloat4Context::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_float4_typeContext* EffectLabParser::PropertyItemFloat4Context::property_float4_type() {
  return getRuleContext<EffectLabParser::Property_float4_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemBoolContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemBoolContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_bool_typeContext* EffectLabParser::PropertyItemBoolContext::property_bool_type() {
  return getRuleContext<EffectLabParser::Property_bool_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemMatrixContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemMatrixContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_matrix_typeContext* EffectLabParser::PropertyItemMatrixContext::property_matrix_type() {
  return getRuleContext<EffectLabParser::Property_matrix_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemRangeContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemRangeContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemFloat2Context::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemFloat2Context::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_float2_typeContext* EffectLabParser::PropertyItemFloat2Context::property_float2_type() {
  return getRuleContext<EffectLabParser::Property_float2_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemFloat3Context::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemFloat3Context::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_float3_typeContext* EffectLabParser::PropertyItemFloat3Context::property_float3_type() {
  return getRuleContext<EffectLabParser::Property_float3_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemFloatContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemFloatContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_float_typeContext* EffectLabParser::PropertyItemFloatContext::property_float_type() {
  return getRuleContext<EffectLabParser::Property_float_typeContext>(0);
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

EffectLabParser::Property_nameContext* EffectLabParser::PropertyItemTextureContext::property_name() {
  return getRuleContext<EffectLabParser::Property_nameContext>(0);
}

EffectLabParser::Property_descriptionContext* EffectLabParser::PropertyItemTextureContext::property_description() {
  return getRuleContext<EffectLabParser::Property_descriptionContext>(0);
}

EffectLabParser::Property_texture_2d_typeContext* EffectLabParser::PropertyItemTextureContext::property_texture_2d_type() {
  return getRuleContext<EffectLabParser::Property_texture_2d_typeContext>(0);
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
  enterRule(_localctx, 48, EffectLabParser::RuleProperty_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(216);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemBoolContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(135);
      property_name();
      setState(136);
      match(EffectLabParser::T__11);
      setState(137);
      property_description();
      setState(138);
      match(EffectLabParser::T__12);
      setState(139);
      property_bool_type();
      setState(140);
      match(EffectLabParser::T__13);
      setState(141);
      match(EffectLabParser::T__33);
      setState(142);
      property_bool_val();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemIntContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(144);
      property_name();
      setState(145);
      match(EffectLabParser::T__11);
      setState(146);
      property_description();
      setState(147);
      match(EffectLabParser::T__12);
      setState(148);
      property_int_type();
      setState(149);
      match(EffectLabParser::T__13);
      setState(150);
      match(EffectLabParser::T__33);
      setState(151);
      property_int_val();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemRangeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(153);
      property_name();
      setState(154);
      match(EffectLabParser::T__11);
      setState(155);
      property_description();
      setState(156);
      match(EffectLabParser::T__12);
      setState(157);
      property_range_type();
      setState(158);
      match(EffectLabParser::T__13);
      setState(159);
      match(EffectLabParser::T__33);
      setState(160);
      property_range_val();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloatContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(162);
      property_name();
      setState(163);
      match(EffectLabParser::T__11);
      setState(164);
      property_description();
      setState(165);
      match(EffectLabParser::T__12);
      setState(166);
      property_float_type();
      setState(167);
      match(EffectLabParser::T__13);
      setState(168);
      match(EffectLabParser::T__33);
      setState(169);
      property_float_val();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(171);
      property_name();
      setState(172);
      match(EffectLabParser::T__11);
      setState(173);
      property_description();
      setState(174);
      match(EffectLabParser::T__12);
      setState(175);
      property_float2_type();
      setState(176);
      match(EffectLabParser::T__13);
      setState(177);
      match(EffectLabParser::T__33);
      setState(178);
      property_float2_val();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat3Context>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(180);
      property_name();
      setState(181);
      match(EffectLabParser::T__11);
      setState(182);
      property_description();
      setState(183);
      match(EffectLabParser::T__12);
      setState(184);
      property_float3_type();
      setState(185);
      match(EffectLabParser::T__13);
      setState(186);
      match(EffectLabParser::T__33);
      setState(187);
      property_float3_val();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat4Context>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(189);
      property_name();
      setState(190);
      match(EffectLabParser::T__11);
      setState(191);
      property_description();
      setState(192);
      match(EffectLabParser::T__12);
      setState(193);
      property_float4_type();
      setState(194);
      match(EffectLabParser::T__13);
      setState(195);
      match(EffectLabParser::T__33);
      setState(196);
      property_float4_val();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemTextureContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(198);
      property_name();
      setState(199);
      match(EffectLabParser::T__11);
      setState(200);
      property_description();
      setState(201);
      match(EffectLabParser::T__12);
      setState(202);
      property_texture_2d_type();
      setState(203);
      match(EffectLabParser::T__13);
      setState(204);
      match(EffectLabParser::T__33);
      setState(205);
      property_texture_val();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemMatrixContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(207);
      property_name();
      setState(208);
      match(EffectLabParser::T__11);
      setState(209);
      property_description();
      setState(210);
      match(EffectLabParser::T__12);
      setState(211);
      property_matrix_type();
      setState(212);
      match(EffectLabParser::T__13);
      setState(213);
      match(EffectLabParser::T__33);
      setState(214);
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
