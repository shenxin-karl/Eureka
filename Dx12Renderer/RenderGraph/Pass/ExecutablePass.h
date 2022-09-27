#pragma once
#include <optional>
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <RenderGraph/Pass/PassResourcePtr.hpp>

namespace rgph {

class ExecutablePass : public NonCopyable {
public:
	explicit ExecutablePass(const std::string &passName);
	PassResourceBase *getPassResource(const std::string &resourceName) const;
	const std::string &getPassName() const;
	virtual void preExecute(dx12lib::DirectContextProxy pDirectCtx);
	virtual void execute(dx12lib::DirectContextProxy pDirectCtx);
	virtual void postExecute(dx12lib::DirectContextProxy pDirectCtx);
	virtual void reset();
	virtual PassType getPassType() const;
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
