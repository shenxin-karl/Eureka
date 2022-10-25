#include "TemporalAAPass.h"
#include "EngineDefinition/EngineDefinition.h"
#include <DirectXColors.h>

namespace Eureka {

TemporalAAPass::TemporalAAPass(const std::string &passName)
: ExecutablePass(passName)
, pScreenMap(this, "ScreenMap")
, pOutputMap(this, "OutputMap")
{
}

void TemporalAAPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(directCtx, view);

}

void TemporalAAPass::onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height) {
	ExecutablePass::onResize(directCtx, width, height);

	directCtx.trackResource(_pTemporalColor[0]);
	directCtx.trackResource(_pTemporalColor[1]);

	auto desc = dx12lib::Texture::make2D(
		kTemporalAAFormat, 
		width, 
		height, 
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
	);

	D3D12_CLEAR_VALUE clearValue;
	std::memcpy(&clearValue.Color, &DX::Colors::Black, sizeof(FLOAT) * 4);

	_pTemporalColor[0] = directCtx.createTexture(desc, &clearValue);
	_pTemporalColor[1] = directCtx.createTexture(desc, &clearValue);
}

}
