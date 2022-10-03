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
	std::shared_ptr<rgph::Material> getMaterial() const;
	void setMaterial(std::shared_ptr<rgph::Material> pMaterial);
	void rebuildTechniqueFromMaterial(dx12lib::IDirectContext &directCtx);
	bool buildVertexDataInput(dx12lib::IDirectContext &directCtx, const rgph::ShaderLayoutIndex &index);

	using rgph::Drawable::submit;
	const Math::BoundingBox &getWorldAABB() const;
	void applyTransform(const Math::Matrix4 &matWorld);
private:
	std::shared_ptr<rgph::Material> _pMaterial;
};

}
