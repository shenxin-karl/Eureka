#include <comdef.h>
#include "Exception.h"

namespace dx12lib {

Exception::Exception(const std::string &message, const std::source_location &sourceLocation)
: _line(sourceLocation.line()), _file(sourceLocation.file_name())
, _func(sourceLocation.function_name()) {
	_whatBuffer = std::format("[File]: {}\n[Line]: {}\n[Function]: {}, [Message]: {}",
		_file, _line, _func, message
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

const char *D3DException::what() const noexcept {
	if (_whatBuffer.empty())
		_whatBuffer = std::format("file: {} line: {} message: {}", _file, _line, getErrorString());
	return _whatBuffer.c_str();
}

std::string D3DException::getErrorString() const {
	_com_error err(_hr);
	std::string msg = err.ErrorMessage();
	return msg;
}

NotImplementedException::NotImplementedException(const char *func) : _func(func) {

}

const char * NotImplementedException::what() const noexcept {
	if (_whatBuffer.empty())
		_whatBuffer = std::format("Function: {} not implemented!", _func);
	return _whatBuffer.c_str();
}

}
