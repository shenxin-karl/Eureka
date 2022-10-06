#pragma once
#include <d3d12.h>
#include <memory>
#include <string>


namespace dx12lib {
	struct IResource;
	struct ICommonContext;
}

namespace rgph {

class ExecutablePass;
class PassResourceBase {
public:
	PassResourceBase(ExecutablePass *pExecutablePass, std::string resourceName);
	void setFinished(bool bCond);
	bool isFinished() const;
	void setResourceSource(const PassResourceBase *pResourceSource);
	const std::string &getResourceName() const;
	const PassResourceBase *getResourceSource() const;
	const ExecutablePass *getExecutablePass() const;
	virtual void link(dx12lib::ICommonContext &commonCtx) = 0;
	virtual void reset() = 0;
	virtual ~PassResourceBase() = default;

	template<typename T> requires(std::is_base_of_v<dx12lib::IResource, T>)
	std::shared_ptr<T> cast() const;
private:
	friend class RenderGraph;
	virtual bool tryLink() = 0;
	virtual std::shared_ptr<dx12lib::IResource> getResource() const = 0;
protected:
	std::string _resourceName;
	ExecutablePass *_pExecutablePass;

	// 在编译 RenderGraph 时使用, 确定 Pass 执行的先后顺序
	bool _finished;
	bool _activated;
	const PassResourceBase *_pResourceSource;
public:
	constexpr static D3D12_RESOURCE_STATES kNoneType = static_cast<D3D12_RESOURCE_STATES>(-1);
	D3D12_RESOURCE_STATES preExecuteState = kNoneType;
};

template <typename T> requires (std::is_base_of_v<dx12lib::IResource, T>)
std::shared_ptr<T> PassResourceBase::cast() const {
	auto pResource = getResource();
	auto pRet = std::dynamic_pointer_cast<T>(pResource);
	assert(pRet != nullptr);
	return pRet;
}

}
