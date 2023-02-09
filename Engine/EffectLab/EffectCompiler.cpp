#include "EffectCompiler.h"
#include "Antlr4Codegen/EffectLabLexer.h"
#include "Foundation/Exception.h"
#include "Objects/PathManager.h"
#include "EffectParser/PropertyBlockParser.h"
#include <fstream>

#include "EffectParser/PassParser.h"

namespace Eureka {

void EffectErrorListener::syntaxError(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, 
	size_t line,
	size_t charPositionInLine, 
	const std::string &msg, 
	std::exception_ptr e)
{
	Exception::Throw("line {}:{}, current token type {}, error message: {}", 
		line, 
		charPositionInLine, 
		offendingSymbol->getType(),
		msg
	);
}

EffectCompiler::EffectCompiler() {
}

EffectCompiler::~EffectCompiler() {

}

auto EffectCompiler::compile(const fs::path &effectSourcePath) -> std::unique_ptr<Effect> {
	_effectSourcePath = effectSourcePath.string();

	std::ifstream fin;
	if (!PathManager::open(effectSourcePath, fin, std::ios::in)) {
		Exception::Throw("can't open the file {}!", effectSourcePath.string());
	}

	antlr4::ANTLRInputStream input(fin);
	pd::EffectLabLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	pd::EffectLabParser parser(&tokens);

	EffectErrorListener errorListener;
	parser.removeErrorListeners();
	parser.addErrorListener(&errorListener);
	return any_to_unique_ptr<Effect>(visitEffect(parser.effect()));
}

std::any EffectCompiler::visitEffect(pd::EffectLabParser::EffectContext *context) {
	auto pEffect = make_any_unique_ptr<Effect>();
	pEffect->_sourcePath = std::any_cast<fs::path>(visitSource_path(context->source_path()));
	if (!PathManager::exist(pEffect->_sourcePath)) {
		Exception::Throw("in file: {}, SourcePath: {} invalid!", 
			_effectSourcePath,
			pEffect->_sourcePath.string()
		);
	}

	if (context->property_block() != nullptr) {
		PropertyBlockParser propertyBlockParser(_effectSourcePath);
		pEffect->_propertyBlock = propertyBlockParser.parserPropertyBlock(context->property_block());
	}

	for (auto *pPassCtx : context->pass()) {
		PassParser passParser(_effectSourcePath);
		pEffect->_passes.push_back(passParser.parse(pPassCtx));
	}

	return pEffect;
}

std::any EffectCompiler::visitSource_path(pd::EffectLabParser::Source_pathContext *context) {
	auto text = context->StringLiteral()->getText();
	fs::path sourcePath = text.substr(1, text.length()-2);
	return sourcePath;
}

}
