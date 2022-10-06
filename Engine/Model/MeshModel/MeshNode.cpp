#include "MeshNode.h"
#include "AssimpLoader/ALNode.h"
#include "Model/RenderItem/RenderItem.h"
#include "AssimpLoader/ALMesh.h"
#include "RenderGraph/Job/TransformCBufferPtr.h"

using namespace Math;
namespace Eureka {

MeshNode::MeshNode(dx12lib::IDirectContext &directCtx, const ALNode *pALNode) {
	_applyTransform = pALNode->getNodeTransform();
	_nodeLocalTransform = pALNode->getNodeTransform();

	if (pALNode->getNumMesh() > 0)
		_nodeTransformCBuffer.setTransformCBuffer(directCtx.createFRConstantBuffer<rgph::TransformStore>());

	for (size_t i = 0; i < pALNode->getNumMesh(); ++i) {
		_alMeshes.push_back(pALNode->getMesh(i));
		_renderItems.emplace_back(std::make_unique<RenderItem>(directCtx, this, i));
	}

	for (size_t i = 0; i < pALNode->getNumChildren(); ++i)
		_children.push_back(std::make_unique<MeshNode>(directCtx, pALNode->getChildren(i)));
}

void MeshNode::submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const {
	if (_transformDirty && _nodeTransformCBuffer != nullptr) {
		Matrix4 matWorld(_applyTransform);
		Matrix4 matInvWorld = inverse(matWorld);
		Matrix4 matNormal = transpose(inverse(Matrix4(_applyTransform)));
		Matrix4 matInvNormal = inverse(matNormal);
		rgph::TransformStore store {
			.matWorld = float4x4(matWorld),
			.matInvWorld = float4x4(matInvWorld),
			.matNormal = float4x4(matNormal),
			.matInvNormal = float4x4(matInvNormal)
		};
		_nodeTransformCBuffer.setTransformStore(store);
		_transformDirty = false;
	}

	for (auto &pRenderItem : _renderItems) {
		const auto &worldAABB = pRenderItem->getWorldAABB();
		if (bounding.contains(worldAABB) == DirectX::ContainmentType::DISJOINT)
			continue;
		pRenderItem->submit(techniqueFlag);
	}

	for (auto &pChild : _children)
		pChild->submit(bounding, techniqueFlag);
}

size_t MeshNode::getNumRenderItem() const {
	return _renderItems.size();
}

RenderItem * MeshNode::getRenderItem(size_t idx) const {
	if (idx >= getNumRenderItem()) {
		assert(false);
		return nullptr;
	}
	return _renderItems[idx].get();
}

void MeshNode::setParentTransform(const Matrix4 &matWorld) {
	Matrix4 localTransform(_nodeLocalTransform);
	Matrix4 applyTransform = localTransform * matWorld;
	_applyTransform = float4x4(applyTransform);
	_transformDirty = true;
	for (auto &pChildren : _children)
		pChildren->setParentTransform(applyTransform);

	for (auto &pRenderItem : _renderItems)
		pRenderItem->setTransform(applyTransform);
}

const rgph::TransformCBufferPtr &MeshNode::getNodeTransformCBuffer() const {
	return _nodeTransformCBuffer;
}

std::shared_ptr<rgph::IMesh> MeshNode::getMesh(size_t idx) const {
	assert(idx < _alMeshes.size());
	return _alMeshes[idx];
}

void MeshNode::createMaterial(rgph::RenderGraph &graph, 
	dx12lib::IDirectContext &directCtx, 
	const MeshModel::MaterialCreator &creator)
{
	size_t idx = 0;
	for (auto &pRenderItem : _renderItems) {
		const auto *pALMaterial = _alMeshes[idx]->getMaterial();
		pRenderItem->setMaterial(directCtx, creator(pALMaterial));
		++idx;
	}
	for (auto &pChild : _children)
		pChild->createMaterial(graph, directCtx, creator);
}

}
