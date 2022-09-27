#include "SamplerTextureBindable.h"
#include "Dx12lib/Texture/Texture.h"

namespace rgph {

void SamplerTextureBindable::bind(dx12lib::IGraphicsContext &graphicsCtx) const {
	graphicsCtx.setShaderResourceView(_shaderRegister, _srv);
}

std::shared_ptr<SamplerTextureBindable> SamplerTextureBindable::make2D(dx12lib::ShaderRegister shaderRegister,
	std::shared_ptr<dx12lib::Texture> pTexture)
{
	assert(shaderRegister.slot.isSRV());
	assert(pTexture != nullptr);
	auto pBindable = std::make_shared<SamplerTextureBindable>();
	pBindable->_srv = pTexture->get2dSRV();
	pBindable->_shaderRegister = shaderRegister;
	pBindable->_pTexture = pTexture;
	return pBindable;
}

std::shared_ptr<SamplerTextureBindable> SamplerTextureBindable::makeArray(dx12lib::ShaderRegister shaderRegister,
	std::shared_ptr<dx12lib::Texture> pTexture)
{
	assert(shaderRegister.slot.isSRV());
	assert(pTexture != nullptr);
	auto pBindable = std::make_shared<SamplerTextureBindable>();
	pBindable->_srv = pTexture->getArraySRV();
	pBindable->_shaderRegister = shaderRegister;
	pBindable->_pTexture = pTexture;
	return pBindable;
}

std::shared_ptr<SamplerTextureBindable> SamplerTextureBindable::makeCube(dx12lib::ShaderRegister shaderRegister,
	std::shared_ptr<dx12lib::Texture> pTexture)
{
	assert(shaderRegister.slot.isSRV());
	assert(pTexture != nullptr);
	auto pBindable = std::make_shared<SamplerTextureBindable>();
	pBindable->_srv = pTexture->getCubeSRV();
	pBindable->_shaderRegister = shaderRegister;
	pBindable->_pTexture = pTexture;
	return pBindable;
}

}
