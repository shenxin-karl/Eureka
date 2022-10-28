#include "RenderGraph.h"
#include <format>
#include <iostream>
#include "RenderGraph/Pass/ExecutablePass.h"
#include "RenderGraph/Pass/RenderQueuePass.h"

namespace rgph {

void RenderGraph::addPass(std::shared_ptr<ExecutablePass> pPass) {
	assert(getPass(pPass->getPassName()) == nullptr);
	_finalized = false;
	if (pPass->getPassType() == PassType::RenderQueuePass)
		_renderQueuePasses.push_back(std::static_pointer_cast<RenderQueuePass>(pPass));
	_passes.push_back(std::move(pPass));
}

ExecutablePass * RenderGraph::getPass(const std::string &passName) const {
	for (auto &pPass : _passes) {
		if (pPass->getPassName() == passName)
			return pPass.get();
	}
	return nullptr;
}

RenderQueuePass * RenderGraph::getRenderQueuePass(const std::string &passName) const {
	for (auto &pRenderQueuePass : _renderQueuePasses) {
		if (pRenderQueuePass->getPassName() == passName)
			return pRenderQueuePass.get();
	}
	return nullptr;
}

void RenderGraph::execute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view) {
	assert(_finalized);
	assert(!_executeList.empty());
	for (auto &pPass : _executeList) {
		pDirectCtx->beginEvent(pPass->getPassName());
		pPass->preExecute(*pDirectCtx, view);
		pPass->execute(*pDirectCtx, view);
		pPass->postExecute(*pDirectCtx, view);
		pDirectCtx->endEvent();
	}
	if (view.pProfiler)
		*view.pProfiler += pDirectCtx->getRenderProfiler();
}

void RenderGraph::reset() {
	assert(_finalized);
	assert(!_executeList.empty());
	for (auto &pPass : _executeList)
		pPass->reset();
}


void RenderGraph::finalize() {
	assert(!_finalized);
	_executeList.clear();

	auto passes = _passes;
	std::vector<std::shared_ptr<ExecutablePass>> pendingExecuteList;

	while (!passes.empty()) {
		auto iter = passes.begin();
		while (iter != passes.end()) {
			auto pPass = *iter;
			bool shouldExecute = true;
			for (auto *pPassResource : pPass->getPassResources()) {
				bool linkState = pPassResource->tryLink();
				auto *pResourceSource = pPassResource->getResourceSource();
				bool isFinished = pResourceSource == nullptr || pResourceSource->isFinished();
				if (!linkState || !isFinished) {
					shouldExecute = false;
					break;
				}
			}

			if (shouldExecute) {
				pendingExecuteList.push_back(std::move(pPass));
				iter = passes.erase(iter);
			} else {
				++iter;
			}
		}

		if (pendingExecuteList.empty()) {
			for (auto &pPass : passes) {
				auto pBindingPass = std::dynamic_pointer_cast<ExecutablePass>(pPass);
				assert(pBindingPass != nullptr);
				std::cerr << "{" << std::endl;
				{
					std::cerr << "\tPassName: " << pBindingPass->getPassName() << std::endl;
					std::cerr << "\tPassResourceCount: " << pBindingPass->getPassResources().size() << std::endl;
					std::cerr << "\t{" << std::endl;
					{
						for (auto *pPassResource : pBindingPass->getPassResources()) {
							std::cerr << "\t\t{" << std::endl;
							std::cerr << "\t\t\tPassResourceName: " << pPassResource->getResourceName() << std::endl;
							auto *pResourceSource = pPassResource->getResourceSource();
							std::string sourceState = "false";
							std::string sourceName = "nil";
							if (pResourceSource != nullptr) {
								sourceState = pPassResource->isFinished() ? "true" : "false";
								sourceName = std::format(
									"{}.{}",
									pResourceSource->getExecutablePass()->getPassName(),
									pResourceSource->getResourceName()
								);
							}
							std::cerr << "\t\t\tSourceName: " << sourceName << std::endl;
							std::cerr << "\t\t\tSourceState: " << sourceState << std::endl;
							std::string linkState = pPassResource->tryLink() ? "true" : "false";
							std::cerr << "\t\t\tLinkState: " << linkState << std::endl;
							std::cerr << "\t\t}" << std::endl;
						}
					}
					std::cerr << "\t}" << std::endl;
				}
				std::cerr << "}" << std::endl;
			}
			assert(false);
			return;
		} else {
			for (auto &pPass : pendingExecuteList) {
				auto pBindingPass = std::dynamic_pointer_cast<ExecutablePass>(pPass);
				assert(pBindingPass != nullptr);
				for (auto *pPassResource : pBindingPass->getPassResources())
					pPassResource->setFinished(true);
				_executeList.push_back(std::move(pPass));
			}
			pendingExecuteList.clear();
		}
	}

	for (auto &pass : _executeList)
		pass->reset();

	_finalized = true;
}

void RenderGraph::onResize(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) {
	for (auto &pass : _passes)
		pass->onResize(*pDirectCtx, width, height);
}

}
