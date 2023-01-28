
// Generated from EffectLab.g4 by ANTLR 4.11.1


#include "EffectLabLexer.h"


using namespace antlr4;

using namespace Eureka::ParserDetails;


using namespace antlr4;

namespace {

struct EffectLabLexerStaticData final {
  EffectLabLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  EffectLabLexerStaticData(const EffectLabLexerStaticData&) = delete;
  EffectLabLexerStaticData(EffectLabLexerStaticData&&) = delete;
  EffectLabLexerStaticData& operator=(const EffectLabLexerStaticData&) = delete;
  EffectLabLexerStaticData& operator=(EffectLabLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag effectlablexerLexerOnceFlag;
EffectLabLexerStaticData *effectlablexerLexerStaticData = nullptr;

void effectlablexerLexerInitialize() {
  assert(effectlablexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<EffectLabLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "BoolVal", 
      "IntVal", "FloatVal", "String", "Identity", "KWIdentity", "KWTrue", 
      "KWFalse", "KWWhite", "KWBlack", "KWBump", "WhiteSpace", "LineComment", 
      "Comment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'SourcePath'", "':'", "';'", "'Properties'", "'{'", "'}'", "'('", 
      "','", "')'", "'bool'", "'Bool'", "'='", "'Int'", "'int'", "'Float'", 
      "'float '", "", "", "", "", "", "'identity'", "'true'", "'false'", 
      "'white'", "'black'", "'bump'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "BoolVal", "IntVal", "FloatVal", "String", "Identity", "KWIdentity", 
      "KWTrue", "KWFalse", "KWWhite", "KWBlack", "KWBump", "WhiteSpace", 
      "LineComment", "Comment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,30,246,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,
  	2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,6,
  	1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,3,16,133,8,16,1,17,
  	1,17,5,17,137,8,17,10,17,12,17,140,9,17,1,18,4,18,143,8,18,11,18,12,18,
  	144,1,18,1,18,5,18,149,8,18,10,18,12,18,152,9,18,1,18,3,18,155,8,18,1,
  	19,1,19,5,19,159,8,19,10,19,12,19,162,9,19,1,19,1,19,1,20,1,20,5,20,168,
  	8,20,10,20,12,20,171,9,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,
  	1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,
  	1,27,4,27,211,8,27,11,27,12,27,212,1,27,1,27,1,28,1,28,1,28,1,28,5,28,
  	221,8,28,10,28,12,28,224,9,28,1,28,3,28,227,8,28,1,28,1,28,1,28,1,28,
  	1,29,1,29,1,29,1,29,5,29,237,8,29,10,29,12,29,240,9,29,1,29,1,29,1,29,
  	1,29,1,29,3,160,222,238,0,30,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,
  	19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,
  	21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,1,0,5,1,0,49,
  	57,1,0,48,57,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,3,0,
  	9,10,13,13,32,32,256,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,
  	0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,
  	1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,
  	0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,
  	0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,
  	1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,1,61,1,0,
  	0,0,3,72,1,0,0,0,5,74,1,0,0,0,7,76,1,0,0,0,9,87,1,0,0,0,11,89,1,0,0,0,
  	13,91,1,0,0,0,15,93,1,0,0,0,17,95,1,0,0,0,19,97,1,0,0,0,21,102,1,0,0,
  	0,23,107,1,0,0,0,25,109,1,0,0,0,27,113,1,0,0,0,29,117,1,0,0,0,31,123,
  	1,0,0,0,33,132,1,0,0,0,35,134,1,0,0,0,37,142,1,0,0,0,39,156,1,0,0,0,41,
  	165,1,0,0,0,43,172,1,0,0,0,45,181,1,0,0,0,47,186,1,0,0,0,49,192,1,0,0,
  	0,51,198,1,0,0,0,53,204,1,0,0,0,55,210,1,0,0,0,57,216,1,0,0,0,59,232,
  	1,0,0,0,61,62,5,83,0,0,62,63,5,111,0,0,63,64,5,117,0,0,64,65,5,114,0,
  	0,65,66,5,99,0,0,66,67,5,101,0,0,67,68,5,80,0,0,68,69,5,97,0,0,69,70,
  	5,116,0,0,70,71,5,104,0,0,71,2,1,0,0,0,72,73,5,58,0,0,73,4,1,0,0,0,74,
  	75,5,59,0,0,75,6,1,0,0,0,76,77,5,80,0,0,77,78,5,114,0,0,78,79,5,111,0,
  	0,79,80,5,112,0,0,80,81,5,101,0,0,81,82,5,114,0,0,82,83,5,116,0,0,83,
  	84,5,105,0,0,84,85,5,101,0,0,85,86,5,115,0,0,86,8,1,0,0,0,87,88,5,123,
  	0,0,88,10,1,0,0,0,89,90,5,125,0,0,90,12,1,0,0,0,91,92,5,40,0,0,92,14,
  	1,0,0,0,93,94,5,44,0,0,94,16,1,0,0,0,95,96,5,41,0,0,96,18,1,0,0,0,97,
  	98,5,98,0,0,98,99,5,111,0,0,99,100,5,111,0,0,100,101,5,108,0,0,101,20,
  	1,0,0,0,102,103,5,66,0,0,103,104,5,111,0,0,104,105,5,111,0,0,105,106,
  	5,108,0,0,106,22,1,0,0,0,107,108,5,61,0,0,108,24,1,0,0,0,109,110,5,73,
  	0,0,110,111,5,110,0,0,111,112,5,116,0,0,112,26,1,0,0,0,113,114,5,105,
  	0,0,114,115,5,110,0,0,115,116,5,116,0,0,116,28,1,0,0,0,117,118,5,70,0,
  	0,118,119,5,108,0,0,119,120,5,111,0,0,120,121,5,97,0,0,121,122,5,116,
  	0,0,122,30,1,0,0,0,123,124,5,102,0,0,124,125,5,108,0,0,125,126,5,111,
  	0,0,126,127,5,97,0,0,127,128,5,116,0,0,128,129,5,32,0,0,129,32,1,0,0,
  	0,130,133,3,45,22,0,131,133,3,47,23,0,132,130,1,0,0,0,132,131,1,0,0,0,
  	133,34,1,0,0,0,134,138,7,0,0,0,135,137,7,1,0,0,136,135,1,0,0,0,137,140,
  	1,0,0,0,138,136,1,0,0,0,138,139,1,0,0,0,139,36,1,0,0,0,140,138,1,0,0,
  	0,141,143,7,1,0,0,142,141,1,0,0,0,143,144,1,0,0,0,144,142,1,0,0,0,144,
  	145,1,0,0,0,145,146,1,0,0,0,146,150,9,0,0,0,147,149,7,1,0,0,148,147,1,
  	0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,154,1,0,0,0,
  	152,150,1,0,0,0,153,155,5,102,0,0,154,153,1,0,0,0,154,155,1,0,0,0,155,
  	38,1,0,0,0,156,160,5,34,0,0,157,159,9,0,0,0,158,157,1,0,0,0,159,162,1,
  	0,0,0,160,161,1,0,0,0,160,158,1,0,0,0,161,163,1,0,0,0,162,160,1,0,0,0,
  	163,164,5,34,0,0,164,40,1,0,0,0,165,169,7,2,0,0,166,168,7,3,0,0,167,166,
  	1,0,0,0,168,171,1,0,0,0,169,167,1,0,0,0,169,170,1,0,0,0,170,42,1,0,0,
  	0,171,169,1,0,0,0,172,173,5,105,0,0,173,174,5,100,0,0,174,175,5,101,0,
  	0,175,176,5,110,0,0,176,177,5,116,0,0,177,178,5,105,0,0,178,179,5,116,
  	0,0,179,180,5,121,0,0,180,44,1,0,0,0,181,182,5,116,0,0,182,183,5,114,
  	0,0,183,184,5,117,0,0,184,185,5,101,0,0,185,46,1,0,0,0,186,187,5,102,
  	0,0,187,188,5,97,0,0,188,189,5,108,0,0,189,190,5,115,0,0,190,191,5,101,
  	0,0,191,48,1,0,0,0,192,193,5,119,0,0,193,194,5,104,0,0,194,195,5,105,
  	0,0,195,196,5,116,0,0,196,197,5,101,0,0,197,50,1,0,0,0,198,199,5,98,0,
  	0,199,200,5,108,0,0,200,201,5,97,0,0,201,202,5,99,0,0,202,203,5,107,0,
  	0,203,52,1,0,0,0,204,205,5,98,0,0,205,206,5,117,0,0,206,207,5,109,0,0,
  	207,208,5,112,0,0,208,54,1,0,0,0,209,211,7,4,0,0,210,209,1,0,0,0,211,
  	212,1,0,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,214,1,0,0,0,214,215,6,
  	27,0,0,215,56,1,0,0,0,216,217,5,47,0,0,217,218,5,47,0,0,218,222,1,0,0,
  	0,219,221,9,0,0,0,220,219,1,0,0,0,221,224,1,0,0,0,222,223,1,0,0,0,222,
  	220,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,225,227,5,13,0,0,226,225,
  	1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,0,228,229,5,10,0,0,229,230,1,0,
  	0,0,230,231,6,28,0,0,231,58,1,0,0,0,232,233,5,47,0,0,233,234,5,42,0,0,
  	234,238,1,0,0,0,235,237,9,0,0,0,236,235,1,0,0,0,237,240,1,0,0,0,238,239,
  	1,0,0,0,238,236,1,0,0,0,239,241,1,0,0,0,240,238,1,0,0,0,241,242,5,42,
  	0,0,242,243,5,47,0,0,243,244,1,0,0,0,244,245,6,29,0,0,245,60,1,0,0,0,
  	12,0,132,138,144,150,154,160,169,212,222,226,238,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  effectlablexerLexerStaticData = staticData.release();
}

}

EffectLabLexer::EffectLabLexer(CharStream *input) : Lexer(input) {
  EffectLabLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *effectlablexerLexerStaticData->atn, effectlablexerLexerStaticData->decisionToDFA, effectlablexerLexerStaticData->sharedContextCache);
}

EffectLabLexer::~EffectLabLexer() {
  delete _interpreter;
}

std::string EffectLabLexer::getGrammarFileName() const {
  return "EffectLab.g4";
}

const std::vector<std::string>& EffectLabLexer::getRuleNames() const {
  return effectlablexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& EffectLabLexer::getChannelNames() const {
  return effectlablexerLexerStaticData->channelNames;
}

const std::vector<std::string>& EffectLabLexer::getModeNames() const {
  return effectlablexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& EffectLabLexer::getVocabulary() const {
  return effectlablexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView EffectLabLexer::getSerializedATN() const {
  return effectlablexerLexerStaticData->serializedATN;
}

const atn::ATN& EffectLabLexer::getATN() const {
  return *effectlablexerLexerStaticData->atn;
}




void EffectLabLexer::initialize() {
  ::antlr4::internal::call_once(effectlablexerLexerOnceFlag, effectlablexerLexerInitialize);
}
