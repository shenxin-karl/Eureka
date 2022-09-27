#include <comdef.h>
#include "D3DException.h"
#include <sstream>
#include <iostream>

namespace d3d {

ExceptionBase::ExceptionBase(const char *file, int line) : file_(file), line_(line) {
}

const char *ExceptionBase::what() const noexcept {
	std::stringstream sbuf;
	sbuf << getType() << std::endl << getOriginString();
	//whatBuffer_ = std::format("{}\n{}", getType(), getOriginString());
	whatBuffer_ = sbuf.str();
	return whatBuffer_.c_str();
}

const char *ExceptionBase::getType() const noexcept {
	return "ExceptionBase";
}

int ExceptionBase::getLine() const noexcept {
	return line_;
}

const std::string &ExceptionBase::getFile() const noexcept {
	return file_;
}

std::string ExceptionBase::getOriginString() const noexcept {
	//return std::format("[File] {}\n[Line] {}\n", file_, line_);
	std::stringstream sbuf;
	sbuf << "[File]: " << file_ << std::endl << "[Line]: " << line_ << std::endl;
	return sbuf.str();
}

D3DException::D3DException(HRESULT hr, const char *file, int line)
	: hr_(hr), ExceptionBase(file, line) {}

const char *D3DException::what() const noexcept {
	ExceptionBase::what();
	whatBuffer_ += getErrorString();
	return whatBuffer_.c_str();
}

const char * D3DException::getType() const noexcept {
	return "D3DException";
}

std::string D3DException::getErrorString() const {
	_com_error err(hr_);
	std::string msg = err.ErrorMessage();
	return msg;
}

}