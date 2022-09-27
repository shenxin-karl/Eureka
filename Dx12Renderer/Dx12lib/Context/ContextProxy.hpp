#pragma once
#include <memory>
#include <Dx12lib/Context/CommandList.h>
#include <Dx12lib/Context/CommonContext.h>

namespace dx12lib {

class CommandList;

template<typename T>
class _ContextProxy {
public:
	_ContextProxy() = default;

	_ContextProxy(std::shared_ptr<CommandList> pCmdList) : _pCmdList(pCmdList) {
	}

	template<typename OT> requires(std::is_same_v<T, OT> || std::is_base_of_v<OT, T>)
	_ContextProxy(_ContextProxy<OT> pOther) : _pCmdList(pOther._pCmdList) {
	}

	T *operator->() {
		return static_cast<T *>(_pCmdList.get());
	}
	T &operator*() {
		return static_cast<T &>(*_pCmdList);
	}
	const T *operator->() const {
		return static_cast<const T *>(_pCmdList.get());
	}
	const T &operator*() const {
		return static_cast<const T &>(*_pCmdList);
	}
	operator bool() const {
		return _pCmdList != nullptr;
	}
	friend bool operator==(const _ContextProxy &lhs, std::nullptr_t) {
		return lhs._pCmdList == nullptr;
	}
	friend bool operator!=(const _ContextProxy &lhs, std::nullptr_t) {
		return lhs._pCmdList != nullptr;
	}

	template<typename OT> requires(std::is_base_of_v<OT, T>)
	operator _ContextProxy<OT>() const {
		return _ContextProxy<OT>(_pCmdList);
	}
private:
	friend class CommandQueue;
	std::shared_ptr<CommandList> getCmdList() const {
		return _pCmdList;
	}

	std::shared_ptr<CommandList> _pCmdList;
};

using ContextProxy = _ContextProxy<IContext>;
using CommonContextProxy = _ContextProxy<ICommonContext>;
using GraphicsContextProxy = _ContextProxy<IGraphicsContext>;
using ComputeContextProxy = _ContextProxy<IComputeContext>;
using DirectContextProxy = _ContextProxy<IDirectContext>;

}