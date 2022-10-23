#pragma once
#include <optional>
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <RenderGraph/Pass/PassResourcePtr.hpp>
#include <RenderGraph/Utility/Utility.h>

namespace rgph {

class ExecutablePass : public NonCopyable {
public:
	explicit ExecutablePass(const std::string &passName);
	PassResourceBase *getPassResource(const std::string &resourceName) const;
	const std::string &getPassName() const;
	virtual void preExecute(dx12lib::IDirectContext &directCtx, const RenderView &view);
	virtual void execute(dx12lib::IDirectContext &directCtx, const RenderView &view);
	virtual void postExecute(dx12lib::IDirectContext &directCtx, const RenderView &view);
	virtual void onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height);
	virtual void reset();
	virtual auto getPassType() const -> PassType;
private:
	friend class PassResourceBase;
	friend class RenderGraph;
	void addPassResource(PassResourceBase *pResource);
	const std::vector<PassResourceBase *> &getPassResources() const;
private:
	std::string _passName;
	std::vector<PassResourceBase *> _passResources;
};

}
