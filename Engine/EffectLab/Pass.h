#pragma once
#include <string>
#include <memory>
#include <Dx12lib/Tool/D3Dx12.h>
#include <filesystem>
#include <unordered_map>
#include "Foundation/NonCopyable.h"
#include "ShaderKeyword.h"

namespace Eureka {

class PassVariant;
class ShaderKeywordSet;

namespace fs = std::filesystem;

enum class RenderQueueLabel : uint16_t {
	Invalid     = static_cast<uint16_t>(-1),
	BackGround	= 1000,
	Geometry	= 2000,
	AlphaTest	= 2450,
	Opaque		= 2500,
	Transparent = 3000,
	Overlay		= 4000,
	Max			= 5000
};

class Pass : NonCopyable {
	friend class PassParser;
public:
	Pass();
	auto getTag() const -> const std::string &;
	auto getPassVariant(const ShaderKeyword &keyword) -> std::shared_ptr<PassVariant>;
	auto getKeywordSet() const -> std::shared_ptr<ShaderKeywordSet>;
	auto getStencilRef() const -> int;
	auto getRenderQueue() const -> RenderQueueLabel;
private:
	using PassVariantMap = std::unordered_map<ShaderKeyword::BitsetType, std::shared_ptr<PassVariant>>;
	std::string						  _tag;
	std::string						  _vertexEntryPoint;
	std::string						  _hullEntryPoint;
	std::string						  _domainEntryPoint;
	std::string						  _geometryEntryPoint;
	std::string						  _pixelEntryPoint;
	std::string						  _programContext;
	RenderQueueLabel				  _renderQueue		= RenderQueueLabel::Invalid;
	std::shared_ptr<ShaderKeywordSet> _pKeywordSet		= nullptr;
	D3D12_RASTERIZER_DESC			  _rasterizerDesc	= CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_BLEND_DESC				  _blendDesc		= CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC		  _depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	int								  _stencilRef		= 0;
	PassVariantMap					  _passVariantMap;
};

}
