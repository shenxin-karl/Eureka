
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabListener.h"


namespace Eureka::ParserDetails {

/**
 * This class provides an empty implementation of EffectLabListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  EffectLabBaseListener : public EffectLabListener {
public:

  virtual void enterEffect(EffectLabParser::EffectContext * /*ctx*/) override { }
  virtual void exitEffect(EffectLabParser::EffectContext * /*ctx*/) override { }

  virtual void enterProperty_block(EffectLabParser::Property_blockContext * /*ctx*/) override { }
  virtual void exitProperty_block(EffectLabParser::Property_blockContext * /*ctx*/) override { }

  virtual void enterHlsl_include_block(EffectLabParser::Hlsl_include_blockContext * /*ctx*/) override { }
  virtual void exitHlsl_include_block(EffectLabParser::Hlsl_include_blockContext * /*ctx*/) override { }

  virtual void enterProperty_name(EffectLabParser::Property_nameContext * /*ctx*/) override { }
  virtual void exitProperty_name(EffectLabParser::Property_nameContext * /*ctx*/) override { }

  virtual void enterProperty_description(EffectLabParser::Property_descriptionContext * /*ctx*/) override { }
  virtual void exitProperty_description(EffectLabParser::Property_descriptionContext * /*ctx*/) override { }

  virtual void enterPropertyItemBool(EffectLabParser::PropertyItemBoolContext * /*ctx*/) override { }
  virtual void exitPropertyItemBool(EffectLabParser::PropertyItemBoolContext * /*ctx*/) override { }

  virtual void enterPropertyItemInt(EffectLabParser::PropertyItemIntContext * /*ctx*/) override { }
  virtual void exitPropertyItemInt(EffectLabParser::PropertyItemIntContext * /*ctx*/) override { }

  virtual void enterPropertyItemRange(EffectLabParser::PropertyItemRangeContext * /*ctx*/) override { }
  virtual void exitPropertyItemRange(EffectLabParser::PropertyItemRangeContext * /*ctx*/) override { }

  virtual void enterPropertyItemFloat(EffectLabParser::PropertyItemFloatContext * /*ctx*/) override { }
  virtual void exitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext * /*ctx*/) override { }

  virtual void enterPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context * /*ctx*/) override { }
  virtual void exitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context * /*ctx*/) override { }

  virtual void enterPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context * /*ctx*/) override { }
  virtual void exitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context * /*ctx*/) override { }

  virtual void enterPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context * /*ctx*/) override { }
  virtual void exitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context * /*ctx*/) override { }

  virtual void enterPropertyItemTexture(EffectLabParser::PropertyItemTextureContext * /*ctx*/) override { }
  virtual void exitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext * /*ctx*/) override { }

  virtual void enterPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext * /*ctx*/) override { }
  virtual void exitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext * /*ctx*/) override { }

  virtual void enterProperty_bool_type(EffectLabParser::Property_bool_typeContext * /*ctx*/) override { }
  virtual void exitProperty_bool_type(EffectLabParser::Property_bool_typeContext * /*ctx*/) override { }

  virtual void enterProperty_int_type(EffectLabParser::Property_int_typeContext * /*ctx*/) override { }
  virtual void exitProperty_int_type(EffectLabParser::Property_int_typeContext * /*ctx*/) override { }

  virtual void enterProperty_range_type(EffectLabParser::Property_range_typeContext * /*ctx*/) override { }
  virtual void exitProperty_range_type(EffectLabParser::Property_range_typeContext * /*ctx*/) override { }

  virtual void enterProperty_float_type(EffectLabParser::Property_float_typeContext * /*ctx*/) override { }
  virtual void exitProperty_float_type(EffectLabParser::Property_float_typeContext * /*ctx*/) override { }

  virtual void enterProperty_float2_type(EffectLabParser::Property_float2_typeContext * /*ctx*/) override { }
  virtual void exitProperty_float2_type(EffectLabParser::Property_float2_typeContext * /*ctx*/) override { }

  virtual void enterProperty_float3_type(EffectLabParser::Property_float3_typeContext * /*ctx*/) override { }
  virtual void exitProperty_float3_type(EffectLabParser::Property_float3_typeContext * /*ctx*/) override { }

  virtual void enterProperty_float4_type(EffectLabParser::Property_float4_typeContext * /*ctx*/) override { }
  virtual void exitProperty_float4_type(EffectLabParser::Property_float4_typeContext * /*ctx*/) override { }

  virtual void enterProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext * /*ctx*/) override { }
  virtual void exitProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext * /*ctx*/) override { }

  virtual void enterProperty_matrix_type(EffectLabParser::Property_matrix_typeContext * /*ctx*/) override { }
  virtual void exitProperty_matrix_type(EffectLabParser::Property_matrix_typeContext * /*ctx*/) override { }

  virtual void enterProperty_range_val(EffectLabParser::Property_range_valContext * /*ctx*/) override { }
  virtual void exitProperty_range_val(EffectLabParser::Property_range_valContext * /*ctx*/) override { }

  virtual void enterProperty_bool_val(EffectLabParser::Property_bool_valContext * /*ctx*/) override { }
  virtual void exitProperty_bool_val(EffectLabParser::Property_bool_valContext * /*ctx*/) override { }

  virtual void enterProperty_int_val(EffectLabParser::Property_int_valContext * /*ctx*/) override { }
  virtual void exitProperty_int_val(EffectLabParser::Property_int_valContext * /*ctx*/) override { }

  virtual void enterProperty_float_val(EffectLabParser::Property_float_valContext * /*ctx*/) override { }
  virtual void exitProperty_float_val(EffectLabParser::Property_float_valContext * /*ctx*/) override { }

  virtual void enterProperty_float2_val(EffectLabParser::Property_float2_valContext * /*ctx*/) override { }
  virtual void exitProperty_float2_val(EffectLabParser::Property_float2_valContext * /*ctx*/) override { }

  virtual void enterProperty_float3_val(EffectLabParser::Property_float3_valContext * /*ctx*/) override { }
  virtual void exitProperty_float3_val(EffectLabParser::Property_float3_valContext * /*ctx*/) override { }

  virtual void enterProperty_float4_val(EffectLabParser::Property_float4_valContext * /*ctx*/) override { }
  virtual void exitProperty_float4_val(EffectLabParser::Property_float4_valContext * /*ctx*/) override { }

  virtual void enterProperty_matrix_val(EffectLabParser::Property_matrix_valContext * /*ctx*/) override { }
  virtual void exitProperty_matrix_val(EffectLabParser::Property_matrix_valContext * /*ctx*/) override { }

  virtual void enterProperty_texture_val(EffectLabParser::Property_texture_valContext * /*ctx*/) override { }
  virtual void exitProperty_texture_val(EffectLabParser::Property_texture_valContext * /*ctx*/) override { }

  virtual void enterNumber_val(EffectLabParser::Number_valContext * /*ctx*/) override { }
  virtual void exitNumber_val(EffectLabParser::Number_valContext * /*ctx*/) override { }

  virtual void enterPass(EffectLabParser::PassContext * /*ctx*/) override { }
  virtual void exitPass(EffectLabParser::PassContext * /*ctx*/) override { }

  virtual void enterPass_tag(EffectLabParser::Pass_tagContext * /*ctx*/) override { }
  virtual void exitPass_tag(EffectLabParser::Pass_tagContext * /*ctx*/) override { }

  virtual void enterPassSourcePath(EffectLabParser::PassSourcePathContext * /*ctx*/) override { }
  virtual void exitPassSourcePath(EffectLabParser::PassSourcePathContext * /*ctx*/) override { }

  virtual void enterPassVertexShader(EffectLabParser::PassVertexShaderContext * /*ctx*/) override { }
  virtual void exitPassVertexShader(EffectLabParser::PassVertexShaderContext * /*ctx*/) override { }

  virtual void enterPassGeometryShader(EffectLabParser::PassGeometryShaderContext * /*ctx*/) override { }
  virtual void exitPassGeometryShader(EffectLabParser::PassGeometryShaderContext * /*ctx*/) override { }

  virtual void enterPassHullShader(EffectLabParser::PassHullShaderContext * /*ctx*/) override { }
  virtual void exitPassHullShader(EffectLabParser::PassHullShaderContext * /*ctx*/) override { }

  virtual void enterPassDomainShader(EffectLabParser::PassDomainShaderContext * /*ctx*/) override { }
  virtual void exitPassDomainShader(EffectLabParser::PassDomainShaderContext * /*ctx*/) override { }

  virtual void enterPassPixelShader(EffectLabParser::PassPixelShaderContext * /*ctx*/) override { }
  virtual void exitPassPixelShader(EffectLabParser::PassPixelShaderContext * /*ctx*/) override { }

  virtual void enterPassRenderQueue(EffectLabParser::PassRenderQueueContext * /*ctx*/) override { }
  virtual void exitPassRenderQueue(EffectLabParser::PassRenderQueueContext * /*ctx*/) override { }

  virtual void enterPassShaderFeature(EffectLabParser::PassShaderFeatureContext * /*ctx*/) override { }
  virtual void exitPassShaderFeature(EffectLabParser::PassShaderFeatureContext * /*ctx*/) override { }

  virtual void enterPassCullMode(EffectLabParser::PassCullModeContext * /*ctx*/) override { }
  virtual void exitPassCullMode(EffectLabParser::PassCullModeContext * /*ctx*/) override { }

  virtual void enterPassZClipMode(EffectLabParser::PassZClipModeContext * /*ctx*/) override { }
  virtual void exitPassZClipMode(EffectLabParser::PassZClipModeContext * /*ctx*/) override { }

  virtual void enterPassZTestMode(EffectLabParser::PassZTestModeContext * /*ctx*/) override { }
  virtual void exitPassZTestMode(EffectLabParser::PassZTestModeContext * /*ctx*/) override { }

  virtual void enterPassZWriteMode(EffectLabParser::PassZWriteModeContext * /*ctx*/) override { }
  virtual void exitPassZWriteMode(EffectLabParser::PassZWriteModeContext * /*ctx*/) override { }

  virtual void enterPassOffset(EffectLabParser::PassOffsetContext * /*ctx*/) override { }
  virtual void exitPassOffset(EffectLabParser::PassOffsetContext * /*ctx*/) override { }

  virtual void enterPassColorMask(EffectLabParser::PassColorMaskContext * /*ctx*/) override { }
  virtual void exitPassColorMask(EffectLabParser::PassColorMaskContext * /*ctx*/) override { }

  virtual void enterPassBlend(EffectLabParser::PassBlendContext * /*ctx*/) override { }
  virtual void exitPassBlend(EffectLabParser::PassBlendContext * /*ctx*/) override { }

  virtual void enterPassBlendOp(EffectLabParser::PassBlendOpContext * /*ctx*/) override { }
  virtual void exitPassBlendOp(EffectLabParser::PassBlendOpContext * /*ctx*/) override { }

  virtual void enterPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext * /*ctx*/) override { }
  virtual void exitPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext * /*ctx*/) override { }

  virtual void enterPassConservative(EffectLabParser::PassConservativeContext * /*ctx*/) override { }
  virtual void exitPassConservative(EffectLabParser::PassConservativeContext * /*ctx*/) override { }

  virtual void enterPassStencil(EffectLabParser::PassStencilContext * /*ctx*/) override { }
  virtual void exitPassStencil(EffectLabParser::PassStencilContext * /*ctx*/) override { }

  virtual void enterPass_source_path(EffectLabParser::Pass_source_pathContext * /*ctx*/) override { }
  virtual void exitPass_source_path(EffectLabParser::Pass_source_pathContext * /*ctx*/) override { }

  virtual void enterPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext * /*ctx*/) override { }
  virtual void exitPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext * /*ctx*/) override { }

  virtual void enterPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext * /*ctx*/) override { }
  virtual void exitPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext * /*ctx*/) override { }

  virtual void enterPass_hull_shader(EffectLabParser::Pass_hull_shaderContext * /*ctx*/) override { }
  virtual void exitPass_hull_shader(EffectLabParser::Pass_hull_shaderContext * /*ctx*/) override { }

  virtual void enterPass_domain_shader(EffectLabParser::Pass_domain_shaderContext * /*ctx*/) override { }
  virtual void exitPass_domain_shader(EffectLabParser::Pass_domain_shaderContext * /*ctx*/) override { }

  virtual void enterPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext * /*ctx*/) override { }
  virtual void exitPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext * /*ctx*/) override { }

  virtual void enterPass_render_queue(EffectLabParser::Pass_render_queueContext * /*ctx*/) override { }
  virtual void exitPass_render_queue(EffectLabParser::Pass_render_queueContext * /*ctx*/) override { }

  virtual void enterPass_shader_feature(EffectLabParser::Pass_shader_featureContext * /*ctx*/) override { }
  virtual void exitPass_shader_feature(EffectLabParser::Pass_shader_featureContext * /*ctx*/) override { }

  virtual void enterPass_cull_mode(EffectLabParser::Pass_cull_modeContext * /*ctx*/) override { }
  virtual void exitPass_cull_mode(EffectLabParser::Pass_cull_modeContext * /*ctx*/) override { }

  virtual void enterPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext * /*ctx*/) override { }
  virtual void exitPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext * /*ctx*/) override { }

  virtual void enterPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext * /*ctx*/) override { }
  virtual void exitPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext * /*ctx*/) override { }

  virtual void enterPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext * /*ctx*/) override { }
  virtual void exitPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext * /*ctx*/) override { }

  virtual void enterPass_offset(EffectLabParser::Pass_offsetContext * /*ctx*/) override { }
  virtual void exitPass_offset(EffectLabParser::Pass_offsetContext * /*ctx*/) override { }

  virtual void enterPass_color_mask(EffectLabParser::Pass_color_maskContext * /*ctx*/) override { }
  virtual void exitPass_color_mask(EffectLabParser::Pass_color_maskContext * /*ctx*/) override { }

  virtual void enterPassBlendOff(EffectLabParser::PassBlendOffContext * /*ctx*/) override { }
  virtual void exitPassBlendOff(EffectLabParser::PassBlendOffContext * /*ctx*/) override { }

  virtual void enterPassBlendRTOff(EffectLabParser::PassBlendRTOffContext * /*ctx*/) override { }
  virtual void exitPassBlendRTOff(EffectLabParser::PassBlendRTOffContext * /*ctx*/) override { }

  virtual void enterPassBlendColor(EffectLabParser::PassBlendColorContext * /*ctx*/) override { }
  virtual void exitPassBlendColor(EffectLabParser::PassBlendColorContext * /*ctx*/) override { }

  virtual void enterPassBlendRTColor(EffectLabParser::PassBlendRTColorContext * /*ctx*/) override { }
  virtual void exitPassBlendRTColor(EffectLabParser::PassBlendRTColorContext * /*ctx*/) override { }

  virtual void enterPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext * /*ctx*/) override { }
  virtual void exitPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext * /*ctx*/) override { }

  virtual void enterPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext * /*ctx*/) override { }
  virtual void exitPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext * /*ctx*/) override { }

  virtual void enterPass_blend_op(EffectLabParser::Pass_blend_opContext * /*ctx*/) override { }
  virtual void exitPass_blend_op(EffectLabParser::Pass_blend_opContext * /*ctx*/) override { }

  virtual void enterPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext * /*ctx*/) override { }
  virtual void exitPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext * /*ctx*/) override { }

  virtual void enterPass_conservative(EffectLabParser::Pass_conservativeContext * /*ctx*/) override { }
  virtual void exitPass_conservative(EffectLabParser::Pass_conservativeContext * /*ctx*/) override { }

  virtual void enterPass_stencil(EffectLabParser::Pass_stencilContext * /*ctx*/) override { }
  virtual void exitPass_stencil(EffectLabParser::Pass_stencilContext * /*ctx*/) override { }

  virtual void enterStencilRef(EffectLabParser::StencilRefContext * /*ctx*/) override { }
  virtual void exitStencilRef(EffectLabParser::StencilRefContext * /*ctx*/) override { }

  virtual void enterStencilReadMask(EffectLabParser::StencilReadMaskContext * /*ctx*/) override { }
  virtual void exitStencilReadMask(EffectLabParser::StencilReadMaskContext * /*ctx*/) override { }

  virtual void enterStencilWriteMask(EffectLabParser::StencilWriteMaskContext * /*ctx*/) override { }
  virtual void exitStencilWriteMask(EffectLabParser::StencilWriteMaskContext * /*ctx*/) override { }

  virtual void enterStencilComp(EffectLabParser::StencilCompContext * /*ctx*/) override { }
  virtual void exitStencilComp(EffectLabParser::StencilCompContext * /*ctx*/) override { }

  virtual void enterStencilPassOp(EffectLabParser::StencilPassOpContext * /*ctx*/) override { }
  virtual void exitStencilPassOp(EffectLabParser::StencilPassOpContext * /*ctx*/) override { }

  virtual void enterStencilFailOp(EffectLabParser::StencilFailOpContext * /*ctx*/) override { }
  virtual void exitStencilFailOp(EffectLabParser::StencilFailOpContext * /*ctx*/) override { }

  virtual void enterStencilZFailOp(EffectLabParser::StencilZFailOpContext * /*ctx*/) override { }
  virtual void exitStencilZFailOp(EffectLabParser::StencilZFailOpContext * /*ctx*/) override { }

  virtual void enterStencilCompBackOp(EffectLabParser::StencilCompBackOpContext * /*ctx*/) override { }
  virtual void exitStencilCompBackOp(EffectLabParser::StencilCompBackOpContext * /*ctx*/) override { }

  virtual void enterStencilPassBackOp(EffectLabParser::StencilPassBackOpContext * /*ctx*/) override { }
  virtual void exitStencilPassBackOp(EffectLabParser::StencilPassBackOpContext * /*ctx*/) override { }

  virtual void enterStencilFailBackOp(EffectLabParser::StencilFailBackOpContext * /*ctx*/) override { }
  virtual void exitStencilFailBackOp(EffectLabParser::StencilFailBackOpContext * /*ctx*/) override { }

  virtual void enterStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext * /*ctx*/) override { }
  virtual void exitStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext * /*ctx*/) override { }

  virtual void enterStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext * /*ctx*/) override { }
  virtual void exitStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext * /*ctx*/) override { }

  virtual void enterStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext * /*ctx*/) override { }
  virtual void exitStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext * /*ctx*/) override { }

  virtual void enterStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext * /*ctx*/) override { }
  virtual void exitStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext * /*ctx*/) override { }

  virtual void enterStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext * /*ctx*/) override { }
  virtual void exitStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext * /*ctx*/) override { }

  virtual void enterStencil_ref(EffectLabParser::Stencil_refContext * /*ctx*/) override { }
  virtual void exitStencil_ref(EffectLabParser::Stencil_refContext * /*ctx*/) override { }

  virtual void enterStencil_read_mask(EffectLabParser::Stencil_read_maskContext * /*ctx*/) override { }
  virtual void exitStencil_read_mask(EffectLabParser::Stencil_read_maskContext * /*ctx*/) override { }

  virtual void enterStencil_write_mask(EffectLabParser::Stencil_write_maskContext * /*ctx*/) override { }
  virtual void exitStencil_write_mask(EffectLabParser::Stencil_write_maskContext * /*ctx*/) override { }

  virtual void enterStencil_comp(EffectLabParser::Stencil_compContext * /*ctx*/) override { }
  virtual void exitStencil_comp(EffectLabParser::Stencil_compContext * /*ctx*/) override { }

  virtual void enterStencil_pass_op(EffectLabParser::Stencil_pass_opContext * /*ctx*/) override { }
  virtual void exitStencil_pass_op(EffectLabParser::Stencil_pass_opContext * /*ctx*/) override { }

  virtual void enterStencil_fail_op(EffectLabParser::Stencil_fail_opContext * /*ctx*/) override { }
  virtual void exitStencil_fail_op(EffectLabParser::Stencil_fail_opContext * /*ctx*/) override { }

  virtual void enterStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext * /*ctx*/) override { }
  virtual void exitStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext * /*ctx*/) override { }

  virtual void enterStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext * /*ctx*/) override { }
  virtual void exitStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext * /*ctx*/) override { }

  virtual void enterStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext * /*ctx*/) override { }
  virtual void exitStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext * /*ctx*/) override { }

  virtual void enterStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext * /*ctx*/) override { }
  virtual void exitStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext * /*ctx*/) override { }

  virtual void enterStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext * /*ctx*/) override { }
  virtual void exitStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext * /*ctx*/) override { }

  virtual void enterStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext * /*ctx*/) override { }
  virtual void exitStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext * /*ctx*/) override { }

  virtual void enterStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext * /*ctx*/) override { }
  virtual void exitStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext * /*ctx*/) override { }

  virtual void enterStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext * /*ctx*/) override { }
  virtual void exitStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext * /*ctx*/) override { }

  virtual void enterStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext * /*ctx*/) override { }
  virtual void exitStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace Eureka::ParserDetails
