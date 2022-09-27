#pragma once
#include <memory>
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>
#include <RenderGraph/Job/TransformCBufferPtr.h>
#include "RenderGraph/Drawable/TechniqueBuffer.h"

namespace rgph {

class Drawable : public IDrawable, public TechniqueBuffer {
public:
	Drawable() = default;
	~Drawable() override = default;
	void submit(const TechniqueFlag &techniqueFlag) const override;
	std::shared_ptr<Geometry> getGeometry() const;
	TransformCBufferPtr getTransformCBuffer() const;
	void setGeometry(std::shared_ptr<Geometry> pGeometry);
	void setTransformCBuffer(TransformCBufferPtr pTransformCBuffer);
protected:
	std::shared_ptr<Geometry> _pGeometry;
	TransformCBufferPtr _pTransformCBuf;
};

}
