#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {

class Computable;
class ComputablePass : public ExecutablePass {
public:
	using ExecutablePass::ExecutablePass;
	void execute(dx12lib::DirectContextProxy pDirectCtx) override;
	void setComputable(std::shared_ptr<Computable> pComputable);
	auto getComputable() const -> std::shared_ptr<Computable>;
	auto getPassType() const -> PassType override;
private:
	std::shared_ptr<Computable> _pComputable;
};

}
