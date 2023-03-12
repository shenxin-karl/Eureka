#pragma once
#include <string>
#include <string_view>
#include "NonCopyable.h"

namespace Eureka {

class NamedObject : public NonCopyable {
public:
	NamedObject() = default;
	NamedObject(std::string_view sv) : _name(sv.data()) {

	}
	void setName(std::string_view sv) {
		_name = { sv.data(), sv.length() };
	}
	auto getName() const -> const std::string & {
		return _name;
	}
private:
	std::string _name;
};

}
