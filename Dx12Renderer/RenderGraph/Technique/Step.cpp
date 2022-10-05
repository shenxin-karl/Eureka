#include "Step.h"
#include "RenderGraph/Bindable/Bindable.hpp"
#include "RenderGraph/Drawable/Drawable.h"
#include "RenderGraph/Job/Job.h"
#include "RenderGraph/Pass/RenderQueuePass.h"
#include "RenderGraph/Pass/SubPass.h"
#include "RenderGraph/RenderGraph/RenderGraph.h"

namespace rgph {

Step::Step(SubPass *pSubPass)
: _pSubPass(pSubPass)
{
}

void Step::addBindable(std::shared_ptr<Bindable> pBindable) {
	assert(pBindable != nullptr);
	_bindables.push_back(std::move(pBindable));
}

void Step::addBindables(std::vector<std::shared_ptr<Bindable>> bindables) {
	_bindables = std::move(bindables);
}

void Step::submit(const Geometry *pGeometry, const TransformCBufferPtr *pTransformCBuffer) const {
	assert(_pSubPass != nullptr);
	_pSubPass->accept({ this, pGeometry, pTransformCBuffer });
}

void Step::bind(dx12lib::IGraphicsContext &graphicsCtx) const {
	for (auto &pBindable : _bindables)
		pBindable->bind(graphicsCtx);
}

}
