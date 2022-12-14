%option noyywrap
%option nounput
%option noinput

%{
    #pragma warning(disable : 4005) 
    #pragma warning(disable : 4819) 

    static int gCurrentLineNo = 1;
	static int gCurrentColumnNo = 1;
	int getCurrentLineNo() {
		return gCurrentLineNo;
	}
	int getCurrentColumnNo() {
		return gCurrentColumnNo + yyleng;
	}
	static void updateLocation() {
		for (const char *ptr = yytext; *ptr != '\0'; ++ptr) {
			if (*ptr == '\n') {
				++gCurrentLineNo;
				gCurrentColumnNo = 1;
			} else {
				++gCurrentColumnNo;
			}
		}
	}
    #define YY_USER_ACTION updateLocation();

    #include <cstdlib>
    #include <string>
    /* 因为 Flex 会用到 Bison 中关于 token 的定义 */
    /* 所以需要 include Bison 生成的头文件 */
    #include "FlexBison/output/BisonEffectParser.hpp"
%}

/* 空白符和注释 */
WhiteSpace    [ \t\n\r]*
LineComment   "//".*
BlockComment  "/*".*?"*/"

/* 标识符 */
Identifier          [a-zA-Z_][a-zA-Z0-9_]*
StringIdentifier    "\""[a-zA-Z_][a-zA-Z0-9_]*"\""

/* 整数字面量 */
Decimal                 [+-]?[1-9][0-9]*
Octal                   0[0-7]*
Hexadecimal             0[xX][0-9a-fA-F]+
FloatingPoint           [-+]?[0-9]+"."[0-9]*[fF]
DoubleFloatingPoint     [-+]?[0-9]+"."[0-9]+


%%

{WhiteSpace}                { /* 忽略, 不做任何操作 */ }
{LineComment}               { /* 忽略, 不做任何操作 */ }
{BlockComment}              { /* 忽略, 不做任何操作 */ }
"Properties"|"properties"   { return KW_PROPERTIES; }
"Texture2D"|"texture2D"     { return KW_TEXTURE2D; }
"Color"|"color"             { return KW_COLOR; }
"Range"|"range"             { return KW_RANGE; }
"Float"|"float"             { return KW_FLOAT; }
"Vector"|"vector"           { return KW_VECTOR; }
"Uint"|"uint"               { return KW_UINT; }
"int"                       { return KW_INT; }
{Identifier}                { yylval.pString = new std::string(yytext); return IDENT; }
{StringIdentifier}          { yylval.pString = new std::string(yytext+1, yyget_leng()-2); return STRING_IDENT; }
{Decimal}                   { yylval.intVal = std::strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}                     { yylval.intVal = std::strtol(yytext, nullptr, 0); return INT_CONST; }
{Hexadecimal}               { yylval.intVal = std::strtol(yytext, nullptr, 0); return INT_CONST; }
{FloatingPoint}             { yylval.doubleVal = std::strtof(yytext, nullptr); return FLOAT_CONST; }
{DoubleFloatingPoint}       { yylval.doubleVal = std::strtod(yytext, nullptr); return DOUBLE_CONST; }
.                           { return yytext[0]; }
%%