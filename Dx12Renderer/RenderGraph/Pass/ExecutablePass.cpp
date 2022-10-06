#include "ExecutablePass.h"
#include "RenderGraph/Bindable/Bindable.hpp"

namespace rgph {

ExecutablePass::ExecutablePass(const std::string &passName) : _passName(passName) {
}

PassResourceBase * ExecutablePass::getPassResource(const std::string &resourceName) const {
	for (auto *pPassResource : _passResources) {
		if (pPassResource->getResourceName() == resourceName)
			return pPassResource;
	}
	return nullptr;
}

const std::string &ExecutablePass::getPassName() const {
	return _passName;
}

void ExecutablePass::preExecute(dx12lib::DirectContextProxy pDirectCtx) {
	for (auto *pPassResource : _passResources) 
			pPassResource->link(*pDirectCtx);
}

void ExecutablePass::execute(dx12lib::DirectContextProxy pDirectCtx) {
}

void ExecutablePass::postExecute(dx12lib::DirectContextProxy pDirectCtx) {
	for (auto *pPassResource : _passResources)
		pPassResource->setFinished(true);
}

void ExecutablePass::reset() {
	for (auto *pPassResource : _passResources) {
		pPassResource->setFinished(false);
		pPassResource->reset();
	}
}

auto ExecutablePass::getPassType() const -> PassType {
	return PassType::ExecutablePass;
}

void ExecutablePass::addPassResource(PassResourceBase *pResource) {
	_passResources.push_back(pResource);
}

const std::vector<PassResourceBase *> & ExecutablePass::getPassResources() const {
	return _passResources;
}



}
