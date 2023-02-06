#pragma once
#include <memory>
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>
#include <RenderGraph/Job/TransformCBufferPtr.h>

namespace rgph {

class Drawable : public IDrawable {
public:
	Drawable() = default;
	~Drawable() override = default;
	auto getGeometry() const -> std::shared_ptr<Geometry>;
	auto getTransformCBuffer() const -> TransformCBufferPtr;
	void setGeometry(std::shared_ptr<Geometry> pGeometry);
	void setTransformCBuffer(TransformCBufferPtr pTransformCBuffer);
protected:
	std::shared_ptr<Geometry> _pGeometry;
	TransformCBufferPtr _pTransformCBuf;
};

}
