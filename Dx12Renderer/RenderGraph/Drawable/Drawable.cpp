#include "Drawable.h"
#include <RenderGraph/Technique/Technique.h>
#include "Dx12lib/Buffer/IndexBuffer.h"
#include "Dx12lib/Buffer/VertexBuffer.h"
#include "RenderGraph/Job/TransformCBufferPtr.h"

namespace rgph {

void Drawable::submit(const TechniqueFlag &techniqueFlag) const {
	assert(_pGeometry != nullptr);
	for (auto &pTechnique : getTechniques()) {
		pTechnique->submit(
			techniqueFlag,
			_pGeometry.get(),
			&_pTransformCBuf
		);
	}
}

std::shared_ptr<Geometry> Drawable::getGeometry() const {
	return _pGeometry;
}

TransformCBufferPtr Drawable::getTransformCBuffer() const {
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
