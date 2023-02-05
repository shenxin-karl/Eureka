
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabParser.h"


namespace Eureka::ParserDetails {

/**
 * This interface defines an abstract listener for a parse tree produced by EffectLabParser.
 */
class  EffectLabListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterEffect(EffectLabParser::EffectContext *ctx) = 0;
  virtual void exitEffect(EffectLabParser::EffectContext *ctx) = 0;

  virtual void enterSource_path(EffectLabParser::Source_pathContext *ctx) = 0;
  virtual void exitSource_path(EffectLabParser::Source_pathContext *ctx) = 0;

  virtual void enterProperty_block(EffectLabParser::Property_blockContext *ctx) = 0;
  virtual void exitProperty_block(EffectLabParser::Property_blockContext *ctx) = 0;

  virtual void enterNumber_val(EffectLabParser::Number_valContext *ctx) = 0;
  virtual void exitNumber_val(EffectLabParser::Number_valContext *ctx) = 0;

  virtual void enterProperty_bool_type(EffectLabParser::Property_bool_typeContext *ctx) = 0;
  virtual void exitProperty_bool_type(EffectLabParser::Property_bool_typeContext *ctx) = 0;

  virtual void enterProperty_int_type(EffectLabParser::Property_int_typeContext *ctx) = 0;
  virtual void exitProperty_int_type(EffectLabParser::Property_int_typeContext *ctx) = 0;

  virtual void enterProperty_range_type(EffectLabParser::Property_range_typeContext *ctx) = 0;
  virtual void exitProperty_range_type(EffectLabParser::Property_range_typeContext *ctx) = 0;

  virtual void enterProperty_float_type(EffectLabParser::Property_float_typeContext *ctx) = 0;
  virtual void exitProperty_float_type(EffectLabParser::Property_float_typeContext *ctx) = 0;

  virtual void enterProperty_float2_type(EffectLabParser::Property_float2_typeContext *ctx) = 0;
  virtual void exitProperty_float2_type(EffectLabParser::Property_float2_typeContext *ctx) = 0;

  virtual void enterProperty_float3_type(EffectLabParser::Property_float3_typeContext *ctx) = 0;
  virtual void exitProperty_float3_type(EffectLabParser::Property_float3_typeContext *ctx) = 0;

  virtual void enterProperty_float4_type(EffectLabParser::Property_float4_typeContext *ctx) = 0;
  virtual void exitProperty_float4_type(EffectLabParser::Property_float4_typeContext *ctx) = 0;

  virtual void enterProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext *ctx) = 0;
  virtual void exitProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext *ctx) = 0;

  virtual void enterProperty_matrix_type(EffectLabParser::Property_matrix_typeContext *ctx) = 0;
  virtual void exitProperty_matrix_type(EffectLabParser::Property_matrix_typeContext *ctx) = 0;

  virtual void enterProperty_range_val(EffectLabParser::Property_range_valContext *ctx) = 0;
  virtual void exitProperty_range_val(EffectLabParser::Property_range_valContext *ctx) = 0;

  virtual void enterProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) = 0;
  virtual void exitProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) = 0;

  virtual void enterProperty_int_val(EffectLabParser::Property_int_valContext *ctx) = 0;
  virtual void exitProperty_int_val(EffectLabParser::Property_int_valContext *ctx) = 0;

  virtual void enterProperty_float_val(EffectLabParser::Property_float_valContext *ctx) = 0;
  virtual void exitProperty_float_val(EffectLabParser::Property_float_valContext *ctx) = 0;

  virtual void enterProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) = 0;
  virtual void exitProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) = 0;

  virtual void enterProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) = 0;
  virtual void exitProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) = 0;

  virtual void enterProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) = 0;
  virtual void exitProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) = 0;

  virtual void enterProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) = 0;
  virtual void exitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) = 0;

  virtual void enterProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) = 0;
  virtual void exitProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) = 0;

  virtual void enterProperty_name(EffectLabParser::Property_nameContext *ctx) = 0;
  virtual void exitProperty_name(EffectLabParser::Property_nameContext *ctx) = 0;

  virtual void enterProperty_description(EffectLabParser::Property_descriptionContext *ctx) = 0;
  virtual void exitProperty_description(EffectLabParser::Property_descriptionContext *ctx) = 0;

  virtual void enterPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) = 0;
  virtual void exitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) = 0;

  virtual void enterPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) = 0;
  virtual void exitPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) = 0;

  virtual void enterPropertyItemRange(EffectLabParser::PropertyItemRangeContext *ctx) = 0;
  virtual void exitPropertyItemRange(EffectLabParser::PropertyItemRangeContext *ctx) = 0;

  virtual void enterPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) = 0;
  virtual void exitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) = 0;

  virtual void enterPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) = 0;
  virtual void exitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) = 0;

  virtual void enterPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) = 0;
  virtual void exitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) = 0;

  virtual void enterPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) = 0;
  virtual void exitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) = 0;

  virtual void enterPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) = 0;
  virtual void exitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) = 0;

  virtual void enterPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) = 0;
  virtual void exitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) = 0;

  virtual void enterPass_tag(EffectLabParser::Pass_tagContext *ctx) = 0;
  virtual void exitPass_tag(EffectLabParser::Pass_tagContext *ctx) = 0;

  virtual void enterPass(EffectLabParser::PassContext *ctx) = 0;
  virtual void exitPass(EffectLabParser::PassContext *ctx) = 0;

  virtual void enterPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext *ctx) = 0;
  virtual void exitPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext *ctx) = 0;

  virtual void enterPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext *ctx) = 0;
  virtual void exitPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext *ctx) = 0;

  virtual void enterPass_hull_shader(EffectLabParser::Pass_hull_shaderContext *ctx) = 0;
  virtual void exitPass_hull_shader(EffectLabParser::Pass_hull_shaderContext *ctx) = 0;

  virtual void enterPass_domain_shader(EffectLabParser::Pass_domain_shaderContext *ctx) = 0;
  virtual void exitPass_domain_shader(EffectLabParser::Pass_domain_shaderContext *ctx) = 0;

  virtual void enterPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext *ctx) = 0;
  virtual void exitPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext *ctx) = 0;

  virtual void enterPass_render_queue(EffectLabParser::Pass_render_queueContext *ctx) = 0;
  virtual void exitPass_render_queue(EffectLabParser::Pass_render_queueContext *ctx) = 0;

  virtual void enterPass_shader_feature(EffectLabParser::Pass_shader_featureContext *ctx) = 0;
  virtual void exitPass_shader_feature(EffectLabParser::Pass_shader_featureContext *ctx) = 0;

  virtual void enterPass_cull_mode(EffectLabParser::Pass_cull_modeContext *ctx) = 0;
  virtual void exitPass_cull_mode(EffectLabParser::Pass_cull_modeContext *ctx) = 0;

  virtual void enterPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext *ctx) = 0;
  virtual void exitPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext *ctx) = 0;

  virtual void enterPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext *ctx) = 0;
  virtual void exitPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext *ctx) = 0;

  virtual void enterPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext *ctx) = 0;
  virtual void exitPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext *ctx) = 0;

  virtual void enterPass_offset(EffectLabParser::Pass_offsetContext *ctx) = 0;
  virtual void exitPass_offset(EffectLabParser::Pass_offsetContext *ctx) = 0;

  virtual void enterPass_color_mask(EffectLabParser::Pass_color_maskContext *ctx) = 0;
  virtual void exitPass_color_mask(EffectLabParser::Pass_color_maskContext *ctx) = 0;

  virtual void enterPassBlendOff(EffectLabParser::PassBlendOffContext *ctx) = 0;
  virtual void exitPassBlendOff(EffectLabParser::PassBlendOffContext *ctx) = 0;

  virtual void enterPassBlendRTOff(EffectLabParser::PassBlendRTOffContext *ctx) = 0;
  virtual void exitPassBlendRTOff(EffectLabParser::PassBlendRTOffContext *ctx) = 0;

  virtual void enterPassBlendColor(EffectLabParser::PassBlendColorContext *ctx) = 0;
  virtual void exitPassBlendColor(EffectLabParser::PassBlendColorContext *ctx) = 0;

  virtual void enterPassBlendRTColor(EffectLabParser::PassBlendRTColorContext *ctx) = 0;
  virtual void exitPassBlendRTColor(EffectLabParser::PassBlendRTColorContext *ctx) = 0;

  virtual void enterPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext *ctx) = 0;
  virtual void exitPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext *ctx) = 0;

  virtual void enterPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext *ctx) = 0;
  virtual void exitPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext *ctx) = 0;

  virtual void enterPass_blend_op(EffectLabParser::Pass_blend_opContext *ctx) = 0;
  virtual void exitPass_blend_op(EffectLabParser::Pass_blend_opContext *ctx) = 0;

  virtual void enterPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext *ctx) = 0;
  virtual void exitPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext *ctx) = 0;

  virtual void enterPass_conservative(EffectLabParser::Pass_conservativeContext *ctx) = 0;
  virtual void exitPass_conservative(EffectLabParser::Pass_conservativeContext *ctx) = 0;

  virtual void enterPass_stencil(EffectLabParser::Pass_stencilContext *ctx) = 0;
  virtual void exitPass_stencil(EffectLabParser::Pass_stencilContext *ctx) = 0;

  virtual void enterPassVertexShader(EffectLabParser::PassVertexShaderContext *ctx) = 0;
  virtual void exitPassVertexShader(EffectLabParser::PassVertexShaderContext *ctx) = 0;

  virtual void enterPassGeometryShader(EffectLabParser::PassGeometryShaderContext *ctx) = 0;
  virtual void exitPassGeometryShader(EffectLabParser::PassGeometryShaderContext *ctx) = 0;

  virtual void enterPassHullShader(EffectLabParser::PassHullShaderContext *ctx) = 0;
  virtual void exitPassHullShader(EffectLabParser::PassHullShaderContext *ctx) = 0;

  virtual void enterPassDomainShader(EffectLabParser::PassDomainShaderContext *ctx) = 0;
  virtual void exitPassDomainShader(EffectLabParser::PassDomainShaderContext *ctx) = 0;

  virtual void enterPassPixelShader(EffectLabParser::PassPixelShaderContext *ctx) = 0;
  virtual void exitPassPixelShader(EffectLabParser::PassPixelShaderContext *ctx) = 0;

  virtual void enterPassRenderQueue(EffectLabParser::PassRenderQueueContext *ctx) = 0;
  virtual void exitPassRenderQueue(EffectLabParser::PassRenderQueueContext *ctx) = 0;

  virtual void enterPassShaderFeature(EffectLabParser::PassShaderFeatureContext *ctx) = 0;
  virtual void exitPassShaderFeature(EffectLabParser::PassShaderFeatureContext *ctx) = 0;

  virtual void enterPassCullMode(EffectLabParser::PassCullModeContext *ctx) = 0;
  virtual void exitPassCullMode(EffectLabParser::PassCullModeContext *ctx) = 0;

  virtual void enterPassZClipMode(EffectLabParser::PassZClipModeContext *ctx) = 0;
  virtual void exitPassZClipMode(EffectLabParser::PassZClipModeContext *ctx) = 0;

  virtual void enterPassZTestMode(EffectLabParser::PassZTestModeContext *ctx) = 0;
  virtual void exitPassZTestMode(EffectLabParser::PassZTestModeContext *ctx) = 0;

  virtual void enterPassZWriteMode(EffectLabParser::PassZWriteModeContext *ctx) = 0;
  virtual void exitPassZWriteMode(EffectLabParser::PassZWriteModeContext *ctx) = 0;

  virtual void enterPassOffset(EffectLabParser::PassOffsetContext *ctx) = 0;
  virtual void exitPassOffset(EffectLabParser::PassOffsetContext *ctx) = 0;

  virtual void enterPassColorMask(EffectLabParser::PassColorMaskContext *ctx) = 0;
  virtual void exitPassColorMask(EffectLabParser::PassColorMaskContext *ctx) = 0;

  virtual void enterPassBlend(EffectLabParser::PassBlendContext *ctx) = 0;
  virtual void exitPassBlend(EffectLabParser::PassBlendContext *ctx) = 0;

  virtual void enterPassBlendOp(EffectLabParser::PassBlendOpContext *ctx) = 0;
  virtual void exitPassBlendOp(EffectLabParser::PassBlendOpContext *ctx) = 0;

  virtual void enterPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext *ctx) = 0;
  virtual void exitPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext *ctx) = 0;

  virtual void enterPassConservative(EffectLabParser::PassConservativeContext *ctx) = 0;
  virtual void exitPassConservative(EffectLabParser::PassConservativeContext *ctx) = 0;

  virtual void enterPassStencil(EffectLabParser::PassStencilContext *ctx) = 0;
  virtual void exitPassStencil(EffectLabParser::PassStencilContext *ctx) = 0;

  virtual void enterStencil_ref(EffectLabParser::Stencil_refContext *ctx) = 0;
  virtual void exitStencil_ref(EffectLabParser::Stencil_refContext *ctx) = 0;

  virtual void enterStencil_read_mask(EffectLabParser::Stencil_read_maskContext *ctx) = 0;
  virtual void exitStencil_read_mask(EffectLabParser::Stencil_read_maskContext *ctx) = 0;

  virtual void enterStencil_write_mask(EffectLabParser::Stencil_write_maskContext *ctx) = 0;
  virtual void exitStencil_write_mask(EffectLabParser::Stencil_write_maskContext *ctx) = 0;

  virtual void enterStencil_comp(EffectLabParser::Stencil_compContext *ctx) = 0;
  virtual void exitStencil_comp(EffectLabParser::Stencil_compContext *ctx) = 0;

  virtual void enterStencil_pass_op(EffectLabParser::Stencil_pass_opContext *ctx) = 0;
  virtual void exitStencil_pass_op(EffectLabParser::Stencil_pass_opContext *ctx) = 0;

  virtual void enterStencil_fail_op(EffectLabParser::Stencil_fail_opContext *ctx) = 0;
  virtual void exitStencil_fail_op(EffectLabParser::Stencil_fail_opContext *ctx) = 0;

  virtual void enterStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext *ctx) = 0;
  virtual void exitStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext *ctx) = 0;

  virtual void enterStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext *ctx) = 0;
  virtual void exitStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext *ctx) = 0;

  virtual void enterStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext *ctx) = 0;
  virtual void exitStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext *ctx) = 0;

  virtual void enterStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext *ctx) = 0;
  virtual void exitStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext *ctx) = 0;

  virtual void enterStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext *ctx) = 0;
  virtual void exitStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext *ctx) = 0;

  virtual void enterStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext *ctx) = 0;
  virtual void exitStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext *ctx) = 0;

  virtual void enterStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext *ctx) = 0;
  virtual void exitStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext *ctx) = 0;

  virtual void enterStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext *ctx) = 0;
  virtual void exitStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext *ctx) = 0;

  virtual void enterStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext *ctx) = 0;
  virtual void exitStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext *ctx) = 0;

  virtual void enterStencilRef(EffectLabParser::StencilRefContext *ctx) = 0;
  virtual void exitStencilRef(EffectLabParser::StencilRefContext *ctx) = 0;

  virtual void enterStencilReadMask(EffectLabParser::StencilReadMaskContext *ctx) = 0;
  virtual void exitStencilReadMask(EffectLabParser::StencilReadMaskContext *ctx) = 0;

  virtual void enterStencilWriteMask(EffectLabParser::StencilWriteMaskContext *ctx) = 0;
  virtual void exitStencilWriteMask(EffectLabParser::StencilWriteMaskContext *ctx) = 0;

  virtual void enterStencilComp(EffectLabParser::StencilCompContext *ctx) = 0;
  virtual void exitStencilComp(EffectLabParser::StencilCompContext *ctx) = 0;

  virtual void enterStencilPassOp(EffectLabParser::StencilPassOpContext *ctx) = 0;
  virtual void exitStencilPassOp(EffectLabParser::StencilPassOpContext *ctx) = 0;

  virtual void enterStencilFailOp(EffectLabParser::StencilFailOpContext *ctx) = 0;
  virtual void exitStencilFailOp(EffectLabParser::StencilFailOpContext *ctx) = 0;

  virtual void enterStencilZFailOp(EffectLabParser::StencilZFailOpContext *ctx) = 0;
  virtual void exitStencilZFailOp(EffectLabParser::StencilZFailOpContext *ctx) = 0;

  virtual void enterStencilCompBackOp(EffectLabParser::StencilCompBackOpContext *ctx) = 0;
  virtual void exitStencilCompBackOp(EffectLabParser::StencilCompBackOpContext *ctx) = 0;

  virtual void enterStencilPassBackOp(EffectLabParser::StencilPassBackOpContext *ctx) = 0;
  virtual void exitStencilPassBackOp(EffectLabParser::StencilPassBackOpContext *ctx) = 0;

  virtual void enterStencilFailBackOp(EffectLabParser::StencilFailBackOpContext *ctx) = 0;
  virtual void exitStencilFailBackOp(EffectLabParser::StencilFailBackOpContext *ctx) = 0;

  virtual void enterStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext *ctx) = 0;
  virtual void exitStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext *ctx) = 0;

  virtual void enterStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext *ctx) = 0;
  virtual void exitStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext *ctx) = 0;

  virtual void enterStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext *ctx) = 0;
  virtual void exitStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext *ctx) = 0;

  virtual void enterStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext *ctx) = 0;
  virtual void exitStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext *ctx) = 0;

  virtual void enterStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext *ctx) = 0;
  virtual void exitStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext *ctx) = 0;


};

}  // namespace Eureka::ParserDetails
