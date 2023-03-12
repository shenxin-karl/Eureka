#pragma once
#include "Foundation/NamedObject.hpp"
#include "Foundation/UUIDRandomGenerator.h"

namespace Eureka {

class Asset : public NamedObject {
public:
	Asset() = default;
	auto getUUID() const -> UUID128;
private:
	UUID128	_uuid128;
};

}
