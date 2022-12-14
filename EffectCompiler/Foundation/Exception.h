#pragma once
#include <exception>
#include <string>
#include <format>

namespace EC {

class Exception : public std::exception {
public:
	Exception(std::string msg) : _message(std::move(msg)) {

	}
	char const *what() const final {
		return _message.data();
	}
	static void Throw(const char *msg) {
		throw Exception(msg);
	}
	template<typename...Args>
	static void Throw(std::string_view fmt, Args&&...args) {
		std::string message;
		if constexpr (sizeof...(args) > 0) 
			message = std::vformat(fmt, std::make_format_args(args...));
		else
			message = fmt.data();
		throw Exception(message);
	}
	template<typename...Args>
	static void Assert(bool condition, std::string_view fmt, Args&&...args) {
		if (!condition)
			Throw(fmt, std::format<Args>(args)...);
	}
private:
	std::string _message;
};

}
