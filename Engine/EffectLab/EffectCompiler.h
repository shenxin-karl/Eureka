#pragma once
#pragma push_macro("ERROR")
#undef ERROR

#include "Antlr4Codegen/EffectLabBaseVisitor.h"
#include "Effect.h"
#include "Pass.h"
#include "PropertyItem.h"
#include "PropertyBlock.h"
#include "Math/MathStd.hpp"
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

class EffectCompiler : public pd::EffectLabBaseVisitor {
public:
	EffectCompiler();
	~EffectCompiler() override;
	auto compile(const fs::path &effectSourcePath)->std::unique_ptr<Effect>;
public:
	std::any visitEffect(pd::EffectLabParser::EffectContext *context) override;
	std::any visitSource_path(pd::EffectLabParser::Source_pathContext *context) override;
	std::any visitProperty_block(pd::EffectLabParser::Property_blockContext *context) override;
	std::any visitNumber_val(pd::EffectLabParser::Number_valContext *context) override;
	std::any visitProperty_range_type(ParserDetails::EffectLabParser::Property_range_typeContext *context) override;
	std::any visitProperty_range_val(ParserDetails::EffectLabParser::Property_range_valContext *context) override;
	std::any visitProperty_bool_val(pd::EffectLabParser::Property_bool_valContext *context) override;
	std::any visitProperty_int_val(pd::EffectLabParser::Property_int_valContext *context) override;
	std::any visitProperty_float_val(pd::EffectLabParser::Property_float_valContext *context) override;
	std::any visitProperty_float2_val(pd::EffectLabParser::Property_float2_valContext *context) override;
	std::any visitProperty_float3_val(pd::EffectLabParser::Property_float3_valContext *context) override;
	std::any visitProperty_float4_val(pd::EffectLabParser::Property_float4_valContext *context) override;
	std::any visitProperty_texture_val(pd::EffectLabParser::Property_texture_valContext *context) override;
	std::any visitProperty_matrix_val(pd::EffectLabParser::Property_matrix_valContext *context) override;
	std::any visitProperty_name(ParserDetails::EffectLabParser::Property_nameContext *context) override;
	std::any visitProperty_description(ParserDetails::EffectLabParser::Property_descriptionContext *context) override;
	std::any visitPropertyItemBool(ParserDetails::EffectLabParser::PropertyItemBoolContext *context) override;
	std::any visitPropertyItemInt(ParserDetails::EffectLabParser::PropertyItemIntContext *context) override;
	std::any visitPropertyItemRange(ParserDetails::EffectLabParser::PropertyItemRangeContext *context) override;
	std::any visitPropertyItemFloat(ParserDetails::EffectLabParser::PropertyItemFloatContext *context) override;
	std::any visitPropertyItemFloat2(ParserDetails::EffectLabParser::PropertyItemFloat2Context *context) override;
	std::any visitPropertyItemFloat3(ParserDetails::EffectLabParser::PropertyItemFloat3Context *context) override;
	std::any visitPropertyItemFloat4(ParserDetails::EffectLabParser::PropertyItemFloat4Context *context) override;
	std::any visitPropertyItemTexture(ParserDetails::EffectLabParser::PropertyItemTextureContext *context) override;
	std::any visitPropertyItemMatrix(ParserDetails::EffectLabParser::PropertyItemMatrixContext *context) override;
private:
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

	struct PropertyVar {
		size_t line = 0;
		size_t column = 0;
	};
private:
	std::string _effectSourcePath;
	std::unordered_map<std::string, PropertyVar> _propertyVars;
};

}

#pragma pop_macro("ERROR")
