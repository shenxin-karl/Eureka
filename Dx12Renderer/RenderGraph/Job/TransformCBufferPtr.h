#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/Buffer/FRConstantBuffer.hpp>

namespace rgph {

struct TransformStore {
	Math::float4x4 matWorld		    = Math::float4x4::Identity;
	Math::float4x4 matInvWorld      = Math::float4x4::Identity;
	Math::float4x4 matNormal		= Math::float4x4::Identity;
	Math::float4x4 matInvNormal		= Math::float4x4::Identity;
	Math::float4x4 matPreFrameWorld = Math::float4x4::Identity;
};

class TransformCBufferPtr {
public:
	const Math::float4x4 &getMatWorld() const;
	const Math::float4x4 &getMatNormal() const;
	const TransformStore &getTransformStore() const;
	void setTransformCBuffer(dx12lib::FRConstantBufferPtr<TransformStore> pTransformCBuf);
	void bind(dx12lib::IGraphicsContext &graphicsCtx, const dx12lib::ShaderRegister &shaderRegister) const;
	void setMatWorld(const Math::float4x4 &world);
	explicit operator bool() const;
	friend bool operator==(const TransformCBufferPtr &lhs, const TransformCBufferPtr &rhs);
	friend bool operator!=(const TransformCBufferPtr &, const TransformCBufferPtr &);
	friend bool operator!=(const TransformCBufferPtr &lhs, std::nullptr_t);
	friend bool operator==(std::nullptr_t, const TransformCBufferPtr &rhs);
protected:
	bool _first = true;
	TransformStore _transform;
	dx12lib::FRConstantBufferPtr<TransformStore> _pTransformCBuf;
};

}
