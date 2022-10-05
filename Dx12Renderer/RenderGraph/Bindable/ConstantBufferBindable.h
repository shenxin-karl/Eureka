#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Bindable/Bindable.hpp>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace rgph {

class ConstantBufferBindable : public Bindable {
public:
	static std::shared_ptr<ConstantBufferBindable> make(std::string shaderInputName,
		std::shared_ptr<dx12lib::IConstantBuffer> pConstantBuffer
	);
	void bind(dx12lib::IGraphicsContext &graphicsCtx) const override;
	ConstantBufferBindable() : Bindable(BindableType::ConstantBuffer) {}
private:
	std::string _shaderInputName;
	std::shared_ptr<dx12lib::IConstantBuffer> _pConstantBuffer;
};

}
