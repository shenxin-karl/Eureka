#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {

class PresentPass : public ExecutablePass {
public:
	PresentPass(const std::string &passName)
	: ExecutablePass(passName)
	, pBackBuffer(this, "pBackBuffer")
	{
		pBackBuffer.preExecuteState = D3D12_RESOURCE_STATE_PRESENT;
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		// Nothing to do
	}
public:
	PassResourcePtr<dx12lib::Texture> pBackBuffer;
};

}
