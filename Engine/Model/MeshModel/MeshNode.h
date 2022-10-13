#pragma once
#include "Model/MeshModel/MeshModel.h"
#include "RenderGraph/Job/TransformCBufferPtr.h"

namespace Eureka {

class ALNode;
class MeshNode final : public INode {
public:
	MeshNode(dx12lib::IDirectContext &directCtx, const ALNode *pALNode);
	void submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const override;
	size_t getNumRenderItem() const override;
	RenderItem *getRenderItem(size_t idx) const override;
	void setParentTransform(const Math::Matrix4 &matWorld) override;
	const rgph::TransformCBufferPtr &getTransformCBuffer() const override;
	std::shared_ptr<rgph::IMesh> getMesh(size_t idx) const override;
	void createMaterial(dx12lib::IDirectContext &directCtx, 
		const MaterialCreator &creator
	);
private:
	mutable bool _transformDirty = true;
	Math::float4x4 _applyTransform;
	Math::float4x4 _nodeLocalTransform;
	std::vector<std::shared_ptr<ALMesh>> _alMeshes;
	std::vector<std::unique_ptr<RenderItem>> _renderItems;
	std::vector<std::unique_ptr<MeshNode>> _children;
	mutable rgph::TransformCBufferPtr _pTransformCBuffer;
};

}
