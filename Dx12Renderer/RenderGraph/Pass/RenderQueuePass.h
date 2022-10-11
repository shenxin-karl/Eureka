#pragma once
#include <RenderGraph/Pass/GraphicsPass.h>
#include <RenderGraph/Job/Job.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace rgph {

class SubPass;
class RenderQueuePass : public GraphicsPass {
public:
	using GraphicsPass::GraphicsPass;
	std::shared_ptr<SubPass> getSubPassByName(const std::string &subPassName) const;
	void addSubPass(std::shared_ptr<SubPass> pSubPass);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view) override;
	void reset() override;
	void setPassCBuffer(std::shared_ptr<dx12lib::IConstantBuffer> pCBuffer);
	PassType getPassType() const override;
	std::shared_ptr<dx12lib::IConstantBuffer> getPassCBuffer() const;
protected:
	std::vector<std::shared_ptr<SubPass>> _subPasses;
	std::shared_ptr<dx12lib::IConstantBuffer> _pPassCBuffer;
};

}
