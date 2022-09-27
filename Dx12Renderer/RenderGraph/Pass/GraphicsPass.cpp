#include "GraphicsPass.h"
#include "Dx12lib/Texture/TextureStd.h"

namespace rgph {

GraphicsPass::GraphicsPass(const std::string &passName, bool rtActive, bool dsActive)
: ExecutablePass(passName)
, pRenderTarget(this, "RenderTarget", rtActive)
, pDepthStencil(this, "DepthStencil", dsActive)
{
	pGetRTVFunc = [](const dx12lib::IRenderTarget *ptr) -> const dx12lib::RenderTargetView & {
		auto *pResource = dynamic_cast<const dx12lib::IRenderTarget2D *>(ptr);
		assert(pResource != nullptr);
		return pResource->getRTV();
	};
	pGetDSVFunc = [](const dx12lib::IDepthStencil *ptr) -> const dx12lib::DepthStencilView &{
		auto *pResource = dynamic_cast<const dx12lib::IDepthStencil2D *>(ptr);
		assert(pResource != nullptr);
		return pResource->getDSV();
	};
}

void GraphicsPass::preExecute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::preExecute(pDirectCtx);
}

void GraphicsPass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::execute(pDirectCtx);
	bindRenderTarget(*pDirectCtx);
}

void GraphicsPass::postExecute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::postExecute(pDirectCtx);
}

PassType GraphicsPass::getPassType() const {
	return PassType::GraphicsPass;
}

void GraphicsPass::bindRenderTarget(dx12lib::IGraphicsContext &graphicsCtx) {
	size_t width = pDepthStencil->getWidth();
	size_t height = pDepthStencil->getHeight();
	if (customViewport.has_value()) {
		graphicsCtx.setViewport(*customViewport);
	} else {
		graphicsCtx.setViewport(D3D12_VIEWPORT{
			.TopLeftX = 0.f,
			.TopLeftY = 0.f,
			.Width = static_cast<FLOAT>(width),
			.Height = static_cast<FLOAT>(height),
			.MinDepth = 0.f,
			.MaxDepth = 1.f,
		});
	}

	if (customScissorRect.has_value()) {
		graphicsCtx.setScissorRect(*customScissorRect);
	} else {
		graphicsCtx.setScissorRect(D3D12_RECT{
			.left = 0,
			.top = 0,
			.right = static_cast<LONG>(width),
			.bottom = static_cast<LONG>(height)
		});
	}

	if (pRenderTarget != nullptr) {
		graphicsCtx.setRenderTarget(
			pGetRTVFunc(pRenderTarget.get()),
			pGetDSVFunc(pDepthStencil.get())
		);
	}
	else {
		graphicsCtx.setRenderTarget(pGetDSVFunc(pDepthStencil.get()));
	}
}

DXGI_FORMAT GraphicsPass::getRtFormat() const {
	return pRenderTarget->getFormat();
}

DXGI_FORMAT GraphicsPass::getDsFormat() const {
	return pDepthStencil->getFormat();
}

const dx12lib::RenderTargetView & GraphicsPass::getRTV() const {
	return pGetRTVFunc(pRenderTarget.get());
}

const dx12lib::DepthStencilView & GraphicsPass::getDSV() const {
	return pGetDSVFunc(pDepthStencil.get());
}

}
