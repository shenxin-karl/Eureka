grammar EffectLab;

effect : source_path property_block?;

source_path     : 'SourcePath' ':' String ';';
property_block  : 'Properties' '{' property_item+ '}';

number_val      : IntVal | FloatVal;

property_bool_val       : BoolVal;
property_int_val        : IntVal;
property_float_val      : number_val;
property_float2_val     : '(' number_val ',' number_val ')';
property_float3_val     : '(' number_val ',' number_val ',' number_val ')';
property_float4_val     : '(' number_val ',' number_val ',' number_val ',' number_val ')';
property_texture_val    : (KWWhite | KWBlack | KWBump );
property_matrix_val     : KWIdentity;

// UniformName(Description, Type) = Value
property_item : Identity '(' String ',' ('bool'  | 'Bool')   ')' '=' property_bool_val       # PropertyItemBool
              | Identity '(' String ',' ('int'   | 'Int')    ')' '=' property_int_val        # PropertyItemInt
              | Identity '(' String ',' ('float' | 'Float')  ')' '=' property_float_val      # PropertyItemFloat
              | Identity '(' String ',' ('float2'| 'Float2') ')' '=' property_float2_val     # PropertyItemFloat2
              | Identity '(' String ',' ('float3'| 'Float3') ')' '=' property_float3_val     # PropertyItemFloat3
              | Identity '(' String ',' ('float4'| 'Float4') ')' '=' property_float4_val     # PropertyItemFloat4
              | Identity '(' String ',' ('2d'    | '2D')     ')' '=' property_texture_val    # PropertyItemTexture
              | Identity '(' String ',' ('matrix'| 'Matrix') ')' '=' property_matrix_val     # PropertyItemMatrix
              ;

// lex
BoolVal     : KWTrue | KWFalse;
IntVal      : [+-]? [1-9][0-9]*;
FloatVal    : [+-]? [0-9]+ '.' [0-9]*? [fF]?;

String      : '"' .*? '"' ;
Identity    : [_a-zA-Z][a-zA-Z0-9_]*;

KWIdentity  : 'identity';
KWTrue      : 'true';
KWFalse     : 'false';
KWWhite     : 'white' | 'White';
KWBlack     : 'black' | 'Black';
KWBump      : 'bump'  | 'Bump';

WhiteSpace  : [ \t\n\r]+          -> skip;
LineComment : '//' .*? '\r'? '\n' -> skip;
Comment     : '/*' .*? '*/'       -> skip;
