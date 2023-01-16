#include "UUIDRandomGenerator.h"
#include <chrono>

namespace Eureka {

#pragma region UUID_Random_Generator

std::unique_ptr<UUIDRandomGenerator> UUIDRandomGenerator::pInst = std::make_unique<UUIDRandomGenerator>();

auto UUIDRandomGenerator::instance() -> UUIDRandomGenerator *{
	return pInst.get();
}

auto UUIDRandomGenerator::newUUID() -> UUID128 {
	return UUID128{ (*pInst->_pUuidGenerator)() };
}

UUIDRandomGenerator::UUIDRandomGenerator() {
	auto currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();
	std::mt19937 generator(timestamp);
	_pUuidGenerator = std::make_unique<uuids::uuid_random_generator>(generator);
}

#pragma endregion UUID_Random_Generator

#pragma region UUID_Name_Generator

UUIDNameGenerator::UUIDNameGenerator(const UUID128 &kind) {
	_pUuidGenerator = std::make_unique<uuids::uuid_name_generator>(kind);
}

auto UUIDNameGenerator::newUUID(const std::string &name) -> UUID128 {
	return UUID128{ (*_pUuidGenerator)(name) };
}

#pragma endregion UUID_Name_Generator

}
