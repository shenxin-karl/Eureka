#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>
#include <RenderGraph/Pass/GraphicsPass.h>

namespace rgph {

class ClearRtPass : public ExecutablePass {
public:
	ClearRtPass(const std::string &passName)
	: ExecutablePass(passName)
	, pRenderTarget2d(this, "pRenderTarget2d") {
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		const auto &clearValue = pRenderTarget2d->getClearValue();
		pDirectCtx->clearColor(pRenderTarget2d->get2dRTV(), clearValue.Color);
	}
public:
	PassResourcePtr<dx12lib::Texture> pRenderTarget2d;
};

class ClearDsPass : public ExecutablePass {
public:
	ClearDsPass(const std::string &passName)
	: ExecutablePass(passName)
	, pDepthStencil2d(this, "pDepthStencil2d") {
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		const auto &clearValue = pDepthStencil2d->getClearValue();
		pDirectCtx->clearDepthStencil(pDepthStencil2d->get2dDSV(), 
			clearValue.DepthStencil.Depth, 
			clearValue.DepthStencil.Stencil
		);
	}
public:
	PassResourcePtr<dx12lib::Texture> pDepthStencil2d;
};


class ClearPass : public ExecutablePass {
public:
public:
	ClearPass(const std::string &passName)
	: ExecutablePass(passName)
	, pRenderTarget2d(this, "pRenderTarget2d")
	, pDepthStencil2d(this, "pDepthStencil2d") {
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		const auto &rtClearValue = pRenderTarget2d->getClearValue();
		pDirectCtx->clearColor(pRenderTarget2d->get2dRTV(), rtClearValue.Color);

		const auto &dsClearValue = pDepthStencil2d->getClearValue();
		pDirectCtx->clearDepthStencil(pDepthStencil2d->get2dDSV(),
			dsClearValue.DepthStencil.Depth,
			dsClearValue.DepthStencil.Stencil
		);
	}
public:
	PassResourcePtr<dx12lib::Texture> pRenderTarget2d;
	PassResourcePtr<dx12lib::Texture> pDepthStencil2d;
};

}
