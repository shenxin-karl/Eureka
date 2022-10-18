#pragma once
#include <RenderGraph/Job/Geometry.h>
#include "EngineDefinition/EngineDefinition.h"

namespace Eureka {

class PartMesh : public rgph::IMesh {
public:
	const std::string &getMeshName() const override;
	const std::vector<Math::float3> &getPositions() const override;
	const std::vector<Math::float3> &getNormals() const override;
	const std::vector<Math::float4> &getTangents() const override;
	const std::vector<Math::float2> &getTexCoord0() const override;
	const std::vector<uint32_t>		&getIndices() const override;
	const Math::BoundingBox			&getBoundingBox() const override;
private:
	friend class GeometryGenerator;
	std::string				  _meshName;
	std::vector<Math::float3> _positions;
	std::vector<Math::float3> _normals;
	std::vector<Math::float4> _tangents;
	std::vector<Math::float2> _texcoord0;
	std::vector<uint32>		  _indices;
	Math::BoundingBox		  _boundingBox;
};

}
