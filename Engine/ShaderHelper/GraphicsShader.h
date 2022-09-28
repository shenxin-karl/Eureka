#pragma once
#include <string>
#include <bitset>
#include <d3d12.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <Dx12lib/Tool/D3Dx12.h>
#include <Dx12lib/dx12libStd.h>
#include "ShaderHelper/KeywordMask.h"

namespace Eureka {

enum class EnterPointType {
	VS = 0,
	HS = 1,
	DS = 2,
	GS = 3,
	PS = 4,
	CS = 5,
};

struct ShaderEnterPoint {
	EnterPointType type;
	std::string entryPoint;
	std::string version;
};

struct GraphicsShaderDesc {
	std::string fileName;
	std::vector<ShaderEnterPoint> enterPoints;
	std::weak_ptr<dx12lib::Device> pDevice;
	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

class GraphicsShaderVariant;
class GraphicsShader {
public:
	using ShaderVariantMap = std::unordered_map<std::bitset<KeywordMask::kMaxKeyWord>, std::unique_ptr<GraphicsShaderVariant>>;
	static inline ShaderEnterPoint VSEnterPoint = { EnterPointType::VS, "VS", "vs_5_0" };
	static inline ShaderEnterPoint HSEnterPoint = { EnterPointType::HS, "HS", "hs_5_0" };
	static inline ShaderEnterPoint DSEnterPoint = { EnterPointType::DS, "DS", "ds_5_0" };
	static inline ShaderEnterPoint GSEnterPoint = { EnterPointType::GS, "GS", "gs_5_0" };
	static inline ShaderEnterPoint PSEnterPoint = { EnterPointType::PS, "PS", "ps_5_0" };
	static inline std::vector<ShaderEnterPoint> VS_PS = { VSEnterPoint, PSEnterPoint };
	static inline std::vector<ShaderEnterPoint> VS_GS_PS = { VSEnterPoint, GSEnterPoint, PSEnterPoint };
	static inline std::vector<ShaderEnterPoint> VS_HS_DS_PS = { VSEnterPoint, HSEnterPoint, DSEnterPoint, PSEnterPoint };
	static inline std::vector<ShaderEnterPoint> VS_HS_DS_GS_PS = { VSEnterPoint, HSEnterPoint, DSEnterPoint, GSEnterPoint, PSEnterPoint };
public:
	GraphicsShader(const GraphicsShaderDesc &desc);
	~GraphicsShader();
	void setKeyWord(const std::string &keyword, bool enable);
	auto getShaderContent() const -> const std::string &;
	auto getBlendDesc() const -> const D3D12_BLEND_DESC &;
	auto getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC &;
	auto getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &;
	auto getPrimitiveType() const ->D3D12_PRIMITIVE_TOPOLOGY_TYPE;
	auto getShaderVariant() const -> GraphicsShaderVariant *;
	auto getEntryPoints() const -> const std::vector<ShaderEnterPoint> &;
	auto getDevice() const -> std::weak_ptr<dx12lib::Device>;
	auto findKeywordIndex(const std::string &keyword) const -> size_t;
	auto getEnableKeywords() const -> std::vector<std::string>;
private:
	std::string				 _shaderContent;
	KeywordMask				 _keywordMask;
	GraphicsShaderDesc		 _graphicsShaderDesc;
	mutable ShaderVariantMap _shaderVariantMap;
};

}
