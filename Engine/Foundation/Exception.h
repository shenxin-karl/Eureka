#pragma once
#include <exception>
#include <string>
#include <format>

namespace Eureka {

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
		std::string message = std::vformat(fmt, std::make_format_args(args...));
		throw Exception(message);
	}
private:
	std::string _message;
};

}
