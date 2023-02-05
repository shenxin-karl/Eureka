
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabVisitor.h"


namespace Eureka::ParserDetails {

/**
 * This class provides an empty implementation of EffectLabVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  EffectLabBaseVisitor : public EffectLabVisitor {
public:

  virtual std::any visitEffect(EffectLabParser::EffectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_path(EffectLabParser::Source_pathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_block(EffectLabParser::Property_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_val(EffectLabParser::Number_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_bool_type(EffectLabParser::Property_bool_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_int_type(EffectLabParser::Property_int_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_range_type(EffectLabParser::Property_range_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float_type(EffectLabParser::Property_float_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float2_type(EffectLabParser::Property_float2_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float3_type(EffectLabParser::Property_float3_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float4_type(EffectLabParser::Property_float4_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_matrix_type(EffectLabParser::Property_matrix_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_range_val(EffectLabParser::Property_range_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_bool_val(EffectLabParser::Property_bool_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_int_val(EffectLabParser::Property_int_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float_val(EffectLabParser::Property_float_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float2_val(EffectLabParser::Property_float2_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float3_val(EffectLabParser::Property_float3_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_float4_val(EffectLabParser::Property_float4_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_texture_val(EffectLabParser::Property_texture_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_name(EffectLabParser::Property_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_description(EffectLabParser::Property_descriptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemInt(EffectLabParser::PropertyItemIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemRange(EffectLabParser::PropertyItemRangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_tag(EffectLabParser::Pass_tagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass(EffectLabParser::PassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_hull_shader(EffectLabParser::Pass_hull_shaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_domain_shader(EffectLabParser::Pass_domain_shaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_render_queue(EffectLabParser::Pass_render_queueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_shader_feature(EffectLabParser::Pass_shader_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_cull_mode(EffectLabParser::Pass_cull_modeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_offset(EffectLabParser::Pass_offsetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_color_mask(EffectLabParser::Pass_color_maskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendOff(EffectLabParser::PassBlendOffContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendRTOff(EffectLabParser::PassBlendRTOffContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendColor(EffectLabParser::PassBlendColorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendRTColor(EffectLabParser::PassBlendRTColorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_blend_op(EffectLabParser::Pass_blend_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_conservative(EffectLabParser::Pass_conservativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPass_stencil(EffectLabParser::Pass_stencilContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassVertexShader(EffectLabParser::PassVertexShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassGeometryShader(EffectLabParser::PassGeometryShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassHullShader(EffectLabParser::PassHullShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassDomainShader(EffectLabParser::PassDomainShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassPixelShader(EffectLabParser::PassPixelShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassRenderQueue(EffectLabParser::PassRenderQueueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassShaderFeature(EffectLabParser::PassShaderFeatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassCullMode(EffectLabParser::PassCullModeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassZClipMode(EffectLabParser::PassZClipModeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassZTestMode(EffectLabParser::PassZTestModeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassZWriteMode(EffectLabParser::PassZWriteModeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassOffset(EffectLabParser::PassOffsetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassColorMask(EffectLabParser::PassColorMaskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlend(EffectLabParser::PassBlendContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassBlendOp(EffectLabParser::PassBlendOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassConservative(EffectLabParser::PassConservativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassStencil(EffectLabParser::PassStencilContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_ref(EffectLabParser::Stencil_refContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_read_mask(EffectLabParser::Stencil_read_maskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_write_mask(EffectLabParser::Stencil_write_maskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_comp(EffectLabParser::Stencil_compContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_pass_op(EffectLabParser::Stencil_pass_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_fail_op(EffectLabParser::Stencil_fail_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilRef(EffectLabParser::StencilRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilReadMask(EffectLabParser::StencilReadMaskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilWriteMask(EffectLabParser::StencilWriteMaskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilComp(EffectLabParser::StencilCompContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilPassOp(EffectLabParser::StencilPassOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilFailOp(EffectLabParser::StencilFailOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilZFailOp(EffectLabParser::StencilZFailOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilCompBackOp(EffectLabParser::StencilCompBackOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilPassBackOp(EffectLabParser::StencilPassBackOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilFailBackOp(EffectLabParser::StencilFailBackOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Eureka::ParserDetails
