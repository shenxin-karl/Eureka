#pragma once
#include <RenderGraph/Drawable/Drawable.h>
#include "AssimpLoader/ALNode.h"

namespace rgph {
class Material;
}

namespace Eureka {

struct INode;
class RenderItem : protected rgph::Drawable {
public:
	RenderItem(dx12lib::IDirectContext &directCtx,  INode *pNode, size_t meshIdx);
	auto getMaterial() const -> std::shared_ptr<rgph::Material>;
	void setMaterial(dx12lib::IDirectContext &directCtx, std::shared_ptr<rgph::Material> pMaterial);
	void submit(const rgph::TechniqueFlag &techniqueFlag) const override;
	auto getWorldAABB() const -> const Math::BoundingBox &;
	void setTransform(const Math::Matrix4 &matWorld);
	static bool buildVertexDataInput(dx12lib::IDirectContext &directCtx,
		rgph::Geometry *pGeometry,
		const rgph::ShaderLayoutIndex &shaderLayoutIndex
	);
private:
	std::shared_ptr<rgph::Material> _pMaterial;
};

}
