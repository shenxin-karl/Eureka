#pragma once
#include <RenderGraph/Drawable/Drawable.h>
#include "AssimpLoader/ALNode.h"

namespace Eureka {

struct INode;
class Material;

class RenderItem : protected rgph::Drawable {
public:
	RenderItem(dx12lib::IDirectContext &directCtc, const rgph::TransformCBufferPtr &trans, std::shared_ptr<rgph::IMesh> pMesh);
	auto getMaterial() const -> std::shared_ptr<Material>;
	void setMaterial(dx12lib::IDirectContext &directCtx, std::shared_ptr<Material> pMaterial);
	void submit(const rgph::TechniqueFlag &techniqueFlag) const override;
	auto getWorldAABB() const -> const Math::BoundingBox &;
	void setTransform(const Math::Matrix &matWorld);
	static bool buildIndexDataInput(dx12lib::IDirectContext &directCtx, rgph::Geometry *pGeometry);
	static bool buildVertexDataInput(dx12lib::IDirectContext &directCtx,
		rgph::Geometry *pGeometry,
		const rgph::ShaderLayoutIndex &shaderLayoutIndex
	);
private:
	std::shared_ptr<Material> _pMaterial;
};

}
