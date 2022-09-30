#include "SubPassVariant.h"
#include "Shader.h"

namespace Eureka {

SubPassVariant::SubPassVariant(const SubPassVariant *pGraphicsShader) : _pGraphicsShader(pGraphicsShader)
{

}

auto SubPassVariant::getPSO(std::vector<DXGI_FORMAT> rtFormats, DXGI_FORMAT dsFormat) const
	-> std::weak_ptr<dx12lib::GraphicsPSO>
{
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto SubPassVariant::getPSO(DXGI_FORMAT rtFormat, DXGI_FORMAT dsFormat) const
	-> std::weak_ptr<dx12lib::GraphicsPSO>
{
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto SubPassVariant::getPSO(DXGI_FORMAT dsFormat) const -> std::weak_ptr<dx12lib::GraphicsPSO> {
	return std::weak_ptr<dx12lib::GraphicsPSO>{};
}

auto SubPassVariant::getVertexInputSlots() -> const rgph::VertexInputSlots & {
	return _vertexInputSlots;
}

auto SubPassVariant::getNumRenderTarget() const -> size_t {
	return 0;
}

}
