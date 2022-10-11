#pragma once
#include <memory>
#include <string>
#include <vector>
#include <Dx12lib/Context/ContextProxy.hpp>
#include "RenderGraph/Utility/Utility.h"

namespace rgph {

class RenderQueuePass;
class ExecutablePass;
class RenderGraph {
public:
	void addPass(std::shared_ptr<ExecutablePass> pPass);
	ExecutablePass *getPass(const std::string &passName) const;
	RenderQueuePass *getRenderQueuePass(const std::string &passName) const;
	void execute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view);
	void reset();
	void finalize();
private:
	bool _finalized = false;
	std::vector<std::shared_ptr<ExecutablePass>> _passes;
	std::vector<std::shared_ptr<ExecutablePass>> _executeList;
	std::vector<std::shared_ptr<RenderQueuePass>> _renderQueuePasses;
};

}
