#include "EffectCompiler.h"
#include "Antlr4Codegen/EffectLabLexer.h"
#include "Foundation/Exception.h"
#include <fstream>

#include "Effect.h"
#include "Pass.h"
#include "PropertyBlock.h"
#include "Objects/PathManager.h"

namespace Eureka {

void EffectErrorListener::syntaxError(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, 
	size_t line,
	size_t charPositionInLine, 
	const std::string &msg, 
	std::exception_ptr e)
{
	Exception::Throw("line {}:{} {}", line, charPositionInLine, msg);
}

EffectCompiler::EffectCompiler() {
}

EffectCompiler::~EffectCompiler() {

}

auto EffectCompiler::compile(const fs::path &effectSourcePath) -> std::unique_ptr<Effect> {
	_effectSourcePath = effectSourcePath;

	std::ifstream fin;
	if (!PathManager::open(effectSourcePath, fin, std::ios::in)) {
		Exception::Throw("can't open the file {}!", effectSourcePath.string());
	}

	try {
		antlr4::ANTLRInputStream input(fin);
		ParserDetails::EffectLabLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		ParserDetails::EffectLabParser parser(&tokens);

		EffectErrorListener errorListener;
		parser.removeErrorListeners();
		parser.addErrorListener(&errorListener);
		return std::unique_ptr<Effect>(std::any_cast<Effect *>(visitEffect(parser.effect())));
	} catch (const Exception &e) {
		Exception::Throw("compile the file: {}, error message: {}", 
			effectSourcePath.string(), 
			e.getMessage()
		);
	}
	return nullptr;
}

std::any EffectCompiler::visitEffect(ParserDetails::EffectLabParser::EffectContext *context) {
	auto pEffect = make_any_unique_ptr<Effect>();
	pEffect->_sourcePath = std::any_cast<fs::path>(visitSource_path(context->source_path()));
	if (!PathManager::exist(pEffect->_sourcePath)) {
		Exception::Throw("in file: {}, SourcePath: {} invalid!", 
			_effectSourcePath.string(),
			pEffect->_sourcePath.string()
		);
	}

	if (context->property_block() != nullptr) {
		pEffect->_propertyBlock = any_to_unique_ptr<PropertyBlock>(
			visitProperty_block(context->property_block())
		);
	}
	return pEffect;
}

std::any EffectCompiler::visitSource_path(ParserDetails::EffectLabParser::Source_pathContext *context) {
	fs::path sourcePath = context->String()->getText();
	return sourcePath;
}

std::any EffectCompiler::visitProperty_block(ParserDetails::EffectLabParser::Property_blockContext *context) {
	return {};
}

std::any EffectCompiler::visitNumber_val(ParserDetails::EffectLabParser::Number_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_bool_val(ParserDetails::EffectLabParser::Property_bool_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_int_val(ParserDetails::EffectLabParser::Property_int_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_float_val(ParserDetails::EffectLabParser::Property_float_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_float2_val(ParserDetails::EffectLabParser::Property_float2_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_float3_val(ParserDetails::EffectLabParser::Property_float3_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_float4_val(ParserDetails::EffectLabParser::Property_float4_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_texture_val(ParserDetails::EffectLabParser::Property_texture_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_matrix(ParserDetails::EffectLabParser::Property_matrixContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_name(ParserDetails::EffectLabParser::Property_nameContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_description(ParserDetails::EffectLabParser::Property_descriptionContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_item(ParserDetails::EffectLabParser::Property_itemContext *context) {
	return {};
}

}
