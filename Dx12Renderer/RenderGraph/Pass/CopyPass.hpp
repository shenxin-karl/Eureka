#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {

class CopyPass : public ExecutablePass {
public:
	CopyPass(const std::string &passName)
		: ExecutablePass(passName)
		, pSrcResource(this, "pSrcResource")
		, pDstResource(this, "pDstResource")
	{
		pSrcResource.preExecuteState = D3D12_RESOURCE_STATE_COPY_SOURCE;
		pDstResource.preExecuteState = D3D12_RESOURCE_STATE_COPY_DEST;
	}

	void execute(dx12lib::IDirectContext &directCtx, const RenderView &view) override {
		directCtx.copyResource(pDstResource.getResource(), pSrcResource.getResource());
	}
public:
	PassResourcePtr<dx12lib::IResource> pSrcResource;
	PassResourcePtr<dx12lib::IResource> pDstResource;
};

}
