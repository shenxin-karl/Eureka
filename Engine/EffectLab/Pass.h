#pragma once
#include <string>
#include <memory>
#include <Dx12lib/Tool/D3Dx12.h>
#include "Foundation/NonCopyable.h"

namespace Eureka {

enum class RenderQueueLabel {
	Invalid     = -1,
	BackGround	= 1000,
	Geometry	= 2000,
	AlphaTest	= 2450,
	Opaque		= 2500,
	Transparent = 3000,
	Overlay		= 4000,
	Max			= 5000
};

class ShaderKeywordSet;
class Pass : NonCopyable {
	friend class PassParser;
public:
	Pass();
private:
	std::string						  _tag;
	std::string						  _vertexEntryPoint;
	std::string						  _hullEntryPoint;
	std::string						  _domainEntryPoint;
	std::string						  _geometryEntryPoint;
	std::string						  _pixelEntryPoint;
	RenderQueueLabel				  _renderQueue		= RenderQueueLabel::Invalid;
	std::shared_ptr<ShaderKeywordSet> _pKeywordSet		= nullptr;
	D3D12_RASTERIZER_DESC			  _rasterizerDesc	= CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_BLEND_DESC				  _blendDesc		= CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC		  _depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	int								  _stencilRef		= 0;
};

}
