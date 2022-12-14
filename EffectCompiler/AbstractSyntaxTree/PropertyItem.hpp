#pragma once
#include <string>
#include "BaseAST.hpp"
#include "Foundation/PropertyFundation.hpp"

namespace EC {

class PropertyItem : public BaseAST {
public:
	std::string   uniformName;
	std::string   propertyName;
	PropertyType  propertyType;
	PropertyValue propertyValue;
	PropertyItem *pNext = nullptr;
};

}
