
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
      "KWFalse", "WhiteSpace", "LineComment", "Comment"
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
      "'float '", "", "", "", "", "", "'Identity'", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "BoolVal", "IntVal", "FloatVal", "String", "Identity", "KWIdentity", 
      "KWTrue", "KWFalse", "WhiteSpace", "LineComment", "Comment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,27,223,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,1,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,
  	9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,1,13,
  	1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,16,1,16,3,16,127,8,16,1,17,1,17,5,17,131,8,17,10,17,12,17,
  	134,9,17,1,18,4,18,137,8,18,11,18,12,18,138,1,18,1,18,5,18,143,8,18,10,
  	18,12,18,146,9,18,1,18,3,18,149,8,18,1,19,1,19,5,19,153,8,19,10,19,12,
  	19,156,9,19,1,19,1,19,1,20,1,20,5,20,162,8,20,10,20,12,20,165,9,20,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,24,4,24,188,8,24,11,24,12,24,189,1,24,1,
  	24,1,25,1,25,1,25,1,25,5,25,198,8,25,10,25,12,25,201,9,25,1,25,3,25,204,
  	8,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,5,26,214,8,26,10,26,12,26,
  	217,9,26,1,26,1,26,1,26,1,26,1,26,3,154,199,215,0,27,1,1,3,2,5,3,7,4,
  	9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,
  	17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,1,0,5,
  	1,0,49,57,1,0,48,57,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,
  	3,0,9,10,13,13,32,32,233,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,1,55,1,0,0,0,3,66,1,0,0,0,5,68,1,0,0,0,7,70,1,
  	0,0,0,9,81,1,0,0,0,11,83,1,0,0,0,13,85,1,0,0,0,15,87,1,0,0,0,17,89,1,
  	0,0,0,19,91,1,0,0,0,21,96,1,0,0,0,23,101,1,0,0,0,25,103,1,0,0,0,27,107,
  	1,0,0,0,29,111,1,0,0,0,31,117,1,0,0,0,33,126,1,0,0,0,35,128,1,0,0,0,37,
  	136,1,0,0,0,39,150,1,0,0,0,41,159,1,0,0,0,43,166,1,0,0,0,45,175,1,0,0,
  	0,47,180,1,0,0,0,49,187,1,0,0,0,51,193,1,0,0,0,53,209,1,0,0,0,55,56,5,
  	83,0,0,56,57,5,111,0,0,57,58,5,117,0,0,58,59,5,114,0,0,59,60,5,99,0,0,
  	60,61,5,101,0,0,61,62,5,80,0,0,62,63,5,97,0,0,63,64,5,116,0,0,64,65,5,
  	104,0,0,65,2,1,0,0,0,66,67,5,58,0,0,67,4,1,0,0,0,68,69,5,59,0,0,69,6,
  	1,0,0,0,70,71,5,80,0,0,71,72,5,114,0,0,72,73,5,111,0,0,73,74,5,112,0,
  	0,74,75,5,101,0,0,75,76,5,114,0,0,76,77,5,116,0,0,77,78,5,105,0,0,78,
  	79,5,101,0,0,79,80,5,115,0,0,80,8,1,0,0,0,81,82,5,123,0,0,82,10,1,0,0,
  	0,83,84,5,125,0,0,84,12,1,0,0,0,85,86,5,40,0,0,86,14,1,0,0,0,87,88,5,
  	44,0,0,88,16,1,0,0,0,89,90,5,41,0,0,90,18,1,0,0,0,91,92,5,98,0,0,92,93,
  	5,111,0,0,93,94,5,111,0,0,94,95,5,108,0,0,95,20,1,0,0,0,96,97,5,66,0,
  	0,97,98,5,111,0,0,98,99,5,111,0,0,99,100,5,108,0,0,100,22,1,0,0,0,101,
  	102,5,61,0,0,102,24,1,0,0,0,103,104,5,73,0,0,104,105,5,110,0,0,105,106,
  	5,116,0,0,106,26,1,0,0,0,107,108,5,105,0,0,108,109,5,110,0,0,109,110,
  	5,116,0,0,110,28,1,0,0,0,111,112,5,70,0,0,112,113,5,108,0,0,113,114,5,
  	111,0,0,114,115,5,97,0,0,115,116,5,116,0,0,116,30,1,0,0,0,117,118,5,102,
  	0,0,118,119,5,108,0,0,119,120,5,111,0,0,120,121,5,97,0,0,121,122,5,116,
  	0,0,122,123,5,32,0,0,123,32,1,0,0,0,124,127,3,45,22,0,125,127,3,47,23,
  	0,126,124,1,0,0,0,126,125,1,0,0,0,127,34,1,0,0,0,128,132,7,0,0,0,129,
  	131,7,1,0,0,130,129,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,133,1,
  	0,0,0,133,36,1,0,0,0,134,132,1,0,0,0,135,137,7,1,0,0,136,135,1,0,0,0,
  	137,138,1,0,0,0,138,136,1,0,0,0,138,139,1,0,0,0,139,140,1,0,0,0,140,144,
  	9,0,0,0,141,143,7,1,0,0,142,141,1,0,0,0,143,146,1,0,0,0,144,142,1,0,0,
  	0,144,145,1,0,0,0,145,148,1,0,0,0,146,144,1,0,0,0,147,149,5,102,0,0,148,
  	147,1,0,0,0,148,149,1,0,0,0,149,38,1,0,0,0,150,154,5,34,0,0,151,153,9,
  	0,0,0,152,151,1,0,0,0,153,156,1,0,0,0,154,155,1,0,0,0,154,152,1,0,0,0,
  	155,157,1,0,0,0,156,154,1,0,0,0,157,158,5,34,0,0,158,40,1,0,0,0,159,163,
  	7,2,0,0,160,162,7,3,0,0,161,160,1,0,0,0,162,165,1,0,0,0,163,161,1,0,0,
  	0,163,164,1,0,0,0,164,42,1,0,0,0,165,163,1,0,0,0,166,167,5,73,0,0,167,
  	168,5,100,0,0,168,169,5,101,0,0,169,170,5,110,0,0,170,171,5,116,0,0,171,
  	172,5,105,0,0,172,173,5,116,0,0,173,174,5,121,0,0,174,44,1,0,0,0,175,
  	176,5,116,0,0,176,177,5,114,0,0,177,178,5,117,0,0,178,179,5,101,0,0,179,
  	46,1,0,0,0,180,181,5,102,0,0,181,182,5,97,0,0,182,183,5,108,0,0,183,184,
  	5,115,0,0,184,185,5,101,0,0,185,48,1,0,0,0,186,188,7,4,0,0,187,186,1,
  	0,0,0,188,189,1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,191,1,0,0,0,
  	191,192,6,24,0,0,192,50,1,0,0,0,193,194,5,47,0,0,194,195,5,47,0,0,195,
  	199,1,0,0,0,196,198,9,0,0,0,197,196,1,0,0,0,198,201,1,0,0,0,199,200,1,
  	0,0,0,199,197,1,0,0,0,200,203,1,0,0,0,201,199,1,0,0,0,202,204,5,13,0,
  	0,203,202,1,0,0,0,203,204,1,0,0,0,204,205,1,0,0,0,205,206,5,10,0,0,206,
  	207,1,0,0,0,207,208,6,25,0,0,208,52,1,0,0,0,209,210,5,47,0,0,210,211,
  	5,42,0,0,211,215,1,0,0,0,212,214,9,0,0,0,213,212,1,0,0,0,214,217,1,0,
  	0,0,215,216,1,0,0,0,215,213,1,0,0,0,216,218,1,0,0,0,217,215,1,0,0,0,218,
  	219,5,42,0,0,219,220,5,47,0,0,220,221,1,0,0,0,221,222,6,26,0,0,222,54,
  	1,0,0,0,12,0,126,132,138,144,148,154,163,189,199,203,215,1,6,0,0
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