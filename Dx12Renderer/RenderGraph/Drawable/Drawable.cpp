#include "Drawable.h"
#include <RenderGraph/Technique/Technique.h>
#include "Dx12lib/Buffer/IndexBuffer.h"
#include "Dx12lib/Buffer/VertexBuffer.h"
#include "RenderGraph/Job/TransformCBufferPtr.h"

namespace rgph {

auto Drawable::getGeometry() const -> std::shared_ptr<Geometry> {
	return _pGeometry;
}

auto Drawable::getTransformCBuffer() const -> TransformCBufferPtr {
	return _pTransformCBuf;
}

void Drawable::setGeometry(std::shared_ptr<Geometry> pGeometry) {
	assert(pGeometry != nullptr);
	_pGeometry = std::move(pGeometry);
}

void Drawable::setTransformCBuffer(TransformCBufferPtr pTransformCBuffer) {
	_pTransformCBuf = std::move(pTransformCBuffer);
}

}
