#pragma once
#include "BaseAST.hpp"
#include <vector>

namespace Eureka {

class PropertyItem;
class PropertySet : public BaseAST {
public:
	std::vector<std::unique_ptr<PropertyItem>> items;
};

}
