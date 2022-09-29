#include "GraphicsShaderVariant.h"
#include "GraphicsShader.h"

namespace Eureka {

GraphicsShaderVariant::GraphicsShaderVariant(const GraphicsShader *pGraphicsShader) : _pGraphicsShader(pGraphicsShader)
{
	const auto &graphicsShaderDesc = pGraphicsShader->getGraphicsShaderDesc();

}

auto GraphicsShaderVariant::getPSO(std::vector<DXGI_FORMAT> rtFormats, DXGI_FORMAT dsFormat) const
	-> std::weak_ptr<dx12lib::GraphicsPSO>
{
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto GraphicsShaderVariant::getPSO(DXGI_FORMAT rtFormat, DXGI_FORMAT dsFormat) const
	-> std::weak_ptr<dx12lib::GraphicsPSO>
{
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto GraphicsShaderVariant::getPSO(DXGI_FORMAT dsFormat) const -> std::weak_ptr<dx12lib::GraphicsPSO> {
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto GraphicsShaderVariant::getVertexInputSlots() -> const rgph::VertexInputSlots & {
	return _vertexInputSlots;
}

auto GraphicsShaderVariant::getNumRenderTarget() const -> size_t {
	return 0;
}

}
