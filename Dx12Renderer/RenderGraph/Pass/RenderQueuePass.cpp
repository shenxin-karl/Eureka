#include "RenderQueuePass.h"

#include <format>
#include <iostream>

#include "RenderGraph/Bindable/Bindable.hpp"
#include "RenderGraph/Pass/SubPass.h"

namespace rgph {

std::shared_ptr<SubPass> RenderQueuePass::getSubPassByName(const std::string &subPassName) const {
	for (auto &pSubPass : _subPasses) {
		if (pSubPass->getSubPassName() == subPassName)
			return pSubPass;
	}
	return nullptr;
}

void RenderQueuePass::addSubPass(std::shared_ptr<SubPass> pSubPass) {
	assert(pSubPass != nullptr);
	const std::string &subPassName = pSubPass->getSubPassName();
	for (auto &subPassPtr : _subPasses) {
		if (subPassPtr->getSubPassName() == subPassName) {
			assert(false);
			return;
		}
	}
	pSubPass->setGraphicsPass(this);
	_subPasses.push_back(std::move(pSubPass));
}


void RenderQueuePass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	bool hasJob = false;
	for (auto &pSubPass : _subPasses) {
		if (pSubPass->getJobCount() > 0) {
			hasJob = true;
			break;
		}
	}

	if (!hasJob)
		return;

	GraphicsPass::execute(pDirectCtx);
	auto iter = _subPasses.begin();
	while (iter != _subPasses.end()) {
		auto pSubPass = *iter;
		if (!pSubPass->valid()) {
			if (pSubPass->getJobCount() > 0)
				std::cerr << std::format("SubPass: {}, pos is empty, but job count > 0", pSubPass->getSubPassName());

			iter = _subPasses.erase(iter);
			continue;
		}

		pSubPass->bind(*pDirectCtx);
		auto passCBufferShaderRegister = pSubPass->getPassCBufferShaderRegister();
		if (_pPassCBuffer != nullptr && passCBufferShaderRegister.slot && !passCBufferShaderRegister.slot.isSampler())
			pDirectCtx->setConstantBuffer(passCBufferShaderRegister, _pPassCBuffer);

		pSubPass->execute(*pDirectCtx);
		++iter;
	}
}

void RenderQueuePass::reset() {
	ExecutablePass::reset();
	for (auto &pSubPass : _subPasses)
		pSubPass->reset();
}

void RenderQueuePass::setPassCBuffer(std::shared_ptr<dx12lib::IConstantBuffer> pCBuffer) {
	_pPassCBuffer = std::move(pCBuffer);
}

PassType RenderQueuePass::getPassType() const {
	return PassType::RenderQueuePass;
}

std::shared_ptr<dx12lib::IConstantBuffer> RenderQueuePass::getPassCBuffer() const {
	return _pPassCBuffer;
}

}
