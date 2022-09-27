#pragma once
#include <string>
#include <vector>
#include <Math/MathStd.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <RenderGraph/Job/Geometry.h>

namespace Eureka {

struct ALMesh;
class ALTree;

class ALNode {
public:
	ALNode(ALTree *pTree, std::string_view modelPath, int id, const aiScene *pAiScene, const aiNode *pAiNode);
	~ALNode();
	ALNode(const ALNode &) = delete;
	int getNodeId() const;
	size_t getNumChildren() const;
	const ALNode *getChildren(size_t idx) const;
	const Math::float4x4 &getNodeTransform() const;
	size_t getNumMesh() const;
	std::shared_ptr<ALMesh> getMesh(size_t idx) const;
	void saveToObj(const std::string &direction) const;
private:
	int _nodeId;
	unsigned int _numChildren;
	Math::float4x4 _nodeTransform;
	std::vector<std::shared_ptr<ALMesh>> _meshs;
	std::vector<std::unique_ptr<ALNode>> _children;
};

}
