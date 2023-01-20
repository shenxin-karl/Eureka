#include "PartModel.h"
#include "AssimpLoader/ALTree.h"
#include "Model/RenderItem/RenderItem.h"
#include "Model/GeometryGenerator/PartMesh.h"

using namespace Math;

namespace Eureka {

PartModel::PartModel(dx12lib::IDirectContext &directCtx, std::shared_ptr<PartMesh> pPartMesh) {
	_pTransformCBuffer.setTransformCBuffer(directCtx.createFRConstantBuffer<rgph::TransformStore>());
	_pRenderItem  = std::make_unique<RenderItem>(directCtx, _pTransformCBuffer, pPartMesh);
}

void PartModel::submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const {
	if (_transformDirty) {
		_transformDirty = false;
		_pTransformCBuffer.setMatWorld(_transform);
		_pRenderItem->setTransform(Matrix(_transform));
	}

	const auto &worldBoundBox = _pRenderItem->getWorldAABB();
	if (bounding.contains(worldBoundBox) != DirectX::DISJOINT)
		_pRenderItem->submit(techniqueFlag);
}

void PartModel::setModelTransform(const Math::float4x4 &matWorld) {
	_transformDirty = true;
	_transform = matWorld;
}

auto PartModel::getMaterial() const -> std::shared_ptr<Material> {
	return _pRenderItem->getMaterial();
}

void PartModel::createMaterial(dx12lib::IDirectContext &directCtx,
                               const MaterialCreator &creator)
{
	const auto *pDefaultMaterial = &ALMaterial::sDefaultMaterial;
	auto pMaterial = creator(pDefaultMaterial);
	_pRenderItem->setMaterial(directCtx, std::move(pMaterial));
}

}
