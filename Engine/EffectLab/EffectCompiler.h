#pragma once
#pragma push_macro("ERROR")
#undef ERROR

#include "Antlr4Codegen/EffectLabVisitor.h"
#include "Effect.h"
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

class EffectCompiler : pd::EffectLabVisitor {
public:
	EffectCompiler();
	~EffectCompiler() override;
	auto compile(const fs::path &effectSourcePath)->std::unique_ptr<Effect>;
private:
	std::any visitEffect(pd::EffectLabParser::EffectContext *context) override;
	std::any visitSource_path(pd::EffectLabParser::Source_pathContext *context) override;
	std::any visitProperty_block(pd::EffectLabParser::Property_blockContext *context) override;
	std::any visitNumber_val(pd::EffectLabParser::Number_valContext *context) override;
	std::any visitProperty_bool_val(pd::EffectLabParser::Property_bool_valContext *context) override;
	std::any visitProperty_int_val(pd::EffectLabParser::Property_int_valContext *context) override;
	std::any visitProperty_float_val(pd::EffectLabParser::Property_float_valContext *context) override;
	std::any visitProperty_float2_val(pd::EffectLabParser::Property_float2_valContext *context) override;
	std::any visitProperty_float3_val(pd::EffectLabParser::Property_float3_valContext *context) override;
	std::any visitProperty_float4_val(pd::EffectLabParser::Property_float4_valContext *context) override;
	std::any visitProperty_texture_val(pd::EffectLabParser::Property_texture_valContext *context) override;
	std::any visitProperty_matrix_val(pd::EffectLabParser::Property_matrix_valContext *context) override;

	template<typename T, typename...Args>
	static T *make_any_unique_ptr(Args&&...args) noexcept {
		return new T{ std::forward<Args>(args)... };
	}
	template<typename T>
	constexpr static T *make_any_nullptr() noexcept {
		return nullptr;
	}
	template<typename T, typename AnyType> requires(std::is_same_v<std::decay_t<AnyType>, std::any>)
	static std::unique_ptr<T> any_to_unique_ptr(AnyType&& any) noexcept {
		return std::unique_ptr<T>(std::any_cast<T *>(std::forward<AnyType>(any)));
	}
private:
	fs::path _effectSourcePath;
};

}

#pragma pop_macro("ERROR")
