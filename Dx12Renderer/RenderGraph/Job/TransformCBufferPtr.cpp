#include "TransformCBufferPtr.h"
#include "Dx12lib/Pipeline/ShaderRegister.hpp"

namespace rgph {

using namespace Math;

const float4x4 & TransformCBufferPtr::getMatWorld() const {
	return getTransformStore().matWorld;
}

const float4x4 & TransformCBufferPtr::getMatNormal() const {
	return getTransformStore().matNormal;
}

const TransformStore & TransformCBufferPtr::getTransformStore() const {
	return _transform;
}

void TransformCBufferPtr::setTransformCBuffer(dx12lib::FRConstantBufferPtr<TransformStore> pTransformCBuf) {
	assert(pTransformCBuf != nullptr);
	_pTransformCBuf = std::move(pTransformCBuf);
}

void TransformCBufferPtr::bind(dx12lib::IGraphicsContext &graphicsCtx, const dx12lib::ShaderRegister &shaderRegister) const {
	assert(_pTransformCBuf != nullptr);
	graphicsCtx.setConstantBuffer(shaderRegister, _pTransformCBuf);
}

void TransformCBufferPtr::setMatWorld(const Math::float4x4 &world) {
	Matrix4 matWorld(world);
	Matrix4 matInvWorld = inverse(matWorld);
	Matrix4 matNormal = transpose(inverse(matWorld));
	Matrix4 matInvNormal = inverse(matNormal);
	rgph::TransformStore store {
		.matWorld = float4x4(matWorld),
		.matInvWorld = float4x4(matInvWorld),
		.matNormal = float4x4(matNormal),
		.matInvNormal = float4x4(matInvNormal),
		.matPreFrameWorld = _first ? world :  _transform.matWorld,
	};
	_transform = store;
	_first = false;
	auto *ptr = _pTransformCBuf->map();
	std::memcpy(ptr, &store, sizeof(store));
}

TransformCBufferPtr::operator bool() const {
	return _pTransformCBuf != nullptr;
}

bool operator==(const TransformCBufferPtr &lhs, const TransformCBufferPtr &rhs) {
	return lhs._pTransformCBuf == rhs._pTransformCBuf;
}

bool operator!=(const TransformCBufferPtr &transformCBufferPtr, const TransformCBufferPtr &transformCBuffer) {
	return !(transformCBufferPtr == transformCBuffer);
}

bool operator!=(const TransformCBufferPtr &lhs, std::nullptr_t) {
	return lhs._pTransformCBuf != nullptr;
}

bool operator==(std::nullptr_t, const TransformCBufferPtr &rhs) {
	return rhs._pTransformCBuf == nullptr;
}
}
