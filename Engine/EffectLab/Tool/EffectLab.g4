grammar EffectLab;

effect : source_path property_block? pass+;

source_path    : 'SourcePath' ':' StringLiteral;
property_block : 'Properties' '{' property_item+ '}';

property_name        : Identity;
property_description : StringLiteral;
property_item 
    : property_name '(' property_description ',' property_bool_type       ')' '=' property_bool_val    # PropertyItemBool
    | property_name '(' property_description ',' property_int_type        ')' '=' property_int_val     # PropertyItemInt
    | property_name '(' property_description ',' property_range_type      ')' '=' property_range_val   # PropertyItemRange
    | property_name '(' property_description ',' property_float_type      ')' '=' property_float_val   # PropertyItemFloat
    | property_name '(' property_description ',' property_float2_type     ')' '=' property_float2_val  # PropertyItemFloat2
    | property_name '(' property_description ',' property_float3_type     ')' '=' property_float3_val  # PropertyItemFloat3
    | property_name '(' property_description ',' property_float4_type     ')' '=' property_float4_val  # PropertyItemFloat4
    | property_name '(' property_description ',' property_texture_2d_type ')' '=' property_texture_val # PropertyItemTexture
    | property_name '(' property_description ',' property_matrix_type     ')' '=' property_matrix_val  # PropertyItemMatrix
    ;

property_bool_type       : ('bool'  | 'Bool');
property_int_type        : ('int'   | 'Int');
property_range_type      : ('range' | 'Range') '(' number_val ',' number_val ')';
property_float_type      : ('float' | 'Float');
property_float2_type     : ('float2'| 'Float2');
property_float3_type     : ('float3'| 'Float3');
property_float4_type     : ('float4'| 'Float4');
property_texture_2d_type : ('2d'    | '2D');
property_matrix_type     : ('matrix'| 'Matrix');

property_range_val      : number_val;
property_bool_val       : BooleanLiteral;
property_int_val        : IntLiteral;
property_float_val      : number_val;
property_float2_val     : '(' number_val ',' number_val ')';
property_float3_val     : '(' number_val ',' number_val ',' number_val ')';
property_float4_val     : '(' number_val ',' number_val ',' number_val ',' number_val ')';
property_matrix_val     : 'identity';
property_texture_val    
    : ('white' | 'White') 
    | ('black' | 'Black') 
    | ('bump'  | 'Bump')
    ;

    
number_val 
    : IntLiteral 
    | FloatLiteral
    ;

pass     : 'Pass' '(' pass_tag ')' '{' pass_block_item+ '}';

pass_tag : StringLiteral;

pass_block_item 
    : pass_vertex_shader   # PassVertexShader
    | pass_geometry_shader # PassGeometryShader
    | pass_hull_shader     # PassHullShader
    | pass_domain_shader   # PassDomainShader
    | pass_pixel_shader    # PassPixelShader
    | pass_render_queue    # PassRenderQueue
    | pass_shader_feature  # PassShaderFeature
    | pass_cull_mode       # PassCullMode
    | pass_zclip_mode      # PassZClipMode
    | pass_ztest_mode      # PassZTestMode
    | pass_zwrite_mode     # PassZWriteMode
    | pass_offset          # PassOffset
    | pass_color_mask      # PassColorMask
    | pass_blend           # PassBlend
    | pass_blend_op        # PassBlendOp
    | pass_alpha_to_mask   # PassAlphaToMask
    | pass_conservative    # PassConservative
    | pass_stencil         # PassStencil
    ;

pass_vertex_shader   : 'VertexShader'   ':' Identity;
pass_geometry_shader : 'GeometryShader' ':' Identity;
pass_hull_shader     : 'HullShader'     ':' Identity;
pass_domain_shader   : 'DomainShader'   ':' Identity;
pass_pixel_shader    : 'PixelShader'    ':' Identity;
pass_render_queue    : 'RenderQueue'    ':' RenderQueueLabel; 

pass_shader_feature : 'ShaderFeature' ':' Identity+;    
pass_cull_mode      : 'Cull' ':' CullModeLabel;
pass_zclip_mode     : 'ZClip' ':' BooleanLiteral;
pass_ztest_mode     : 'ZTest' ':' ZTestModeLabel;
pass_zwrite_mode    : 'ZWrite' ':' OnOffLabel;
pass_offset         : 'Offset' ':' FloatLiteral FloatLiteral;
pass_color_mask     
    : 'ColorMask' ColorMaskChannel
    | 'ColorMask' ColorMaskChannel IntLiteral
    ;


pass_blend
    : 'Blend' ':' KWOff                                                                              # PassBlendOff
    | 'Blend' ':' IntLiteral KWOff                                                                   # PassBlendRTOff
    | 'Blend' ':' BlendFactorLabel BlendFactorLabel                                                  # PassBlendColor
    | 'Blend' ':' IntLiteral BlendFactorLabel BlendFactorLabel                                       # PassBlendRTColor
    | 'Blend' ':' BlendFactorLabel BlendFactorLabel ',' BlendFactorLabel BlendFactorLabel            # PassBlendColorAlpha
    | 'Blend' ':' IntLiteral BlendFactorLabel BlendFactorLabel ',' BlendFactorLabel BlendFactorLabel # PassBlendRTColorAlpha
    ;

pass_blend_op      : 'BlendOp' ':' BlendOPLabel;
pass_alpha_to_mask : 'AlphaToMask' ':' OnOffLabel;
pass_conservative  : 'Conservative' ':' BooleanLiteral;
pass_stencil       : 'Stencil' '{' stencil_item+ '}';

stencil_item
    : stencil_ref            # StencilRef
    | stencil_read_mask      # StencilReadMask
    | stencil_write_mask     # StencilWriteMask
    | stencil_comp           # StencilComp
    | stencil_pass_op        # StencilPassOp
    | stencil_fail_op        # StencilFailOp
    | stencil_zfail_op       # StencilZFailOp
    | stencil_comp_back_op   # StencilCompBackOp
    | stancil_pass_back_op   # StencilPassBackOp
    | stencil_fail_back_op   # StencilFailBackOp
    | stencil_zfail_back_op  # StencilZFailBackOp
    | stencil_comp_front_op  # StencilCompFrontOp
    | stancil_pass_front_op  # StencilPassFrontOp
    | stencil_fail_front_op  # StencilFailFrontOp
    | stencil_zfail_front_op # StencilZFailFrontOp
    ;

stencil_ref            : 'Ref'        ':' IntLiteral;
stencil_read_mask      : 'ReadMask'   ':' IntLiteral;
stencil_write_mask     : 'WriteMask'  ':' IntLiteral;
stencil_comp           : 'Comp'       ':' StencilCompareLabel;
stencil_pass_op        : 'Pass'       ':' StencilOpLabel;
stencil_fail_op        : 'Fail'       ':' StencilOpLabel;
stencil_zfail_op       : 'ZFail'      ':' StencilOpLabel;
stencil_comp_back_op   : 'CompBack'   ':' StencilCompareLabel;
stancil_pass_back_op   : 'PassBack'   ':' StencilOpLabel;
stencil_fail_back_op   : 'FailBack'   ':' StencilOpLabel;
stencil_zfail_back_op  : 'ZFailBack'  ':' StencilOpLabel;
stencil_comp_front_op  : 'CompFront'  ':' StencilCompareLabel;
stancil_pass_front_op  : 'PassFront'  ':' StencilOpLabel;
stencil_fail_front_op  : 'FailFront'  ':' StencilOpLabel;
stencil_zfail_front_op : 'ZFailFront' ':' StencilOpLabel;

// lex

WhiteSpace   : [ \t\n\r]+          -> skip;
LineComment  : '//' .*? '\r'? '\n' -> skip;
BlockComment : '/*' .*? '*/'       -> skip;

BooleanLiteral
	: KWTrue
	| KWFalse
	;

OnOffLabel
    : KWOn
    | KWOff
    ;

CullModeLabel 
    : KWOff
    | 'Front'
    | 'Back'
    ;

RenderQueueLabel
    : 'BackGround'
    | 'Geometry'
    | 'Opaque'
    | 'AlphaTest'
    | 'Transparent'
    | 'Overlay'
    ;

ZTestModeLabel
    : KWNever
    | KWLess
    | KWEqual
    | KWLEqaul
    | KWGEqual     
    | KWNotEqual
    | KWGreater
    | KWAlways
    ;

BlendFactorLabel
    : KWZero
    | 'SrcColor'
    | 'SrcAlpha'
    | 'DstColor'
    | 'DstAlpha'
    | 'OneMinusSrcColor'
    | 'OneMinusSrcAlpha'
    | 'OneMinusDstColor'
    | 'OneMinusDstAlpha'
    ;

BlendOPLabel
    : 'Add'
    | 'Sub'
    | 'RevSub'
    | 'Min'
    | 'Max'
    ;   

StencilCompareLabel
    : KWNever
    | KWAlways
    | KWEqual
    | KWLEqaul
    | KWGreater
    | KWNotEqual
    | KWGEqual
    | KWAlways
    ;    

StencilOpLabel
    : KWKeep
    | KWZero
    | KWReplace
    | KWIncrSat
    | KWDecrSat
    | KWInvert
    | KWIncrWrap
    | KWDecrWrap
    ;    

IntLiteral 
    : [+-]? [1-9][0-9]*
    | '0'
    ;

FloatLiteral 
    : [+-]? [0-9]+ '.' [0-9]* [fF]?
    | '.' [0-9]+ [fF]?
    ;

ColorMaskChannel
    : [RGBA]
    | [RGBA] [RGBA]
    | [RGBA] [RGBA] [RGBA]
    | [RGBA] [RGBA] [RGBA] [RGBA]
    ;   

KWOff       : 'Off';
KWOn        : 'On';
KWNever     : 'Never';
KWLess      : 'Less';
KWEqual     : 'Equal';
KWLEqaul    : 'LEqual';
KWGreater   : 'Greater';
KWNotEqual  : 'NotEqual';
KWGEqual    : 'GEqual';
KWAlways    : 'Always';
KWKeep      : 'Keep';
KWZero      : 'Zero';
KWReplace   : 'Replace';
KWIncrSat   : 'IncrSat';
KWDecrSat   : 'DecrSat';
KWInvert    : 'Invert';
KWIncrWrap  : 'IncrWrap';
KWDecrWrap  : 'DecrWrap';
KWTrue      : 'true'  | 'True';
KWFalse     : 'false' | 'False';

StringLiteral : '"' .*? '"' ;
Identity      : [_a-zA-Z][a-zA-Z0-9_]*; 