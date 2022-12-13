#pragma once
#include <memory>
#include "BaseAST.hpp"

namespace Eureka {

class PropertySet;
class CompUnit : public BaseAST {
public:
	std::unique_ptr<PropertySet> pPropertySet;
};

}
