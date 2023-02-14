#pragma once
#include <optional>
#include "EffectLab/Antlr4Codegen/EffectLabBaseVisitor.h"
#include "Foundation/Exception.h"

namespace Eureka {

namespace pd = Eureka::ParserDetails;
class BaseParser : public pd::EffectLabBaseVisitor {
public:
	static inline std::any NullAny;

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

	static std::string extractString(const std::string &source) {
		return source.substr(1, source.length() - 2);
	}

	struct Location {
		size_t line	  = -1;
		size_t column = -1;
	public:
		void setLocation(const antlr4::Token *pToken) {
			line = pToken->getLine();
			column = pToken->getCharPositionInLine();
		}
		void resetLocation() {
			line = -1;
			column = -1;
		}
		bool valid() const {
			return line != -1 && column != -1;
		}
	};

	template<typename T>
	struct LocAndObject : public Location {
		std::optional<T> pObject;
	public:
		auto get() -> T & {
			return *pObject;
		}
		auto get() const -> const T & {
			return *pObject;
		}
		template<typename ...Args> requires(std::is_constructible_v<T, Args...>)
		auto set(Args&&...args) -> T & {
			pObject = std::make_optional<T>(std::forward<Args>(args)...);
			return get();
		}
		bool hasValue() const noexcept {
			return pObject.has_value();
		}
	};
};

}
