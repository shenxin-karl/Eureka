
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
      "T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "T__32", 
      "T__33", "T__34", "T__35", "T__36", "T__37", "T__38", "T__39", "T__40", 
      "T__41", "T__42", "T__43", "T__44", "T__45", "T__46", "T__47", "T__48", 
      "T__49", "T__50", "T__51", "T__52", "T__53", "T__54", "T__55", "T__56", 
      "T__57", "T__58", "T__59", "T__60", "T__61", "T__62", "T__63", "T__64", 
      "T__65", "T__66", "WhiteSpace", "LineComment", "BlockComment", "BooleanLiteral", 
      "OnOffLabel", "CullModeLabel", "RenderQueueLabel", "ZTestModeLabel", 
      "BlendFactorLabel", "BlendOPLabel", "StencilCompareLabel", "StencilOpLabel", 
      "IntLiteral", "FloatLiteral", "ColorMaskChannel", "KWOff", "KWOn", 
      "KWNever", "KWLess", "KWEqual", "KWLEqaul", "KWGreater", "KWNotEqual", 
      "KWGEqual", "KWAlways", "KWKeep", "KWZero", "KWReplace", "KWIncrSat", 
      "KWDecrSat", "KWInvert", "KWIncrWrap", "KWDecrWrap", "KWTrue", "KWFalse", 
      "StringLiteral", "Identity"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'SourcePath'", "':'", "'Properties'", "'{'", "'}'", "'('", "','", 
      "')'", "'='", "'bool'", "'Bool'", "'int'", "'Int'", "'range'", "'Range'", 
      "'float'", "'Float'", "'float2'", "'Float2'", "'float3'", "'Float3'", 
      "'float4'", "'Float4'", "'2d'", "'2D'", "'matrix'", "'Matrix'", "'identity'", 
      "'white'", "'White'", "'black'", "'Black'", "'bump'", "'Bump'", "'Pass'", 
      "'VertexShader'", "'GeometryShader'", "'HullShader'", "'DomainShader'", 
      "'PixelShader'", "'RenderQueue'", "'ShaderFeature'", "'Cull'", "'ZClip'", 
      "'ZTest'", "'ZWrite'", "'Offset'", "'ColorMask'", "'Blend'", "'BlendOp'", 
      "'AlphaToMask'", "'Conservative'", "'Stencil'", "'Ref'", "'ReadMask'", 
      "'WriteMask'", "'Comp'", "'Fail'", "'ZFail'", "'CompBack'", "'PassBack'", 
      "'FailBack'", "'ZFailBack'", "'CompFront'", "'PassFront'", "'FailFront'", 
      "'ZFailFront'", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "'Off'", "'On'", "'Never'", "'Less'", "'Equal'", "'LEqual'", 
      "'Greater'", "'NotEqual'", "'GEqual'", "'Always'", "'Keep'", "'Zero'", 
      "'Replace'", "'IncrSat'", "'DecrSat'", "'Invert'", "'IncrWrap'", "'DecrWrap'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "WhiteSpace", "LineComment", "BlockComment", "BooleanLiteral", "OnOffLabel", 
      "CullModeLabel", "RenderQueueLabel", "ZTestModeLabel", "BlendFactorLabel", 
      "BlendOPLabel", "StencilCompareLabel", "StencilOpLabel", "IntLiteral", 
      "FloatLiteral", "ColorMaskChannel", "KWOff", "KWOn", "KWNever", "KWLess", 
      "KWEqual", "KWLEqaul", "KWGreater", "KWNotEqual", "KWGEqual", "KWAlways", 
      "KWKeep", "KWZero", "KWReplace", "KWIncrSat", "KWDecrSat", "KWInvert", 
      "KWIncrWrap", "KWDecrWrap", "KWTrue", "KWFalse", "StringLiteral", 
      "Identity"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,104,1164,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,
  	7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,
  	14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,
  	21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,
  	28,7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,
  	35,7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,
  	42,7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,
  	49,7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,
  	56,7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,
  	63,7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,
  	70,7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,
  	77,7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,
  	84,7,84,2,85,7,85,2,86,7,86,2,87,7,87,2,88,7,88,2,89,7,89,2,90,7,90,2,
  	91,7,91,2,92,7,92,2,93,7,93,2,94,7,94,2,95,7,95,2,96,7,96,2,97,7,97,2,
  	98,7,98,2,99,7,99,2,100,7,100,2,101,7,101,2,102,7,102,2,103,7,103,1,0,
  	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,
  	1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,12,
  	1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,
  	1,23,1,23,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,
  	1,32,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,
  	1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,37,1,37,1,37,
  	1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,38,
  	1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,39,1,39,1,39,1,39,1,39,1,39,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	1,40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,
  	1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,43,1,43,1,43,1,43,1,43,1,43,
  	1,44,1,44,1,44,1,44,1,44,1,44,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,46,
  	1,46,1,46,1,46,1,46,1,46,1,46,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,
  	1,47,1,47,1,48,1,48,1,48,1,48,1,48,1,48,1,49,1,49,1,49,1,49,1,49,1,49,
  	1,49,1,49,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,52,
  	1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,53,1,53,1,53,1,53,1,54,1,54,1,54,
  	1,54,1,54,1,54,1,54,1,54,1,54,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,
  	1,55,1,55,1,56,1,56,1,56,1,56,1,56,1,57,1,57,1,57,1,57,1,57,1,58,1,58,
  	1,58,1,58,1,58,1,58,1,59,1,59,1,59,1,59,1,59,1,59,1,59,1,59,1,59,1,60,
  	1,60,1,60,1,60,1,60,1,60,1,60,1,60,1,60,1,61,1,61,1,61,1,61,1,61,1,61,
  	1,61,1,61,1,61,1,62,1,62,1,62,1,62,1,62,1,62,1,62,1,62,1,62,1,62,1,63,
  	1,63,1,63,1,63,1,63,1,63,1,63,1,63,1,63,1,63,1,64,1,64,1,64,1,64,1,64,
  	1,64,1,64,1,64,1,64,1,64,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,
  	1,65,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,67,4,67,
  	694,8,67,11,67,12,67,695,1,67,1,67,1,68,1,68,1,68,1,68,5,68,704,8,68,
  	10,68,12,68,707,9,68,1,68,3,68,710,8,68,1,68,1,68,1,68,1,68,1,69,1,69,
  	1,69,1,69,5,69,720,8,69,10,69,12,69,723,9,69,1,69,1,69,1,69,1,69,1,69,
  	1,70,1,70,3,70,732,8,70,1,71,1,71,3,71,736,8,71,1,72,1,72,1,72,1,72,1,
  	72,1,72,1,72,1,72,1,72,1,72,3,72,748,8,72,1,73,1,73,1,73,1,73,1,73,1,
  	73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,
  	73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,
  	73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,
  	73,1,73,1,73,1,73,3,73,801,8,73,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,
  	74,3,74,811,8,74,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,75,1,
  	75,1,75,1,75,3,75,910,8,75,1,76,1,76,1,76,1,76,1,76,1,76,1,76,1,76,1,
  	76,1,76,1,76,1,76,1,76,1,76,1,76,1,76,1,76,1,76,3,76,930,8,76,1,77,1,
  	77,1,77,1,77,1,77,1,77,1,77,1,77,3,77,940,8,77,1,78,1,78,1,78,1,78,1,
  	78,1,78,1,78,1,78,3,78,950,8,78,1,79,3,79,953,8,79,1,79,1,79,5,79,957,
  	8,79,10,79,12,79,960,9,79,1,79,3,79,963,8,79,1,80,3,80,966,8,80,1,80,
  	4,80,969,8,80,11,80,12,80,970,1,80,1,80,5,80,975,8,80,10,80,12,80,978,
  	9,80,1,80,3,80,981,8,80,1,80,1,80,4,80,985,8,80,11,80,12,80,986,1,80,
  	3,80,990,8,80,3,80,992,8,80,1,81,1,81,1,81,1,81,1,81,1,81,1,81,1,81,1,
  	81,1,81,3,81,1004,8,81,1,82,1,82,1,82,1,82,1,83,1,83,1,83,1,84,1,84,1,
  	84,1,84,1,84,1,84,1,85,1,85,1,85,1,85,1,85,1,86,1,86,1,86,1,86,1,86,1,
  	86,1,87,1,87,1,87,1,87,1,87,1,87,1,87,1,88,1,88,1,88,1,88,1,88,1,88,1,
  	88,1,88,1,89,1,89,1,89,1,89,1,89,1,89,1,89,1,89,1,89,1,90,1,90,1,90,1,
  	90,1,90,1,90,1,90,1,91,1,91,1,91,1,91,1,91,1,91,1,91,1,92,1,92,1,92,1,
  	92,1,92,1,93,1,93,1,93,1,93,1,93,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,
  	94,1,95,1,95,1,95,1,95,1,95,1,95,1,95,1,95,1,96,1,96,1,96,1,96,1,96,1,
  	96,1,96,1,96,1,97,1,97,1,97,1,97,1,97,1,97,1,97,1,98,1,98,1,98,1,98,1,
  	98,1,98,1,98,1,98,1,98,1,99,1,99,1,99,1,99,1,99,1,99,1,99,1,99,1,99,1,
  	100,1,100,1,100,1,100,1,100,1,100,1,100,1,100,3,100,1135,8,100,1,101,
  	1,101,1,101,1,101,1,101,1,101,1,101,1,101,1,101,1,101,3,101,1147,8,101,
  	1,102,1,102,5,102,1151,8,102,10,102,12,102,1154,9,102,1,102,1,102,1,103,
  	1,103,5,103,1160,8,103,10,103,12,103,1163,9,103,3,705,721,1152,0,104,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,
  	29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,
  	26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,
  	75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,
  	49,99,50,101,51,103,52,105,53,107,54,109,55,111,56,113,57,115,58,117,
  	59,119,60,121,61,123,62,125,63,127,64,129,65,131,66,133,67,135,68,137,
  	69,139,70,141,71,143,72,145,73,147,74,149,75,151,76,153,77,155,78,157,
  	79,159,80,161,81,163,82,165,83,167,84,169,85,171,86,173,87,175,88,177,
  	89,179,90,181,91,183,92,185,93,187,94,189,95,191,96,193,97,195,98,197,
  	99,199,100,201,101,203,102,205,103,207,104,1,0,8,3,0,9,10,13,13,32,32,
  	2,0,43,43,45,45,1,0,49,57,1,0,48,57,2,0,70,70,102,102,3,0,65,66,71,71,
  	82,82,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1226,0,1,1,
  	0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,
  	13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,
  	0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,
  	0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,
  	45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,
  	0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,
  	0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,
  	77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,
  	0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,0,0,
  	0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,0,0,105,1,0,0,0,0,107,1,0,0,
  	0,0,109,1,0,0,0,0,111,1,0,0,0,0,113,1,0,0,0,0,115,1,0,0,0,0,117,1,0,0,
  	0,0,119,1,0,0,0,0,121,1,0,0,0,0,123,1,0,0,0,0,125,1,0,0,0,0,127,1,0,0,
  	0,0,129,1,0,0,0,0,131,1,0,0,0,0,133,1,0,0,0,0,135,1,0,0,0,0,137,1,0,0,
  	0,0,139,1,0,0,0,0,141,1,0,0,0,0,143,1,0,0,0,0,145,1,0,0,0,0,147,1,0,0,
  	0,0,149,1,0,0,0,0,151,1,0,0,0,0,153,1,0,0,0,0,155,1,0,0,0,0,157,1,0,0,
  	0,0,159,1,0,0,0,0,161,1,0,0,0,0,163,1,0,0,0,0,165,1,0,0,0,0,167,1,0,0,
  	0,0,169,1,0,0,0,0,171,1,0,0,0,0,173,1,0,0,0,0,175,1,0,0,0,0,177,1,0,0,
  	0,0,179,1,0,0,0,0,181,1,0,0,0,0,183,1,0,0,0,0,185,1,0,0,0,0,187,1,0,0,
  	0,0,189,1,0,0,0,0,191,1,0,0,0,0,193,1,0,0,0,0,195,1,0,0,0,0,197,1,0,0,
  	0,0,199,1,0,0,0,0,201,1,0,0,0,0,203,1,0,0,0,0,205,1,0,0,0,0,207,1,0,0,
  	0,1,209,1,0,0,0,3,220,1,0,0,0,5,222,1,0,0,0,7,233,1,0,0,0,9,235,1,0,0,
  	0,11,237,1,0,0,0,13,239,1,0,0,0,15,241,1,0,0,0,17,243,1,0,0,0,19,245,
  	1,0,0,0,21,250,1,0,0,0,23,255,1,0,0,0,25,259,1,0,0,0,27,263,1,0,0,0,29,
  	269,1,0,0,0,31,275,1,0,0,0,33,281,1,0,0,0,35,287,1,0,0,0,37,294,1,0,0,
  	0,39,301,1,0,0,0,41,308,1,0,0,0,43,315,1,0,0,0,45,322,1,0,0,0,47,329,
  	1,0,0,0,49,332,1,0,0,0,51,335,1,0,0,0,53,342,1,0,0,0,55,349,1,0,0,0,57,
  	358,1,0,0,0,59,364,1,0,0,0,61,370,1,0,0,0,63,376,1,0,0,0,65,382,1,0,0,
  	0,67,387,1,0,0,0,69,392,1,0,0,0,71,397,1,0,0,0,73,410,1,0,0,0,75,425,
  	1,0,0,0,77,436,1,0,0,0,79,449,1,0,0,0,81,461,1,0,0,0,83,473,1,0,0,0,85,
  	487,1,0,0,0,87,492,1,0,0,0,89,498,1,0,0,0,91,504,1,0,0,0,93,511,1,0,0,
  	0,95,518,1,0,0,0,97,528,1,0,0,0,99,534,1,0,0,0,101,542,1,0,0,0,103,554,
  	1,0,0,0,105,567,1,0,0,0,107,575,1,0,0,0,109,579,1,0,0,0,111,588,1,0,0,
  	0,113,598,1,0,0,0,115,603,1,0,0,0,117,608,1,0,0,0,119,614,1,0,0,0,121,
  	623,1,0,0,0,123,632,1,0,0,0,125,641,1,0,0,0,127,651,1,0,0,0,129,661,1,
  	0,0,0,131,671,1,0,0,0,133,681,1,0,0,0,135,693,1,0,0,0,137,699,1,0,0,0,
  	139,715,1,0,0,0,141,731,1,0,0,0,143,735,1,0,0,0,145,747,1,0,0,0,147,800,
  	1,0,0,0,149,810,1,0,0,0,151,909,1,0,0,0,153,929,1,0,0,0,155,939,1,0,0,
  	0,157,949,1,0,0,0,159,962,1,0,0,0,161,991,1,0,0,0,163,1003,1,0,0,0,165,
  	1005,1,0,0,0,167,1009,1,0,0,0,169,1012,1,0,0,0,171,1018,1,0,0,0,173,1023,
  	1,0,0,0,175,1029,1,0,0,0,177,1036,1,0,0,0,179,1044,1,0,0,0,181,1053,1,
  	0,0,0,183,1060,1,0,0,0,185,1067,1,0,0,0,187,1072,1,0,0,0,189,1077,1,0,
  	0,0,191,1085,1,0,0,0,193,1093,1,0,0,0,195,1101,1,0,0,0,197,1108,1,0,0,
  	0,199,1117,1,0,0,0,201,1134,1,0,0,0,203,1146,1,0,0,0,205,1148,1,0,0,0,
  	207,1157,1,0,0,0,209,210,5,83,0,0,210,211,5,111,0,0,211,212,5,117,0,0,
  	212,213,5,114,0,0,213,214,5,99,0,0,214,215,5,101,0,0,215,216,5,80,0,0,
  	216,217,5,97,0,0,217,218,5,116,0,0,218,219,5,104,0,0,219,2,1,0,0,0,220,
  	221,5,58,0,0,221,4,1,0,0,0,222,223,5,80,0,0,223,224,5,114,0,0,224,225,
  	5,111,0,0,225,226,5,112,0,0,226,227,5,101,0,0,227,228,5,114,0,0,228,229,
  	5,116,0,0,229,230,5,105,0,0,230,231,5,101,0,0,231,232,5,115,0,0,232,6,
  	1,0,0,0,233,234,5,123,0,0,234,8,1,0,0,0,235,236,5,125,0,0,236,10,1,0,
  	0,0,237,238,5,40,0,0,238,12,1,0,0,0,239,240,5,44,0,0,240,14,1,0,0,0,241,
  	242,5,41,0,0,242,16,1,0,0,0,243,244,5,61,0,0,244,18,1,0,0,0,245,246,5,
  	98,0,0,246,247,5,111,0,0,247,248,5,111,0,0,248,249,5,108,0,0,249,20,1,
  	0,0,0,250,251,5,66,0,0,251,252,5,111,0,0,252,253,5,111,0,0,253,254,5,
  	108,0,0,254,22,1,0,0,0,255,256,5,105,0,0,256,257,5,110,0,0,257,258,5,
  	116,0,0,258,24,1,0,0,0,259,260,5,73,0,0,260,261,5,110,0,0,261,262,5,116,
  	0,0,262,26,1,0,0,0,263,264,5,114,0,0,264,265,5,97,0,0,265,266,5,110,0,
  	0,266,267,5,103,0,0,267,268,5,101,0,0,268,28,1,0,0,0,269,270,5,82,0,0,
  	270,271,5,97,0,0,271,272,5,110,0,0,272,273,5,103,0,0,273,274,5,101,0,
  	0,274,30,1,0,0,0,275,276,5,102,0,0,276,277,5,108,0,0,277,278,5,111,0,
  	0,278,279,5,97,0,0,279,280,5,116,0,0,280,32,1,0,0,0,281,282,5,70,0,0,
  	282,283,5,108,0,0,283,284,5,111,0,0,284,285,5,97,0,0,285,286,5,116,0,
  	0,286,34,1,0,0,0,287,288,5,102,0,0,288,289,5,108,0,0,289,290,5,111,0,
  	0,290,291,5,97,0,0,291,292,5,116,0,0,292,293,5,50,0,0,293,36,1,0,0,0,
  	294,295,5,70,0,0,295,296,5,108,0,0,296,297,5,111,0,0,297,298,5,97,0,0,
  	298,299,5,116,0,0,299,300,5,50,0,0,300,38,1,0,0,0,301,302,5,102,0,0,302,
  	303,5,108,0,0,303,304,5,111,0,0,304,305,5,97,0,0,305,306,5,116,0,0,306,
  	307,5,51,0,0,307,40,1,0,0,0,308,309,5,70,0,0,309,310,5,108,0,0,310,311,
  	5,111,0,0,311,312,5,97,0,0,312,313,5,116,0,0,313,314,5,51,0,0,314,42,
  	1,0,0,0,315,316,5,102,0,0,316,317,5,108,0,0,317,318,5,111,0,0,318,319,
  	5,97,0,0,319,320,5,116,0,0,320,321,5,52,0,0,321,44,1,0,0,0,322,323,5,
  	70,0,0,323,324,5,108,0,0,324,325,5,111,0,0,325,326,5,97,0,0,326,327,5,
  	116,0,0,327,328,5,52,0,0,328,46,1,0,0,0,329,330,5,50,0,0,330,331,5,100,
  	0,0,331,48,1,0,0,0,332,333,5,50,0,0,333,334,5,68,0,0,334,50,1,0,0,0,335,
  	336,5,109,0,0,336,337,5,97,0,0,337,338,5,116,0,0,338,339,5,114,0,0,339,
  	340,5,105,0,0,340,341,5,120,0,0,341,52,1,0,0,0,342,343,5,77,0,0,343,344,
  	5,97,0,0,344,345,5,116,0,0,345,346,5,114,0,0,346,347,5,105,0,0,347,348,
  	5,120,0,0,348,54,1,0,0,0,349,350,5,105,0,0,350,351,5,100,0,0,351,352,
  	5,101,0,0,352,353,5,110,0,0,353,354,5,116,0,0,354,355,5,105,0,0,355,356,
  	5,116,0,0,356,357,5,121,0,0,357,56,1,0,0,0,358,359,5,119,0,0,359,360,
  	5,104,0,0,360,361,5,105,0,0,361,362,5,116,0,0,362,363,5,101,0,0,363,58,
  	1,0,0,0,364,365,5,87,0,0,365,366,5,104,0,0,366,367,5,105,0,0,367,368,
  	5,116,0,0,368,369,5,101,0,0,369,60,1,0,0,0,370,371,5,98,0,0,371,372,5,
  	108,0,0,372,373,5,97,0,0,373,374,5,99,0,0,374,375,5,107,0,0,375,62,1,
  	0,0,0,376,377,5,66,0,0,377,378,5,108,0,0,378,379,5,97,0,0,379,380,5,99,
  	0,0,380,381,5,107,0,0,381,64,1,0,0,0,382,383,5,98,0,0,383,384,5,117,0,
  	0,384,385,5,109,0,0,385,386,5,112,0,0,386,66,1,0,0,0,387,388,5,66,0,0,
  	388,389,5,117,0,0,389,390,5,109,0,0,390,391,5,112,0,0,391,68,1,0,0,0,
  	392,393,5,80,0,0,393,394,5,97,0,0,394,395,5,115,0,0,395,396,5,115,0,0,
  	396,70,1,0,0,0,397,398,5,86,0,0,398,399,5,101,0,0,399,400,5,114,0,0,400,
  	401,5,116,0,0,401,402,5,101,0,0,402,403,5,120,0,0,403,404,5,83,0,0,404,
  	405,5,104,0,0,405,406,5,97,0,0,406,407,5,100,0,0,407,408,5,101,0,0,408,
  	409,5,114,0,0,409,72,1,0,0,0,410,411,5,71,0,0,411,412,5,101,0,0,412,413,
  	5,111,0,0,413,414,5,109,0,0,414,415,5,101,0,0,415,416,5,116,0,0,416,417,
  	5,114,0,0,417,418,5,121,0,0,418,419,5,83,0,0,419,420,5,104,0,0,420,421,
  	5,97,0,0,421,422,5,100,0,0,422,423,5,101,0,0,423,424,5,114,0,0,424,74,
  	1,0,0,0,425,426,5,72,0,0,426,427,5,117,0,0,427,428,5,108,0,0,428,429,
  	5,108,0,0,429,430,5,83,0,0,430,431,5,104,0,0,431,432,5,97,0,0,432,433,
  	5,100,0,0,433,434,5,101,0,0,434,435,5,114,0,0,435,76,1,0,0,0,436,437,
  	5,68,0,0,437,438,5,111,0,0,438,439,5,109,0,0,439,440,5,97,0,0,440,441,
  	5,105,0,0,441,442,5,110,0,0,442,443,5,83,0,0,443,444,5,104,0,0,444,445,
  	5,97,0,0,445,446,5,100,0,0,446,447,5,101,0,0,447,448,5,114,0,0,448,78,
  	1,0,0,0,449,450,5,80,0,0,450,451,5,105,0,0,451,452,5,120,0,0,452,453,
  	5,101,0,0,453,454,5,108,0,0,454,455,5,83,0,0,455,456,5,104,0,0,456,457,
  	5,97,0,0,457,458,5,100,0,0,458,459,5,101,0,0,459,460,5,114,0,0,460,80,
  	1,0,0,0,461,462,5,82,0,0,462,463,5,101,0,0,463,464,5,110,0,0,464,465,
  	5,100,0,0,465,466,5,101,0,0,466,467,5,114,0,0,467,468,5,81,0,0,468,469,
  	5,117,0,0,469,470,5,101,0,0,470,471,5,117,0,0,471,472,5,101,0,0,472,82,
  	1,0,0,0,473,474,5,83,0,0,474,475,5,104,0,0,475,476,5,97,0,0,476,477,5,
  	100,0,0,477,478,5,101,0,0,478,479,5,114,0,0,479,480,5,70,0,0,480,481,
  	5,101,0,0,481,482,5,97,0,0,482,483,5,116,0,0,483,484,5,117,0,0,484,485,
  	5,114,0,0,485,486,5,101,0,0,486,84,1,0,0,0,487,488,5,67,0,0,488,489,5,
  	117,0,0,489,490,5,108,0,0,490,491,5,108,0,0,491,86,1,0,0,0,492,493,5,
  	90,0,0,493,494,5,67,0,0,494,495,5,108,0,0,495,496,5,105,0,0,496,497,5,
  	112,0,0,497,88,1,0,0,0,498,499,5,90,0,0,499,500,5,84,0,0,500,501,5,101,
  	0,0,501,502,5,115,0,0,502,503,5,116,0,0,503,90,1,0,0,0,504,505,5,90,0,
  	0,505,506,5,87,0,0,506,507,5,114,0,0,507,508,5,105,0,0,508,509,5,116,
  	0,0,509,510,5,101,0,0,510,92,1,0,0,0,511,512,5,79,0,0,512,513,5,102,0,
  	0,513,514,5,102,0,0,514,515,5,115,0,0,515,516,5,101,0,0,516,517,5,116,
  	0,0,517,94,1,0,0,0,518,519,5,67,0,0,519,520,5,111,0,0,520,521,5,108,0,
  	0,521,522,5,111,0,0,522,523,5,114,0,0,523,524,5,77,0,0,524,525,5,97,0,
  	0,525,526,5,115,0,0,526,527,5,107,0,0,527,96,1,0,0,0,528,529,5,66,0,0,
  	529,530,5,108,0,0,530,531,5,101,0,0,531,532,5,110,0,0,532,533,5,100,0,
  	0,533,98,1,0,0,0,534,535,5,66,0,0,535,536,5,108,0,0,536,537,5,101,0,0,
  	537,538,5,110,0,0,538,539,5,100,0,0,539,540,5,79,0,0,540,541,5,112,0,
  	0,541,100,1,0,0,0,542,543,5,65,0,0,543,544,5,108,0,0,544,545,5,112,0,
  	0,545,546,5,104,0,0,546,547,5,97,0,0,547,548,5,84,0,0,548,549,5,111,0,
  	0,549,550,5,77,0,0,550,551,5,97,0,0,551,552,5,115,0,0,552,553,5,107,0,
  	0,553,102,1,0,0,0,554,555,5,67,0,0,555,556,5,111,0,0,556,557,5,110,0,
  	0,557,558,5,115,0,0,558,559,5,101,0,0,559,560,5,114,0,0,560,561,5,118,
  	0,0,561,562,5,97,0,0,562,563,5,116,0,0,563,564,5,105,0,0,564,565,5,118,
  	0,0,565,566,5,101,0,0,566,104,1,0,0,0,567,568,5,83,0,0,568,569,5,116,
  	0,0,569,570,5,101,0,0,570,571,5,110,0,0,571,572,5,99,0,0,572,573,5,105,
  	0,0,573,574,5,108,0,0,574,106,1,0,0,0,575,576,5,82,0,0,576,577,5,101,
  	0,0,577,578,5,102,0,0,578,108,1,0,0,0,579,580,5,82,0,0,580,581,5,101,
  	0,0,581,582,5,97,0,0,582,583,5,100,0,0,583,584,5,77,0,0,584,585,5,97,
  	0,0,585,586,5,115,0,0,586,587,5,107,0,0,587,110,1,0,0,0,588,589,5,87,
  	0,0,589,590,5,114,0,0,590,591,5,105,0,0,591,592,5,116,0,0,592,593,5,101,
  	0,0,593,594,5,77,0,0,594,595,5,97,0,0,595,596,5,115,0,0,596,597,5,107,
  	0,0,597,112,1,0,0,0,598,599,5,67,0,0,599,600,5,111,0,0,600,601,5,109,
  	0,0,601,602,5,112,0,0,602,114,1,0,0,0,603,604,5,70,0,0,604,605,5,97,0,
  	0,605,606,5,105,0,0,606,607,5,108,0,0,607,116,1,0,0,0,608,609,5,90,0,
  	0,609,610,5,70,0,0,610,611,5,97,0,0,611,612,5,105,0,0,612,613,5,108,0,
  	0,613,118,1,0,0,0,614,615,5,67,0,0,615,616,5,111,0,0,616,617,5,109,0,
  	0,617,618,5,112,0,0,618,619,5,66,0,0,619,620,5,97,0,0,620,621,5,99,0,
  	0,621,622,5,107,0,0,622,120,1,0,0,0,623,624,5,80,0,0,624,625,5,97,0,0,
  	625,626,5,115,0,0,626,627,5,115,0,0,627,628,5,66,0,0,628,629,5,97,0,0,
  	629,630,5,99,0,0,630,631,5,107,0,0,631,122,1,0,0,0,632,633,5,70,0,0,633,
  	634,5,97,0,0,634,635,5,105,0,0,635,636,5,108,0,0,636,637,5,66,0,0,637,
  	638,5,97,0,0,638,639,5,99,0,0,639,640,5,107,0,0,640,124,1,0,0,0,641,642,
  	5,90,0,0,642,643,5,70,0,0,643,644,5,97,0,0,644,645,5,105,0,0,645,646,
  	5,108,0,0,646,647,5,66,0,0,647,648,5,97,0,0,648,649,5,99,0,0,649,650,
  	5,107,0,0,650,126,1,0,0,0,651,652,5,67,0,0,652,653,5,111,0,0,653,654,
  	5,109,0,0,654,655,5,112,0,0,655,656,5,70,0,0,656,657,5,114,0,0,657,658,
  	5,111,0,0,658,659,5,110,0,0,659,660,5,116,0,0,660,128,1,0,0,0,661,662,
  	5,80,0,0,662,663,5,97,0,0,663,664,5,115,0,0,664,665,5,115,0,0,665,666,
  	5,70,0,0,666,667,5,114,0,0,667,668,5,111,0,0,668,669,5,110,0,0,669,670,
  	5,116,0,0,670,130,1,0,0,0,671,672,5,70,0,0,672,673,5,97,0,0,673,674,5,
  	105,0,0,674,675,5,108,0,0,675,676,5,70,0,0,676,677,5,114,0,0,677,678,
  	5,111,0,0,678,679,5,110,0,0,679,680,5,116,0,0,680,132,1,0,0,0,681,682,
  	5,90,0,0,682,683,5,70,0,0,683,684,5,97,0,0,684,685,5,105,0,0,685,686,
  	5,108,0,0,686,687,5,70,0,0,687,688,5,114,0,0,688,689,5,111,0,0,689,690,
  	5,110,0,0,690,691,5,116,0,0,691,134,1,0,0,0,692,694,7,0,0,0,693,692,1,
  	0,0,0,694,695,1,0,0,0,695,693,1,0,0,0,695,696,1,0,0,0,696,697,1,0,0,0,
  	697,698,6,67,0,0,698,136,1,0,0,0,699,700,5,47,0,0,700,701,5,47,0,0,701,
  	705,1,0,0,0,702,704,9,0,0,0,703,702,1,0,0,0,704,707,1,0,0,0,705,706,1,
  	0,0,0,705,703,1,0,0,0,706,709,1,0,0,0,707,705,1,0,0,0,708,710,5,13,0,
  	0,709,708,1,0,0,0,709,710,1,0,0,0,710,711,1,0,0,0,711,712,5,10,0,0,712,
  	713,1,0,0,0,713,714,6,68,0,0,714,138,1,0,0,0,715,716,5,47,0,0,716,717,
  	5,42,0,0,717,721,1,0,0,0,718,720,9,0,0,0,719,718,1,0,0,0,720,723,1,0,
  	0,0,721,722,1,0,0,0,721,719,1,0,0,0,722,724,1,0,0,0,723,721,1,0,0,0,724,
  	725,5,42,0,0,725,726,5,47,0,0,726,727,1,0,0,0,727,728,6,69,0,0,728,140,
  	1,0,0,0,729,732,3,201,100,0,730,732,3,203,101,0,731,729,1,0,0,0,731,730,
  	1,0,0,0,732,142,1,0,0,0,733,736,3,167,83,0,734,736,3,165,82,0,735,733,
  	1,0,0,0,735,734,1,0,0,0,736,144,1,0,0,0,737,748,3,165,82,0,738,739,5,
  	70,0,0,739,740,5,114,0,0,740,741,5,111,0,0,741,742,5,110,0,0,742,748,
  	5,116,0,0,743,744,5,66,0,0,744,745,5,97,0,0,745,746,5,99,0,0,746,748,
  	5,107,0,0,747,737,1,0,0,0,747,738,1,0,0,0,747,743,1,0,0,0,748,146,1,0,
  	0,0,749,750,5,66,0,0,750,751,5,97,0,0,751,752,5,99,0,0,752,753,5,107,
  	0,0,753,754,5,71,0,0,754,755,5,114,0,0,755,756,5,111,0,0,756,757,5,117,
  	0,0,757,758,5,110,0,0,758,801,5,100,0,0,759,760,5,71,0,0,760,761,5,101,
  	0,0,761,762,5,111,0,0,762,763,5,109,0,0,763,764,5,101,0,0,764,765,5,116,
  	0,0,765,766,5,114,0,0,766,801,5,121,0,0,767,768,5,79,0,0,768,769,5,112,
  	0,0,769,770,5,97,0,0,770,771,5,113,0,0,771,772,5,117,0,0,772,801,5,101,
  	0,0,773,774,5,65,0,0,774,775,5,108,0,0,775,776,5,112,0,0,776,777,5,104,
  	0,0,777,778,5,97,0,0,778,779,5,84,0,0,779,780,5,101,0,0,780,781,5,115,
  	0,0,781,801,5,116,0,0,782,783,5,84,0,0,783,784,5,114,0,0,784,785,5,97,
  	0,0,785,786,5,110,0,0,786,787,5,115,0,0,787,788,5,112,0,0,788,789,5,97,
  	0,0,789,790,5,114,0,0,790,791,5,101,0,0,791,792,5,110,0,0,792,801,5,116,
  	0,0,793,794,5,79,0,0,794,795,5,118,0,0,795,796,5,101,0,0,796,797,5,114,
  	0,0,797,798,5,108,0,0,798,799,5,97,0,0,799,801,5,121,0,0,800,749,1,0,
  	0,0,800,759,1,0,0,0,800,767,1,0,0,0,800,773,1,0,0,0,800,782,1,0,0,0,800,
  	793,1,0,0,0,801,148,1,0,0,0,802,811,3,169,84,0,803,811,3,171,85,0,804,
  	811,3,173,86,0,805,811,3,175,87,0,806,811,3,181,90,0,807,811,3,179,89,
  	0,808,811,3,177,88,0,809,811,3,183,91,0,810,802,1,0,0,0,810,803,1,0,0,
  	0,810,804,1,0,0,0,810,805,1,0,0,0,810,806,1,0,0,0,810,807,1,0,0,0,810,
  	808,1,0,0,0,810,809,1,0,0,0,811,150,1,0,0,0,812,910,3,187,93,0,813,814,
  	5,83,0,0,814,815,5,114,0,0,815,816,5,99,0,0,816,817,5,67,0,0,817,818,
  	5,111,0,0,818,819,5,108,0,0,819,820,5,111,0,0,820,910,5,114,0,0,821,822,
  	5,83,0,0,822,823,5,114,0,0,823,824,5,99,0,0,824,825,5,65,0,0,825,826,
  	5,108,0,0,826,827,5,112,0,0,827,828,5,104,0,0,828,910,5,97,0,0,829,830,
  	5,68,0,0,830,831,5,115,0,0,831,832,5,116,0,0,832,833,5,67,0,0,833,834,
  	5,111,0,0,834,835,5,108,0,0,835,836,5,111,0,0,836,910,5,114,0,0,837,838,
  	5,68,0,0,838,839,5,115,0,0,839,840,5,116,0,0,840,841,5,65,0,0,841,842,
  	5,108,0,0,842,843,5,112,0,0,843,844,5,104,0,0,844,910,5,97,0,0,845,846,
  	5,79,0,0,846,847,5,110,0,0,847,848,5,101,0,0,848,849,5,77,0,0,849,850,
  	5,105,0,0,850,851,5,110,0,0,851,852,5,117,0,0,852,853,5,115,0,0,853,854,
  	5,83,0,0,854,855,5,114,0,0,855,856,5,99,0,0,856,857,5,67,0,0,857,858,
  	5,111,0,0,858,859,5,108,0,0,859,860,5,111,0,0,860,910,5,114,0,0,861,862,
  	5,79,0,0,862,863,5,110,0,0,863,864,5,101,0,0,864,865,5,77,0,0,865,866,
  	5,105,0,0,866,867,5,110,0,0,867,868,5,117,0,0,868,869,5,115,0,0,869,870,
  	5,83,0,0,870,871,5,114,0,0,871,872,5,99,0,0,872,873,5,65,0,0,873,874,
  	5,108,0,0,874,875,5,112,0,0,875,876,5,104,0,0,876,910,5,97,0,0,877,878,
  	5,79,0,0,878,879,5,110,0,0,879,880,5,101,0,0,880,881,5,77,0,0,881,882,
  	5,105,0,0,882,883,5,110,0,0,883,884,5,117,0,0,884,885,5,115,0,0,885,886,
  	5,68,0,0,886,887,5,115,0,0,887,888,5,116,0,0,888,889,5,67,0,0,889,890,
  	5,111,0,0,890,891,5,108,0,0,891,892,5,111,0,0,892,910,5,114,0,0,893,894,
  	5,79,0,0,894,895,5,110,0,0,895,896,5,101,0,0,896,897,5,77,0,0,897,898,
  	5,105,0,0,898,899,5,110,0,0,899,900,5,117,0,0,900,901,5,115,0,0,901,902,
  	5,68,0,0,902,903,5,115,0,0,903,904,5,116,0,0,904,905,5,65,0,0,905,906,
  	5,108,0,0,906,907,5,112,0,0,907,908,5,104,0,0,908,910,5,97,0,0,909,812,
  	1,0,0,0,909,813,1,0,0,0,909,821,1,0,0,0,909,829,1,0,0,0,909,837,1,0,0,
  	0,909,845,1,0,0,0,909,861,1,0,0,0,909,877,1,0,0,0,909,893,1,0,0,0,910,
  	152,1,0,0,0,911,912,5,65,0,0,912,913,5,100,0,0,913,930,5,100,0,0,914,
  	915,5,83,0,0,915,916,5,117,0,0,916,930,5,98,0,0,917,918,5,82,0,0,918,
  	919,5,101,0,0,919,920,5,118,0,0,920,921,5,83,0,0,921,922,5,117,0,0,922,
  	930,5,98,0,0,923,924,5,77,0,0,924,925,5,105,0,0,925,930,5,110,0,0,926,
  	927,5,77,0,0,927,928,5,97,0,0,928,930,5,120,0,0,929,911,1,0,0,0,929,914,
  	1,0,0,0,929,917,1,0,0,0,929,923,1,0,0,0,929,926,1,0,0,0,930,154,1,0,0,
  	0,931,940,3,169,84,0,932,940,3,171,85,0,933,940,3,173,86,0,934,940,3,
  	175,87,0,935,940,3,177,88,0,936,940,3,179,89,0,937,940,3,181,90,0,938,
  	940,3,183,91,0,939,931,1,0,0,0,939,932,1,0,0,0,939,933,1,0,0,0,939,934,
  	1,0,0,0,939,935,1,0,0,0,939,936,1,0,0,0,939,937,1,0,0,0,939,938,1,0,0,
  	0,940,156,1,0,0,0,941,950,3,185,92,0,942,950,3,187,93,0,943,950,3,189,
  	94,0,944,950,3,191,95,0,945,950,3,193,96,0,946,950,3,195,97,0,947,950,
  	3,197,98,0,948,950,3,199,99,0,949,941,1,0,0,0,949,942,1,0,0,0,949,943,
  	1,0,0,0,949,944,1,0,0,0,949,945,1,0,0,0,949,946,1,0,0,0,949,947,1,0,0,
  	0,949,948,1,0,0,0,950,158,1,0,0,0,951,953,7,1,0,0,952,951,1,0,0,0,952,
  	953,1,0,0,0,953,954,1,0,0,0,954,958,7,2,0,0,955,957,7,3,0,0,956,955,1,
  	0,0,0,957,960,1,0,0,0,958,956,1,0,0,0,958,959,1,0,0,0,959,963,1,0,0,0,
  	960,958,1,0,0,0,961,963,5,48,0,0,962,952,1,0,0,0,962,961,1,0,0,0,963,
  	160,1,0,0,0,964,966,7,1,0,0,965,964,1,0,0,0,965,966,1,0,0,0,966,968,1,
  	0,0,0,967,969,7,3,0,0,968,967,1,0,0,0,969,970,1,0,0,0,970,968,1,0,0,0,
  	970,971,1,0,0,0,971,972,1,0,0,0,972,976,5,46,0,0,973,975,7,3,0,0,974,
  	973,1,0,0,0,975,978,1,0,0,0,976,974,1,0,0,0,976,977,1,0,0,0,977,980,1,
  	0,0,0,978,976,1,0,0,0,979,981,7,4,0,0,980,979,1,0,0,0,980,981,1,0,0,0,
  	981,992,1,0,0,0,982,984,5,46,0,0,983,985,7,3,0,0,984,983,1,0,0,0,985,
  	986,1,0,0,0,986,984,1,0,0,0,986,987,1,0,0,0,987,989,1,0,0,0,988,990,7,
  	4,0,0,989,988,1,0,0,0,989,990,1,0,0,0,990,992,1,0,0,0,991,965,1,0,0,0,
  	991,982,1,0,0,0,992,162,1,0,0,0,993,1004,7,5,0,0,994,995,7,5,0,0,995,
  	1004,7,5,0,0,996,997,7,5,0,0,997,998,7,5,0,0,998,1004,7,5,0,0,999,1000,
  	7,5,0,0,1000,1001,7,5,0,0,1001,1002,7,5,0,0,1002,1004,7,5,0,0,1003,993,
  	1,0,0,0,1003,994,1,0,0,0,1003,996,1,0,0,0,1003,999,1,0,0,0,1004,164,1,
  	0,0,0,1005,1006,5,79,0,0,1006,1007,5,102,0,0,1007,1008,5,102,0,0,1008,
  	166,1,0,0,0,1009,1010,5,79,0,0,1010,1011,5,110,0,0,1011,168,1,0,0,0,1012,
  	1013,5,78,0,0,1013,1014,5,101,0,0,1014,1015,5,118,0,0,1015,1016,5,101,
  	0,0,1016,1017,5,114,0,0,1017,170,1,0,0,0,1018,1019,5,76,0,0,1019,1020,
  	5,101,0,0,1020,1021,5,115,0,0,1021,1022,5,115,0,0,1022,172,1,0,0,0,1023,
  	1024,5,69,0,0,1024,1025,5,113,0,0,1025,1026,5,117,0,0,1026,1027,5,97,
  	0,0,1027,1028,5,108,0,0,1028,174,1,0,0,0,1029,1030,5,76,0,0,1030,1031,
  	5,69,0,0,1031,1032,5,113,0,0,1032,1033,5,117,0,0,1033,1034,5,97,0,0,1034,
  	1035,5,108,0,0,1035,176,1,0,0,0,1036,1037,5,71,0,0,1037,1038,5,114,0,
  	0,1038,1039,5,101,0,0,1039,1040,5,97,0,0,1040,1041,5,116,0,0,1041,1042,
  	5,101,0,0,1042,1043,5,114,0,0,1043,178,1,0,0,0,1044,1045,5,78,0,0,1045,
  	1046,5,111,0,0,1046,1047,5,116,0,0,1047,1048,5,69,0,0,1048,1049,5,113,
  	0,0,1049,1050,5,117,0,0,1050,1051,5,97,0,0,1051,1052,5,108,0,0,1052,180,
  	1,0,0,0,1053,1054,5,71,0,0,1054,1055,5,69,0,0,1055,1056,5,113,0,0,1056,
  	1057,5,117,0,0,1057,1058,5,97,0,0,1058,1059,5,108,0,0,1059,182,1,0,0,
  	0,1060,1061,5,65,0,0,1061,1062,5,108,0,0,1062,1063,5,119,0,0,1063,1064,
  	5,97,0,0,1064,1065,5,121,0,0,1065,1066,5,115,0,0,1066,184,1,0,0,0,1067,
  	1068,5,75,0,0,1068,1069,5,101,0,0,1069,1070,5,101,0,0,1070,1071,5,112,
  	0,0,1071,186,1,0,0,0,1072,1073,5,90,0,0,1073,1074,5,101,0,0,1074,1075,
  	5,114,0,0,1075,1076,5,111,0,0,1076,188,1,0,0,0,1077,1078,5,82,0,0,1078,
  	1079,5,101,0,0,1079,1080,5,112,0,0,1080,1081,5,108,0,0,1081,1082,5,97,
  	0,0,1082,1083,5,99,0,0,1083,1084,5,101,0,0,1084,190,1,0,0,0,1085,1086,
  	5,73,0,0,1086,1087,5,110,0,0,1087,1088,5,99,0,0,1088,1089,5,114,0,0,1089,
  	1090,5,83,0,0,1090,1091,5,97,0,0,1091,1092,5,116,0,0,1092,192,1,0,0,0,
  	1093,1094,5,68,0,0,1094,1095,5,101,0,0,1095,1096,5,99,0,0,1096,1097,5,
  	114,0,0,1097,1098,5,83,0,0,1098,1099,5,97,0,0,1099,1100,5,116,0,0,1100,
  	194,1,0,0,0,1101,1102,5,73,0,0,1102,1103,5,110,0,0,1103,1104,5,118,0,
  	0,1104,1105,5,101,0,0,1105,1106,5,114,0,0,1106,1107,5,116,0,0,1107,196,
  	1,0,0,0,1108,1109,5,73,0,0,1109,1110,5,110,0,0,1110,1111,5,99,0,0,1111,
  	1112,5,114,0,0,1112,1113,5,87,0,0,1113,1114,5,114,0,0,1114,1115,5,97,
  	0,0,1115,1116,5,112,0,0,1116,198,1,0,0,0,1117,1118,5,68,0,0,1118,1119,
  	5,101,0,0,1119,1120,5,99,0,0,1120,1121,5,114,0,0,1121,1122,5,87,0,0,1122,
  	1123,5,114,0,0,1123,1124,5,97,0,0,1124,1125,5,112,0,0,1125,200,1,0,0,
  	0,1126,1127,5,116,0,0,1127,1128,5,114,0,0,1128,1129,5,117,0,0,1129,1135,
  	5,101,0,0,1130,1131,5,84,0,0,1131,1132,5,114,0,0,1132,1133,5,117,0,0,
  	1133,1135,5,101,0,0,1134,1126,1,0,0,0,1134,1130,1,0,0,0,1135,202,1,0,
  	0,0,1136,1137,5,102,0,0,1137,1138,5,97,0,0,1138,1139,5,108,0,0,1139,1140,
  	5,115,0,0,1140,1147,5,101,0,0,1141,1142,5,70,0,0,1142,1143,5,97,0,0,1143,
  	1144,5,108,0,0,1144,1145,5,115,0,0,1145,1147,5,101,0,0,1146,1136,1,0,
  	0,0,1146,1141,1,0,0,0,1147,204,1,0,0,0,1148,1152,5,34,0,0,1149,1151,9,
  	0,0,0,1150,1149,1,0,0,0,1151,1154,1,0,0,0,1152,1153,1,0,0,0,1152,1150,
  	1,0,0,0,1153,1155,1,0,0,0,1154,1152,1,0,0,0,1155,1156,5,34,0,0,1156,206,
  	1,0,0,0,1157,1161,7,6,0,0,1158,1160,7,7,0,0,1159,1158,1,0,0,0,1160,1163,
  	1,0,0,0,1161,1159,1,0,0,0,1161,1162,1,0,0,0,1162,208,1,0,0,0,1163,1161,
  	1,0,0,0,29,0,695,705,709,721,731,735,747,800,810,909,929,939,949,952,
  	958,962,965,970,976,980,986,989,991,1003,1134,1146,1152,1161,1,6,0,0
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
