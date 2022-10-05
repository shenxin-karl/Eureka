#pragma once
#include <vector>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <RenderGraph/Bindable/Bindable.hpp>
#include <RenderGraph/Job/Geometry.h>
#include <RenderGraph/Job/Job.h>

namespace rgph {

class GraphicsPass;
class SubPass {
public:
	SubPass(std::weak_ptr<dx12lib::GraphicsPSO> pGraphicsPso);
	const std::string &getSubPassName() const;
	void addBindable(std::shared_ptr<Bindable> pBindable);
	void bind(dx12lib::IGraphicsContext &graphicsCtx) const;
	void accept(const Job &job);
	void execute(dx12lib::IGraphicsContext &graphicsCtx) const;
	void reset();
	~SubPass();
	size_t getJobCount() const;
	const std::vector<Job> &getJobs() const;
	void setShaderLayoutMask(const ShaderLayoutMask &inputSlot);
	void setTransformCBufferShaderRegister(const dx12lib::ShaderRegister &transShaderRegister);
	void setPassCBufferShaderRegister(const dx12lib::ShaderRegister &passShaderRegister);
	const ShaderLayoutMask &getShaderLayoutMask() const;
	const dx12lib::ShaderRegister &getTransformCBufferShaderRegister() const;
	const dx12lib::ShaderRegister &getPassCBufferShaderRegister() const;
	const std::vector<std::shared_ptr<Bindable>> &getBindables() const;
	void execute(dx12lib::IGraphicsContext &graphicsCtx, const std::vector<Job> &jobs) const;
	void setGraphicsPass(const GraphicsPass *pGraphicsPass);
	const GraphicsPass *getGraphicsPass() const;
	bool valid() const;

	using BindCallBackType = std::function<void(const SubPass *, dx12lib::IGraphicsContext &)>;
	// [&](const rgph::SubPass *pSubPass, dx12lib::IGraphicsContext &graphicsCtx)
	void setOnBindCallback(const BindCallBackType &pOnBindCallBack);
protected:
	bool _finalize = false;
	std::vector<Job> _jobs;
	std::string _subPassName;
	BindCallBackType _pOnBindCallback;
	ShaderLayoutMask _shaderLayoutMask;
	const GraphicsPass *_pGraphicsPass = nullptr;
	dx12lib::ShaderRegister _transformCBufferShaderRegister;
	dx12lib::ShaderRegister _passCBufferShaderRegister;
	std::weak_ptr<dx12lib::GraphicsPSO> _pGraphicsPso;
	std::vector<std::shared_ptr<Bindable>> _bindables;
};

}
