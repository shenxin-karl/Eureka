#pragma once
#include <memory>
#include <vector>
#include "BaseAST.hpp"

namespace EC {

class PropertyItem;
class PropertySet : public BaseAST {
public:
	std::vector<std::unique_ptr<PropertyItem>> items;
};

}
