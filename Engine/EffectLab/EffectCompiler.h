#pragma once
#pragma push_macro("ERROR")
#undef ERROR

#include "Antlr4Codegen/EffectLabBaseVisitor.h"
#include "EffectParser/BaseParser.h"
#include "Effect.h"
#include "Pass.h"
#include "PropertyItem.h"
#include <filesystem>

namespace Eureka {

namespace fs = std::filesystem;
namespace pd = ParserDetails;

class EffectErrorListener : public antlr4::BaseErrorListener {
public:
	void syntaxError(antlr4::Recognizer *recognizer,
		antlr4::Token *offendingSymbol,
		size_t line,
		size_t charPositionInLine,
		const std::string &msg,
		std::exception_ptr e
	) override;
};

class EffectCompiler : public BaseParser, private NonCopyable {
public:
	EffectCompiler();
	~EffectCompiler() override;
	auto compile(const fs::path &effectSourcePath) -> std::shared_ptr<Effect>;
	std::any visitEffect(pd::EffectLabParser::EffectContext *context) override;
	std::any visitHlsl_include_block(ParserDetails::EffectLabParser::Hlsl_include_blockContext *context) override;
private:
	Location    _hlslIncludeBlock;
	std::string _effectSourcePath;
};

}

#pragma pop_macro("ERROR")
