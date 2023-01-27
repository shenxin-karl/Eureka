#pragma once
#pragma push_macro("ERROR")
#undef ERROR

#include "Antlr4Codegen/EffectLabVisitor.h"
#include "Effect.h"
#include <filesystem>


namespace Eureka {

namespace fs = std::filesystem;

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

class EffectCompiler : ParserDetails::EffectLabVisitor {
public:
	EffectCompiler();
	~EffectCompiler() override;
	auto compile(const fs::path &effectSourcePath) -> std::unique_ptr<Effect>;
private:
	std::any visitEffect(ParserDetails::EffectLabParser::EffectContext *context) override;
	std::any visitSource_path(ParserDetails::EffectLabParser::Source_pathContext *context) override;
	std::any visitProperty_block(ParserDetails::EffectLabParser::Property_blockContext *context) override;
	std::any visitNumber_val(ParserDetails::EffectLabParser::Number_valContext *context) override;
	std::any visitProperty_bool_val(ParserDetails::EffectLabParser::Property_bool_valContext *context) override;
	std::any visitProperty_int_val(ParserDetails::EffectLabParser::Property_int_valContext *context) override;
	std::any visitProperty_float_val(ParserDetails::EffectLabParser::Property_float_valContext *context) override;
	std::any visitProperty_float2_val(ParserDetails::EffectLabParser::Property_float2_valContext *context) override;
	std::any visitProperty_float3_val(ParserDetails::EffectLabParser::Property_float3_valContext *context) override;
	std::any visitProperty_float4_val(ParserDetails::EffectLabParser::Property_float4_valContext *context) override;
	std::any visitProperty_texture_val(ParserDetails::EffectLabParser::Property_texture_valContext *context) override;
	std::any visitProperty_matrix(ParserDetails::EffectLabParser::Property_matrixContext *context) override;
	std::any visitProperty_name(ParserDetails::EffectLabParser::Property_nameContext *context) override;
	std::any visitProperty_description(ParserDetails::EffectLabParser::Property_descriptionContext *context) override;
	std::any visitProperty_item(ParserDetails::EffectLabParser::Property_itemContext *context) override;

	template<typename T, typename...Args>
	T *make_any_unique_ptr(Args&&...args) {
		return new T{ std::forward<Args>(args)... };
	}
	template<typename T, typename AnyType> requires(std::is_same_v<std::decay_t<AnyType>, std::any>)
	std::unique_ptr<T> any_to_unique_ptr(AnyType&& any) {
		return std::unique_ptr<T>(std::any_cast<T *>(std::forward<AnyType>(any)));
	}
private:
	fs::path _effectSourcePath;
};

}

#pragma pop_macro("ERROR")
