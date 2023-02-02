#pragma once
#include "EffectLab/Antlr4Codegen/EffectLabBaseVisitor.h"

namespace Eureka {

namespace pd = Eureka::ParserDetails;
class BaseParser : public pd::EffectLabBaseVisitor {
public:
	template<typename T, typename...Args>
	static T *make_any_unique_ptr(Args&&...args) noexcept {
		return new T{ std::forward<Args>(args)... };
	}
	template<typename T>
	constexpr static T *make_any_nullptr() noexcept {
		return nullptr;
	}
	template<typename T, typename AnyType> requires(std::is_same_v<std::decay_t<AnyType>, std::any>)
		static std::unique_ptr<T> any_to_unique_ptr(AnyType &&any) noexcept {
		return std::unique_ptr<T>(std::any_cast<T *>(std::forward<AnyType>(any)));
	}

	template<typename T>
	struct MetaObject {
		size_t line   = -1;
		size_t column = -1;
		std::optional<T> pObject;
	public:
		bool hasValue() const noexcept {
			return pObject.has_value();
		}
	};
};

}
