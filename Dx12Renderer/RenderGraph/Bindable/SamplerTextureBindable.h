#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Bindable/Bindable.hpp>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace rgph {

class SamplerTextureBindable : public Bindable {
public:
	SamplerTextureBindable() : Bindable(BindableType::SamplerTexture) {}

	void bind(dx12lib::IGraphicsContext &graphicsCtx) const override;

	static std::shared_ptr<SamplerTextureBindable> make2D(
		dx12lib::ShaderRegister shaderRegister,  
		std::shared_ptr<dx12lib::Texture> pTexture
	);

	static std::shared_ptr<SamplerTextureBindable> makeArray(
		dx12lib::ShaderRegister shaderRegister,
		std::shared_ptr<dx12lib::Texture> pTexture
	);

	static std::shared_ptr<SamplerTextureBindable> makeCube(
		dx12lib::ShaderRegister shaderRegister,
		std::shared_ptr<dx12lib::Texture> pTexture
	);
private:
	dx12lib::ShaderResourceView _srv;
	dx12lib::ShaderRegister _shaderRegister;
	std::shared_ptr<dx12lib::Texture> _pTexture;
};

}
