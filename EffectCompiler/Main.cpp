#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <iostream>
#include "AbstractSyntaxTree/BaseAST.hpp"


extern FILE *yyin;
extern int yyparse(std::unique_ptr<Eureka::BaseAST> &ast);

int main() {
	yyin = fopen("Main.txt", "r");
	assert(yyin);

	// 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
	std::unique_ptr<Eureka::BaseAST> ast;
	auto ret = yyparse(ast);
	assert(!ret);

	// 输出解析得到的 AST, 其实就是个字符串
	//std::cout << *ast << std::endl;
	return 0;
}