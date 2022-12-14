
%code requires {
    #include <memory>
    #include <string>
    #include "AbstractSyntaxTree/BaseAST.hpp"
    #include "AbstractSyntaxTree/CompUnit.hpp"
    #include "AbstractSyntaxTree/PropertySet.hpp"
    #include "AbstractSyntaxTree/PropertyItem.hpp"
}

%{
    #pragma warning(disable : 4065) 
    #pragma warning(disable : 4819) 
      
    #include <iostream>
    #include <memory>
    #include <string>
    extern int yylineno;

	namespace EC {
		class CompUnit;
	};

    /* 声明 lexer 函数和错误处理函数 */
    int yylex();
    void yyerror(std::unique_ptr<EC::CompUnit> &ast, const char *s);
%}

// 定义 parser 函数和错误处理函数的附加参数
%parse-param { std::unique_ptr<EC::CompUnit> &ast }

// yylval 的定义, 我们把它定义成了一个联合体 (union)
// 因为 token 的值有的是字符串指针, 有的是整数
// 之前我们在 lexer 中用到的 strVal 和 intVal 就是在这里被定义的
// 至于为什么要用字符串指针而不直接用 string 或者 unique_ptr<string>?
// 请自行 STFW 在 union 里写一个带析构函数的类会出现什么情况
%union {
    int                  intVal;
    uint32_t             uintVal;
    double               doubleVal;
    float                floatVal;
    std::string         *pString;
    EC::BaseAST         *pAst;
    EC::PropertyValue   *pPropertyValue;
}

// token 定义
%token KW_PROPERTIES
%token KW_TEXTURE2D
%token KW_COLOR
%token KW_RANGE
%token KW_FLOAT
%token KW_VECTOR
%token KW_UINT
%token KW_INT 
%token <pString>   IDENT
%token <pString>   STRING_IDENT
%token <intVal>    INT_CONST
%token <floatVal>  FLOAT_CONST
%token <doubleVal> DOUBLE_CONST

// 非终结符的类型定义
%type <pAst>    PropertySet PropertyItem PropertyItems
%type <intVal>  PropertyType

%type <floatVal>  ToFloat
%type <intVal>    ToInt
%type <uintVal>   ToUint

%type <pPropertyValue> PropertyValue PropertyValueTexture2D PropertyValueColor PropertyValueRange 
%type <pPropertyValue> PropertyValueFloat PropertyValueVector PropertyValueUint PropertyValueInt

// 开启bison完整的报错信息
%define parse.trace
%define parse.error detailed
%define parse.lac full

%%

CompUnit 
	: PropertySet {
        auto pComtUnit = std::make_unique<EC::CompUnit>();
        pComtUnit->pPropertySet = std::unique_ptr<EC::PropertySet>(
            static_cast<EC::PropertySet *>($1)
        );
		ast = std::move(pComtUnit);
	}
;

// property begin
    PropertySet
        : KW_PROPERTIES '{' '}' { 
            $$ = new EC::PropertySet(); 
        }
        | KW_PROPERTIES '{' PropertyItems '}' {  
            auto *pCurrItem = static_cast<EC::PropertyItem *>($3);
            auto *pPropertySet = new EC::PropertySet();
            while (pCurrItem != nullptr) {
                pPropertySet->items.push_back(std::unique_ptr<EC::PropertyItem>(pCurrItem));
                pCurrItem = pCurrItem->pNext;
            }
            $$ = pPropertySet;
        }
    ;
    PropertyItem
        : IDENT '(' STRING_IDENT ',' PropertyType ')' '=' PropertyValue { 
            auto pUniformName = std::unique_ptr<std::string>($1);
            auto pPropertyName = std::unique_ptr<std::string>($3);
            auto pPropertyValue = std::unique_ptr<EC::PropertyValue>($8);
            auto *pItem = new EC::PropertyItem();
            pItem->uniformName = std::move(*pUniformName);
            pItem->propertyName = std::move(*pPropertyName);
            pItem->propertyType = EC::PropertyType($5);
            pItem->propertyValue = std::move(*pPropertyValue);
            $$ = pItem;
        }
    ;
    PropertyItems
        : PropertyItem ',' PropertyItems { 
            auto *pCurrItem = static_cast<EC::PropertyItem *>($1);
            pCurrItem->pNext = static_cast<EC::PropertyItem *>($3); 
            $$ = pCurrItem; 
        }
        | PropertyItem ',' { 
            $$ = $1; 
        }
        | PropertyItem { 
            $$ = $1; 
        }
    ;
    PropertyType
        : KW_TEXTURE2D { $$ = static_cast<int>(EC::PropertyType::Texture2D); }
        | KW_COLOR     { $$ = static_cast<int>(EC::PropertyType::Color);     }
        | KW_RANGE     { $$ = static_cast<int>(EC::PropertyType::Range);     }
        | KW_FLOAT     { $$ = static_cast<int>(EC::PropertyType::Float);     }
        | KW_VECTOR    { $$ = static_cast<int>(EC::PropertyType::Vector);    }
        | KW_UINT      { $$ = static_cast<int>(EC::PropertyType::Uint);      }
        | KW_INT       { $$ = static_cast<int>(EC::PropertyType::Int); 	     }
    ;
    PropertyValue
        : PropertyValueTexture2D { $$ = $1; }
        | PropertyValueColor     { $$ = $1; }
        | PropertyValueRange     { $$ = $1; }
        | PropertyValueFloat     { $$ = $1; }
        | PropertyValueVector    { $$ = $1; }
        | PropertyValueUint      { $$ = $1; }
        | PropertyValueInt       { $$ = $1; }
    ;
    PropertyValueTexture2D 
        : KW_TEXTURE2D '(' STRING_IDENT ',' INT_CONST ')' {
            std::unique_ptr<std::string> pStringIdent($3);;
            EC::Texture2D tex2D;
            tex2D.defaultTex = std::move(*pStringIdent);
            tex2D.slot = $5;
            $$ = new EC::PropertyValue(std::move(tex2D));
        }
    ;
    PropertyValueColor 
        : KW_COLOR '(' ToFloat ',' ToFloat ',' ToFloat ',' ToFloat ')' {
            EC::Color color(static_cast<float>($3), static_cast<float>($5), static_cast<float>($7), static_cast<float>($9));
            $$ = new EC::PropertyValue(color);
        }
    ;
    PropertyValueRange
        : PropertyValueFloat '(' ToFloat ',' ToFloat ')' {
            EC::Range range(static_cast<float>($3), static_cast<float>($5));
            $$ = new EC::PropertyValue(range);
        }
    ;
    PropertyValueFloat
        : KW_FLOAT '(' ToFloat ')' {
            $$ = new EC::PropertyValue($3);
        }
    ;
    PropertyValueVector 
        : KW_VECTOR '(' ToFloat ',' ToFloat ',' ToFloat ',' ToFloat ')' {
            EC::Vector vector(static_cast<float>($3), static_cast<float>($5), static_cast<float>($7), static_cast<float>($9));
            $$ = new EC::PropertyValue(vector);
        }
    ;
    PropertyValueUint 
        : KW_UINT '(' ToUint ')' {
            $$ = new EC::PropertyValue($3);
        }
    ;
    PropertyValueInt 
        : KW_INT '(' ToInt ')' {
            $$ = new EC::PropertyValue($3);
        }
    ;
// property end

// type convert begin
    ToFloat
        : FLOAT_CONST   { $$ = $1; }
        | INT_CONST     { $$ = static_cast<float>($1); }
        | DOUBLE_CONST  { $$ = static_cast<float>($1); }
    ;
    ToInt
        : INT_CONST     { $$ = $1; }
        | FLOAT_CONST   { $$ = static_cast<int>($1); }
        | DOUBLE_CONST  { $$ = static_cast<int>($1); }
    ;
    ToUint
        : INT_CONST     { $$ = static_cast<int32_t>($1); }
        | FLOAT_CONST   { $$ = static_cast<int32_t>($1); }
        | DOUBLE_CONST  { $$ = static_cast<int32_t>($1); }
    ;
// type convert end

%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
extern int getCurrentLineNo();
extern int getCurrentColumnNo();
void yyerror(std::unique_ptr<EC::CompUnit> &ast, const char *s) {
    std::cerr << "line: " << getCurrentLineNo() << " " << "column: " << getCurrentColumnNo() << ", " << "error: " << s << std::endl;
}