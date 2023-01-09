#pragma once
#include <exception>
#include <string>
#include <source_location>
#include <format>
#include <Windows.h>

namespace dx12lib {

struct FormatAndLocation {
	std::string_view fmt;
	std::source_location location;
public:
	template<size_t N>
	FormatAndLocation(const char(&arr)[N], const std::source_location &location = std::source_location::current())
	: fmt(arr), location(location) {

	}
	FormatAndLocation(const std::string_view &fmt, const std::source_location &location = std::source_location::current())
	: fmt(fmt), location(location) {

	}
};

class Exception : public std::exception {
public:
	Exception(const std::string &message, const std::source_location &sourceLocation);
	auto what() const noexcept -> const char* override;
	auto getLine() const noexcept -> int;
	auto getFile() const noexcept -> const char *;
	auto getFunc() const noexcept -> const char *;
	auto getMessage() const noexcept -> const std::string &;

	template<typename ...Args>
	static void Throw(const FormatAndLocation &fmtAndLocation, Args&&...args) {
		std::string message;
		if constexpr (sizeof...(Args))
			message = std::vformat(fmtAndLocation.fmt, std::make_format_args(args...));
		else
			message = fmtAndLocation.fmt.data();
		throw Exception(std::move(message), fmtAndLocation.location);
	}
	template<typename ...Args>
	static void Throw(bool cond, const FormatAndLocation &fmtAndLocation, Args&&...args) {
		if (!cond)
			Exception::Throw(fmtAndLocation, std::forward<Args>(args)...);
	}
protected:
	int	         _line;
	const char  *_file;
	const char	*_func;
	std::string	 _message;
	std::string  _whatBuffer;
};

class D3DException : public std::exception {
public:
	D3DException(HRESULT hr, const char *file, int line);
	D3DException(HRESULT hr, const std::string &errorMessage, const char *file, int line);
	auto what() const noexcept -> const char* override;
	auto getHResultMessage() const -> std::string;
	auto getErrorMessage() const -> const std::string &;
	static void Throw(HRESULT hr, std::source_location sourceLocation = std::source_location::current()) {
		if (FAILED(hr)) {
			throw D3DException(hr, sourceLocation.file_name(), sourceLocation.line());
		}
	}
	static void Throw(HRESULT hr, const std::string &errorMessage, std::source_location sourceLocation = std::source_location::current()) {
		if (FAILED(hr)) {
			throw D3DException(hr, errorMessage, sourceLocation.file_name(), sourceLocation.line());
		}
	}
private:
	HRESULT				_hr;
	int					_line;
	const char *		_file;
	std::string			_errorMessage;
	mutable std::string _whatBuffer;
};

class NotImplementedException : public std::exception {
public:
	explicit NotImplementedException(const char *func);
	auto what() const noexcept -> const char *override;
	static void Throw(const std::source_location &sourceLocation = std::source_location::current()) {
		throw NotImplementedException(sourceLocation.function_name());
	}
private:
	const char		   *_func;
	mutable std::string _whatBuffer;
};

}