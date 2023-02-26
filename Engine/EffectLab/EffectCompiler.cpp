#include "EffectCompiler.h"
#include "Antlr4Codegen/EffectLabLexer.h"
#include "Foundation/Exception.h"
#include "Objects/PathManager.h"
#include "EffectParser/PropertyBlockParser.h"
#include "EffectParser/PassParser.h"
#include <fstream>

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

auto EffectCompiler::compile(const fs::path &effectSourcePath) -> std::shared_ptr<Effect> {
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
	return std::any_cast<std::shared_ptr<Effect>>(visitEffect(parser.effect()));
}

std::any EffectCompiler::visitEffect(pd::EffectLabParser::EffectContext *context) {
	auto pEffect = std::make_shared<Effect>();
	if (context->property_block() != nullptr) {
		PropertyBlockParser propertyBlockParser(_effectSourcePath);
		pEffect->_propertyBlock = propertyBlockParser.parserPropertyBlock(context->property_block());
	}

	for (auto *pPassCtx : context->pass()) {
		PassParser passParser(_effectSourcePath);
		pEffect->_passes.push_back(passParser.parse(pPassCtx));
		auto &passShaderFeatures = passParser.getShaderFeatures();
	}

	return pEffect;
}

}
