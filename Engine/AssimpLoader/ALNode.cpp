#include <filesystem>
#include <format>
#include <DirectXMath.h>
#include "ALNode.h"
#include "ALMesh.h"
#include "ALTree.h"

namespace Eureka {

using namespace Math;

ALNode::ALNode(ALTree *pTree, std::string_view modelPath, int id, const aiScene *pAiScene, const aiNode *pAiNode)
: _nodeId(id), _numChildren(pAiNode->mNumChildren) {
	for (size_t i = 0; i < pAiNode->mNumMeshes; ++i) {
		unsigned int meshIdx = pAiNode->mMeshes[i];
		_meshs.push_back(std::make_shared<ALMesh>(pTree, modelPath, _nodeId, meshIdx, pAiScene->mMeshes[meshIdx]));
	}

	aiVector3D scale;
	aiVector3D position;
	aiQuaternion rotate;
	pAiNode->mTransformation.Decompose(scale, rotate, position);

	_nodeTransform = float4x4(Matrix4(DirectX::XMMatrixAffineTransformation(
		Vector3(scale.x, scale.y, scale.z),
		Vector3(0.f),
		Quaternion(rotate.x, rotate.y, rotate.z, rotate.w),
		Vector3(position.x, position.y, position.z)
	)));

	for (size_t i = 0; i < pAiNode->mNumChildren; ++i) {
		++id;
		_children.push_back(std::make_unique<ALNode>(
			pTree,
			modelPath,
			id,
			pAiScene,
			pAiNode->mChildren[i]
		));
	}
}

ALNode::~ALNode() {
}

int ALNode::getNodeId() const {
	return _nodeId;
}

size_t ALNode::getNumChildren() const {
	return _numChildren;
}

const ALNode * ALNode::getChildren(size_t idx) const {
	return _children[idx].get();
}

const float4x4 & ALNode::getNodeTransform() const {
	return _nodeTransform;
}

size_t ALNode::getNumMesh() const {
	return _meshs.size();
}

std::shared_ptr<ALMesh> ALNode::getMesh(size_t idx) const {
	if (idx >= getNumMesh()) {
		assert(false);
		return nullptr;
	}
	return _meshs[idx];
}

void ALNode::saveToObj(const std::string &direction) const {
	for (auto &pMesh : _meshs) {
		const auto &meshName = pMesh->getMeshName();
		std::filesystem::path path(meshName);
		std::string fileName = std::format("{}{}_.obj", direction, path.filename().string());
		bool res = pMesh->saveToObj(fileName);
		assert(res);
	}
}
}
