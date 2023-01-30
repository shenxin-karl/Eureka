#include "EffectCompiler.h"
#include "Antlr4Codegen/EffectLabLexer.h"
#include "Foundation/Exception.h"
#include "Objects/PathManager.h"
#include <fstream>

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

	auto pPropertyBlock = make_any_unique_ptr<PropertyBlock>();
	for (auto *pPropertyItem : context->property_item()) {
		pPropertyBlock->addItem(any_to_unique_ptr<PropertyItem>(pPropertyItem->accept(this)));
	}
	return pPropertyBlock;
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

std::any EffectCompiler::visitProperty_range_type(ParserDetails::EffectLabParser::Property_range_typeContext *context) {
	return std::make_pair(
		std::any_cast<float>(visitNumber_val(context->number_val(0))),
		std::any_cast<float>(visitNumber_val(context->number_val(1)))
	);
}

std::any EffectCompiler::visitProperty_range_val(ParserDetails::EffectLabParser::Property_range_valContext *context) {
	return visitNumber_val(context->number_val());
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
	if (context->KWWhite()) {
		return PropertyTexture::White;
	}
	if (context->KWBlack()) {
		return PropertyTexture::Black;
	}
	if (context->KWBump()) {
		return PropertyTexture::Black;
	}
	return PropertyTexture::None;
}

std::any EffectCompiler::visitProperty_matrix_val(pd::EffectLabParser::Property_matrix_valContext *context) {
	return PropertyMatrix::Identity;
}

std::any EffectCompiler::visitPropertyItemBool(ParserDetails::EffectLabParser::PropertyItemBoolContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<bool>(visitProperty_bool_val(context->property_bool_val()));
	pPropertyItem->setBool(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemInt(ParserDetails::EffectLabParser::PropertyItemIntContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<int>(visitProperty_int_val(context->property_int_val()));
	pPropertyItem->setInt(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemRange(ParserDetails::EffectLabParser::PropertyItemRangeContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto rangeType = std::any_cast<std::pair<float, float>>(
		visitProperty_range_type(context->property_range_type())
	);
	PropertyRange range;
	range.min = rangeType.first;
	range.max = rangeType.second;
	range.val = std::any_cast<float>(visitProperty_range_val(context->property_range_val()));
	pPropertyItem->setRange(range);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemFloat(ParserDetails::EffectLabParser::PropertyItemFloatContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<float>(visitProperty_float_val(context->property_float_val()));
	pPropertyItem->setFloat(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemFloat2(ParserDetails::EffectLabParser::PropertyItemFloat2Context *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<Math::float2>(visitProperty_float2_val(context->property_float2_val()));
	pPropertyItem->setFloat2(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemFloat3(ParserDetails::EffectLabParser::PropertyItemFloat3Context *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<Math::float3>(visitProperty_float3_val(context->property_float3_val()));
	pPropertyItem->setFloat3(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemFloat4(ParserDetails::EffectLabParser::PropertyItemFloat4Context *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<Math::float4>(visitProperty_float4_val(context->property_float4_val()));
	pPropertyItem->setFloat4(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemTexture(ParserDetails::EffectLabParser::PropertyItemTextureContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<PropertyTexture>(visitProperty_texture_val(context->property_texture_val()));
	pPropertyItem->setTexture2D(val);
	return pPropertyItem;
}

std::any EffectCompiler::visitPropertyItemMatrix(ParserDetails::EffectLabParser::PropertyItemMatrixContext *context) {
	auto pPropertyItem = make_any_unique_ptr<PropertyItem>(context->Identity()->getText());
	pPropertyItem->setDescription(context->String()->getText());
	auto val = std::any_cast<PropertyMatrix>(visitProperty_matrix_val(context->property_matrix_val()));
	pPropertyItem->setMatrix(val);
	return pPropertyItem;
}


}
