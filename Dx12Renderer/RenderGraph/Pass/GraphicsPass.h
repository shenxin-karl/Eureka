#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {

class GraphicsPass : public ExecutablePass {
public:
	GraphicsPass(const std::string &passName, bool rtActive = true, bool dsActive = true);
	void preExecute(dx12lib::DirectContextProxy pDirectCtx) override;
	void execute(dx12lib::DirectContextProxy pDirectCtx) override;
	void postExecute(dx12lib::DirectContextProxy pDirectCtx) override;
	PassType getPassType() const override;
	void bindRenderTarget(dx12lib::IGraphicsContext &graphicsCtx);
	DXGI_FORMAT getRtFormat() const;
	DXGI_FORMAT getDsFormat() const;
	const dx12lib::RenderTargetView &getRTV() const;
	const dx12lib::DepthStencilView &getDSV() const;
public:
	using GetRTVFuncType = std::function<const dx12lib::RenderTargetView &(const dx12lib::IRenderTarget *)>;
	using GetDSVFuncType = std::function<const dx12lib::DepthStencilView &(const dx12lib::IDepthStencil *)>;

	std::optional<D3D12_RECT> customScissorRect;
	std::optional<D3D12_VIEWPORT> customViewport;
	GetRTVFuncType pGetRTVFunc;
	GetDSVFuncType pGetDSVFunc;
	PassResourcePtr<dx12lib::IRenderTarget> pRenderTarget;
	PassResourcePtr<dx12lib::IDepthStencil> pDepthStencil;
};

}
