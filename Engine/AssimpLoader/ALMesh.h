#pragma once
#include <Math/MathStd.hpp>
#include <RenderGraph/RenderGraphStd.h>
#include "RenderGraph/Job/Geometry.h"

struct aiMesh;

namespace Eureka {

class ALMaterial;
class ALTree;
struct ALMesh final : public rgph::IMesh {
	using BoneIndex = std::array<uint8_t, 4>;
	ALMesh(ALTree *pTree, std::string_view modelPath, size_t nodeIdx, size_t meshIdx, const aiMesh *pAiMesh);
	const ALMaterial *getMaterial() const;
	size_t getMeshIdx() const;
	const std::string &getMeshName() const override;
	const std::vector<Math::float3> &getPositions() const override;
	const std::vector<Math::float3> &getNormals() const override;
	const std::vector<Math::float4> &getTangents() const override;
	const std::vector<Math::float2> &getTexCoord0() const override;
	const std::vector<Math::float2> &getTexCoord1() const override;
	const std::vector<BoneIndex>	&getBoneIndices() const override;
	const std::vector<Math::float3> &getBoneWeight() const override;
	const std::vector<uint32_t> &getIndices() const override;
	const Math::BoundingBox &getBoundingBox() const override;
	bool saveToObj(const std::string &fileName) const;
private:
	using BoneIndex = std::array<uint8_t, 4>;
	const ALMaterial		   *_pMaterial;
	size_t						_meshIdx;
	Math::BoundingBox		_boundingBox;
	std::string					_meshName;
	std::vector<Math::float3>   _positions;
	std::vector<Math::float3>   _normals;
	std::vector<Math::float4>   _tangents;
	std::vector<Math::float2>   _texcoord0;
	std::vector<Math::float2>   _texcoord1;
	std::vector<BoneIndex>		_boneIndices;
	std::vector<Math::float3>	_boneWeight;
	std::vector<uint32_t>		_indices;
};
}
