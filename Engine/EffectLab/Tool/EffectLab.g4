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
property_texture_val    : String '{' '}';
property_matrix         : KWIdentity;

property_name        : Identity;
property_description : String;
property_item : property_name '(' property_description ',' ('bool'  | 'Bool') ')' ')' '=' property_bool_val
              | property_name '(' property_description ',' ('Int'   | 'int')  ')' ')' '=' property_int_val
              | property_name '(' property_description ',' ('Float' | 'float ')   ')' '=' property_float_val
              ;

// lex
BoolVal     : KWTrue | KWFalse;
IntVal      : [1-9][0-9]*;
FloatVal    : [0-9]+ . [0-9]* 'f'?;

String      : '"' .*? '"' ;
Identity    : [_a-zA-Z][a-zA-Z0-9_]*;
KWIdentity  : 'Identity';
KWTrue      : 'true';
KWFalse     : 'false';

WhiteSpace  : [ \t\n\r]+          -> skip;
LineComment : '//' .*? '\r'? '\n' -> skip;
Comment     : '/*' .*? '*/'       -> skip;
