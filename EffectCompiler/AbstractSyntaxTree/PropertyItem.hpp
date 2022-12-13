#pragma once
#include "BaseAST.hpp"
#include <string>

namespace Eureka {

class PropertyItem : public BaseAST {
public:
	std::string uniformName;
	PropertyItem *pNext = nullptr;
};

}
