#pragma once
#include <memory>
#include "BaseAST.hpp"

namespace Eureka {

struct CompUnitAst : public BaseAST {
	std::unique_ptr<BaseAST> pProperties;
};

}
