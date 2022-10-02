#include <format>
#include "RenderItem.h"
#include "D3D/Model/IModel.hpp"
#include "RenderGraph/Material/Material.h"

namespace d3d {

using namespace Math;

RenderItem::RenderItem(dx12lib::IDirectContext &directCtx, INode *pNode, size_t meshIdx) {
	auto pALMesh = pNode->getMesh(meshIdx);
	_pGeometry = std::make_shared<rgph::Geometry>();
	_pGeometry->setMesh(pALMesh);
	_pGeometry->genDrawArgs();
	_pTransformCBuf = pNode->getNodeTransformCBuffer();

	const auto &indices = pALMesh->getIndices();
	if (indices.size() < 3)
		return;

	std::shared_ptr<dx12lib::IndexBuffer> pIndexBuffer;
	if (pALMesh->getPositions().size() > std::numeric_limits<uint16_t>::max()) {
		std::string key = pALMesh->getMeshName() + "_IndexBuffer_uint32";
		pIndexBuffer = MeshManager::instance()->getIndexBuffer(key);
		if (pIndexBuffer == nullptr) {
			pIndexBuffer = directCtx.createIndexBuffer(
				indices.data(), 
				indices.size(), 
				DXGI_FORMAT_R32_UINT
			);
			MeshManager::instance()->cacheIndexBuffer(key, pIndexBuffer);
		}
	} else {
		std::string key = pALMesh->getMeshName() + "_IndexBuffer_uint16";
		pIndexBuffer = MeshManager::instance()->getIndexBuffer(key);
		if (pIndexBuffer == nullptr) {
			std::vector<uint16_t> newIndices;
			newIndices.resize(indices.size());
			for (size_t i = 0; i < indices.size()-2; i += 3) {
				newIndices[i+0] = static_cast<uint16_t>(indices[i+0]);
				newIndices[i+1] = static_cast<uint16_t>(indices[i+1]);
				newIndices[i+2] = static_cast<uint16_t>(indices[i+2]);
			}

			pIndexBuffer = directCtx.createIndexBuffer(
				newIndices.data(), 
				newIndices.size(), 
				DXGI_FORMAT_R16_UINT
			);
			MeshManager::instance()->cacheIndexBuffer(key, pIndexBuffer);
		}
	}
	_pGeometry->setIndexBuffer(pIndexBuffer);
}

std::shared_ptr<rgph::Material> RenderItem::getMaterial() const {
	return _pMaterial;
}

void RenderItem::setMaterial(std::shared_ptr<rgph::Material> pMaterial) {
	_pMaterial = std::move(pMaterial);
}

void RenderItem::rebuildTechniqueFromMaterial(dx12lib::IDirectContext &directCtx) {
	clearTechnique();
	assert(_pMaterial != nullptr);
	for (size_t i = 0; i < _pMaterial->getNumTechnique(); ++i)
		addTechnique(_pMaterial->getTechnique(i));

	auto vertexInputSlots = _pMaterial->getVertexInputSlots();
	for (size_t i = 0; i < std::size(d3d::SemanticList); ++i) {
		if (vertexInputSlots.test(i))
			buildVertexDataInput(directCtx, d3d::SemanticList[i]);
	}
}

template<typename T>
static std::shared_ptr<dx12lib::VertexBuffer> buildVertexDataInputImpl(
	dx12lib::IDirectContext &directCtx,
	const VertexDataSemantic &semantic,
	const std::string &meshName,
	const std::vector<T> &data)
{
	assert(!data.empty());
	std::string key = meshName + std::format("_{}", semantic.name);
	auto pVertexBuffer = MeshManager::instance()->getVertexBuffer(key);
	if (pVertexBuffer == nullptr) {
		pVertexBuffer = directCtx.createVertexBuffer(data.data(), data.size(), sizeof(T));
		MeshManager::instance()->cacheVertexBuffer(key, pVertexBuffer);
	}
	return pVertexBuffer;
}

bool RenderItem::buildVertexDataInput(dx12lib::IDirectContext &directCtx, const VertexDataSemantic &semantic) {
	if (_pGeometry->getVertexBuffer(semantic.slot) != nullptr)
		return false;

	auto pMesh = _pGeometry->getMesh();
	const std::string &meshName = pMesh->getMeshName();
	std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer = nullptr;
	if (semantic == PositionSemantic)
		pVertexBuffer = buildVertexDataInputImpl(directCtx, semantic, meshName, pMesh->getPositions());
	else if (semantic == NormalSemantic)
		pVertexBuffer = buildVertexDataInputImpl(directCtx, semantic, meshName, pMesh->getNormals());
	else if (semantic == TangentSemantic)
		pVertexBuffer = buildVertexDataInputImpl(directCtx, semantic, meshName, pMesh->getTangents());
	else if (semantic == Texcoord0Semantic)
		pVertexBuffer = buildVertexDataInputImpl(directCtx, semantic, meshName, pMesh->getTexcoord0());
	else if (semantic == Texcoord1Semantic)
		pVertexBuffer = buildVertexDataInputImpl(directCtx, semantic, meshName, pMesh->getTexcoord1());

	assert(pVertexBuffer != nullptr);
	_pGeometry->setVertexBuffer(semantic.slot, pVertexBuffer);
	return true;
}

const BoundingBox & RenderItem::getWorldAABB() const {
	return _pGeometry->getWorldAABB();
}

void RenderItem::applyTransform(const Matrix4 &matWorld) {
	_pGeometry->applyTransform(matWorld);
}

}
