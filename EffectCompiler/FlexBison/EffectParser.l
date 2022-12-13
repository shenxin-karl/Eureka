%option noyywrap
%option nounput
%option noinput
%option yylineno

%{
    #pragma warning(disable : 4005) 
    #pragma warning(disable : 4819) 

    #include <cstdlib>
    #include <string>
    /* 因为 Flex 会用到 Bison 中关于 token 的定义 */
    /* 所以需要 include Bison 生成的头文件 */
    #include "FlexBison/output/BisonEffectParser.hpp"

    using namespace std;
%}

/* 空白符和注释 */
WhiteSpace    [ \t\n\r]*
LineComment   "//".*
BlockComment  "/*".*?"*/"

/* 标识符 */
Identifier    [a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
Decimal                 [1-9][0-9]*
Octal                   0[0-7]*
Hexadecimal             0[xX][0-9a-fA-F]+
FloatingPoint           [-+]?[0-9]+"."[0-9]*[fF]
DoubleFloatingPoint     [-+]?[0-9]+"."[0-9]+


%%

{WhiteSpace}                { /* 忽略, 不做任何操作 */ }
{LineComment}               { /* 忽略, 不做任何操作 */ }
{BlockComment}              { /* 忽略, 不做任何操作 */ }
"int"                       { return KW_INT; }
"return"                    { return KW_RETURN; }
"Properties"|"properties"   { return KW_PROPERTIES; }
"Texture2D"|"texture2D"     { return KW_TEXTURE2D; }
"Color"|"color"             { return KW_COLOR; }
"Float"|"float"             { return KW_FLOAT; }
"Vector"|"vector"           { return KW_VECTOR; }
"Uint"|"uint"               { return KW_UINT; }
"Range"|"range"             { return KW_RANGE; }
{Identifier}                { yylval.str_val = new string(yytext); return IDENT; }
{Decimal}                   { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}                     { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Hexadecimal}               { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{FloatingPoint}             { yylval.float_val = strtof(yytext, nullptr); return FLOAT_CONST; }
{DoubleFloatingPoint}       { yylval.double_val = strtod(yytext, nullptr); return DOUBLE_CONST; }
.                           { return yytext[0]; }
%%