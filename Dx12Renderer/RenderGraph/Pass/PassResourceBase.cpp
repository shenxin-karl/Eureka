#include "PassResourceBase.h"

#include <cassert>

#include "ExecutablePass.h"

namespace rgph {

PassResourceBase::PassResourceBase(ExecutablePass *pExecutablePass, std::string resourceName)
: _resourceName(std::move(resourceName)), _pExecutablePass(pExecutablePass)
, _finished(false), _pResourceSource(nullptr)
{
	pExecutablePass->addPassResource(this);
}

void PassResourceBase::setFinished(bool bCond) {
	_finished = bCond;
}

bool PassResourceBase::isFinished() const {
	return _finished;
}

void PassResourceBase::setResourceSource(const PassResourceBase *pResourceSource) {
	assert(_pResourceSource == nullptr);
	_pResourceSource = pResourceSource;
}

const std::string & PassResourceBase::getResourceName() const {
	return _resourceName;
}

const PassResourceBase * PassResourceBase::getResourceSource() const {
	return _pResourceSource;
}

const ExecutablePass * PassResourceBase::getExecutablePass() const {
	return _pExecutablePass;
}

}
