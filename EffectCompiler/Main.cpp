#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <iostream>
#include "AbstractSyntaxTree/CompUnit.hpp"


extern FILE *yyin;
extern int yyparse(std::unique_ptr<EC::CompUnit> &ast);

int main() {
	yyin = fopen("Main.txt", "r");
	assert(yyin);

	// ���� parser ����, parser �������һ������ lexer ���������ļ���
	std::unique_ptr<EC::CompUnit> ast;
	auto ret = yyparse(ast);
	assert(!ret);

	// ��������õ��� AST, ��ʵ���Ǹ��ַ���
	//std::cout << *ast << std::endl;
	return 0;
}