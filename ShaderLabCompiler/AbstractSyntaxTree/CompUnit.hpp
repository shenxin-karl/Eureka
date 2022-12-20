#pragma once
#include <memory>
#include "BaseAST.hpp"

namespace EC {

class PropertySet;
class CompUnit : public BaseAST {
public:
	std::unique_ptr<PropertySet> pPropertySet;
};

}
