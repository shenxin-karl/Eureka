
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"


namespace Eureka::ParserDetails {


class  EffectLabLexer : public antlr4::Lexer {
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
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, WhiteSpace = 68, 
    LineComment = 69, BlockComment = 70, BooleanLiteral = 71, OnOffLabel = 72, 
    CullModeLabel = 73, RenderQueueLabel = 74, ZTestModeLabel = 75, BlendFactorLabel = 76, 
    BlendOPLabel = 77, StencilCompareLabel = 78, StencilOpLabel = 79, IntLiteral = 80, 
    FloatLiteral = 81, ColorMaskChannel = 82, KWOff = 83, KWOn = 84, KWNever = 85, 
    KWLess = 86, KWEqual = 87, KWLEqaul = 88, KWGreater = 89, KWNotEqual = 90, 
    KWGEqual = 91, KWAlways = 92, KWKeep = 93, KWZero = 94, KWReplace = 95, 
    KWIncrSat = 96, KWDecrSat = 97, KWInvert = 98, KWIncrWrap = 99, KWDecrWrap = 100, 
    KWTrue = 101, KWFalse = 102, StringLiteral = 103, HlslIncludeBlock = 104, 
    HlslProgramBlock = 105, Identity = 106
  };

  explicit EffectLabLexer(antlr4::CharStream *input);

  ~EffectLabLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace Eureka::ParserDetails
