#include "PartMesh.h"

namespace Eureka {

const std::string & PartMesh::getMeshName() const {
	return _meshName;
}

const std::vector<Math::float3> & PartMesh::getPositions() const {
	return _positions;
}

const std::vector<Math::float3> & PartMesh::getNormals() const {
	return _normals;
}

const std::vector<Math::float4> & PartMesh::getTangents() const {
	return _tangents;
}

const std::vector<Math::float2> & PartMesh::getTexCoord0() const {
	return _texcoord0;
}

const Math::BoundingBox & PartMesh::getBoundingBox() const {
	return _boundingBox;
}

}
