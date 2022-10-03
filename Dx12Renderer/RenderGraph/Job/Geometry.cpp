#include "Geometry.h"

#include "Dx12lib/Buffer/IndexBuffer.h"
#include "Dx12lib/Buffer/VertexBuffer.h"

namespace rgph {

using namespace Math;

void Geometry::bind(dx12lib::IGraphicsContext &graphicsCtx, const ShaderLayoutMask &vertexInputMask) const {
	graphicsCtx.setPrimitiveTopology(_topology);
	for (size_t i = 0; i < ShaderLayoutIndex::Max; ++i) {
		ShaderLayoutIndex index(i);
		if (!(vertexInputMask & index))
			continue;

		assert(_pVertexBufferList[i] != nullptr);
		graphicsCtx.setVertexBuffer(_pVertexBufferList[i], static_cast<UINT>(i));
	}

	if (_pIndexBuffer != nullptr)
		graphicsCtx.setIndexBuffer(_pIndexBuffer);
}

void Geometry::setVertexBuffer(size_t idx, std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer) {
	assert(idx < dx12lib::kVertexBufferSlotCount);
	_pVertexBufferList[idx] = std::move(pVertexBuffer);
}

void Geometry::setIndexBuffer(std::shared_ptr<dx12lib::IndexBuffer> pIndexBuffer) {
	_pIndexBuffer = std::move(pIndexBuffer);
}

void Geometry::setMesh(std::shared_ptr<IMesh> pMesh) {
	_pMesh = std::move(pMesh);
}

std::shared_ptr<dx12lib::VertexBuffer> Geometry::getVertexBuffer(size_t idx) const {
	assert(idx < dx12lib::kVertexBufferSlotCount);
	return _pVertexBufferList[idx];
}

std::shared_ptr<dx12lib::IndexBuffer> Geometry::getIndexBuffer() const {
	return _pIndexBuffer;
}

std::shared_ptr<IMesh> Geometry::getMesh() const {
	return _pMesh;
}

void Geometry::setDrawArgs(const DrawArgs &drawArgs) {
	_drawArgs = drawArgs;
}

void Geometry::applyTransform(const Matrix4 &matWorld) {
	if (_pMesh != nullptr) {
		auto localAABB = _pMesh->getBoundingBox();
		_worldAABB = localAABB.transform(matWorld);
		return;
	}
	assert(false);
}

void Geometry::setTopology(D3D_PRIMITIVE_TOPOLOGY topology) {
	_topology = topology;
}

const DrawArgs & Geometry::getDrawArgs() const {
	return _drawArgs;
}

const BoundingBox & Geometry::getWorldAABB() const {
	return _worldAABB;
}

D3D_PRIMITIVE_TOPOLOGY Geometry::getTopology() const {
	return _topology;
}

void Geometry::genDrawArgs() {
	if (_pMesh == nullptr)
		return;

	_drawArgs.vertexCount = _pMesh->getPositions().size();
	_drawArgs.indexCount = _pMesh->getIndices().size();
	_topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void Geometry::draw(dx12lib::IGraphicsContext &graphicsCtx) const {
	if (_drawArgs.indexCount > 0) {
		graphicsCtx.drawIndexedInstanced(
			_drawArgs.indexCount,
			_drawArgs.instanceCount,
			_drawArgs.startIndexLocation,
			_drawArgs.baseVertexLocation,
			_drawArgs.startInstanceLocation
		);
	} else {
		graphicsCtx.drawInstanced(
			_drawArgs.vertexCount,
			_drawArgs.instanceCount,
			_drawArgs.baseVertexLocation,
			_drawArgs.startInstanceLocation
		);
	}
}

}
