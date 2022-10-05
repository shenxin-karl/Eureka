#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Bindable/Bindable.hpp>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace rgph {

class SamplerTextureBindable : public Bindable {
public:
	SamplerTextureBindable() : Bindable(BindableType::SamplerTexture) {}
	void bind(dx12lib::IGraphicsContext &graphicsCtx) const override;
	static std::shared_ptr<SamplerTextureBindable> make(
		std::string shaderInputName, 
		dx12lib::ShaderResourceView srv,
		std::shared_ptr<dx12lib::Texture> pTexture
	);
private:
	std::string _shaderInputName;
	dx12lib::ShaderResourceView _srv;
	std::shared_ptr<dx12lib::Texture> _pTexture;
};

}
