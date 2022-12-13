#pragma once
#include "BaseAST.hpp"
#include <string>

namespace Eureka {

class PropertyItem : public BaseAST {
public:
	
public:
	std::string uniformName;
	std::string propertyName;
	PropertyItem *pNext = nullptr;
};

}
