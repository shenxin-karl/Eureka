grammar EffectLab;

effect : source_path property_block?;

source_path    : 'SourcePath' ':' StringLiteral;
property_block : 'Properties' '{' property_item+ '}';

number_val 
    : IntLiteral 
    | FloatLiteral
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

// lex
IntLiteral 
    : [+-]? [1-9][0-9]*
    | '0'
    ;
FloatLiteral 
    : [+-]? [0-9]+ '.' [0-9]* [fF]?
    | '.' [0-9]+ [fF]?
    ;
BooleanLiteral
	: 'false'
	| 'true'
	;

StringLiteral : '"' .*? '"' ;
Identity      : [_a-zA-Z][a-zA-Z0-9_]*; 

WhiteSpace   : [ \t\n\r]+          -> skip;
LineComment  : '//' .*? '\r'? '\n' -> skip;
BlockComment : '/*' .*? '*/'       -> skip;
