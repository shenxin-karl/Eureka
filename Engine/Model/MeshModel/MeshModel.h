#pragma once
#include "AssimpLoader/ALTree.h"
#include "Model/IModel.hpp"
#include "Model/RenderItem/RenderItem.h"

namespace rpgh {

class Material;
class RenderGraph;

}

namespace Eureka {

class MeshNode;
class MeshModel final : public IModel {
public:
	MeshModel(dx12lib::IDirectContext &directCtx, std::shared_ptr<ALTree> pALTree);
	~MeshModel() override;
	void submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const override ;
	auto getRootNode() const -> MeshNode *;
	void setModelTransform(const Math::float4x4 &matWorld) override;

	void createMaterial(rgph::RenderGraph &graph, 
		dx12lib::IDirectContext &directCtx, 
		const MaterialCreator &creator
	);
private:
	mutable bool _modelTransformDirty = true;
	Math::float4x4 _modelTransform;
	std::unique_ptr<MeshNode> _pRootNode;
	std::shared_ptr<ALTree> _pALTree;
};

}
