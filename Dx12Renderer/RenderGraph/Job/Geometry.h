#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Job/ShaderLayout.h>

namespace rgph {

interface IMesh : public NonCopyable {
#define VEC_REF(type) static std::vector<type> vec; return vec;
	using BoneIndex = std::array<uint8_t, 4>;
	virtual const std::string &getMeshName() const = 0;
	virtual const std::vector<Math::float3> &getPositions() const	{ VEC_REF(Math::float3); }
	virtual const std::vector<Math::float3> &getNormals() const		{ VEC_REF(Math::float3); }
	virtual const std::vector<Math::float4> &getTangents() const	{ VEC_REF(Math::float4); }
	virtual const std::vector<Math::float4> &getColors() const		{ VEC_REF(Math::float4); }
	virtual const std::vector<Math::float2> &getTexCoord0() const	{ VEC_REF(Math::float2); }
	virtual const std::vector<Math::float2> &getTexCoord1() const	{ VEC_REF(Math::float2); }
	virtual const std::vector<Math::float2> &getTexCoord2() const	{ VEC_REF(Math::float2); }
	virtual const std::vector<Math::float2> &getTexCoord3() const	{ VEC_REF(Math::float2); }
	virtual const std::vector<Math::float3> &getTexCoord4() const	{ VEC_REF(Math::float3); }
	virtual const std::vector<Math::float3> &getTexCoord5() const	{ VEC_REF(Math::float3); }
	virtual const std::vector<Math::float4> &getTexCoord6() const	{ VEC_REF(Math::float4); }
	virtual const std::vector<Math::float4> &getTexCoord7() const	{ VEC_REF(Math::float4); }
	virtual const std::vector<BoneIndex>	&getBoneIndices() const	{ VEC_REF(BoneIndex);	 }
	virtual const std::vector<Math::float3> &getBoneWeight() const	{ VEC_REF(Math::float3); }
	virtual const std::vector<uint32_t>		&getIndices() const		{ VEC_REF(uint32_t);	 }
	virtual const Math::BoundingBox			&getBoundingBox() const	{ static Math::BoundingBox box; return box; }
#undef VEC_REF
};

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

	void bind(dx12lib::IGraphicsContext &graphicsCtx, const ShaderLayoutMask &vertexInputSlot) const;
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
