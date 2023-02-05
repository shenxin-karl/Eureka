
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
      "property_texture_val", "property_name", "property_description", "property_item", 
      "pass_tag", "pass", "pass_vertex_shader", "pass_geometry_shader", 
      "pass_hull_shader", "pass_domain_shader", "pass_pixel_shader", "pass_render_queue", 
      "pass_shader_feature", "pass_cull_mode", "pass_zclip_mode", "pass_ztest_mode", 
      "pass_zwrite_mode", "pass_offset", "pass_color_mask", "pass_blend", 
      "pass_blend_op", "pass_alpha_to_mask", "pass_conservative", "pass_stencil", 
      "pass_block_item", "stencil_ref", "stencil_read_mask", "stencil_write_mask", 
      "stencil_comp", "stencil_pass_op", "stencil_fail_op", "stencil_zfail_op", 
      "stencil_comp_back_op", "stancil_pass_back_op", "stencil_fail_back_op", 
      "stencil_zfail_back_op", "stencil_comp_front_op", "stancil_pass_front_op", 
      "stencil_fail_front_op", "stencil_zfail_front_op", "stencil_item"
    },
    std::vector<std::string>{
      "", "'SourcePath'", "':'", "'Properties'", "'{'", "'}'", "'bool'", 
      "'Bool'", "'int'", "'Int'", "'range'", "'Range'", "'('", "','", "')'", 
      "'float'", "'Float'", "'float2'", "'Float2'", "'float3'", "'Float3'", 
      "'float4'", "'Float4'", "'2d'", "'2D'", "'matrix'", "'Matrix'", "'identity'", 
      "'white'", "'White'", "'black'", "'Black'", "'bump'", "'Bump'", "'='", 
      "'Pass'", "'Vertex'", "'Geometry'", "'Hull'", "'Domain'", "'Pixel'", 
      "'BackGround'", "'Opaque'", "'AlphaTest'", "'Transparent'", "'Overlay'", 
      "'ShaderFeature'", "'Cull'", "'ZClip'", "'ZTest'", "'ZWrite'", "'Offset'", 
      "'ColorMask'", "'BlendOp'", "'AlphaToMask'", "'Conservative'", "'Stencil'", 
      "'Ref'", "'ReadMask'", "'WriteMask'", "'Comp'", "'Fail'", "'ZFail'", 
      "'CompBack'", "'PassBack'", "'FailBack'", "'ZFailBack'", "'CompFront'", 
      "'PassFront'", "'FailFront'", "'ZFailFront'", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "'Off'", "'On'", "'Never'", "'Less'", 
      "'Equal'", "'LEqual'", "'Greater'", "'NotEqual'", "'GEqual'", "'Always'", 
      "'Keep'", "'Zero'", "'Replace'", "'IncrSat'", "'DecrSat'", "'Invert'", 
      "'IncrWrap'", "'DecrWrap'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "IntLiteral", "FloatLiteral", "BooleanLiteral", "CullModeLabel", 
      "ZTestModeLabel", "ZWriteModeLabel", "ColorMaskChannel", "RenderTargetID", 
      "BlendFactorLabel", "BlendOPLabel", "AlphaToMaskLabel", "StencilCompareLabel", 
      "StencilOpLabel", "KWOff", "KWOn", "KWNever", "KWLess", "KWEqual", 
      "KWLEqaul", "KWGreater", "KWNotEqual", "KWGEqual", "KWAlways", "KWKeep", 
      "KWZero", "KWReplace", "KWIncrSat", "KWDecrSat", "KWInvert", "KWIncrWrap", 
      "KWDecrWrap", "KWTrue", "KWFalse", "StringLiteral", "Identity", "WhiteSpace", 
      "LineComment", "BlockComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,108,484,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,1,0,1,0,3,0,127,
  	8,0,1,0,4,0,130,8,0,11,0,12,0,131,1,1,1,1,1,1,1,1,1,2,1,2,1,2,4,2,141,
  	8,2,11,2,12,2,142,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,
  	13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,
  	18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	19,1,19,1,19,1,20,1,20,1,21,1,21,1,21,3,21,209,8,21,1,22,1,22,1,23,1,
  	23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,296,8,
  	24,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,4,26,306,8,26,11,26,12,26,
  	307,1,26,1,26,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,29,1,29,1,29,
  	1,29,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,1,33,1,33,4,33,
  	336,8,33,11,33,12,33,337,1,34,1,34,1,34,1,35,1,35,1,35,1,36,1,36,1,36,
  	1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,39,1,39,1,39,1,39,1,39,3,39,361,
  	8,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	1,40,1,40,1,40,1,40,1,40,1,40,3,40,382,8,40,1,41,1,41,1,41,1,42,1,42,
  	1,42,1,43,1,43,1,43,1,44,1,44,1,44,4,44,396,8,44,11,44,12,44,397,1,44,
  	1,44,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,
  	1,45,1,45,1,45,1,45,1,45,3,45,420,8,45,1,46,1,46,1,46,1,47,1,47,1,47,
  	1,48,1,48,1,48,1,49,1,49,1,49,1,50,1,50,1,50,1,51,1,51,1,51,1,52,1,52,
  	1,52,1,53,1,53,1,53,1,54,1,54,1,54,1,55,1,55,1,55,1,56,1,56,1,56,1,57,
  	1,57,1,57,1,58,1,58,1,58,1,59,1,59,1,59,1,60,1,60,1,60,1,61,1,61,1,61,
  	1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,3,61,482,
  	8,61,1,61,0,0,62,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
  	38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,
  	84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,
  	0,14,1,0,71,72,1,0,6,7,1,0,8,9,1,0,10,11,1,0,15,16,1,0,17,18,1,0,19,20,
  	1,0,21,22,1,0,23,24,1,0,25,26,1,0,28,29,1,0,30,31,1,0,32,33,2,0,37,37,
  	41,45,474,0,124,1,0,0,0,2,133,1,0,0,0,4,137,1,0,0,0,6,146,1,0,0,0,8,148,
  	1,0,0,0,10,150,1,0,0,0,12,152,1,0,0,0,14,159,1,0,0,0,16,161,1,0,0,0,18,
  	163,1,0,0,0,20,165,1,0,0,0,22,167,1,0,0,0,24,169,1,0,0,0,26,171,1,0,0,
  	0,28,173,1,0,0,0,30,175,1,0,0,0,32,177,1,0,0,0,34,179,1,0,0,0,36,185,
  	1,0,0,0,38,193,1,0,0,0,40,203,1,0,0,0,42,208,1,0,0,0,44,210,1,0,0,0,46,
  	212,1,0,0,0,48,295,1,0,0,0,50,297,1,0,0,0,52,299,1,0,0,0,54,311,1,0,0,
  	0,56,315,1,0,0,0,58,319,1,0,0,0,60,323,1,0,0,0,62,327,1,0,0,0,64,331,
  	1,0,0,0,66,333,1,0,0,0,68,339,1,0,0,0,70,342,1,0,0,0,72,345,1,0,0,0,74,
  	348,1,0,0,0,76,351,1,0,0,0,78,360,1,0,0,0,80,381,1,0,0,0,82,383,1,0,0,
  	0,84,386,1,0,0,0,86,389,1,0,0,0,88,392,1,0,0,0,90,419,1,0,0,0,92,421,
  	1,0,0,0,94,424,1,0,0,0,96,427,1,0,0,0,98,430,1,0,0,0,100,433,1,0,0,0,
  	102,436,1,0,0,0,104,439,1,0,0,0,106,442,1,0,0,0,108,445,1,0,0,0,110,448,
  	1,0,0,0,112,451,1,0,0,0,114,454,1,0,0,0,116,457,1,0,0,0,118,460,1,0,0,
  	0,120,463,1,0,0,0,122,481,1,0,0,0,124,126,3,2,1,0,125,127,3,4,2,0,126,
  	125,1,0,0,0,126,127,1,0,0,0,127,129,1,0,0,0,128,130,3,52,26,0,129,128,
  	1,0,0,0,130,131,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,1,1,0,0,0,
  	133,134,5,1,0,0,134,135,5,2,0,0,135,136,5,104,0,0,136,3,1,0,0,0,137,138,
  	5,3,0,0,138,140,5,4,0,0,139,141,3,48,24,0,140,139,1,0,0,0,141,142,1,0,
  	0,0,142,140,1,0,0,0,142,143,1,0,0,0,143,144,1,0,0,0,144,145,5,5,0,0,145,
  	5,1,0,0,0,146,147,7,0,0,0,147,7,1,0,0,0,148,149,7,1,0,0,149,9,1,0,0,0,
  	150,151,7,2,0,0,151,11,1,0,0,0,152,153,7,3,0,0,153,154,5,12,0,0,154,155,
  	3,6,3,0,155,156,5,13,0,0,156,157,3,6,3,0,157,158,5,14,0,0,158,13,1,0,
  	0,0,159,160,7,4,0,0,160,15,1,0,0,0,161,162,7,5,0,0,162,17,1,0,0,0,163,
  	164,7,6,0,0,164,19,1,0,0,0,165,166,7,7,0,0,166,21,1,0,0,0,167,168,7,8,
  	0,0,168,23,1,0,0,0,169,170,7,9,0,0,170,25,1,0,0,0,171,172,3,6,3,0,172,
  	27,1,0,0,0,173,174,5,73,0,0,174,29,1,0,0,0,175,176,5,71,0,0,176,31,1,
  	0,0,0,177,178,3,6,3,0,178,33,1,0,0,0,179,180,5,12,0,0,180,181,3,6,3,0,
  	181,182,5,13,0,0,182,183,3,6,3,0,183,184,5,14,0,0,184,35,1,0,0,0,185,
  	186,5,12,0,0,186,187,3,6,3,0,187,188,5,13,0,0,188,189,3,6,3,0,189,190,
  	5,13,0,0,190,191,3,6,3,0,191,192,5,14,0,0,192,37,1,0,0,0,193,194,5,12,
  	0,0,194,195,3,6,3,0,195,196,5,13,0,0,196,197,3,6,3,0,197,198,5,13,0,0,
  	198,199,3,6,3,0,199,200,5,13,0,0,200,201,3,6,3,0,201,202,5,14,0,0,202,
  	39,1,0,0,0,203,204,5,27,0,0,204,41,1,0,0,0,205,209,7,10,0,0,206,209,7,
  	11,0,0,207,209,7,12,0,0,208,205,1,0,0,0,208,206,1,0,0,0,208,207,1,0,0,
  	0,209,43,1,0,0,0,210,211,5,105,0,0,211,45,1,0,0,0,212,213,5,104,0,0,213,
  	47,1,0,0,0,214,215,3,44,22,0,215,216,5,12,0,0,216,217,3,46,23,0,217,218,
  	5,13,0,0,218,219,3,8,4,0,219,220,5,14,0,0,220,221,5,34,0,0,221,222,3,
  	28,14,0,222,296,1,0,0,0,223,224,3,44,22,0,224,225,5,12,0,0,225,226,3,
  	46,23,0,226,227,5,13,0,0,227,228,3,10,5,0,228,229,5,14,0,0,229,230,5,
  	34,0,0,230,231,3,30,15,0,231,296,1,0,0,0,232,233,3,44,22,0,233,234,5,
  	12,0,0,234,235,3,46,23,0,235,236,5,13,0,0,236,237,3,12,6,0,237,238,5,
  	14,0,0,238,239,5,34,0,0,239,240,3,26,13,0,240,296,1,0,0,0,241,242,3,44,
  	22,0,242,243,5,12,0,0,243,244,3,46,23,0,244,245,5,13,0,0,245,246,3,14,
  	7,0,246,247,5,14,0,0,247,248,5,34,0,0,248,249,3,32,16,0,249,296,1,0,0,
  	0,250,251,3,44,22,0,251,252,5,12,0,0,252,253,3,46,23,0,253,254,5,13,0,
  	0,254,255,3,16,8,0,255,256,5,14,0,0,256,257,5,34,0,0,257,258,3,34,17,
  	0,258,296,1,0,0,0,259,260,3,44,22,0,260,261,5,12,0,0,261,262,3,46,23,
  	0,262,263,5,13,0,0,263,264,3,18,9,0,264,265,5,14,0,0,265,266,5,34,0,0,
  	266,267,3,36,18,0,267,296,1,0,0,0,268,269,3,44,22,0,269,270,5,12,0,0,
  	270,271,3,46,23,0,271,272,5,13,0,0,272,273,3,20,10,0,273,274,5,14,0,0,
  	274,275,5,34,0,0,275,276,3,38,19,0,276,296,1,0,0,0,277,278,3,44,22,0,
  	278,279,5,12,0,0,279,280,3,46,23,0,280,281,5,13,0,0,281,282,3,22,11,0,
  	282,283,5,14,0,0,283,284,5,34,0,0,284,285,3,42,21,0,285,296,1,0,0,0,286,
  	287,3,44,22,0,287,288,5,12,0,0,288,289,3,46,23,0,289,290,5,13,0,0,290,
  	291,3,24,12,0,291,292,5,14,0,0,292,293,5,34,0,0,293,294,3,40,20,0,294,
  	296,1,0,0,0,295,214,1,0,0,0,295,223,1,0,0,0,295,232,1,0,0,0,295,241,1,
  	0,0,0,295,250,1,0,0,0,295,259,1,0,0,0,295,268,1,0,0,0,295,277,1,0,0,0,
  	295,286,1,0,0,0,296,49,1,0,0,0,297,298,5,104,0,0,298,51,1,0,0,0,299,300,
  	5,35,0,0,300,301,5,12,0,0,301,302,3,50,25,0,302,303,5,14,0,0,303,305,
  	5,4,0,0,304,306,3,90,45,0,305,304,1,0,0,0,306,307,1,0,0,0,307,305,1,0,
  	0,0,307,308,1,0,0,0,308,309,1,0,0,0,309,310,5,5,0,0,310,53,1,0,0,0,311,
  	312,5,36,0,0,312,313,5,2,0,0,313,314,5,104,0,0,314,55,1,0,0,0,315,316,
  	5,37,0,0,316,317,5,2,0,0,317,318,5,104,0,0,318,57,1,0,0,0,319,320,5,38,
  	0,0,320,321,5,2,0,0,321,322,5,104,0,0,322,59,1,0,0,0,323,324,5,39,0,0,
  	324,325,5,2,0,0,325,326,5,104,0,0,326,61,1,0,0,0,327,328,5,40,0,0,328,
  	329,5,2,0,0,329,330,5,104,0,0,330,63,1,0,0,0,331,332,7,13,0,0,332,65,
  	1,0,0,0,333,335,5,46,0,0,334,336,5,104,0,0,335,334,1,0,0,0,336,337,1,
  	0,0,0,337,335,1,0,0,0,337,338,1,0,0,0,338,67,1,0,0,0,339,340,5,47,0,0,
  	340,341,5,74,0,0,341,69,1,0,0,0,342,343,5,48,0,0,343,344,5,73,0,0,344,
  	71,1,0,0,0,345,346,5,49,0,0,346,347,5,75,0,0,347,73,1,0,0,0,348,349,5,
  	50,0,0,349,350,5,76,0,0,350,75,1,0,0,0,351,352,5,51,0,0,352,353,5,72,
  	0,0,353,354,5,72,0,0,354,77,1,0,0,0,355,356,5,52,0,0,356,361,5,77,0,0,
  	357,358,5,52,0,0,358,359,5,77,0,0,359,361,5,78,0,0,360,355,1,0,0,0,360,
  	357,1,0,0,0,361,79,1,0,0,0,362,382,5,84,0,0,363,364,5,78,0,0,364,382,
  	5,84,0,0,365,366,5,79,0,0,366,382,5,79,0,0,367,368,5,78,0,0,368,369,5,
  	79,0,0,369,382,5,79,0,0,370,371,5,79,0,0,371,372,5,79,0,0,372,373,5,13,
  	0,0,373,374,5,79,0,0,374,382,5,79,0,0,375,376,5,78,0,0,376,377,5,79,0,
  	0,377,378,5,79,0,0,378,379,5,13,0,0,379,380,5,79,0,0,380,382,5,79,0,0,
  	381,362,1,0,0,0,381,363,1,0,0,0,381,365,1,0,0,0,381,367,1,0,0,0,381,370,
  	1,0,0,0,381,375,1,0,0,0,382,81,1,0,0,0,383,384,5,53,0,0,384,385,5,80,
  	0,0,385,83,1,0,0,0,386,387,5,54,0,0,387,388,5,81,0,0,388,85,1,0,0,0,389,
  	390,5,55,0,0,390,391,5,73,0,0,391,87,1,0,0,0,392,393,5,56,0,0,393,395,
  	5,4,0,0,394,396,3,122,61,0,395,394,1,0,0,0,396,397,1,0,0,0,397,395,1,
  	0,0,0,397,398,1,0,0,0,398,399,1,0,0,0,399,400,5,5,0,0,400,89,1,0,0,0,
  	401,420,3,54,27,0,402,420,3,56,28,0,403,420,3,58,29,0,404,420,3,60,30,
  	0,405,420,3,62,31,0,406,420,3,64,32,0,407,420,3,66,33,0,408,420,3,68,
  	34,0,409,420,3,70,35,0,410,420,3,72,36,0,411,420,3,74,37,0,412,420,3,
  	76,38,0,413,420,3,78,39,0,414,420,3,80,40,0,415,420,3,82,41,0,416,420,
  	3,84,42,0,417,420,3,86,43,0,418,420,3,88,44,0,419,401,1,0,0,0,419,402,
  	1,0,0,0,419,403,1,0,0,0,419,404,1,0,0,0,419,405,1,0,0,0,419,406,1,0,0,
  	0,419,407,1,0,0,0,419,408,1,0,0,0,419,409,1,0,0,0,419,410,1,0,0,0,419,
  	411,1,0,0,0,419,412,1,0,0,0,419,413,1,0,0,0,419,414,1,0,0,0,419,415,1,
  	0,0,0,419,416,1,0,0,0,419,417,1,0,0,0,419,418,1,0,0,0,420,91,1,0,0,0,
  	421,422,5,57,0,0,422,423,5,71,0,0,423,93,1,0,0,0,424,425,5,58,0,0,425,
  	426,5,71,0,0,426,95,1,0,0,0,427,428,5,59,0,0,428,429,5,71,0,0,429,97,
  	1,0,0,0,430,431,5,60,0,0,431,432,5,82,0,0,432,99,1,0,0,0,433,434,5,35,
  	0,0,434,435,5,83,0,0,435,101,1,0,0,0,436,437,5,61,0,0,437,438,5,83,0,
  	0,438,103,1,0,0,0,439,440,5,62,0,0,440,441,5,83,0,0,441,105,1,0,0,0,442,
  	443,5,63,0,0,443,444,5,83,0,0,444,107,1,0,0,0,445,446,5,64,0,0,446,447,
  	5,83,0,0,447,109,1,0,0,0,448,449,5,65,0,0,449,450,5,83,0,0,450,111,1,
  	0,0,0,451,452,5,66,0,0,452,453,5,83,0,0,453,113,1,0,0,0,454,455,5,67,
  	0,0,455,456,5,83,0,0,456,115,1,0,0,0,457,458,5,68,0,0,458,459,5,83,0,
  	0,459,117,1,0,0,0,460,461,5,69,0,0,461,462,5,83,0,0,462,119,1,0,0,0,463,
  	464,5,70,0,0,464,465,5,83,0,0,465,121,1,0,0,0,466,482,3,92,46,0,467,482,
  	3,94,47,0,468,482,3,96,48,0,469,482,3,98,49,0,470,482,3,100,50,0,471,
  	482,3,102,51,0,472,482,3,104,52,0,473,482,3,106,53,0,474,482,3,108,54,
  	0,475,482,3,110,55,0,476,482,3,112,56,0,477,482,3,114,57,0,478,482,3,
  	116,58,0,479,482,3,118,59,0,480,482,3,120,60,0,481,466,1,0,0,0,481,467,
  	1,0,0,0,481,468,1,0,0,0,481,469,1,0,0,0,481,470,1,0,0,0,481,471,1,0,0,
  	0,481,472,1,0,0,0,481,473,1,0,0,0,481,474,1,0,0,0,481,475,1,0,0,0,481,
  	476,1,0,0,0,481,477,1,0,0,0,481,478,1,0,0,0,481,479,1,0,0,0,481,480,1,
  	0,0,0,482,123,1,0,0,0,12,126,131,142,208,295,307,337,360,381,397,419,
  	481
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

std::vector<EffectLabParser::PassContext *> EffectLabParser::EffectContext::pass() {
  return getRuleContexts<EffectLabParser::PassContext>();
}

EffectLabParser::PassContext* EffectLabParser::EffectContext::pass(size_t i) {
  return getRuleContext<EffectLabParser::PassContext>(i);
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
    setState(124);
    source_path();
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EffectLabParser::T__2) {
      setState(125);
      property_block();
    }
    setState(129); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(128);
      pass();
      setState(131); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EffectLabParser::T__34);
   
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
    setState(133);
    match(EffectLabParser::T__0);
    setState(134);
    match(EffectLabParser::T__1);
    setState(135);
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
    setState(137);
    match(EffectLabParser::T__2);
    setState(138);
    match(EffectLabParser::T__3);
    setState(140); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(139);
      property_item();
      setState(142); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EffectLabParser::Identity);
    setState(144);
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
    setState(146);
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
    setState(148);
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
    setState(150);
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
    setState(152);
    _la = _input->LA(1);
    if (!(_la == EffectLabParser::T__9

    || _la == EffectLabParser::T__10)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(153);
    match(EffectLabParser::T__11);
    setState(154);
    number_val();
    setState(155);
    match(EffectLabParser::T__12);
    setState(156);
    number_val();
    setState(157);
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
    setState(159);
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
    setState(161);
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
    setState(163);
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
    setState(165);
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
    setState(167);
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
    setState(169);
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
    setState(171);
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
    setState(173);
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
    setState(175);
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
    setState(177);
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
    setState(179);
    match(EffectLabParser::T__11);
    setState(180);
    number_val();
    setState(181);
    match(EffectLabParser::T__12);
    setState(182);
    number_val();
    setState(183);
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
    setState(185);
    match(EffectLabParser::T__11);
    setState(186);
    number_val();
    setState(187);
    match(EffectLabParser::T__12);
    setState(188);
    number_val();
    setState(189);
    match(EffectLabParser::T__12);
    setState(190);
    number_val();
    setState(191);
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
    setState(193);
    match(EffectLabParser::T__11);
    setState(194);
    number_val();
    setState(195);
    match(EffectLabParser::T__12);
    setState(196);
    number_val();
    setState(197);
    match(EffectLabParser::T__12);
    setState(198);
    number_val();
    setState(199);
    match(EffectLabParser::T__12);
    setState(200);
    number_val();
    setState(201);
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
    setState(203);
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
    setState(208);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EffectLabParser::T__27:
      case EffectLabParser::T__28: {
        enterOuterAlt(_localctx, 1);
        setState(205);
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
        setState(206);
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
        setState(207);
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
    setState(210);
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
    setState(212);
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
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemBoolContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(214);
      property_name();
      setState(215);
      match(EffectLabParser::T__11);
      setState(216);
      property_description();
      setState(217);
      match(EffectLabParser::T__12);
      setState(218);
      property_bool_type();
      setState(219);
      match(EffectLabParser::T__13);
      setState(220);
      match(EffectLabParser::T__33);
      setState(221);
      property_bool_val();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemIntContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(223);
      property_name();
      setState(224);
      match(EffectLabParser::T__11);
      setState(225);
      property_description();
      setState(226);
      match(EffectLabParser::T__12);
      setState(227);
      property_int_type();
      setState(228);
      match(EffectLabParser::T__13);
      setState(229);
      match(EffectLabParser::T__33);
      setState(230);
      property_int_val();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemRangeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(232);
      property_name();
      setState(233);
      match(EffectLabParser::T__11);
      setState(234);
      property_description();
      setState(235);
      match(EffectLabParser::T__12);
      setState(236);
      property_range_type();
      setState(237);
      match(EffectLabParser::T__13);
      setState(238);
      match(EffectLabParser::T__33);
      setState(239);
      property_range_val();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloatContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(241);
      property_name();
      setState(242);
      match(EffectLabParser::T__11);
      setState(243);
      property_description();
      setState(244);
      match(EffectLabParser::T__12);
      setState(245);
      property_float_type();
      setState(246);
      match(EffectLabParser::T__13);
      setState(247);
      match(EffectLabParser::T__33);
      setState(248);
      property_float_val();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(250);
      property_name();
      setState(251);
      match(EffectLabParser::T__11);
      setState(252);
      property_description();
      setState(253);
      match(EffectLabParser::T__12);
      setState(254);
      property_float2_type();
      setState(255);
      match(EffectLabParser::T__13);
      setState(256);
      match(EffectLabParser::T__33);
      setState(257);
      property_float2_val();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat3Context>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(259);
      property_name();
      setState(260);
      match(EffectLabParser::T__11);
      setState(261);
      property_description();
      setState(262);
      match(EffectLabParser::T__12);
      setState(263);
      property_float3_type();
      setState(264);
      match(EffectLabParser::T__13);
      setState(265);
      match(EffectLabParser::T__33);
      setState(266);
      property_float3_val();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemFloat4Context>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(268);
      property_name();
      setState(269);
      match(EffectLabParser::T__11);
      setState(270);
      property_description();
      setState(271);
      match(EffectLabParser::T__12);
      setState(272);
      property_float4_type();
      setState(273);
      match(EffectLabParser::T__13);
      setState(274);
      match(EffectLabParser::T__33);
      setState(275);
      property_float4_val();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemTextureContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(277);
      property_name();
      setState(278);
      match(EffectLabParser::T__11);
      setState(279);
      property_description();
      setState(280);
      match(EffectLabParser::T__12);
      setState(281);
      property_texture_2d_type();
      setState(282);
      match(EffectLabParser::T__13);
      setState(283);
      match(EffectLabParser::T__33);
      setState(284);
      property_texture_val();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<EffectLabParser::PropertyItemMatrixContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(286);
      property_name();
      setState(287);
      match(EffectLabParser::T__11);
      setState(288);
      property_description();
      setState(289);
      match(EffectLabParser::T__12);
      setState(290);
      property_matrix_type();
      setState(291);
      match(EffectLabParser::T__13);
      setState(292);
      match(EffectLabParser::T__33);
      setState(293);
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

//----------------- Pass_tagContext ------------------------------------------------------------------

EffectLabParser::Pass_tagContext::Pass_tagContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_tagContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_tagContext::getRuleIndex() const {
  return EffectLabParser::RulePass_tag;
}

void EffectLabParser::Pass_tagContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_tag(this);
}

void EffectLabParser::Pass_tagContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_tag(this);
}


std::any EffectLabParser::Pass_tagContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_tag(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_tagContext* EffectLabParser::pass_tag() {
  Pass_tagContext *_localctx = _tracker.createInstance<Pass_tagContext>(_ctx, getState());
  enterRule(_localctx, 50, EffectLabParser::RulePass_tag);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PassContext ------------------------------------------------------------------

EffectLabParser::PassContext::PassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EffectLabParser::Pass_tagContext* EffectLabParser::PassContext::pass_tag() {
  return getRuleContext<EffectLabParser::Pass_tagContext>(0);
}

std::vector<EffectLabParser::Pass_block_itemContext *> EffectLabParser::PassContext::pass_block_item() {
  return getRuleContexts<EffectLabParser::Pass_block_itemContext>();
}

EffectLabParser::Pass_block_itemContext* EffectLabParser::PassContext::pass_block_item(size_t i) {
  return getRuleContext<EffectLabParser::Pass_block_itemContext>(i);
}


size_t EffectLabParser::PassContext::getRuleIndex() const {
  return EffectLabParser::RulePass;
}

void EffectLabParser::PassContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass(this);
}

void EffectLabParser::PassContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass(this);
}


std::any EffectLabParser::PassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::PassContext* EffectLabParser::pass() {
  PassContext *_localctx = _tracker.createInstance<PassContext>(_ctx, getState());
  enterRule(_localctx, 52, EffectLabParser::RulePass);
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
    setState(299);
    match(EffectLabParser::T__34);
    setState(300);
    match(EffectLabParser::T__11);
    setState(301);
    pass_tag();
    setState(302);
    match(EffectLabParser::T__13);
    setState(303);
    match(EffectLabParser::T__3);
    setState(305); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(304);
      pass_block_item();
      setState(307); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la - 36) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 36)) & 294669118341119) != 0);
    setState(309);
    match(EffectLabParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_vertex_shaderContext ------------------------------------------------------------------

EffectLabParser::Pass_vertex_shaderContext::Pass_vertex_shaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_vertex_shaderContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_vertex_shaderContext::getRuleIndex() const {
  return EffectLabParser::RulePass_vertex_shader;
}

void EffectLabParser::Pass_vertex_shaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_vertex_shader(this);
}

void EffectLabParser::Pass_vertex_shaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_vertex_shader(this);
}


std::any EffectLabParser::Pass_vertex_shaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_vertex_shader(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_vertex_shaderContext* EffectLabParser::pass_vertex_shader() {
  Pass_vertex_shaderContext *_localctx = _tracker.createInstance<Pass_vertex_shaderContext>(_ctx, getState());
  enterRule(_localctx, 54, EffectLabParser::RulePass_vertex_shader);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(311);
    match(EffectLabParser::T__35);
    setState(312);
    match(EffectLabParser::T__1);
    setState(313);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_geometry_shaderContext ------------------------------------------------------------------

EffectLabParser::Pass_geometry_shaderContext::Pass_geometry_shaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_geometry_shaderContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_geometry_shaderContext::getRuleIndex() const {
  return EffectLabParser::RulePass_geometry_shader;
}

void EffectLabParser::Pass_geometry_shaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_geometry_shader(this);
}

void EffectLabParser::Pass_geometry_shaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_geometry_shader(this);
}


std::any EffectLabParser::Pass_geometry_shaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_geometry_shader(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_geometry_shaderContext* EffectLabParser::pass_geometry_shader() {
  Pass_geometry_shaderContext *_localctx = _tracker.createInstance<Pass_geometry_shaderContext>(_ctx, getState());
  enterRule(_localctx, 56, EffectLabParser::RulePass_geometry_shader);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(315);
    match(EffectLabParser::T__36);
    setState(316);
    match(EffectLabParser::T__1);
    setState(317);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_hull_shaderContext ------------------------------------------------------------------

EffectLabParser::Pass_hull_shaderContext::Pass_hull_shaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_hull_shaderContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_hull_shaderContext::getRuleIndex() const {
  return EffectLabParser::RulePass_hull_shader;
}

void EffectLabParser::Pass_hull_shaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_hull_shader(this);
}

void EffectLabParser::Pass_hull_shaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_hull_shader(this);
}


std::any EffectLabParser::Pass_hull_shaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_hull_shader(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_hull_shaderContext* EffectLabParser::pass_hull_shader() {
  Pass_hull_shaderContext *_localctx = _tracker.createInstance<Pass_hull_shaderContext>(_ctx, getState());
  enterRule(_localctx, 58, EffectLabParser::RulePass_hull_shader);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    match(EffectLabParser::T__37);
    setState(320);
    match(EffectLabParser::T__1);
    setState(321);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_domain_shaderContext ------------------------------------------------------------------

EffectLabParser::Pass_domain_shaderContext::Pass_domain_shaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_domain_shaderContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_domain_shaderContext::getRuleIndex() const {
  return EffectLabParser::RulePass_domain_shader;
}

void EffectLabParser::Pass_domain_shaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_domain_shader(this);
}

void EffectLabParser::Pass_domain_shaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_domain_shader(this);
}


std::any EffectLabParser::Pass_domain_shaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_domain_shader(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_domain_shaderContext* EffectLabParser::pass_domain_shader() {
  Pass_domain_shaderContext *_localctx = _tracker.createInstance<Pass_domain_shaderContext>(_ctx, getState());
  enterRule(_localctx, 60, EffectLabParser::RulePass_domain_shader);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    match(EffectLabParser::T__38);
    setState(324);
    match(EffectLabParser::T__1);
    setState(325);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_pixel_shaderContext ------------------------------------------------------------------

EffectLabParser::Pass_pixel_shaderContext::Pass_pixel_shaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_pixel_shaderContext::StringLiteral() {
  return getToken(EffectLabParser::StringLiteral, 0);
}


size_t EffectLabParser::Pass_pixel_shaderContext::getRuleIndex() const {
  return EffectLabParser::RulePass_pixel_shader;
}

void EffectLabParser::Pass_pixel_shaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_pixel_shader(this);
}

void EffectLabParser::Pass_pixel_shaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_pixel_shader(this);
}


std::any EffectLabParser::Pass_pixel_shaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_pixel_shader(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_pixel_shaderContext* EffectLabParser::pass_pixel_shader() {
  Pass_pixel_shaderContext *_localctx = _tracker.createInstance<Pass_pixel_shaderContext>(_ctx, getState());
  enterRule(_localctx, 62, EffectLabParser::RulePass_pixel_shader);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    match(EffectLabParser::T__39);
    setState(328);
    match(EffectLabParser::T__1);
    setState(329);
    match(EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_render_queueContext ------------------------------------------------------------------

EffectLabParser::Pass_render_queueContext::Pass_render_queueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Pass_render_queueContext::getRuleIndex() const {
  return EffectLabParser::RulePass_render_queue;
}

void EffectLabParser::Pass_render_queueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_render_queue(this);
}

void EffectLabParser::Pass_render_queueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_render_queue(this);
}


std::any EffectLabParser::Pass_render_queueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_render_queue(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_render_queueContext* EffectLabParser::pass_render_queue() {
  Pass_render_queueContext *_localctx = _tracker.createInstance<Pass_render_queueContext>(_ctx, getState());
  enterRule(_localctx, 64, EffectLabParser::RulePass_render_queue);
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
    setState(331);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 68307159875584) != 0)) {
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

//----------------- Pass_shader_featureContext ------------------------------------------------------------------

EffectLabParser::Pass_shader_featureContext::Pass_shader_featureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> EffectLabParser::Pass_shader_featureContext::StringLiteral() {
  return getTokens(EffectLabParser::StringLiteral);
}

tree::TerminalNode* EffectLabParser::Pass_shader_featureContext::StringLiteral(size_t i) {
  return getToken(EffectLabParser::StringLiteral, i);
}


size_t EffectLabParser::Pass_shader_featureContext::getRuleIndex() const {
  return EffectLabParser::RulePass_shader_feature;
}

void EffectLabParser::Pass_shader_featureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_shader_feature(this);
}

void EffectLabParser::Pass_shader_featureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_shader_feature(this);
}


std::any EffectLabParser::Pass_shader_featureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_shader_feature(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_shader_featureContext* EffectLabParser::pass_shader_feature() {
  Pass_shader_featureContext *_localctx = _tracker.createInstance<Pass_shader_featureContext>(_ctx, getState());
  enterRule(_localctx, 66, EffectLabParser::RulePass_shader_feature);
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
    setState(333);
    match(EffectLabParser::T__45);
    setState(335); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(334);
      match(EffectLabParser::StringLiteral);
      setState(337); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EffectLabParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_cull_modeContext ------------------------------------------------------------------

EffectLabParser::Pass_cull_modeContext::Pass_cull_modeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_cull_modeContext::CullModeLabel() {
  return getToken(EffectLabParser::CullModeLabel, 0);
}


size_t EffectLabParser::Pass_cull_modeContext::getRuleIndex() const {
  return EffectLabParser::RulePass_cull_mode;
}

void EffectLabParser::Pass_cull_modeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_cull_mode(this);
}

void EffectLabParser::Pass_cull_modeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_cull_mode(this);
}


std::any EffectLabParser::Pass_cull_modeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_cull_mode(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_cull_modeContext* EffectLabParser::pass_cull_mode() {
  Pass_cull_modeContext *_localctx = _tracker.createInstance<Pass_cull_modeContext>(_ctx, getState());
  enterRule(_localctx, 68, EffectLabParser::RulePass_cull_mode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    match(EffectLabParser::T__46);
    setState(340);
    match(EffectLabParser::CullModeLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_zclip_modeContext ------------------------------------------------------------------

EffectLabParser::Pass_zclip_modeContext::Pass_zclip_modeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_zclip_modeContext::BooleanLiteral() {
  return getToken(EffectLabParser::BooleanLiteral, 0);
}


size_t EffectLabParser::Pass_zclip_modeContext::getRuleIndex() const {
  return EffectLabParser::RulePass_zclip_mode;
}

void EffectLabParser::Pass_zclip_modeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_zclip_mode(this);
}

void EffectLabParser::Pass_zclip_modeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_zclip_mode(this);
}


std::any EffectLabParser::Pass_zclip_modeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_zclip_mode(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_zclip_modeContext* EffectLabParser::pass_zclip_mode() {
  Pass_zclip_modeContext *_localctx = _tracker.createInstance<Pass_zclip_modeContext>(_ctx, getState());
  enterRule(_localctx, 70, EffectLabParser::RulePass_zclip_mode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(EffectLabParser::T__47);
    setState(343);
    match(EffectLabParser::BooleanLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_ztest_modeContext ------------------------------------------------------------------

EffectLabParser::Pass_ztest_modeContext::Pass_ztest_modeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_ztest_modeContext::ZTestModeLabel() {
  return getToken(EffectLabParser::ZTestModeLabel, 0);
}


size_t EffectLabParser::Pass_ztest_modeContext::getRuleIndex() const {
  return EffectLabParser::RulePass_ztest_mode;
}

void EffectLabParser::Pass_ztest_modeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_ztest_mode(this);
}

void EffectLabParser::Pass_ztest_modeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_ztest_mode(this);
}


std::any EffectLabParser::Pass_ztest_modeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_ztest_mode(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_ztest_modeContext* EffectLabParser::pass_ztest_mode() {
  Pass_ztest_modeContext *_localctx = _tracker.createInstance<Pass_ztest_modeContext>(_ctx, getState());
  enterRule(_localctx, 72, EffectLabParser::RulePass_ztest_mode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    match(EffectLabParser::T__48);
    setState(346);
    match(EffectLabParser::ZTestModeLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_zwrite_modeContext ------------------------------------------------------------------

EffectLabParser::Pass_zwrite_modeContext::Pass_zwrite_modeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_zwrite_modeContext::ZWriteModeLabel() {
  return getToken(EffectLabParser::ZWriteModeLabel, 0);
}


size_t EffectLabParser::Pass_zwrite_modeContext::getRuleIndex() const {
  return EffectLabParser::RulePass_zwrite_mode;
}

void EffectLabParser::Pass_zwrite_modeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_zwrite_mode(this);
}

void EffectLabParser::Pass_zwrite_modeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_zwrite_mode(this);
}


std::any EffectLabParser::Pass_zwrite_modeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_zwrite_mode(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_zwrite_modeContext* EffectLabParser::pass_zwrite_mode() {
  Pass_zwrite_modeContext *_localctx = _tracker.createInstance<Pass_zwrite_modeContext>(_ctx, getState());
  enterRule(_localctx, 74, EffectLabParser::RulePass_zwrite_mode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    match(EffectLabParser::T__49);
    setState(349);
    match(EffectLabParser::ZWriteModeLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_offsetContext ------------------------------------------------------------------

EffectLabParser::Pass_offsetContext::Pass_offsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> EffectLabParser::Pass_offsetContext::FloatLiteral() {
  return getTokens(EffectLabParser::FloatLiteral);
}

tree::TerminalNode* EffectLabParser::Pass_offsetContext::FloatLiteral(size_t i) {
  return getToken(EffectLabParser::FloatLiteral, i);
}


size_t EffectLabParser::Pass_offsetContext::getRuleIndex() const {
  return EffectLabParser::RulePass_offset;
}

void EffectLabParser::Pass_offsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_offset(this);
}

void EffectLabParser::Pass_offsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_offset(this);
}


std::any EffectLabParser::Pass_offsetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_offset(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_offsetContext* EffectLabParser::pass_offset() {
  Pass_offsetContext *_localctx = _tracker.createInstance<Pass_offsetContext>(_ctx, getState());
  enterRule(_localctx, 76, EffectLabParser::RulePass_offset);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(351);
    match(EffectLabParser::T__50);
    setState(352);
    match(EffectLabParser::FloatLiteral);
    setState(353);
    match(EffectLabParser::FloatLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_color_maskContext ------------------------------------------------------------------

EffectLabParser::Pass_color_maskContext::Pass_color_maskContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_color_maskContext::ColorMaskChannel() {
  return getToken(EffectLabParser::ColorMaskChannel, 0);
}

tree::TerminalNode* EffectLabParser::Pass_color_maskContext::RenderTargetID() {
  return getToken(EffectLabParser::RenderTargetID, 0);
}


size_t EffectLabParser::Pass_color_maskContext::getRuleIndex() const {
  return EffectLabParser::RulePass_color_mask;
}

void EffectLabParser::Pass_color_maskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_color_mask(this);
}

void EffectLabParser::Pass_color_maskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_color_mask(this);
}


std::any EffectLabParser::Pass_color_maskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_color_mask(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_color_maskContext* EffectLabParser::pass_color_mask() {
  Pass_color_maskContext *_localctx = _tracker.createInstance<Pass_color_maskContext>(_ctx, getState());
  enterRule(_localctx, 78, EffectLabParser::RulePass_color_mask);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(355);
      match(EffectLabParser::T__51);
      setState(356);
      match(EffectLabParser::ColorMaskChannel);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(357);
      match(EffectLabParser::T__51);
      setState(358);
      match(EffectLabParser::ColorMaskChannel);
      setState(359);
      match(EffectLabParser::RenderTargetID);
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

//----------------- Pass_blendContext ------------------------------------------------------------------

EffectLabParser::Pass_blendContext::Pass_blendContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Pass_blendContext::getRuleIndex() const {
  return EffectLabParser::RulePass_blend;
}

void EffectLabParser::Pass_blendContext::copyFrom(Pass_blendContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PassBlendRTOffContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PassBlendRTOffContext::RenderTargetID() {
  return getToken(EffectLabParser::RenderTargetID, 0);
}

tree::TerminalNode* EffectLabParser::PassBlendRTOffContext::KWOff() {
  return getToken(EffectLabParser::KWOff, 0);
}

EffectLabParser::PassBlendRTOffContext::PassBlendRTOffContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendRTOffContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendRTOff(this);
}
void EffectLabParser::PassBlendRTOffContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendRTOff(this);
}

std::any EffectLabParser::PassBlendRTOffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendRTOff(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendOffContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PassBlendOffContext::KWOff() {
  return getToken(EffectLabParser::KWOff, 0);
}

EffectLabParser::PassBlendOffContext::PassBlendOffContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendOffContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendOff(this);
}
void EffectLabParser::PassBlendOffContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendOff(this);
}

std::any EffectLabParser::PassBlendOffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendOff(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendRTColorAlphaContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PassBlendRTColorAlphaContext::RenderTargetID() {
  return getToken(EffectLabParser::RenderTargetID, 0);
}

std::vector<tree::TerminalNode *> EffectLabParser::PassBlendRTColorAlphaContext::BlendFactorLabel() {
  return getTokens(EffectLabParser::BlendFactorLabel);
}

tree::TerminalNode* EffectLabParser::PassBlendRTColorAlphaContext::BlendFactorLabel(size_t i) {
  return getToken(EffectLabParser::BlendFactorLabel, i);
}

EffectLabParser::PassBlendRTColorAlphaContext::PassBlendRTColorAlphaContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendRTColorAlphaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendRTColorAlpha(this);
}
void EffectLabParser::PassBlendRTColorAlphaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendRTColorAlpha(this);
}

std::any EffectLabParser::PassBlendRTColorAlphaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendRTColorAlpha(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendColorContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> EffectLabParser::PassBlendColorContext::BlendFactorLabel() {
  return getTokens(EffectLabParser::BlendFactorLabel);
}

tree::TerminalNode* EffectLabParser::PassBlendColorContext::BlendFactorLabel(size_t i) {
  return getToken(EffectLabParser::BlendFactorLabel, i);
}

EffectLabParser::PassBlendColorContext::PassBlendColorContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendColorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendColor(this);
}
void EffectLabParser::PassBlendColorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendColor(this);
}

std::any EffectLabParser::PassBlendColorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendColor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendColorAlphaContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> EffectLabParser::PassBlendColorAlphaContext::BlendFactorLabel() {
  return getTokens(EffectLabParser::BlendFactorLabel);
}

tree::TerminalNode* EffectLabParser::PassBlendColorAlphaContext::BlendFactorLabel(size_t i) {
  return getToken(EffectLabParser::BlendFactorLabel, i);
}

EffectLabParser::PassBlendColorAlphaContext::PassBlendColorAlphaContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendColorAlphaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendColorAlpha(this);
}
void EffectLabParser::PassBlendColorAlphaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendColorAlpha(this);
}

std::any EffectLabParser::PassBlendColorAlphaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendColorAlpha(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendRTColorContext ------------------------------------------------------------------

tree::TerminalNode* EffectLabParser::PassBlendRTColorContext::RenderTargetID() {
  return getToken(EffectLabParser::RenderTargetID, 0);
}

std::vector<tree::TerminalNode *> EffectLabParser::PassBlendRTColorContext::BlendFactorLabel() {
  return getTokens(EffectLabParser::BlendFactorLabel);
}

tree::TerminalNode* EffectLabParser::PassBlendRTColorContext::BlendFactorLabel(size_t i) {
  return getToken(EffectLabParser::BlendFactorLabel, i);
}

EffectLabParser::PassBlendRTColorContext::PassBlendRTColorContext(Pass_blendContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendRTColorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendRTColor(this);
}
void EffectLabParser::PassBlendRTColorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendRTColor(this);
}

std::any EffectLabParser::PassBlendRTColorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendRTColor(this);
  else
    return visitor->visitChildren(this);
}
EffectLabParser::Pass_blendContext* EffectLabParser::pass_blend() {
  Pass_blendContext *_localctx = _tracker.createInstance<Pass_blendContext>(_ctx, getState());
  enterRule(_localctx, 80, EffectLabParser::RulePass_blend);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(381);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendOffContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(362);
      match(EffectLabParser::KWOff);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendRTOffContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(363);
      match(EffectLabParser::RenderTargetID);
      setState(364);
      match(EffectLabParser::KWOff);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendColorContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(365);
      match(EffectLabParser::BlendFactorLabel);
      setState(366);
      match(EffectLabParser::BlendFactorLabel);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendRTColorContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(367);
      match(EffectLabParser::RenderTargetID);
      setState(368);
      match(EffectLabParser::BlendFactorLabel);
      setState(369);
      match(EffectLabParser::BlendFactorLabel);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendColorAlphaContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(370);
      match(EffectLabParser::BlendFactorLabel);
      setState(371);
      match(EffectLabParser::BlendFactorLabel);
      setState(372);
      match(EffectLabParser::T__12);
      setState(373);
      match(EffectLabParser::BlendFactorLabel);
      setState(374);
      match(EffectLabParser::BlendFactorLabel);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendRTColorAlphaContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(375);
      match(EffectLabParser::RenderTargetID);
      setState(376);
      match(EffectLabParser::BlendFactorLabel);
      setState(377);
      match(EffectLabParser::BlendFactorLabel);
      setState(378);
      match(EffectLabParser::T__12);
      setState(379);
      match(EffectLabParser::BlendFactorLabel);
      setState(380);
      match(EffectLabParser::BlendFactorLabel);
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

//----------------- Pass_blend_opContext ------------------------------------------------------------------

EffectLabParser::Pass_blend_opContext::Pass_blend_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_blend_opContext::BlendOPLabel() {
  return getToken(EffectLabParser::BlendOPLabel, 0);
}


size_t EffectLabParser::Pass_blend_opContext::getRuleIndex() const {
  return EffectLabParser::RulePass_blend_op;
}

void EffectLabParser::Pass_blend_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_blend_op(this);
}

void EffectLabParser::Pass_blend_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_blend_op(this);
}


std::any EffectLabParser::Pass_blend_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_blend_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_blend_opContext* EffectLabParser::pass_blend_op() {
  Pass_blend_opContext *_localctx = _tracker.createInstance<Pass_blend_opContext>(_ctx, getState());
  enterRule(_localctx, 82, EffectLabParser::RulePass_blend_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    match(EffectLabParser::T__52);
    setState(384);
    match(EffectLabParser::BlendOPLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_alpha_to_maskContext ------------------------------------------------------------------

EffectLabParser::Pass_alpha_to_maskContext::Pass_alpha_to_maskContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_alpha_to_maskContext::AlphaToMaskLabel() {
  return getToken(EffectLabParser::AlphaToMaskLabel, 0);
}


size_t EffectLabParser::Pass_alpha_to_maskContext::getRuleIndex() const {
  return EffectLabParser::RulePass_alpha_to_mask;
}

void EffectLabParser::Pass_alpha_to_maskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_alpha_to_mask(this);
}

void EffectLabParser::Pass_alpha_to_maskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_alpha_to_mask(this);
}


std::any EffectLabParser::Pass_alpha_to_maskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_alpha_to_mask(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_alpha_to_maskContext* EffectLabParser::pass_alpha_to_mask() {
  Pass_alpha_to_maskContext *_localctx = _tracker.createInstance<Pass_alpha_to_maskContext>(_ctx, getState());
  enterRule(_localctx, 84, EffectLabParser::RulePass_alpha_to_mask);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(386);
    match(EffectLabParser::T__53);
    setState(387);
    match(EffectLabParser::AlphaToMaskLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_conservativeContext ------------------------------------------------------------------

EffectLabParser::Pass_conservativeContext::Pass_conservativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Pass_conservativeContext::BooleanLiteral() {
  return getToken(EffectLabParser::BooleanLiteral, 0);
}


size_t EffectLabParser::Pass_conservativeContext::getRuleIndex() const {
  return EffectLabParser::RulePass_conservative;
}

void EffectLabParser::Pass_conservativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_conservative(this);
}

void EffectLabParser::Pass_conservativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_conservative(this);
}


std::any EffectLabParser::Pass_conservativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_conservative(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_conservativeContext* EffectLabParser::pass_conservative() {
  Pass_conservativeContext *_localctx = _tracker.createInstance<Pass_conservativeContext>(_ctx, getState());
  enterRule(_localctx, 86, EffectLabParser::RulePass_conservative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(389);
    match(EffectLabParser::T__54);
    setState(390);
    match(EffectLabParser::BooleanLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_stencilContext ------------------------------------------------------------------

EffectLabParser::Pass_stencilContext::Pass_stencilContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EffectLabParser::Stencil_itemContext *> EffectLabParser::Pass_stencilContext::stencil_item() {
  return getRuleContexts<EffectLabParser::Stencil_itemContext>();
}

EffectLabParser::Stencil_itemContext* EffectLabParser::Pass_stencilContext::stencil_item(size_t i) {
  return getRuleContext<EffectLabParser::Stencil_itemContext>(i);
}


size_t EffectLabParser::Pass_stencilContext::getRuleIndex() const {
  return EffectLabParser::RulePass_stencil;
}

void EffectLabParser::Pass_stencilContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_stencil(this);
}

void EffectLabParser::Pass_stencilContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_stencil(this);
}


std::any EffectLabParser::Pass_stencilContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPass_stencil(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Pass_stencilContext* EffectLabParser::pass_stencil() {
  Pass_stencilContext *_localctx = _tracker.createInstance<Pass_stencilContext>(_ctx, getState());
  enterRule(_localctx, 88, EffectLabParser::RulePass_stencil);
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
    setState(392);
    match(EffectLabParser::T__55);
    setState(393);
    match(EffectLabParser::T__3);
    setState(395); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(394);
      stencil_item();
      setState(397); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la - 35) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 35)) & 68715282433) != 0);
    setState(399);
    match(EffectLabParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_block_itemContext ------------------------------------------------------------------

EffectLabParser::Pass_block_itemContext::Pass_block_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Pass_block_itemContext::getRuleIndex() const {
  return EffectLabParser::RulePass_block_item;
}

void EffectLabParser::Pass_block_itemContext::copyFrom(Pass_block_itemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PassStencilContext ------------------------------------------------------------------

EffectLabParser::Pass_stencilContext* EffectLabParser::PassStencilContext::pass_stencil() {
  return getRuleContext<EffectLabParser::Pass_stencilContext>(0);
}

EffectLabParser::PassStencilContext::PassStencilContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassStencilContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassStencil(this);
}
void EffectLabParser::PassStencilContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassStencil(this);
}

std::any EffectLabParser::PassStencilContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassStencil(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassColorMaskContext ------------------------------------------------------------------

EffectLabParser::Pass_color_maskContext* EffectLabParser::PassColorMaskContext::pass_color_mask() {
  return getRuleContext<EffectLabParser::Pass_color_maskContext>(0);
}

EffectLabParser::PassColorMaskContext::PassColorMaskContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassColorMaskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassColorMask(this);
}
void EffectLabParser::PassColorMaskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassColorMask(this);
}

std::any EffectLabParser::PassColorMaskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassColorMask(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassPixelShaderContext ------------------------------------------------------------------

EffectLabParser::Pass_pixel_shaderContext* EffectLabParser::PassPixelShaderContext::pass_pixel_shader() {
  return getRuleContext<EffectLabParser::Pass_pixel_shaderContext>(0);
}

EffectLabParser::PassPixelShaderContext::PassPixelShaderContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassPixelShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassPixelShader(this);
}
void EffectLabParser::PassPixelShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassPixelShader(this);
}

std::any EffectLabParser::PassPixelShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassPixelShader(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassZClipModeContext ------------------------------------------------------------------

EffectLabParser::Pass_zclip_modeContext* EffectLabParser::PassZClipModeContext::pass_zclip_mode() {
  return getRuleContext<EffectLabParser::Pass_zclip_modeContext>(0);
}

EffectLabParser::PassZClipModeContext::PassZClipModeContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassZClipModeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassZClipMode(this);
}
void EffectLabParser::PassZClipModeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassZClipMode(this);
}

std::any EffectLabParser::PassZClipModeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassZClipMode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassGeometryShaderContext ------------------------------------------------------------------

EffectLabParser::Pass_geometry_shaderContext* EffectLabParser::PassGeometryShaderContext::pass_geometry_shader() {
  return getRuleContext<EffectLabParser::Pass_geometry_shaderContext>(0);
}

EffectLabParser::PassGeometryShaderContext::PassGeometryShaderContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassGeometryShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassGeometryShader(this);
}
void EffectLabParser::PassGeometryShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassGeometryShader(this);
}

std::any EffectLabParser::PassGeometryShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassGeometryShader(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassShaderFeatureContext ------------------------------------------------------------------

EffectLabParser::Pass_shader_featureContext* EffectLabParser::PassShaderFeatureContext::pass_shader_feature() {
  return getRuleContext<EffectLabParser::Pass_shader_featureContext>(0);
}

EffectLabParser::PassShaderFeatureContext::PassShaderFeatureContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassShaderFeatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassShaderFeature(this);
}
void EffectLabParser::PassShaderFeatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassShaderFeature(this);
}

std::any EffectLabParser::PassShaderFeatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassShaderFeature(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassConservativeContext ------------------------------------------------------------------

EffectLabParser::Pass_conservativeContext* EffectLabParser::PassConservativeContext::pass_conservative() {
  return getRuleContext<EffectLabParser::Pass_conservativeContext>(0);
}

EffectLabParser::PassConservativeContext::PassConservativeContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassConservativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassConservative(this);
}
void EffectLabParser::PassConservativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassConservative(this);
}

std::any EffectLabParser::PassConservativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassConservative(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassDomainShaderContext ------------------------------------------------------------------

EffectLabParser::Pass_domain_shaderContext* EffectLabParser::PassDomainShaderContext::pass_domain_shader() {
  return getRuleContext<EffectLabParser::Pass_domain_shaderContext>(0);
}

EffectLabParser::PassDomainShaderContext::PassDomainShaderContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassDomainShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassDomainShader(this);
}
void EffectLabParser::PassDomainShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassDomainShader(this);
}

std::any EffectLabParser::PassDomainShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassDomainShader(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassRenderQueueContext ------------------------------------------------------------------

EffectLabParser::Pass_render_queueContext* EffectLabParser::PassRenderQueueContext::pass_render_queue() {
  return getRuleContext<EffectLabParser::Pass_render_queueContext>(0);
}

EffectLabParser::PassRenderQueueContext::PassRenderQueueContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassRenderQueueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassRenderQueue(this);
}
void EffectLabParser::PassRenderQueueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassRenderQueue(this);
}

std::any EffectLabParser::PassRenderQueueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassRenderQueue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassZWriteModeContext ------------------------------------------------------------------

EffectLabParser::Pass_zwrite_modeContext* EffectLabParser::PassZWriteModeContext::pass_zwrite_mode() {
  return getRuleContext<EffectLabParser::Pass_zwrite_modeContext>(0);
}

EffectLabParser::PassZWriteModeContext::PassZWriteModeContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassZWriteModeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassZWriteMode(this);
}
void EffectLabParser::PassZWriteModeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassZWriteMode(this);
}

std::any EffectLabParser::PassZWriteModeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassZWriteMode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendContext ------------------------------------------------------------------

EffectLabParser::Pass_blendContext* EffectLabParser::PassBlendContext::pass_blend() {
  return getRuleContext<EffectLabParser::Pass_blendContext>(0);
}

EffectLabParser::PassBlendContext::PassBlendContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlend(this);
}
void EffectLabParser::PassBlendContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlend(this);
}

std::any EffectLabParser::PassBlendContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlend(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassOffsetContext ------------------------------------------------------------------

EffectLabParser::Pass_offsetContext* EffectLabParser::PassOffsetContext::pass_offset() {
  return getRuleContext<EffectLabParser::Pass_offsetContext>(0);
}

EffectLabParser::PassOffsetContext::PassOffsetContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassOffsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassOffset(this);
}
void EffectLabParser::PassOffsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassOffset(this);
}

std::any EffectLabParser::PassOffsetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassOffset(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassHullShaderContext ------------------------------------------------------------------

EffectLabParser::Pass_hull_shaderContext* EffectLabParser::PassHullShaderContext::pass_hull_shader() {
  return getRuleContext<EffectLabParser::Pass_hull_shaderContext>(0);
}

EffectLabParser::PassHullShaderContext::PassHullShaderContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassHullShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassHullShader(this);
}
void EffectLabParser::PassHullShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassHullShader(this);
}

std::any EffectLabParser::PassHullShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassHullShader(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassCullModeContext ------------------------------------------------------------------

EffectLabParser::Pass_cull_modeContext* EffectLabParser::PassCullModeContext::pass_cull_mode() {
  return getRuleContext<EffectLabParser::Pass_cull_modeContext>(0);
}

EffectLabParser::PassCullModeContext::PassCullModeContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassCullModeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassCullMode(this);
}
void EffectLabParser::PassCullModeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassCullMode(this);
}

std::any EffectLabParser::PassCullModeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassCullMode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassZTestModeContext ------------------------------------------------------------------

EffectLabParser::Pass_ztest_modeContext* EffectLabParser::PassZTestModeContext::pass_ztest_mode() {
  return getRuleContext<EffectLabParser::Pass_ztest_modeContext>(0);
}

EffectLabParser::PassZTestModeContext::PassZTestModeContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassZTestModeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassZTestMode(this);
}
void EffectLabParser::PassZTestModeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassZTestMode(this);
}

std::any EffectLabParser::PassZTestModeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassZTestMode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassVertexShaderContext ------------------------------------------------------------------

EffectLabParser::Pass_vertex_shaderContext* EffectLabParser::PassVertexShaderContext::pass_vertex_shader() {
  return getRuleContext<EffectLabParser::Pass_vertex_shaderContext>(0);
}

EffectLabParser::PassVertexShaderContext::PassVertexShaderContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassVertexShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassVertexShader(this);
}
void EffectLabParser::PassVertexShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassVertexShader(this);
}

std::any EffectLabParser::PassVertexShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassVertexShader(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassBlendOpContext ------------------------------------------------------------------

EffectLabParser::Pass_blend_opContext* EffectLabParser::PassBlendOpContext::pass_blend_op() {
  return getRuleContext<EffectLabParser::Pass_blend_opContext>(0);
}

EffectLabParser::PassBlendOpContext::PassBlendOpContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassBlendOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassBlendOp(this);
}
void EffectLabParser::PassBlendOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassBlendOp(this);
}

std::any EffectLabParser::PassBlendOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassBlendOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassAlphaToMaskContext ------------------------------------------------------------------

EffectLabParser::Pass_alpha_to_maskContext* EffectLabParser::PassAlphaToMaskContext::pass_alpha_to_mask() {
  return getRuleContext<EffectLabParser::Pass_alpha_to_maskContext>(0);
}

EffectLabParser::PassAlphaToMaskContext::PassAlphaToMaskContext(Pass_block_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::PassAlphaToMaskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPassAlphaToMask(this);
}
void EffectLabParser::PassAlphaToMaskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPassAlphaToMask(this);
}

std::any EffectLabParser::PassAlphaToMaskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitPassAlphaToMask(this);
  else
    return visitor->visitChildren(this);
}
EffectLabParser::Pass_block_itemContext* EffectLabParser::pass_block_item() {
  Pass_block_itemContext *_localctx = _tracker.createInstance<Pass_block_itemContext>(_ctx, getState());
  enterRule(_localctx, 90, EffectLabParser::RulePass_block_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(419);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EffectLabParser::PassVertexShaderContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(401);
      pass_vertex_shader();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<EffectLabParser::PassGeometryShaderContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(402);
      pass_geometry_shader();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<EffectLabParser::PassHullShaderContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(403);
      pass_hull_shader();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EffectLabParser::PassDomainShaderContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(404);
      pass_domain_shader();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<EffectLabParser::PassPixelShaderContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(405);
      pass_pixel_shader();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<EffectLabParser::PassRenderQueueContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(406);
      pass_render_queue();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<EffectLabParser::PassShaderFeatureContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(407);
      pass_shader_feature();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<EffectLabParser::PassCullModeContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(408);
      pass_cull_mode();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<EffectLabParser::PassZClipModeContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(409);
      pass_zclip_mode();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<EffectLabParser::PassZTestModeContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(410);
      pass_ztest_mode();
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<EffectLabParser::PassZWriteModeContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(411);
      pass_zwrite_mode();
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<EffectLabParser::PassOffsetContext>(_localctx);
      enterOuterAlt(_localctx, 12);
      setState(412);
      pass_offset();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<EffectLabParser::PassColorMaskContext>(_localctx);
      enterOuterAlt(_localctx, 13);
      setState(413);
      pass_color_mask();
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendContext>(_localctx);
      enterOuterAlt(_localctx, 14);
      setState(414);
      pass_blend();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<EffectLabParser::PassBlendOpContext>(_localctx);
      enterOuterAlt(_localctx, 15);
      setState(415);
      pass_blend_op();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<EffectLabParser::PassAlphaToMaskContext>(_localctx);
      enterOuterAlt(_localctx, 16);
      setState(416);
      pass_alpha_to_mask();
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<EffectLabParser::PassConservativeContext>(_localctx);
      enterOuterAlt(_localctx, 17);
      setState(417);
      pass_conservative();
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<EffectLabParser::PassStencilContext>(_localctx);
      enterOuterAlt(_localctx, 18);
      setState(418);
      pass_stencil();
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

//----------------- Stencil_refContext ------------------------------------------------------------------

EffectLabParser::Stencil_refContext::Stencil_refContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_refContext::IntLiteral() {
  return getToken(EffectLabParser::IntLiteral, 0);
}


size_t EffectLabParser::Stencil_refContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_ref;
}

void EffectLabParser::Stencil_refContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_ref(this);
}

void EffectLabParser::Stencil_refContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_ref(this);
}


std::any EffectLabParser::Stencil_refContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_ref(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_refContext* EffectLabParser::stencil_ref() {
  Stencil_refContext *_localctx = _tracker.createInstance<Stencil_refContext>(_ctx, getState());
  enterRule(_localctx, 92, EffectLabParser::RuleStencil_ref);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    match(EffectLabParser::T__56);
    setState(422);
    match(EffectLabParser::IntLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_read_maskContext ------------------------------------------------------------------

EffectLabParser::Stencil_read_maskContext::Stencil_read_maskContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_read_maskContext::IntLiteral() {
  return getToken(EffectLabParser::IntLiteral, 0);
}


size_t EffectLabParser::Stencil_read_maskContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_read_mask;
}

void EffectLabParser::Stencil_read_maskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_read_mask(this);
}

void EffectLabParser::Stencil_read_maskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_read_mask(this);
}


std::any EffectLabParser::Stencil_read_maskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_read_mask(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_read_maskContext* EffectLabParser::stencil_read_mask() {
  Stencil_read_maskContext *_localctx = _tracker.createInstance<Stencil_read_maskContext>(_ctx, getState());
  enterRule(_localctx, 94, EffectLabParser::RuleStencil_read_mask);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(424);
    match(EffectLabParser::T__57);
    setState(425);
    match(EffectLabParser::IntLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_write_maskContext ------------------------------------------------------------------

EffectLabParser::Stencil_write_maskContext::Stencil_write_maskContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_write_maskContext::IntLiteral() {
  return getToken(EffectLabParser::IntLiteral, 0);
}


size_t EffectLabParser::Stencil_write_maskContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_write_mask;
}

void EffectLabParser::Stencil_write_maskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_write_mask(this);
}

void EffectLabParser::Stencil_write_maskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_write_mask(this);
}


std::any EffectLabParser::Stencil_write_maskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_write_mask(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_write_maskContext* EffectLabParser::stencil_write_mask() {
  Stencil_write_maskContext *_localctx = _tracker.createInstance<Stencil_write_maskContext>(_ctx, getState());
  enterRule(_localctx, 96, EffectLabParser::RuleStencil_write_mask);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(EffectLabParser::T__58);
    setState(428);
    match(EffectLabParser::IntLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_compContext ------------------------------------------------------------------

EffectLabParser::Stencil_compContext::Stencil_compContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_compContext::StencilCompareLabel() {
  return getToken(EffectLabParser::StencilCompareLabel, 0);
}


size_t EffectLabParser::Stencil_compContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_comp;
}

void EffectLabParser::Stencil_compContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_comp(this);
}

void EffectLabParser::Stencil_compContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_comp(this);
}


std::any EffectLabParser::Stencil_compContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_comp(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_compContext* EffectLabParser::stencil_comp() {
  Stencil_compContext *_localctx = _tracker.createInstance<Stencil_compContext>(_ctx, getState());
  enterRule(_localctx, 98, EffectLabParser::RuleStencil_comp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    match(EffectLabParser::T__59);
    setState(431);
    match(EffectLabParser::StencilCompareLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_pass_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_pass_opContext::Stencil_pass_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_pass_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_pass_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_pass_op;
}

void EffectLabParser::Stencil_pass_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_pass_op(this);
}

void EffectLabParser::Stencil_pass_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_pass_op(this);
}


std::any EffectLabParser::Stencil_pass_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_pass_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_pass_opContext* EffectLabParser::stencil_pass_op() {
  Stencil_pass_opContext *_localctx = _tracker.createInstance<Stencil_pass_opContext>(_ctx, getState());
  enterRule(_localctx, 100, EffectLabParser::RuleStencil_pass_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    match(EffectLabParser::T__34);
    setState(434);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_fail_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_opContext::Stencil_fail_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_fail_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_fail_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_fail_op;
}

void EffectLabParser::Stencil_fail_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_fail_op(this);
}

void EffectLabParser::Stencil_fail_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_fail_op(this);
}


std::any EffectLabParser::Stencil_fail_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_fail_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_fail_opContext* EffectLabParser::stencil_fail_op() {
  Stencil_fail_opContext *_localctx = _tracker.createInstance<Stencil_fail_opContext>(_ctx, getState());
  enterRule(_localctx, 102, EffectLabParser::RuleStencil_fail_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    match(EffectLabParser::T__60);
    setState(437);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_zfail_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_opContext::Stencil_zfail_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_zfail_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_zfail_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_zfail_op;
}

void EffectLabParser::Stencil_zfail_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_zfail_op(this);
}

void EffectLabParser::Stencil_zfail_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_zfail_op(this);
}


std::any EffectLabParser::Stencil_zfail_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_zfail_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_zfail_opContext* EffectLabParser::stencil_zfail_op() {
  Stencil_zfail_opContext *_localctx = _tracker.createInstance<Stencil_zfail_opContext>(_ctx, getState());
  enterRule(_localctx, 104, EffectLabParser::RuleStencil_zfail_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(439);
    match(EffectLabParser::T__61);
    setState(440);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_comp_back_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_comp_back_opContext::Stencil_comp_back_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_comp_back_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_comp_back_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_comp_back_op;
}

void EffectLabParser::Stencil_comp_back_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_comp_back_op(this);
}

void EffectLabParser::Stencil_comp_back_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_comp_back_op(this);
}


std::any EffectLabParser::Stencil_comp_back_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_comp_back_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_comp_back_opContext* EffectLabParser::stencil_comp_back_op() {
  Stencil_comp_back_opContext *_localctx = _tracker.createInstance<Stencil_comp_back_opContext>(_ctx, getState());
  enterRule(_localctx, 106, EffectLabParser::RuleStencil_comp_back_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    match(EffectLabParser::T__62);
    setState(443);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stancil_pass_back_opContext ------------------------------------------------------------------

EffectLabParser::Stancil_pass_back_opContext::Stancil_pass_back_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stancil_pass_back_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stancil_pass_back_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStancil_pass_back_op;
}

void EffectLabParser::Stancil_pass_back_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStancil_pass_back_op(this);
}

void EffectLabParser::Stancil_pass_back_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStancil_pass_back_op(this);
}


std::any EffectLabParser::Stancil_pass_back_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStancil_pass_back_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stancil_pass_back_opContext* EffectLabParser::stancil_pass_back_op() {
  Stancil_pass_back_opContext *_localctx = _tracker.createInstance<Stancil_pass_back_opContext>(_ctx, getState());
  enterRule(_localctx, 108, EffectLabParser::RuleStancil_pass_back_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(445);
    match(EffectLabParser::T__63);
    setState(446);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_fail_back_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_back_opContext::Stencil_fail_back_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_fail_back_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_fail_back_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_fail_back_op;
}

void EffectLabParser::Stencil_fail_back_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_fail_back_op(this);
}

void EffectLabParser::Stencil_fail_back_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_fail_back_op(this);
}


std::any EffectLabParser::Stencil_fail_back_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_fail_back_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_fail_back_opContext* EffectLabParser::stencil_fail_back_op() {
  Stencil_fail_back_opContext *_localctx = _tracker.createInstance<Stencil_fail_back_opContext>(_ctx, getState());
  enterRule(_localctx, 110, EffectLabParser::RuleStencil_fail_back_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(448);
    match(EffectLabParser::T__64);
    setState(449);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_zfail_back_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_back_opContext::Stencil_zfail_back_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_zfail_back_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_zfail_back_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_zfail_back_op;
}

void EffectLabParser::Stencil_zfail_back_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_zfail_back_op(this);
}

void EffectLabParser::Stencil_zfail_back_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_zfail_back_op(this);
}


std::any EffectLabParser::Stencil_zfail_back_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_zfail_back_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_zfail_back_opContext* EffectLabParser::stencil_zfail_back_op() {
  Stencil_zfail_back_opContext *_localctx = _tracker.createInstance<Stencil_zfail_back_opContext>(_ctx, getState());
  enterRule(_localctx, 112, EffectLabParser::RuleStencil_zfail_back_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(451);
    match(EffectLabParser::T__65);
    setState(452);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_comp_front_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_comp_front_opContext::Stencil_comp_front_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_comp_front_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_comp_front_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_comp_front_op;
}

void EffectLabParser::Stencil_comp_front_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_comp_front_op(this);
}

void EffectLabParser::Stencil_comp_front_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_comp_front_op(this);
}


std::any EffectLabParser::Stencil_comp_front_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_comp_front_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_comp_front_opContext* EffectLabParser::stencil_comp_front_op() {
  Stencil_comp_front_opContext *_localctx = _tracker.createInstance<Stencil_comp_front_opContext>(_ctx, getState());
  enterRule(_localctx, 114, EffectLabParser::RuleStencil_comp_front_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(454);
    match(EffectLabParser::T__66);
    setState(455);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stancil_pass_front_opContext ------------------------------------------------------------------

EffectLabParser::Stancil_pass_front_opContext::Stancil_pass_front_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stancil_pass_front_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stancil_pass_front_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStancil_pass_front_op;
}

void EffectLabParser::Stancil_pass_front_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStancil_pass_front_op(this);
}

void EffectLabParser::Stancil_pass_front_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStancil_pass_front_op(this);
}


std::any EffectLabParser::Stancil_pass_front_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStancil_pass_front_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stancil_pass_front_opContext* EffectLabParser::stancil_pass_front_op() {
  Stancil_pass_front_opContext *_localctx = _tracker.createInstance<Stancil_pass_front_opContext>(_ctx, getState());
  enterRule(_localctx, 116, EffectLabParser::RuleStancil_pass_front_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(457);
    match(EffectLabParser::T__67);
    setState(458);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_fail_front_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_front_opContext::Stencil_fail_front_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_fail_front_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_fail_front_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_fail_front_op;
}

void EffectLabParser::Stencil_fail_front_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_fail_front_op(this);
}

void EffectLabParser::Stencil_fail_front_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_fail_front_op(this);
}


std::any EffectLabParser::Stencil_fail_front_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_fail_front_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_fail_front_opContext* EffectLabParser::stencil_fail_front_op() {
  Stencil_fail_front_opContext *_localctx = _tracker.createInstance<Stencil_fail_front_opContext>(_ctx, getState());
  enterRule(_localctx, 118, EffectLabParser::RuleStencil_fail_front_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(460);
    match(EffectLabParser::T__68);
    setState(461);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_zfail_front_opContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_front_opContext::Stencil_zfail_front_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EffectLabParser::Stencil_zfail_front_opContext::StencilOpLabel() {
  return getToken(EffectLabParser::StencilOpLabel, 0);
}


size_t EffectLabParser::Stencil_zfail_front_opContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_zfail_front_op;
}

void EffectLabParser::Stencil_zfail_front_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencil_zfail_front_op(this);
}

void EffectLabParser::Stencil_zfail_front_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencil_zfail_front_op(this);
}


std::any EffectLabParser::Stencil_zfail_front_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencil_zfail_front_op(this);
  else
    return visitor->visitChildren(this);
}

EffectLabParser::Stencil_zfail_front_opContext* EffectLabParser::stencil_zfail_front_op() {
  Stencil_zfail_front_opContext *_localctx = _tracker.createInstance<Stencil_zfail_front_opContext>(_ctx, getState());
  enterRule(_localctx, 120, EffectLabParser::RuleStencil_zfail_front_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(463);
    match(EffectLabParser::T__69);
    setState(464);
    match(EffectLabParser::StencilOpLabel);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stencil_itemContext ------------------------------------------------------------------

EffectLabParser::Stencil_itemContext::Stencil_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EffectLabParser::Stencil_itemContext::getRuleIndex() const {
  return EffectLabParser::RuleStencil_item;
}

void EffectLabParser::Stencil_itemContext::copyFrom(Stencil_itemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StencilCompBackOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_comp_back_opContext* EffectLabParser::StencilCompBackOpContext::stencil_comp_back_op() {
  return getRuleContext<EffectLabParser::Stencil_comp_back_opContext>(0);
}

EffectLabParser::StencilCompBackOpContext::StencilCompBackOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilCompBackOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilCompBackOp(this);
}
void EffectLabParser::StencilCompBackOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilCompBackOp(this);
}

std::any EffectLabParser::StencilCompBackOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilCompBackOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilReadMaskContext ------------------------------------------------------------------

EffectLabParser::Stencil_read_maskContext* EffectLabParser::StencilReadMaskContext::stencil_read_mask() {
  return getRuleContext<EffectLabParser::Stencil_read_maskContext>(0);
}

EffectLabParser::StencilReadMaskContext::StencilReadMaskContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilReadMaskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilReadMask(this);
}
void EffectLabParser::StencilReadMaskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilReadMask(this);
}

std::any EffectLabParser::StencilReadMaskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilReadMask(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilRefContext ------------------------------------------------------------------

EffectLabParser::Stencil_refContext* EffectLabParser::StencilRefContext::stencil_ref() {
  return getRuleContext<EffectLabParser::Stencil_refContext>(0);
}

EffectLabParser::StencilRefContext::StencilRefContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilRef(this);
}
void EffectLabParser::StencilRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilRef(this);
}

std::any EffectLabParser::StencilRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilRef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilPassOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_pass_opContext* EffectLabParser::StencilPassOpContext::stencil_pass_op() {
  return getRuleContext<EffectLabParser::Stencil_pass_opContext>(0);
}

EffectLabParser::StencilPassOpContext::StencilPassOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilPassOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilPassOp(this);
}
void EffectLabParser::StencilPassOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilPassOp(this);
}

std::any EffectLabParser::StencilPassOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilPassOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilFailOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_opContext* EffectLabParser::StencilFailOpContext::stencil_fail_op() {
  return getRuleContext<EffectLabParser::Stencil_fail_opContext>(0);
}

EffectLabParser::StencilFailOpContext::StencilFailOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilFailOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilFailOp(this);
}
void EffectLabParser::StencilFailOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilFailOp(this);
}

std::any EffectLabParser::StencilFailOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilFailOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilCompFrontOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_comp_front_opContext* EffectLabParser::StencilCompFrontOpContext::stencil_comp_front_op() {
  return getRuleContext<EffectLabParser::Stencil_comp_front_opContext>(0);
}

EffectLabParser::StencilCompFrontOpContext::StencilCompFrontOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilCompFrontOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilCompFrontOp(this);
}
void EffectLabParser::StencilCompFrontOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilCompFrontOp(this);
}

std::any EffectLabParser::StencilCompFrontOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilCompFrontOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilPassBackOpContext ------------------------------------------------------------------

EffectLabParser::Stancil_pass_back_opContext* EffectLabParser::StencilPassBackOpContext::stancil_pass_back_op() {
  return getRuleContext<EffectLabParser::Stancil_pass_back_opContext>(0);
}

EffectLabParser::StencilPassBackOpContext::StencilPassBackOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilPassBackOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilPassBackOp(this);
}
void EffectLabParser::StencilPassBackOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilPassBackOp(this);
}

std::any EffectLabParser::StencilPassBackOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilPassBackOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilWriteMaskContext ------------------------------------------------------------------

EffectLabParser::Stencil_write_maskContext* EffectLabParser::StencilWriteMaskContext::stencil_write_mask() {
  return getRuleContext<EffectLabParser::Stencil_write_maskContext>(0);
}

EffectLabParser::StencilWriteMaskContext::StencilWriteMaskContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilWriteMaskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilWriteMask(this);
}
void EffectLabParser::StencilWriteMaskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilWriteMask(this);
}

std::any EffectLabParser::StencilWriteMaskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilWriteMask(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilFailBackOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_back_opContext* EffectLabParser::StencilFailBackOpContext::stencil_fail_back_op() {
  return getRuleContext<EffectLabParser::Stencil_fail_back_opContext>(0);
}

EffectLabParser::StencilFailBackOpContext::StencilFailBackOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilFailBackOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilFailBackOp(this);
}
void EffectLabParser::StencilFailBackOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilFailBackOp(this);
}

std::any EffectLabParser::StencilFailBackOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilFailBackOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilPassFrontOpContext ------------------------------------------------------------------

EffectLabParser::Stancil_pass_front_opContext* EffectLabParser::StencilPassFrontOpContext::stancil_pass_front_op() {
  return getRuleContext<EffectLabParser::Stancil_pass_front_opContext>(0);
}

EffectLabParser::StencilPassFrontOpContext::StencilPassFrontOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilPassFrontOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilPassFrontOp(this);
}
void EffectLabParser::StencilPassFrontOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilPassFrontOp(this);
}

std::any EffectLabParser::StencilPassFrontOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilPassFrontOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilFailFrontOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_fail_front_opContext* EffectLabParser::StencilFailFrontOpContext::stencil_fail_front_op() {
  return getRuleContext<EffectLabParser::Stencil_fail_front_opContext>(0);
}

EffectLabParser::StencilFailFrontOpContext::StencilFailFrontOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilFailFrontOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilFailFrontOp(this);
}
void EffectLabParser::StencilFailFrontOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilFailFrontOp(this);
}

std::any EffectLabParser::StencilFailFrontOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilFailFrontOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilZFailOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_opContext* EffectLabParser::StencilZFailOpContext::stencil_zfail_op() {
  return getRuleContext<EffectLabParser::Stencil_zfail_opContext>(0);
}

EffectLabParser::StencilZFailOpContext::StencilZFailOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilZFailOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilZFailOp(this);
}
void EffectLabParser::StencilZFailOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilZFailOp(this);
}

std::any EffectLabParser::StencilZFailOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilZFailOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilCompContext ------------------------------------------------------------------

EffectLabParser::Stencil_compContext* EffectLabParser::StencilCompContext::stencil_comp() {
  return getRuleContext<EffectLabParser::Stencil_compContext>(0);
}

EffectLabParser::StencilCompContext::StencilCompContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilCompContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilComp(this);
}
void EffectLabParser::StencilCompContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilComp(this);
}

std::any EffectLabParser::StencilCompContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilComp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilZFailBackOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_back_opContext* EffectLabParser::StencilZFailBackOpContext::stencil_zfail_back_op() {
  return getRuleContext<EffectLabParser::Stencil_zfail_back_opContext>(0);
}

EffectLabParser::StencilZFailBackOpContext::StencilZFailBackOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilZFailBackOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilZFailBackOp(this);
}
void EffectLabParser::StencilZFailBackOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilZFailBackOp(this);
}

std::any EffectLabParser::StencilZFailBackOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilZFailBackOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StencilZFailFrontOpContext ------------------------------------------------------------------

EffectLabParser::Stencil_zfail_front_opContext* EffectLabParser::StencilZFailFrontOpContext::stencil_zfail_front_op() {
  return getRuleContext<EffectLabParser::Stencil_zfail_front_opContext>(0);
}

EffectLabParser::StencilZFailFrontOpContext::StencilZFailFrontOpContext(Stencil_itemContext *ctx) { copyFrom(ctx); }

void EffectLabParser::StencilZFailFrontOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStencilZFailFrontOp(this);
}
void EffectLabParser::StencilZFailFrontOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EffectLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStencilZFailFrontOp(this);
}

std::any EffectLabParser::StencilZFailFrontOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EffectLabVisitor*>(visitor))
    return parserVisitor->visitStencilZFailFrontOp(this);
  else
    return visitor->visitChildren(this);
}
EffectLabParser::Stencil_itemContext* EffectLabParser::stencil_item() {
  Stencil_itemContext *_localctx = _tracker.createInstance<Stencil_itemContext>(_ctx, getState());
  enterRule(_localctx, 122, EffectLabParser::RuleStencil_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(481);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EffectLabParser::T__56: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilRefContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(466);
        stencil_ref();
        break;
      }

      case EffectLabParser::T__57: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilReadMaskContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(467);
        stencil_read_mask();
        break;
      }

      case EffectLabParser::T__58: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilWriteMaskContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(468);
        stencil_write_mask();
        break;
      }

      case EffectLabParser::T__59: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilCompContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(469);
        stencil_comp();
        break;
      }

      case EffectLabParser::T__34: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilPassOpContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(470);
        stencil_pass_op();
        break;
      }

      case EffectLabParser::T__60: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilFailOpContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(471);
        stencil_fail_op();
        break;
      }

      case EffectLabParser::T__61: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilZFailOpContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(472);
        stencil_zfail_op();
        break;
      }

      case EffectLabParser::T__62: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilCompBackOpContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(473);
        stencil_comp_back_op();
        break;
      }

      case EffectLabParser::T__63: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilPassBackOpContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(474);
        stancil_pass_back_op();
        break;
      }

      case EffectLabParser::T__64: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilFailBackOpContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(475);
        stencil_fail_back_op();
        break;
      }

      case EffectLabParser::T__65: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilZFailBackOpContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(476);
        stencil_zfail_back_op();
        break;
      }

      case EffectLabParser::T__66: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilCompFrontOpContext>(_localctx);
        enterOuterAlt(_localctx, 12);
        setState(477);
        stencil_comp_front_op();
        break;
      }

      case EffectLabParser::T__67: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilPassFrontOpContext>(_localctx);
        enterOuterAlt(_localctx, 13);
        setState(478);
        stancil_pass_front_op();
        break;
      }

      case EffectLabParser::T__68: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilFailFrontOpContext>(_localctx);
        enterOuterAlt(_localctx, 14);
        setState(479);
        stencil_fail_front_op();
        break;
      }

      case EffectLabParser::T__69: {
        _localctx = _tracker.createInstance<EffectLabParser::StencilZFailFrontOpContext>(_localctx);
        enterOuterAlt(_localctx, 15);
        setState(480);
        stencil_zfail_front_op();
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

void EffectLabParser::initialize() {
  ::antlr4::internal::call_once(effectlabParserOnceFlag, effectlabParserInitialize);
}
