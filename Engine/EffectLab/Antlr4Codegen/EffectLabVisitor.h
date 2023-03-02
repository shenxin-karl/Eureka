
// Generated from EffectLab.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "EffectLabParser.h"


namespace Eureka::ParserDetails {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by EffectLabParser.
 */
class  EffectLabVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by EffectLabParser.
   */
    virtual std::any visitEffect(EffectLabParser::EffectContext *context) = 0;

    virtual std::any visitProperty_block(EffectLabParser::Property_blockContext *context) = 0;

    virtual std::any visitHlsl_include_block(EffectLabParser::Hlsl_include_blockContext *context) = 0;

    virtual std::any visitProperty_name(EffectLabParser::Property_nameContext *context) = 0;

    virtual std::any visitProperty_description(EffectLabParser::Property_descriptionContext *context) = 0;

    virtual std::any visitPropertyItemBool(EffectLabParser::PropertyItemBoolContext *context) = 0;

    virtual std::any visitPropertyItemInt(EffectLabParser::PropertyItemIntContext *context) = 0;

    virtual std::any visitPropertyItemRange(EffectLabParser::PropertyItemRangeContext *context) = 0;

    virtual std::any visitPropertyItemFloat(EffectLabParser::PropertyItemFloatContext *context) = 0;

    virtual std::any visitPropertyItemFloat2(EffectLabParser::PropertyItemFloat2Context *context) = 0;

    virtual std::any visitPropertyItemFloat3(EffectLabParser::PropertyItemFloat3Context *context) = 0;

    virtual std::any visitPropertyItemFloat4(EffectLabParser::PropertyItemFloat4Context *context) = 0;

    virtual std::any visitPropertyItemTexture(EffectLabParser::PropertyItemTextureContext *context) = 0;

    virtual std::any visitPropertyItemMatrix(EffectLabParser::PropertyItemMatrixContext *context) = 0;

    virtual std::any visitProperty_bool_type(EffectLabParser::Property_bool_typeContext *context) = 0;

    virtual std::any visitProperty_int_type(EffectLabParser::Property_int_typeContext *context) = 0;

    virtual std::any visitProperty_range_type(EffectLabParser::Property_range_typeContext *context) = 0;

    virtual std::any visitProperty_float_type(EffectLabParser::Property_float_typeContext *context) = 0;

    virtual std::any visitProperty_float2_type(EffectLabParser::Property_float2_typeContext *context) = 0;

    virtual std::any visitProperty_float3_type(EffectLabParser::Property_float3_typeContext *context) = 0;

    virtual std::any visitProperty_float4_type(EffectLabParser::Property_float4_typeContext *context) = 0;

    virtual std::any visitProperty_texture_2d_type(EffectLabParser::Property_texture_2d_typeContext *context) = 0;

    virtual std::any visitProperty_matrix_type(EffectLabParser::Property_matrix_typeContext *context) = 0;

    virtual std::any visitProperty_range_val(EffectLabParser::Property_range_valContext *context) = 0;

    virtual std::any visitProperty_bool_val(EffectLabParser::Property_bool_valContext *context) = 0;

    virtual std::any visitProperty_int_val(EffectLabParser::Property_int_valContext *context) = 0;

    virtual std::any visitProperty_float_val(EffectLabParser::Property_float_valContext *context) = 0;

    virtual std::any visitProperty_float2_val(EffectLabParser::Property_float2_valContext *context) = 0;

    virtual std::any visitProperty_float3_val(EffectLabParser::Property_float3_valContext *context) = 0;

    virtual std::any visitProperty_float4_val(EffectLabParser::Property_float4_valContext *context) = 0;

    virtual std::any visitProperty_matrix_val(EffectLabParser::Property_matrix_valContext *context) = 0;

    virtual std::any visitProperty_texture_val(EffectLabParser::Property_texture_valContext *context) = 0;

    virtual std::any visitNumber_val(EffectLabParser::Number_valContext *context) = 0;

    virtual std::any visitPass(EffectLabParser::PassContext *context) = 0;

    virtual std::any visitPass_tag(EffectLabParser::Pass_tagContext *context) = 0;

    virtual std::any visitPassSourceContext(EffectLabParser::PassSourceContextContext *context) = 0;

    virtual std::any visitPassVertexShader(EffectLabParser::PassVertexShaderContext *context) = 0;

    virtual std::any visitPassGeometryShader(EffectLabParser::PassGeometryShaderContext *context) = 0;

    virtual std::any visitPassHullShader(EffectLabParser::PassHullShaderContext *context) = 0;

    virtual std::any visitPassDomainShader(EffectLabParser::PassDomainShaderContext *context) = 0;

    virtual std::any visitPassPixelShader(EffectLabParser::PassPixelShaderContext *context) = 0;

    virtual std::any visitPassRenderQueue(EffectLabParser::PassRenderQueueContext *context) = 0;

    virtual std::any visitPassShaderFeature(EffectLabParser::PassShaderFeatureContext *context) = 0;

    virtual std::any visitPassCullMode(EffectLabParser::PassCullModeContext *context) = 0;

    virtual std::any visitPassZClipMode(EffectLabParser::PassZClipModeContext *context) = 0;

    virtual std::any visitPassZTestMode(EffectLabParser::PassZTestModeContext *context) = 0;

    virtual std::any visitPassZWriteMode(EffectLabParser::PassZWriteModeContext *context) = 0;

    virtual std::any visitPassOffset(EffectLabParser::PassOffsetContext *context) = 0;

    virtual std::any visitPassColorMask(EffectLabParser::PassColorMaskContext *context) = 0;

    virtual std::any visitPassBlend(EffectLabParser::PassBlendContext *context) = 0;

    virtual std::any visitPassBlendOp(EffectLabParser::PassBlendOpContext *context) = 0;

    virtual std::any visitPassAlphaToMask(EffectLabParser::PassAlphaToMaskContext *context) = 0;

    virtual std::any visitPassConservative(EffectLabParser::PassConservativeContext *context) = 0;

    virtual std::any visitPassStencil(EffectLabParser::PassStencilContext *context) = 0;

    virtual std::any visitPass_source_context(EffectLabParser::Pass_source_contextContext *context) = 0;

    virtual std::any visitPass_vertex_shader(EffectLabParser::Pass_vertex_shaderContext *context) = 0;

    virtual std::any visitPass_geometry_shader(EffectLabParser::Pass_geometry_shaderContext *context) = 0;

    virtual std::any visitPass_hull_shader(EffectLabParser::Pass_hull_shaderContext *context) = 0;

    virtual std::any visitPass_domain_shader(EffectLabParser::Pass_domain_shaderContext *context) = 0;

    virtual std::any visitPass_pixel_shader(EffectLabParser::Pass_pixel_shaderContext *context) = 0;

    virtual std::any visitPass_render_queue(EffectLabParser::Pass_render_queueContext *context) = 0;

    virtual std::any visitPass_shader_feature(EffectLabParser::Pass_shader_featureContext *context) = 0;

    virtual std::any visitPass_cull_mode(EffectLabParser::Pass_cull_modeContext *context) = 0;

    virtual std::any visitPass_zclip_mode(EffectLabParser::Pass_zclip_modeContext *context) = 0;

    virtual std::any visitPass_ztest_mode(EffectLabParser::Pass_ztest_modeContext *context) = 0;

    virtual std::any visitPass_zwrite_mode(EffectLabParser::Pass_zwrite_modeContext *context) = 0;

    virtual std::any visitPass_offset(EffectLabParser::Pass_offsetContext *context) = 0;

    virtual std::any visitPass_color_mask(EffectLabParser::Pass_color_maskContext *context) = 0;

    virtual std::any visitPassBlendOff(EffectLabParser::PassBlendOffContext *context) = 0;

    virtual std::any visitPassBlendRTOff(EffectLabParser::PassBlendRTOffContext *context) = 0;

    virtual std::any visitPassBlendColor(EffectLabParser::PassBlendColorContext *context) = 0;

    virtual std::any visitPassBlendRTColor(EffectLabParser::PassBlendRTColorContext *context) = 0;

    virtual std::any visitPassBlendColorAlpha(EffectLabParser::PassBlendColorAlphaContext *context) = 0;

    virtual std::any visitPassBlendRTColorAlpha(EffectLabParser::PassBlendRTColorAlphaContext *context) = 0;

    virtual std::any visitPass_blend_op(EffectLabParser::Pass_blend_opContext *context) = 0;

    virtual std::any visitPass_alpha_to_mask(EffectLabParser::Pass_alpha_to_maskContext *context) = 0;

    virtual std::any visitPass_conservative(EffectLabParser::Pass_conservativeContext *context) = 0;

    virtual std::any visitPass_stencil(EffectLabParser::Pass_stencilContext *context) = 0;

    virtual std::any visitStencilRef(EffectLabParser::StencilRefContext *context) = 0;

    virtual std::any visitStencilReadMask(EffectLabParser::StencilReadMaskContext *context) = 0;

    virtual std::any visitStencilWriteMask(EffectLabParser::StencilWriteMaskContext *context) = 0;

    virtual std::any visitStencilComp(EffectLabParser::StencilCompContext *context) = 0;

    virtual std::any visitStencilPassOp(EffectLabParser::StencilPassOpContext *context) = 0;

    virtual std::any visitStencilFailOp(EffectLabParser::StencilFailOpContext *context) = 0;

    virtual std::any visitStencilZFailOp(EffectLabParser::StencilZFailOpContext *context) = 0;

    virtual std::any visitStencilCompBackOp(EffectLabParser::StencilCompBackOpContext *context) = 0;

    virtual std::any visitStencilPassBackOp(EffectLabParser::StencilPassBackOpContext *context) = 0;

    virtual std::any visitStencilFailBackOp(EffectLabParser::StencilFailBackOpContext *context) = 0;

    virtual std::any visitStencilZFailBackOp(EffectLabParser::StencilZFailBackOpContext *context) = 0;

    virtual std::any visitStencilCompFrontOp(EffectLabParser::StencilCompFrontOpContext *context) = 0;

    virtual std::any visitStencilPassFrontOp(EffectLabParser::StencilPassFrontOpContext *context) = 0;

    virtual std::any visitStencilFailFrontOp(EffectLabParser::StencilFailFrontOpContext *context) = 0;

    virtual std::any visitStencilZFailFrontOp(EffectLabParser::StencilZFailFrontOpContext *context) = 0;

    virtual std::any visitStencil_ref(EffectLabParser::Stencil_refContext *context) = 0;

    virtual std::any visitStencil_read_mask(EffectLabParser::Stencil_read_maskContext *context) = 0;

    virtual std::any visitStencil_write_mask(EffectLabParser::Stencil_write_maskContext *context) = 0;

    virtual std::any visitStencil_comp(EffectLabParser::Stencil_compContext *context) = 0;

    virtual std::any visitStencil_pass_op(EffectLabParser::Stencil_pass_opContext *context) = 0;

    virtual std::any visitStencil_fail_op(EffectLabParser::Stencil_fail_opContext *context) = 0;

    virtual std::any visitStencil_zfail_op(EffectLabParser::Stencil_zfail_opContext *context) = 0;

    virtual std::any visitStencil_comp_back_op(EffectLabParser::Stencil_comp_back_opContext *context) = 0;

    virtual std::any visitStancil_pass_back_op(EffectLabParser::Stancil_pass_back_opContext *context) = 0;

    virtual std::any visitStencil_fail_back_op(EffectLabParser::Stencil_fail_back_opContext *context) = 0;

    virtual std::any visitStencil_zfail_back_op(EffectLabParser::Stencil_zfail_back_opContext *context) = 0;

    virtual std::any visitStencil_comp_front_op(EffectLabParser::Stencil_comp_front_opContext *context) = 0;

    virtual std::any visitStancil_pass_front_op(EffectLabParser::Stancil_pass_front_opContext *context) = 0;

    virtual std::any visitStencil_fail_front_op(EffectLabParser::Stencil_fail_front_opContext *context) = 0;

    virtual std::any visitStencil_zfail_front_op(EffectLabParser::Stencil_zfail_front_opContext *context) = 0;


};

}  // namespace Eureka::ParserDetails
