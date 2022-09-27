#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Bindable/Bindable.hpp>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace rgph {

class ConstantBufferBindable : public Bindable {
public:
	static std::shared_ptr<ConstantBufferBindable> make(const dx12lib::ShaderRegister &sr,
		std::shared_ptr<dx12lib::IConstantBuffer> pConstantBuffer
	);
	void bind(dx12lib::IGraphicsContext &graphicsCtx) const override;
	ConstantBufferBindable() : Bindable(BindableType::ConstantBuffer) {}
private:
	dx12lib::ShaderRegister _shaderRegister;
	std::shared_ptr<dx12lib::IConstantBuffer> _pConstantBuffer;
};

}
