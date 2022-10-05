#include "SamplerTextureBindable.h"
#include "Dx12lib/Texture/Texture.h"

namespace rgph {

void SamplerTextureBindable::bind(dx12lib::IGraphicsContext &graphicsCtx) const {
	graphicsCtx.setShaderResourceView(_shaderInputName, _srv);
}

std::shared_ptr<SamplerTextureBindable> SamplerTextureBindable::make(
	std::string shaderInputName,
	dx12lib::ShaderResourceView srv,
	std::shared_ptr<dx12lib::Texture> pTexture)
{
	auto pBindable = std::make_shared<SamplerTextureBindable>();
	pBindable->_shaderInputName = std::move(shaderInputName);
	pBindable->_srv = std::move(srv);
	pBindable->_pTexture = std::move(pTexture);
	return pBindable;

}

}
