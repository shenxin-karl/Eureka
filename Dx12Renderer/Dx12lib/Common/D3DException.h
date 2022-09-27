#pragma once
#define  NOMINMAX
#include <exception>
#include <string>
#include <Windows.h>

namespace d3d {

class ExceptionBase : public std::exception {
public:
	ExceptionBase(const char *file, int line);
	virtual const char *what() const noexcept override;
	virtual const char *getType() const noexcept;
	int getLine() const noexcept;
	const std::string &getFile() const noexcept;
	std::string getOriginString() const noexcept;
private:
	std::string	file_;
	int			line_;
protected:
	mutable std::string whatBuffer_;
};

class D3DException : public ExceptionBase {
public:
	D3DException(HRESULT hr, const char *file, int line);
	virtual const char *what() const noexcept override;
	virtual const char *getType() const noexcept override;
	std::string getErrorString() const;
public:
	HRESULT hr_;
};

}