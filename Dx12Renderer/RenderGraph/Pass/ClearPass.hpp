#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>
#include <Dx12lib/Texture/RenderTargetTexture.h>

#include "Dx12lib/Texture/DepthStencilTexture.h"

namespace rgph {

class ClearRtPass : public GraphicsPass {
public:
	ClearRtPass(const std::string &passName) : GraphicsPass(passName, true, false) {
		pRenderTarget.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		assert(pDepthStencil == nullptr);
		pDirectCtx->clearColor(getRTV(), pRenderTarget->getClearValue().Color);
	}
};

class ClearDsPass : public GraphicsPass {
public:
	ClearDsPass(const std::string &passName) : GraphicsPass(passName, false, true) {
		pDepthStencil.preExecuteState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		assert(pRenderTarget == nullptr);
		auto clearValue = pDepthStencil->getClearValue();
		pDirectCtx->clearDepthStencil(
			getDSV(),
			clearValue.DepthStencil.Depth,
			clearValue.DepthStencil.Stencil
		);
	}
};

class ClearPass : public GraphicsPass {
public:
	ClearPass(const std::string &passName) : GraphicsPass(passName, true, true) {
		pRenderTarget.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
		pDepthStencil.preExecuteState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		auto clearValue = pDepthStencil->getClearValue();
		pDirectCtx->clearColor(getRTV(), pRenderTarget->getClearValue().Color);
		pDirectCtx->clearDepthStencil(
			getDSV(),
			clearValue.DepthStencil.Depth,
			clearValue.DepthStencil.Stencil
		);
	}
};

}
