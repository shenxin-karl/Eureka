#include "EffectCompiler.h"
#include "Antlr4Codegen/EffectLabLexer.h"
#include "Foundation/Exception.h"
#include <fstream>

#include "Effect.h"
#include "Pass.h"
#include "PropertyBlock.h"
#include "Math/MathStd.hpp"
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
		pd::EffectLabLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		pd::EffectLabParser parser(&tokens);

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

std::any EffectCompiler::visitEffect(pd::EffectLabParser::EffectContext *context) {
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

std::any EffectCompiler::visitSource_path(pd::EffectLabParser::Source_pathContext *context) {
	fs::path sourcePath = context->String()->getText();
	return sourcePath;
}

std::any EffectCompiler::visitProperty_block(pd::EffectLabParser::Property_blockContext *context) {
	if (context->property_item().empty()) {
		return make_any_nullptr<PropertyBlock>();
	}

	auto *pPropertyBlock = make_any_unique_ptr<PropertyBlock>();
	for (auto *pPropertyItem : context->property_item()) {
		
	}
}

std::any EffectCompiler::visitNumber_val(pd::EffectLabParser::Number_valContext *context) {
	if (context->IntVal()) {
		return static_cast<float>(std::stoi(context->IntVal()->getText()));
	}
	if (context->FloatVal()) {
		return std::stof(context->FloatVal()->getText());
	}
	return 0.f;
}

std::any EffectCompiler::visitProperty_bool_val(pd::EffectLabParser::Property_bool_valContext *context) {
	auto text = context->BoolVal()->getText();
	return text == "true";
}

std::any EffectCompiler::visitProperty_int_val(pd::EffectLabParser::Property_int_valContext *context) {
	auto text = context->IntVal()->getText();
	return std::stoi(text);
}

std::any EffectCompiler::visitProperty_float_val(pd::EffectLabParser::Property_float_valContext *context) {
	return visitNumber_val(context->number_val());
}

std::any EffectCompiler::visitProperty_float2_val(pd::EffectLabParser::Property_float2_valContext *context) {
	return Math::float2 {
		std::any_cast<float>(visitNumber_val(context->number_val(0))),
		std::any_cast<float>(visitNumber_val(context->number_val(1))),
	};
}

std::any EffectCompiler::visitProperty_float3_val(pd::EffectLabParser::Property_float3_valContext *context) {
	return Math::float3 {
		std::any_cast<float>(visitNumber_val(context->number_val(0))),
		std::any_cast<float>(visitNumber_val(context->number_val(1))),
		std::any_cast<float>(visitNumber_val(context->number_val(2))),
	};
}

std::any EffectCompiler::visitProperty_float4_val(pd::EffectLabParser::Property_float4_valContext *context) {
	return Math::float4 {
		std::any_cast<float>(visitNumber_val(context->number_val(0))),
		std::any_cast<float>(visitNumber_val(context->number_val(1))),
		std::any_cast<float>(visitNumber_val(context->number_val(2))),
		std::any_cast<float>(visitNumber_val(context->number_val(3))),
	};
}

std::any EffectCompiler::visitProperty_texture_val(pd::EffectLabParser::Property_texture_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_matrix_val(pd::EffectLabParser::Property_matrix_valContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_name(pd::EffectLabParser::Property_nameContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_description(pd::EffectLabParser::Property_descriptionContext *context) {
	return {};
}

std::any EffectCompiler::visitProperty_item(pd::EffectLabParser::Property_itemContext *context) {
	return {};
}

}
