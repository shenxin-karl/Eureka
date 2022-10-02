#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include "Geometry.h"

namespace rgph {

class Step;
class Geometry;
class TransformCBufferPtr;

struct Job {
	Job(const Step *pStep, const Geometry *pGeometry, const TransformCBufferPtr *pTransformCBuffer);
	void execute(dx12lib::IGraphicsContext &graphicsCtx, 
		const ShaderLayoutMask &vertexInputSlots,
		const dx12lib::ShaderRegister &transformCBufferReg
	) const;
public:
	const Step *pStep;
	const Geometry *pGeometry;
	const TransformCBufferPtr *pTransformCBuffer; 
};

}
