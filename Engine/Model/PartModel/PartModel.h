#pragma once
#include "Model/IModel.hpp"

namespace Eureka {

class PartMesh;
class Material;
class PartModel final : public IModel {
public:
	PartModel(dx12lib::IDirectContext &directCtx, std::shared_ptr<PartMesh> pPartMesh);
	void submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const override;
	void setModelTransform(const Math::float4x4 &matWorld) override;
	auto getMaterial() const -> std::shared_ptr<Material>;
	void createMaterial(dx12lib::IDirectContext &directCtx,
		const MaterialCreator &creator
	);
private:
	mutable bool _transformDirty = true;
	Math::float4x4 _transform = Math::float4x4::identity();
	std::unique_ptr<RenderItem> _pRenderItem;
	mutable rgph::TransformCBufferPtr _pTransformCBuffer;
};

}
