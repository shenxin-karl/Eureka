#include "MeshModel.h"
#include "MeshNode.h"

namespace Eureka {

using namespace Math;

MeshModel::MeshModel(dx12lib::IDirectContext &directCtx, std::shared_ptr<ALTree> pALTree)
: _modelTransform(float4x4::Identity)
, _pRootNode(std::make_unique<MeshNode>(directCtx, pALTree->getRootNode()))
{
	_pALTree = std::move(pALTree);
}

MeshModel::~MeshModel() = default;

void MeshModel::submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const {
	if (_modelTransformDirty) {
		_pRootNode->setParentTransform(Matrix(_modelTransform));
		_modelTransformDirty = false;
	}
	_pRootNode->submit(bounding, techniqueFlag);
}

auto MeshModel::getRootNode() const -> MeshNode *{
	return _pRootNode.get();
}

void MeshModel::setModelTransform(const float4x4 &matWorld) {
	_modelTransform = matWorld;
	_modelTransformDirty = true;
}

void MeshModel::createMaterial(dx12lib::IDirectContext &directCtx, 
	const MaterialCreator &creator)
{
	_pRootNode->createMaterial(directCtx, creator);
}


}
