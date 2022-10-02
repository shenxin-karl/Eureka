#pragma once
#include <RenderGraph/Drawable/Drawable.h>
#include "D3D/AssimpLoader/ALNode.h"
#include "D3D/Model/RenderItem/VertexDataSemantic.h"
#include "D3D/Model/Mesh/MeshManager.h"

namespace rgph {
class Material;
}

namespace d3d {

struct INode;
class RenderItem : protected rgph::Drawable {
public:
	RenderItem(dx12lib::IDirectContext &directCtx,  INode *pNode, size_t meshIdx);
	std::shared_ptr<rgph::Material> getMaterial() const;
	void setMaterial(std::shared_ptr<rgph::Material> pMaterial);
	void rebuildTechniqueFromMaterial(dx12lib::IDirectContext &directCtx);
	bool buildVertexDataInput(dx12lib::IDirectContext &directCtx, const VertexDataSemantic &semantic);

	using rgph::Drawable::submit;
	const Math::BoundingBox &getWorldAABB() const;
	void applyTransform(const Math::Matrix4 &matWorld);
private:
	std::shared_ptr<rgph::Material> _pMaterial;
};

}
