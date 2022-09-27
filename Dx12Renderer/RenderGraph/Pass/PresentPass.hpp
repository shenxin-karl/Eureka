#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {

class PresentPass : public GraphicsPass {
public:
	PresentPass(const std::string &passName) : GraphicsPass(passName, true, false) {
		pRenderTarget.preExecuteState = D3D12_RESOURCE_STATE_PRESENT;
	}

	void execute(dx12lib::DirectContextProxy pDirectCtx) override {
		// Nothing to do
	}
};

}
