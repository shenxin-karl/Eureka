#pragma once
#include <RenderGraph/RenderGraphStd.h>

namespace rgph {

interface IMesh : public NonCopyable {
	using BoneIndex = std::array<uint8_t, 4>;
	virtual const std::string &getMeshName() const = 0;
	virtual const std::vector<Math::float4> &getPositions() const { static std::vector<Math::float4> vec; return vec; }
	virtual const std::vector<Math::float3> &getNormals() const { static std::vector<Math::float3> vec; return vec; }
	virtual const std::vector<Math::float3> &getTangents() const { static std::vector<Math::float3> vec; return vec; }
	virtual const std::vector<Math::float2> &getTexcoord0() const { static std::vector<Math::float2> vec; return vec; }
	virtual const std::vector<Math::float2> &getTexcoord1() const { static std::vector<Math::float2> vec; return vec; }
	virtual const std::vector<BoneIndex> &getBoneIndices() const { static std::vector<BoneIndex> vec; return vec; }
	virtual const std::vector<Math::float3> &getBoneWeight() const { static std::vector<Math::float3> vec; return vec; }
	virtual const std::vector<uint32_t> &getIndices() const { static std::vector<uint32_t> vec; return vec; }
	virtual const Math::BoundingBox &getBoundingBox() const { static Math::BoundingBox box; return box; }
};

using VertexInputSlots = std::bitset<dx12lib::kVertexBufferSlotCount>;

struct DrawArgs {
	size_t vertexCount = 0;
	size_t baseVertexLocation = 0;
	size_t indexCount = 0;
	size_t startIndexLocation = 0;
	size_t instanceCount = 1;
	size_t startInstanceLocation = 0;
};

class Geometry {
public:
	void bind(dx12lib::IGraphicsContext &graphicsCtx, const VertexInputSlots &vertexInputSlot) const;
	void setVertexBuffer(size_t idx, std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer);
	void setIndexBuffer(std::shared_ptr<dx12lib::IndexBuffer> pIndexBuffer);
	void setMesh(std::shared_ptr<IMesh> pMesh);
	std::shared_ptr<dx12lib::VertexBuffer> getVertexBuffer(size_t idx) const;
	std::shared_ptr<dx12lib::IndexBuffer> getIndexBuffer() const;
	std::shared_ptr<IMesh> getMesh() const;
	void setDrawArgs(const DrawArgs &drawArgs);
	void applyTransform(const Math::Matrix4 &matWorld);
	void setTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	const DrawArgs &getDrawArgs() const;
	const Math::BoundingBox &getWorldAABB() const;
	D3D_PRIMITIVE_TOPOLOGY getTopology() const;
	void genDrawArgs();
	void draw(dx12lib::IGraphicsContext &graphicsCtx) const;
protected:
	DrawArgs _drawArgs;
	Math::BoundingBox _worldAABB;
	std::shared_ptr<IMesh> _pMesh;
	std::shared_ptr<dx12lib::IndexBuffer> _pIndexBuffer;
	std::shared_ptr<dx12lib::VertexBuffer> _pVertexBufferList[dx12lib::kVertexBufferSlotCount];
	D3D_PRIMITIVE_TOPOLOGY _topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
};

}
