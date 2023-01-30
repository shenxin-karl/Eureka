
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
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "BoolVal", "IntVal", "FloatVal", "String", "Identity", 
      "KWIdentity", "KWTrue", "KWFalse", "KWWhite", "KWBlack", "KWBump", 
      "WhiteSpace", "LineComment", "Comment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,41,362,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,1,0,1,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,
  	1,11,1,11,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,24,
  	1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,27,1,27,3,27,226,8,27,1,28,3,28,229,8,28,1,28,1,28,5,28,233,
  	8,28,10,28,12,28,236,9,28,1,29,3,29,239,8,29,1,29,4,29,242,8,29,11,29,
  	12,29,243,1,29,1,29,5,29,248,8,29,10,29,12,29,251,9,29,1,29,3,29,254,
  	8,29,1,30,1,30,5,30,258,8,30,10,30,12,30,261,9,30,1,30,1,30,1,31,1,31,
  	5,31,267,8,31,10,31,12,31,270,9,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,1,35,
  	1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,302,8,35,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,314,8,36,1,37,1,37,1,37,
  	1,37,1,37,1,37,1,37,1,37,3,37,324,8,37,1,38,4,38,327,8,38,11,38,12,38,
  	328,1,38,1,38,1,39,1,39,1,39,1,39,5,39,337,8,39,10,39,12,39,340,9,39,
  	1,39,3,39,343,8,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,5,40,353,8,
  	40,10,40,12,40,356,9,40,1,40,1,40,1,40,1,40,1,40,4,249,259,338,354,0,
  	41,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,
  	14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,
  	51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,
  	37,75,38,77,39,79,40,81,41,1,0,7,2,0,43,43,45,45,1,0,49,57,1,0,48,57,
  	2,0,70,70,102,102,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,
  	3,0,9,10,13,13,32,32,377,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,
  	0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,
  	0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,1,
  	83,1,0,0,0,3,94,1,0,0,0,5,96,1,0,0,0,7,107,1,0,0,0,9,109,1,0,0,0,11,111,
  	1,0,0,0,13,117,1,0,0,0,15,123,1,0,0,0,17,125,1,0,0,0,19,127,1,0,0,0,21,
  	129,1,0,0,0,23,134,1,0,0,0,25,139,1,0,0,0,27,141,1,0,0,0,29,145,1,0,0,
  	0,31,149,1,0,0,0,33,155,1,0,0,0,35,161,1,0,0,0,37,168,1,0,0,0,39,175,
  	1,0,0,0,41,182,1,0,0,0,43,189,1,0,0,0,45,196,1,0,0,0,47,203,1,0,0,0,49,
  	206,1,0,0,0,51,209,1,0,0,0,53,216,1,0,0,0,55,225,1,0,0,0,57,228,1,0,0,
  	0,59,238,1,0,0,0,61,255,1,0,0,0,63,264,1,0,0,0,65,271,1,0,0,0,67,280,
  	1,0,0,0,69,285,1,0,0,0,71,301,1,0,0,0,73,313,1,0,0,0,75,323,1,0,0,0,77,
  	326,1,0,0,0,79,332,1,0,0,0,81,348,1,0,0,0,83,84,5,83,0,0,84,85,5,111,
  	0,0,85,86,5,117,0,0,86,87,5,114,0,0,87,88,5,99,0,0,88,89,5,101,0,0,89,
  	90,5,80,0,0,90,91,5,97,0,0,91,92,5,116,0,0,92,93,5,104,0,0,93,2,1,0,0,
  	0,94,95,5,58,0,0,95,4,1,0,0,0,96,97,5,80,0,0,97,98,5,114,0,0,98,99,5,
  	111,0,0,99,100,5,112,0,0,100,101,5,101,0,0,101,102,5,114,0,0,102,103,
  	5,116,0,0,103,104,5,105,0,0,104,105,5,101,0,0,105,106,5,115,0,0,106,6,
  	1,0,0,0,107,108,5,123,0,0,108,8,1,0,0,0,109,110,5,125,0,0,110,10,1,0,
  	0,0,111,112,5,114,0,0,112,113,5,97,0,0,113,114,5,110,0,0,114,115,5,103,
  	0,0,115,116,5,101,0,0,116,12,1,0,0,0,117,118,5,82,0,0,118,119,5,97,0,
  	0,119,120,5,110,0,0,120,121,5,103,0,0,121,122,5,101,0,0,122,14,1,0,0,
  	0,123,124,5,40,0,0,124,16,1,0,0,0,125,126,5,44,0,0,126,18,1,0,0,0,127,
  	128,5,41,0,0,128,20,1,0,0,0,129,130,5,98,0,0,130,131,5,111,0,0,131,132,
  	5,111,0,0,132,133,5,108,0,0,133,22,1,0,0,0,134,135,5,66,0,0,135,136,5,
  	111,0,0,136,137,5,111,0,0,137,138,5,108,0,0,138,24,1,0,0,0,139,140,5,
  	61,0,0,140,26,1,0,0,0,141,142,5,105,0,0,142,143,5,110,0,0,143,144,5,116,
  	0,0,144,28,1,0,0,0,145,146,5,73,0,0,146,147,5,110,0,0,147,148,5,116,0,
  	0,148,30,1,0,0,0,149,150,5,102,0,0,150,151,5,108,0,0,151,152,5,111,0,
  	0,152,153,5,97,0,0,153,154,5,116,0,0,154,32,1,0,0,0,155,156,5,70,0,0,
  	156,157,5,108,0,0,157,158,5,111,0,0,158,159,5,97,0,0,159,160,5,116,0,
  	0,160,34,1,0,0,0,161,162,5,102,0,0,162,163,5,108,0,0,163,164,5,111,0,
  	0,164,165,5,97,0,0,165,166,5,116,0,0,166,167,5,50,0,0,167,36,1,0,0,0,
  	168,169,5,70,0,0,169,170,5,108,0,0,170,171,5,111,0,0,171,172,5,97,0,0,
  	172,173,5,116,0,0,173,174,5,50,0,0,174,38,1,0,0,0,175,176,5,102,0,0,176,
  	177,5,108,0,0,177,178,5,111,0,0,178,179,5,97,0,0,179,180,5,116,0,0,180,
  	181,5,51,0,0,181,40,1,0,0,0,182,183,5,70,0,0,183,184,5,108,0,0,184,185,
  	5,111,0,0,185,186,5,97,0,0,186,187,5,116,0,0,187,188,5,51,0,0,188,42,
  	1,0,0,0,189,190,5,102,0,0,190,191,5,108,0,0,191,192,5,111,0,0,192,193,
  	5,97,0,0,193,194,5,116,0,0,194,195,5,52,0,0,195,44,1,0,0,0,196,197,5,
  	70,0,0,197,198,5,108,0,0,198,199,5,111,0,0,199,200,5,97,0,0,200,201,5,
  	116,0,0,201,202,5,52,0,0,202,46,1,0,0,0,203,204,5,50,0,0,204,205,5,100,
  	0,0,205,48,1,0,0,0,206,207,5,50,0,0,207,208,5,68,0,0,208,50,1,0,0,0,209,
  	210,5,109,0,0,210,211,5,97,0,0,211,212,5,116,0,0,212,213,5,114,0,0,213,
  	214,5,105,0,0,214,215,5,120,0,0,215,52,1,0,0,0,216,217,5,77,0,0,217,218,
  	5,97,0,0,218,219,5,116,0,0,219,220,5,114,0,0,220,221,5,105,0,0,221,222,
  	5,120,0,0,222,54,1,0,0,0,223,226,3,67,33,0,224,226,3,69,34,0,225,223,
  	1,0,0,0,225,224,1,0,0,0,226,56,1,0,0,0,227,229,7,0,0,0,228,227,1,0,0,
  	0,228,229,1,0,0,0,229,230,1,0,0,0,230,234,7,1,0,0,231,233,7,2,0,0,232,
  	231,1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,58,1,
  	0,0,0,236,234,1,0,0,0,237,239,7,0,0,0,238,237,1,0,0,0,238,239,1,0,0,0,
  	239,241,1,0,0,0,240,242,7,2,0,0,241,240,1,0,0,0,242,243,1,0,0,0,243,241,
  	1,0,0,0,243,244,1,0,0,0,244,245,1,0,0,0,245,249,5,46,0,0,246,248,7,2,
  	0,0,247,246,1,0,0,0,248,251,1,0,0,0,249,250,1,0,0,0,249,247,1,0,0,0,250,
  	253,1,0,0,0,251,249,1,0,0,0,252,254,7,3,0,0,253,252,1,0,0,0,253,254,1,
  	0,0,0,254,60,1,0,0,0,255,259,5,34,0,0,256,258,9,0,0,0,257,256,1,0,0,0,
  	258,261,1,0,0,0,259,260,1,0,0,0,259,257,1,0,0,0,260,262,1,0,0,0,261,259,
  	1,0,0,0,262,263,5,34,0,0,263,62,1,0,0,0,264,268,7,4,0,0,265,267,7,5,0,
  	0,266,265,1,0,0,0,267,270,1,0,0,0,268,266,1,0,0,0,268,269,1,0,0,0,269,
  	64,1,0,0,0,270,268,1,0,0,0,271,272,5,105,0,0,272,273,5,100,0,0,273,274,
  	5,101,0,0,274,275,5,110,0,0,275,276,5,116,0,0,276,277,5,105,0,0,277,278,
  	5,116,0,0,278,279,5,121,0,0,279,66,1,0,0,0,280,281,5,116,0,0,281,282,
  	5,114,0,0,282,283,5,117,0,0,283,284,5,101,0,0,284,68,1,0,0,0,285,286,
  	5,102,0,0,286,287,5,97,0,0,287,288,5,108,0,0,288,289,5,115,0,0,289,290,
  	5,101,0,0,290,70,1,0,0,0,291,292,5,119,0,0,292,293,5,104,0,0,293,294,
  	5,105,0,0,294,295,5,116,0,0,295,302,5,101,0,0,296,297,5,87,0,0,297,298,
  	5,104,0,0,298,299,5,105,0,0,299,300,5,116,0,0,300,302,5,101,0,0,301,291,
  	1,0,0,0,301,296,1,0,0,0,302,72,1,0,0,0,303,304,5,98,0,0,304,305,5,108,
  	0,0,305,306,5,97,0,0,306,307,5,99,0,0,307,314,5,107,0,0,308,309,5,66,
  	0,0,309,310,5,108,0,0,310,311,5,97,0,0,311,312,5,99,0,0,312,314,5,107,
  	0,0,313,303,1,0,0,0,313,308,1,0,0,0,314,74,1,0,0,0,315,316,5,98,0,0,316,
  	317,5,117,0,0,317,318,5,109,0,0,318,324,5,112,0,0,319,320,5,66,0,0,320,
  	321,5,117,0,0,321,322,5,109,0,0,322,324,5,112,0,0,323,315,1,0,0,0,323,
  	319,1,0,0,0,324,76,1,0,0,0,325,327,7,6,0,0,326,325,1,0,0,0,327,328,1,
  	0,0,0,328,326,1,0,0,0,328,329,1,0,0,0,329,330,1,0,0,0,330,331,6,38,0,
  	0,331,78,1,0,0,0,332,333,5,47,0,0,333,334,5,47,0,0,334,338,1,0,0,0,335,
  	337,9,0,0,0,336,335,1,0,0,0,337,340,1,0,0,0,338,339,1,0,0,0,338,336,1,
  	0,0,0,339,342,1,0,0,0,340,338,1,0,0,0,341,343,5,13,0,0,342,341,1,0,0,
  	0,342,343,1,0,0,0,343,344,1,0,0,0,344,345,5,10,0,0,345,346,1,0,0,0,346,
  	347,6,39,0,0,347,80,1,0,0,0,348,349,5,47,0,0,349,350,5,42,0,0,350,354,
  	1,0,0,0,351,353,9,0,0,0,352,351,1,0,0,0,353,356,1,0,0,0,354,355,1,0,0,
  	0,354,352,1,0,0,0,355,357,1,0,0,0,356,354,1,0,0,0,357,358,5,42,0,0,358,
  	359,5,47,0,0,359,360,1,0,0,0,360,361,6,40,0,0,361,82,1,0,0,0,17,0,225,
  	228,234,238,243,249,253,259,268,301,313,323,328,338,342,354,1,6,0,0
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
