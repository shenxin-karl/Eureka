#include <cassert>
#include "SubPass.h"
#include "SubPassDesc.h"

namespace Eureka {

SubPass::SubPass(std::shared_ptr<SubPassDesc> pSubPassDesc) : _pSubPassDesc(std::move(pSubPassDesc)) {
	assert(_pSubPassDesc != nullptr);
}

auto SubPass::getSubPassName() const -> const std::string & {
	return _pSubPassDesc->getSubPassName();
}

}
