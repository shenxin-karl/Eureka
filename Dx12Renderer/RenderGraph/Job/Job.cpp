#include "Job.h"
#include "Geometry.h"
#include "TransformCBufferPtr.h"
#include "Dx12lib/Pipeline/ShaderRegister.hpp"
#include "RenderGraph/Drawable/Drawable.h"
#include "RenderGraph/Technique/Step.h"

namespace rgph {

Job::Job(const Step *pStep, const Geometry *pGeometry, const TransformCBufferPtr *pTransformCBuffer)
:  pStep(pStep), pGeometry(pGeometry), pTransformCBuffer(pTransformCBuffer)
{
	assert(pStep != nullptr);
	assert(pGeometry != nullptr);
	assert(pTransformCBuffer != nullptr);
	assert((*pTransformCBuffer) != nullptr);
}

void Job::execute(dx12lib::IGraphicsContext &graphicsCtx, 
	const VertexInputSlots &vertexInputSlots,
	const dx12lib::ShaderRegister &transformCBufferReg) const
{
	assert(pStep != nullptr);
	assert(pGeometry != nullptr);
	assert(pTransformCBuffer != nullptr);

	pGeometry->bind(graphicsCtx, vertexInputSlots);
	pStep->bind(graphicsCtx);

	if (pTransformCBuffer != nullptr) {
		assert(static_cast<bool>(transformCBufferReg.slot));
		pTransformCBuffer->bind(graphicsCtx, transformCBufferReg);
	}
	pGeometry->draw(graphicsCtx);
}
}
