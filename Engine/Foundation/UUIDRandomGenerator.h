#pragma once
#include <uuid.h>
#include "Singletion.hpp"

namespace Eureka {

namespace UUID = uuids;

// UUID128 wrapper 
class UUID128 : public uuids::uuid {
public:
	using uuids::uuid::uuid;
	UUID128(const uuids::uuid &other) : uuids::uuid(other) {
	}
};

class UUIDRandomGenerator : public Singletion<UUIDRandomGenerator> {
public:
	UUIDRandomGenerator();
	static auto newUUID() -> UUID128;
private:
	std::unique_ptr<uuids::uuid_random_generator> _pUuidGenerator;
};

class UUIDNameGenerator {
public:
	UUIDNameGenerator(const UUID128 &kind);
	auto newUUID(const std::string &name) -> UUID128;
private:
	std::unique_ptr<uuids::uuid_name_generator> _pUuidGenerator;
};

}
