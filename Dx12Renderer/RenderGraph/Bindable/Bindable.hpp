#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <source_location>

namespace rgph {

enum class BindableType {
	Unknown = 0,
	ConstantBuffer,
	SamplerTexture,
	PassResourceUAV,
	PassResourceSRV,
};

class Bindable : public	NonCopyable {
public:
	Bindable(BindableType bindableType) : _bindableType(bindableType) {}
	virtual void bind(dx12lib::IGraphicsContext &graphicsCtx) const = 0;
	~Bindable() override = default;
	BindableType getBindableType() const {
		return _bindableType;
	}
private:
	BindableType _bindableType;
};

}
