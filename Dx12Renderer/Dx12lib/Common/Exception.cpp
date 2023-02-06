#include <comdef.h>
#include "Exception.h"
#include "Dx12lib/dx12libStd.h"
#include <fmt/format.h>

namespace dx12lib {

Exception::Exception(const std::string &message, const std::source_location &sourceLocation)
: _line(sourceLocation.line()), _file(sourceLocation.file_name())
, _func(sourceLocation.function_name())
{
	_message = message;
	_whatBuffer = fmt::format("[Message]: {}\n[Function]: {}\n[File]: {}\n[Line]: {}\n",
		message, _func, _file, _line
	);
}

const char *Exception::what() const noexcept {
	return _whatBuffer.c_str();
}

int Exception::getLine() const noexcept {
	return _line;
}

const char *Exception::getFile() const noexcept {
	return _file;
}

auto Exception::getFunc() const noexcept -> const char * {
	return _func;
}

const std::string &Exception::getMessage() const noexcept {
	return _message;
}

D3DException::D3DException(HRESULT hr, const char *file, int line)
: _hr(hr), _line(line), _file(file) {
	
}

D3DException::D3DException(HRESULT hr, const std::string &errorMessage, const char *file, int line)
: _hr(hr), _line(line), _file(file), _errorMessage(errorMessage) {

}

const char *D3DException::what() const noexcept {
	if (_whatBuffer.empty())
		_whatBuffer = fmt::format("file: {} line: {} message: {}", _file, _line, getHResultMessage());
	return _whatBuffer.c_str();
}

std::string D3DException::getHResultMessage() const {
	_com_error err(_hr);
	std::string msg(to_string(err.ErrorMessage()));
	return msg;
}

auto D3DException::getErrorMessage() const -> const std::string & {
	return _errorMessage;
}

NotImplementedException::NotImplementedException(const char *func) : _func(func) {

}

const char * NotImplementedException::what() const noexcept {
	if (_whatBuffer.empty())
		_whatBuffer = fmt::format("Function: {} not implemented!", _func);
	return _whatBuffer.c_str();
}

}
