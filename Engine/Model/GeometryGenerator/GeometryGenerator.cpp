#include "GeometryGenerator.h"

#include <format>
#include <iostream>

#include "Model/RenderItem/RenderItem.h"

using namespace Math;

namespace Eureka {

struct SubDivVertex {
	float3 position;
	float2 texcoord;
};

struct LoopEdge {
	uint32 v0;
	uint32 v1;
public:
	friend bool operator==(const LoopEdge &lhs, const LoopEdge &rhs) {
		return lhs.v0 == rhs.v0 && lhs.v1 == rhs.v1 || lhs.v0 == rhs.v1 && lhs.v1 == rhs.v0;
	}
};

struct LoopEdgeHasher {
	std::size_t operator()(const LoopEdge &edge) const {
		return std::hash<uint32>()(edge.v0) ^ std::hash<uint32>()(edge.v1);
	}
};

SubDivVertex middleVertex(const SubDivVertex &lhs, const SubDivVertex &rhs) {
	return {
		lerp(Vector3(lhs.position), Vector3(rhs.position), 0.5f).xyz,
		lerp(Vector2(lhs.texcoord), Vector2(rhs.texcoord), 0.5f).xy,
	};
}

template<typename T>
static T lerp(const T &lhs, const T &rhs, float t) {
	return lhs + (rhs - lhs) * t;
}

static void splitPositionTexcoord(const std::vector<SubDivVertex> &vertices, 
	std::vector<float3> &outPositions,
	std::vector<float2> &outTexcoord)
{
	outPositions.clear();
	outTexcoord.clear();
	outPositions.reserve(vertices.size());
	outTexcoord.reserve(vertices.size());
	for (size_t i = 0; i < vertices.size(); ++i) {
		outPositions.emplace_back(vertices[i].position);
		outTexcoord.emplace_back(vertices[i].texcoord);
	}
}

static void subDivisions(std::vector<SubDivVertex> &inOutVertices, std::vector<uint32> &inOutIndices, size_t numSubDivisions) {
	std::unordered_map<LoopEdge, uint32, LoopEdgeHasher> newVert;
	auto createNewVert = [&](LoopEdge edge) -> uint32 {
		if (auto iter = newVert.find(edge); iter != newVert.end())
			return iter->second;

		inOutVertices.push_back(middleVertex(inOutVertices[edge.v0], inOutVertices[edge.v1]));
		auto idx = static_cast<uint32>(inOutVertices.size() - 1);
		newVert.insert(std::make_pair(edge, idx));
		return idx;
	};

	for (uint32 i = 0; i < numSubDivisions; ++i) {
		newVert.clear();
		std::vector<uint32> newIndices;
		newIndices.swap(inOutIndices);
		inOutIndices.reserve(newIndices.size() * 4);
		for (size_t j = 0; j < newIndices.size()-2; j += 3) {
			uint32 idx0 = newIndices[j + 0];
			uint32 idx1 = newIndices[j + 1];
			uint32 idx2 = newIndices[j + 2];
			uint32 newIdx0 = createNewVert({ idx0, idx1 });
			uint32 newIdx1 = createNewVert({ idx1, idx2 });
			uint32 newIdx2 = createNewVert({ idx2, idx0 });
			inOutIndices.insert(inOutIndices.end(), { idx0, newIdx0, newIdx2 });
			inOutIndices.insert(inOutIndices.end(), { newIdx0, idx1, newIdx1 });
			inOutIndices.insert(inOutIndices.end(), { newIdx1, idx2, newIdx2 });
			inOutIndices.insert(inOutIndices.end(), { newIdx0, newIdx1, newIdx2 });
		}
	}
}

static void generateTangentAndNormal(const std::vector<SubDivVertex> &vertices, 
	const std::vector<uint32> &indices,
	std::vector<float3> &outNormals,
	std::vector<float4> &outTangents)
{
	if (indices.size() < 3)
		return;

	std::vector<Vector3> normals(vertices.size(), Vector3(0));
	std::vector<Vector3> tangents(vertices.size(), Vector3(0));
	std::vector<Vector3> bitangents(vertices.size(), Vector3(0));
	for (size_t i = 0; i < indices.size()-2; i += 3) {
		size_t idx0 = indices[i+0];
		size_t idx1 = indices[i+1];
		size_t idx2 = indices[i+2];
		const auto &v0 = vertices[idx0];
		const auto &v1 = vertices[idx1];
		const auto &v2 = vertices[idx2];
		Vector3 E1 = Vector3(v1.position) - Vector3(v0.position);
		Vector3 E2 = Vector3(v2.position) - Vector3(v0.position);
		float t1 = v1.texcoord.y - v0.texcoord.y;
		float t2 = v2.texcoord.y - v0.texcoord.y;
		float u0 = v1.texcoord.x - v0.texcoord.x;
		float u1 = v2.texcoord.x - v0.texcoord.x;
		Vector3 normal = cross(E1, E2);
		Vector3 tangent = (t2 * E1) - (t1 * E2);
		Vector3 binormal = (-u1 * E1) + (u0 * E2);
		for (size_t j = i; j < i+3; ++j) {
			size_t index = indices[j];
			normals[index] += normal;
			tangents[index] += tangent;
			bitangents[index] += binormal;
		}
	}

	outNormals.clear();
	outTangents.clear();
	outNormals.reserve(vertices.size());
	outTangents.reserve(vertices.size());
	for (size_t i = 0; i < tangents.size(); ++i) {
		Vector3 n = normalize(normals[i]);
		Vector3 t = tangents[i];
		t -= n * dot(n, t);		// Õý½»ÐÞÕý
		t = normalize(t);

		float det = 1.f;
		if (dot(cross(n, t), bitangents[i]) < 0.f)
			det = -1.f;

		outNormals.emplace_back(n.xyz);
		outTangents.emplace_back(t.xyz, det);
	}
}

auto GeometryGenerator::createCylinder(float bottomRadius, float topRadius, float height, uint32 stackCount,
	uint32 sliceCount) const -> std::shared_ptr<PartMesh>
{
	std::vector<SubDivVertex> vertices;
	std::vector<uint32> indices;
	uint32 ringVertexCount = sliceCount + 1;
	float delta = DirectX::XM_2PI / sliceCount;
	for (uint32 i = 0; i < stackCount+1; ++i) {
		for (uint32 j = 0; j < ringVertexCount; ++j) {
			float ratio = static_cast<float>(i) / static_cast<float>(stackCount);
			float radius = lerp(bottomRadius, topRadius, ratio);
			float radian = j * delta;
			float x = std::cos(radian) * radius;
			float y = lerp(-0.5f*height, +0.5f*height, ratio);;
			float z = std::sin(radian) * radius;
			float u = static_cast<float>(j) / static_cast<float>(sliceCount);
			float v = ratio;
			SubDivVertex vertex;
			vertex.position = float3(x, y, z);
			vertex.texcoord = float2(u, v);
			vertices.push_back(vertex);
		}
	}
	for (uint32 i = 0; i < stackCount; ++i) {
		for (uint32 j = 0; j < sliceCount; ++j) {
			indices.push_back((i+0) * ringVertexCount + j+0);
			indices.push_back((i+1) * ringVertexCount + j+0);
			indices.push_back((i+1) * ringVertexCount + j+1);
			indices.push_back((i+1) * ringVertexCount + j+1);
			indices.push_back((i+0) * ringVertexCount + j+1);
			indices.push_back((i+0) * ringVertexCount + j+0);
		}
	}
	// generate top
	if (topRadius > 0.f) {
		float topHeight = +0.5f * height;
		uint32 centerIdx = static_cast<uint32>(vertices.size());
		vertices.push_back(SubDivVertex{ float3(0, topHeight, 0), float2(0.5f, 0.5f) });
		uint32 baseIdx = static_cast<uint32>(vertices.size());
		for (uint32 i = 0; i < sliceCount+1; ++i) {
			float radian = i * delta;
			float x = std::cos(radian) * topRadius;
			float z = std::sin(radian) * topRadius;
			float y = topHeight;
			float u = x / height + 0.5f;
			float v = z / height + 0.5f;
			vertices.push_back(SubDivVertex{ float3(x, y, z), float2(u, v) });
		}
		for (uint32 i = 0; i < sliceCount; ++i) {
			indices.push_back(baseIdx + i);
			indices.push_back(centerIdx);
			indices.push_back(baseIdx + i + 1);
		}
	}
	// generate bottom
	if (bottomRadius > 0.f) {
		float bottomHeight = -0.5f * height;
		uint32 centerIdx = static_cast<uint32>(vertices.size());
		vertices.push_back(SubDivVertex{ float3(0, bottomHeight, 0), float2(0.5f, 0.5f) });
		uint32 baseIdx = static_cast<uint32>(vertices.size());
		for (uint32 i = 0; i < sliceCount+1; ++i) {
			float radian = i * delta;
			float x = std::cos(radian) * bottomRadius;
			float z = std::sin(radian) * bottomRadius;
			float y = bottomHeight;
			float u = x / height + 0.5f;
			float v = z / height + 0.5f;
			vertices.push_back(SubDivVertex{ float3(x, y, z), float2(u, v) });
		}
		for (uint32 i = 0; i < sliceCount; ++i) {
			indices.push_back(baseIdx + i + 1);
			indices.push_back(centerIdx);
			indices.push_back(baseIdx + i);
		}
	}

	std::vector<float3> positions;
	std::vector<float2> texcoord;
	splitPositionTexcoord(vertices, positions, texcoord);

	std::vector<float3> normals;
	std::vector<float4> tangents;
	generateTangentAndNormal(vertices, indices, normals, tangents);

	auto pPartMesh = std::make_shared<PartMesh>();
	pPartMesh->_meshName = std::format("Cylinder_{}_{}_{}_{}_{}", bottomRadius, topRadius, height, stackCount, sliceCount);
	pPartMesh->_positions = std::move(positions);
	pPartMesh->_normals = std::move(normals);
	pPartMesh->_texcoord0 = std::move(texcoord);
	pPartMesh->_tangents = std::move(tangents);
	float halfWidth = std::max(bottomRadius, topRadius);
	float halfHeight = height * 0.5f;
	float x = halfWidth;
	float z = halfWidth;
	float y = halfHeight;
	pPartMesh->_boundingBox = BoundingBox(Vector3(-x, -y, -z), Vector3(x, y, z));
	return pPartMesh;
}

auto GeometryGenerator::createBox(float width, float height, float depth,
	uint32 numSubdivisions) const -> std::shared_ptr<PartMesh>
{
	float x = 0.5f * width;
	float y = 0.5f * height;
	float z = 0.5f * depth;
	std::vector<SubDivVertex> vertices = {
		{ float3{ -x, -y, -z },  float2{ 0.0f, 1.0f } },
		{ float3{ -x, +y, -z },  float2{ 0.0f, 0.0f } },
		{ float3{ +x, +y, -z },  float2{ 1.0f, 0.0f } },
		{ float3{ +x, -y, -z },  float2{ 1.0f, 1.0f } },
		{ float3{ +x, -y, -z },  float2{ 0.0f, 1.0f } },
		{ float3{ +x, +y, -z },  float2{ 0.0f, 0.0f } },
		{ float3{ +x, +y, +z },  float2{ 1.0f, 0.0f } },
		{ float3{ +x, -y, +z },  float2{ 1.0f, 1.0f } },
		{ float3{ +x, -y, +z },  float2{ 0.0f, 1.0f } },
		{ float3{ +x, +y, +z },  float2{ 0.0f, 0.0f } },
		{ float3{ -x, +y, +z },  float2{ 1.0f, 0.0f } },
		{ float3{ -x, -y, +z },  float2{ 1.0f, 1.0f } },
		{ float3{ -x, -y, +z },  float2{ 0.0f, 1.0f } },
		{ float3{ -x, +y, +z },  float2{ 0.0f, 0.0f } },
		{ float3{ -x, +y, -z },  float2{ 1.0f, 0.0f } },
		{ float3{ -x, -y, -z },  float2{ 1.0f, 1.0f } },
		{ float3{ -x, +y, -z },  float2{ 0.0f, 1.0f } },
		{ float3{ -x, +y, +z },  float2{ 0.0f, 0.0f } },
		{ float3{ +x, +y, +z },  float2{ 1.0f, 0.0f } },
		{ float3{ +x, +y, -z },  float2{ 1.0f, 1.0f } },
		{ float3{ -x, -y, +z },  float2{ 0.0f, 1.0f } },
		{ float3{ -x, -y, -z },  float2{ 0.0f, 0.0f } },
		{ float3{ +x, -y, -z },  float2{ 1.0f, 0.0f } },
		{ float3{ +x, -y, +z },  float2{ 1.0f, 1.0f } },
	};

	std::vector<uint32> indices = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9,  10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23,
	};

	subDivisions(vertices, indices, numSubdivisions);

	std::vector<float3> positions;
	std::vector<float2> texcoord;
	splitPositionTexcoord(vertices, positions, texcoord);

	std::vector<float3> normals;
	std::vector<float4> tangents;
	generateTangentAndNormal(vertices, indices, normals, tangents);

	auto pPartMesh = std::make_shared<PartMesh>();
	pPartMesh->_meshName = std::format("Box_{}_{}_{}", width, height, depth);
	pPartMesh->_positions = std::move(positions);
	pPartMesh->_normals = std::move(normals);
	pPartMesh->_texcoord0 = std::move(texcoord);
	pPartMesh->_tangents = std::move(tangents);
	pPartMesh->_boundingBox = BoundingBox(Vector3(-x, -y, -z), Vector3(x, y, z));
	return pPartMesh;
}

auto GeometryGenerator::createSphere(float radius, uint32 numSubdivisions) const -> std::shared_ptr<PartMesh> {
	constexpr float x = 0.525731f;
	constexpr float y = 0.f;
	constexpr float z = 0.850651f;

	std::vector<SubDivVertex> vertices = {
		{ float3(-x, +y, +z), float2(0.f) }, { float3(+x, +y, +z), float2(0.f) },
		{ float3(-x, +y, -z), float2(0.f) }, { float3(+x, +y, -z), float2(0.f) },
		{ float3(+y, +z, +x), float2(0.f) }, { float3(+y, +z, -x), float2(0.f) },
		{ float3(+y, -z, +x), float2(0.f) }, { float3(+y, -z, -x), float2(0.f) },
		{ float3(+z, +x, +y), float2(0.f) }, { float3(-z, +x, +y), float2(0.f) },
		{ float3(+z, -x, +y), float2(0.f) }, { float3(-z, -x, +y), float2(0.f) },
	};

	std::vector<uint32> indices = {
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7,
	};

	subDivisions(vertices, indices, numSubdivisions);

	const float PI = 3.141592654f;
	float2 invATan = { 0.5f / PI, 1 / PI };
	for (auto &vert : vertices) {
		Vector3 n = normalize(Vector3(vert.position));
		Vector3 point = n * radius;
		float u = std::atan2(n.z, n.x);
		float v = std::asin(n.y);
		float2 texcoord(u, v);
		texcoord = float2{ texcoord.x * (0.5f / PI), texcoord.y * (1.f / PI) };
		texcoord = float2(texcoord.x + 0.5f, texcoord.y + 0.5f);
		vert.position = float3(point);
		vert.texcoord = float2(u, v);
	}

	std::vector<float3> positions;
	std::vector<float2> texcoord;
	splitPositionTexcoord(vertices, positions, texcoord);

	std::vector<float3> normals;
	std::vector<float4> tangents;
	generateTangentAndNormal(vertices, indices, normals, tangents);

	auto pPartMesh = std::make_shared<PartMesh>();
	pPartMesh->_meshName = std::format("Sphere_{}_{}", radius, numSubdivisions);
	pPartMesh->_positions = std::move(positions);
	pPartMesh->_normals = std::move(normals);
	pPartMesh->_texcoord0 = std::move(texcoord);
	pPartMesh->_tangents = std::move(tangents);
	pPartMesh->_boundingBox = BoundingBox(Vector3(-radius), Vector3(radius));
	return pPartMesh;
}

auto GeometryGenerator::createGrid(float width, float depth, uint32 m, uint32 n) const -> std::shared_ptr<PartMesh> {
	std::vector<SubDivVertex> vertices;
	float left = -0.5f * width;
	float right = +0.5f * width;
	float depthFar = +0.5f * depth;
	float depthNear = -0.5f * depth;
	for (uint32 zi = 0; zi < n+1; ++zi) {
		for (uint32 xi = 0; xi < m+1; ++xi) {
			float u = static_cast<float>(xi) / static_cast<float>(m);
			float v = static_cast<float>(zi) / static_cast<float>(n);
			float x = lerp(left, right, u);
			float z = lerp(depthFar, depthNear, v);
			vertices.push_back(SubDivVertex{ float3(x, 0, z), float2(u, v) });
		}
	}

	std::vector<uint32> indices;
	uint32 sliceSize = m+1;
	for (uint32 zi = 0; zi < n; ++zi) {
		for (uint32 xi = 0; xi < m; ++xi) {
			indices.push_back((zi+0) * sliceSize + (xi+0));
			indices.push_back((zi+0) * sliceSize + (xi+1));
			indices.push_back((zi+1) * sliceSize + (xi+0));
			indices.push_back((zi+1) * sliceSize + (xi+0));
			indices.push_back((zi+0) * sliceSize + (xi+1));
			indices.push_back((zi+1) * sliceSize + (xi+1));
		}
	}

	std::vector<float3> positions;
	std::vector<float2> texcoord;
	splitPositionTexcoord(vertices, positions, texcoord);

	std::vector<float3> normals;
	std::vector<float4> tangents;
	generateTangentAndNormal(vertices, indices, normals, tangents);

	auto pPartMesh = std::make_shared<PartMesh>();
	pPartMesh->_meshName = std::format("Grid_{}_{}_{}_{}", width, depth, m, n);
	pPartMesh->_positions = std::move(positions);
	pPartMesh->_normals = std::move(normals);
	pPartMesh->_texcoord0 = std::move(texcoord);
	pPartMesh->_tangents = std::move(tangents);
	pPartMesh->_boundingBox = BoundingBox(Vector3(left, -1.f, depthNear), Vector3(right, 1.f, depthFar));
	return pPartMesh;
}

auto GeometryGenerator::createQuad(float x, float y, float w, float h, float depth) const -> std::shared_ptr<PartMesh> {
	std::vector<SubDivVertex> vertices = {
		{ float3(x, y, depth),		float2(0, 1) },
		{ float3(x, y+h, depth),	float2(0, 0) },
		{ float3(x+w, y+h, depth),	float2(1, 0) },
		{ float3(x+w, y, depth),	float2(1, 1) },
	};

	/*
	 * 1---------2
	 * |         |
	 * |         |
	 * 0---------3
	 */
	std::vector<uint32> indices = {
		0, 1, 2,
		0, 2, 3,
	};

	std::vector<float3> positions;
	std::vector<float2> texcoord;
	splitPositionTexcoord(vertices, positions, texcoord);

	std::vector<float3> normals;
	std::vector<float4> tangents;
	generateTangentAndNormal(vertices, indices, normals, tangents);

	auto pPartMesh = std::make_shared<PartMesh>();
	pPartMesh->_meshName = std::format("Quad_{}_{}_{}_{}", x, y, w, h, depth);
	pPartMesh->_positions = std::move(positions);
	pPartMesh->_normals = std::move(normals);
	pPartMesh->_texcoord0 = std::move(texcoord);
	pPartMesh->_tangents = std::move(tangents);
	pPartMesh->_boundingBox = BoundingBox(Vector3(x, y, depth), Vector3(x+w, y+h, depth+0.5f));
	return pPartMesh;
}

auto GeometryGenerator::createBoxGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask)
	const -> std::shared_ptr<rgph::Geometry>
{
	return createGeometry(directCtx, mask, _pBoxMesh);
}

auto GeometryGenerator::createSphereGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask)
	const -> std::shared_ptr<rgph::Geometry>
{
	return createGeometry(directCtx, mask, _pSphereMesh);
}

auto GeometryGenerator::createGridGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask)
	const -> std::shared_ptr<rgph::Geometry>
{
	return createGeometry(directCtx, mask, _pGridMesh);
}

auto GeometryGenerator::createQuadGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask)
	const -> std::shared_ptr<rgph::Geometry>
{
	return createGeometry(directCtx, mask, _pQuadMesh);
}

void GeometryGenerator::loading() {
	_pBoxMesh = createBox(1.f, 1.f, 1.f, 0);
	_pSphereMesh = createSphere(0.5f, 3);
	_pGridMesh = createGrid(0.5f, 0.5f, 10, 10);
	_pQuadMesh = createQuad(-0.5f, -0.5f, 1.f, 1.f, 0.f);
}

auto GeometryGenerator::createGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask,
	std::shared_ptr<PartMesh> pPartMesh) const -> std::shared_ptr<rgph::Geometry>
{
	auto pGeometry = std::make_shared<rgph::Geometry>();
	pGeometry->setMesh(pPartMesh);
	pGeometry->genDrawArgs();
	for (size_t i = rgph::ShaderLayoutIndex::Position; i < rgph::ShaderLayoutIndex::Max; ++i) {
		rgph::ShaderLayoutIndex shaderLayoutIndex(i);
		if (mask & shaderLayoutIndex)
			RenderItem::buildVertexDataInput(directCtx, pGeometry.get(), shaderLayoutIndex);
	}
	return pGeometry;
}


}
