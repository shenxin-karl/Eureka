#include "PassResourceBase.h"

#include <cassert>

#include "ExecutablePass.h"

namespace rgph {

PassResourceBase::PassResourceBase(ExecutablePass *pExecutablePass, std::string resourceName, bool activate)
: _resourceName(std::move(resourceName)), _pExecutablePass(pExecutablePass)
, _finished(false), _activated(activate),  _pResourceSource(nullptr)
{
	if (activate)
		pExecutablePass->addPassResource(this);
}

void PassResourceBase::setFinished(bool bCond) {
	_finished = bCond;
}

bool PassResourceBase::isFinished() const {
	return _finished;
}

bool PassResourceBase::isActivated() const {
	return _activated;
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
