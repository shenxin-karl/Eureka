#include <cassert>
#include <unordered_set>
#include "ShaderDesc.h"

namespace Eureka {

std::string toupper(const std::string &str) {
	std::string res;
	res.resize(str.size());
	for (auto c : str)
		res.push_back(std::toupper(c));
	return res;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

template<typename T, size_t N>
T getEnum(const std::pair<std::string, T>(&map)[N], const std::string &str) {
	auto s = toupper(str);
	trim(s);
	for (size_t i = 0; i < N; ++i) {
		if (s == map[i].first)
			return map[i].second;
	}
	return static_cast<T>(-1);
}

void ShaderDesc::setShaderFileName(const std::string &shaderFileName) {
	this->shaderFileName = shaderFileName;
}

void ShaderDesc::addShaderFeature(const sol::as_table_t<std::vector<std::string>> &strings) {
	auto strArray = strings.value();
	for (auto &s : strArray) {
		trim(s);
#if defined(DEBUG) || defined(_DEBUG)
		for (auto &c : s)
			assert(!std::isspace(c));
#endif
	}

	std::unordered_set<std::string> hashMap;
	for (auto &features : shaderFeatures) {
		for (auto &s : features) {
			if (hashMap.find(s) != hashMap.end()) {
				assert(false && "Repetition of variants");
				return;
			}
		}
	}
	shaderFeatures.push_back(strings.value());
}

void ShaderDesc::setVertexShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::VS));
	entryPoints.push_back({ ShaderType::VS, entryPoint });
}

void ShaderDesc::setHullShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::HS));
	entryPoints.push_back({ ShaderType::HS, entryPoint });
}

void ShaderDesc::setDomainShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::DS));
	entryPoints.push_back({ ShaderType::DS, entryPoint });
}

void ShaderDesc::setGeometryShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::GS));
	entryPoints.push_back({ ShaderType::GS, entryPoint });
}

void ShaderDesc::setPixelShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::PS));
	entryPoints.push_back({ ShaderType::PS, entryPoint });
}

void ShaderDesc::setAlphaToMask(bool enabled) {
	blendDesc.AlphaToCoverageEnable = enabled;
}

void ShaderDesc::setBlendColor(const std::string &srcOp, const std::string &dstOp) {
	setBlendColor(srcOp, dstOp, 0);
}

void ShaderDesc::setBlendColor(const std::string &srcOp, const std::string &dstOp, size_t renderTarget) {
	assert(renderTarget < 7);
	static const std::pair<std::string, D3D12_BLEND> blendMap[] = {
		{ toupper("One"), D3D12_BLEND_ONE },
		{ toupper("Zero"), D3D12_BLEND_ZERO },
		{ toupper("SrcColor"), D3D12_BLEND_SRC_COLOR },
		{ toupper("SrcAlpha"), D3D12_BLEND_SRC_ALPHA },
		{ toupper("DstColor"), D3D12_BLEND_DEST_COLOR },
		{ toupper("DstAlpha"), D3D12_BLEND_DEST_ALPHA },
		{ toupper("OneMinusSrcColor"), D3D12_BLEND_INV_SRC_COLOR },
		{ toupper("OneMinusSrcAlpha"), D3D12_BLEND_INV_SRC_ALPHA },
		{ toupper("OneMinusDstColor"), D3D12_BLEND_INV_DEST_COLOR },
		{ toupper("OneMinusDstAlpha"), D3D12_BLEND_INV_DEST_ALPHA },
	};

	D3D12_BLEND src = getEnum(blendMap, srcOp);
	D3D12_BLEND dst = getEnum(blendMap, dstOp);
	assert(src != static_cast<D3D12_BLEND>(-1));
	assert(dst != static_cast<D3D12_BLEND>(-1));
	blendDesc.RenderTarget[renderTarget].BlendEnable = true;
	blendDesc.RenderTarget[renderTarget].SrcBlend = src;
	blendDesc.RenderTarget[renderTarget].DestBlend = dst;
	blendDesc.IndependentBlendEnable = (renderTarget != 0);
}

void ShaderDesc::setBlendAlpha(const std::string &srcOp, const std::string &dstOp) {
	setBlendAlpha(srcOp, dstOp, 0);
}

void ShaderDesc::setBlendAlpha(const std::string &srcOp, const std::string &dstOp, size_t renderTarget) {
	static const std::pair<std::string, D3D12_BLEND> blendMap[] = {
		{ toupper("One"), D3D12_BLEND_ONE },
		{ toupper("Zero"), D3D12_BLEND_ZERO },
		{ toupper("SrcAlpha"), D3D12_BLEND_SRC_ALPHA },
		{ toupper("DstAlpha"), D3D12_BLEND_DEST_ALPHA },
		{ toupper("OneMinusSrcAlpha"), D3D12_BLEND_INV_SRC_ALPHA },
		{ toupper("OneMinusDstAlpha"), D3D12_BLEND_INV_DEST_ALPHA },
	};
	D3D12_BLEND src = getEnum(blendMap, srcOp);
	D3D12_BLEND dst = getEnum(blendMap, dstOp);
	assert(src != static_cast<D3D12_BLEND>(-1));
	assert(dst != static_cast<D3D12_BLEND>(-1));
	blendDesc.RenderTarget[renderTarget].BlendEnable = true;
	blendDesc.RenderTarget[renderTarget].SrcBlendAlpha = src;
	blendDesc.RenderTarget[renderTarget].DestBlendAlpha = dst;
	blendDesc.IndependentBlendEnable = (renderTarget != 0);
}

void ShaderDesc::setBlendOp(const std::string &op) {
	setBlendOp(op, 0);
}

void ShaderDesc::setBlendOp(const std::string &op, size_t renderTarget) {
	assert(renderTarget < 7);
	static const std::pair<std::string, D3D12_BLEND_OP> blendOpMap[] = {
		{ toupper("Add"), D3D12_BLEND_OP_ADD },
		{ toupper("Sub"), D3D12_BLEND_OP_SUBTRACT },
		{ toupper("RevSub"), D3D12_BLEND_OP_REV_SUBTRACT },
		{ toupper("Min"), D3D12_BLEND_OP_MIN },
		{ toupper("Max"), D3D12_BLEND_OP_MAX },
	};
	D3D12_BLEND_OP oper = getEnum(blendOpMap, op);
	assert(oper != static_cast<D3D12_BLEND_OP>(-1));
	blendDesc.RenderTarget[renderTarget].BlendOp = oper;
}

void ShaderDesc::setColorMask(const std::string &channel) {
	setColorMask(channel, 0);
}

void ShaderDesc::setColorMask(const std::string &channel, int renderTarget) {
	assert(renderTarget < 7);
	UINT8 state = 0;
	for (auto c : channel) {
		switch (std::toupper(c)) {
		case 'R':
			assert(!(state & D3D12_COLOR_WRITE_ENABLE_RED));
			state = state | D3D12_COLOR_WRITE_ENABLE_RED;
			break;
		case 'G':
			assert(!(state & D3D12_COLOR_WRITE_ENABLE_GREEN));
			state = state | D3D12_COLOR_WRITE_ENABLE_GREEN;
			break;
		case 'B':
			assert(!(state & D3D12_COLOR_WRITE_ENABLE_BLUE));
			state = state | D3D12_COLOR_WRITE_ENABLE_BLUE;
			break;
		case 'A':
			assert(!(state & D3D12_COLOR_WRITE_ENABLE_ALPHA));
			state = state | D3D12_COLOR_WRITE_ENABLE_ALPHA;
			break;
		default:
			assert(false);
		}
	}
	blendDesc.RenderTarget[renderTarget].RenderTargetWriteMask = state;
}

void ShaderDesc::setConservative(bool enabled) {
	rasterizerDesc.ConservativeRaster = enabled ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}

void ShaderDesc::setCull(const std::string &state) {
	static const std::pair<std::string, D3D12_CULL_MODE> cullMap[] = {
		{ toupper("Off"), D3D12_CULL_MODE_NONE },
		{ toupper("Front"), D3D12_CULL_MODE_FRONT },
		{ toupper("Back"), D3D12_CULL_MODE_BACK },
	};
	D3D12_CULL_MODE mode = getEnum(cullMap, state);
	assert(mode != static_cast<D3D12_CULL_MODE>(-1));
	rasterizerDesc.CullMode = mode;
}

void ShaderDesc::setOffset(float slopeScaledDepthBias, INT depthBias) {
	rasterizerDesc.SlopeScaledDepthBias = slopeScaledDepthBias;
	rasterizerDesc.DepthBias = depthBias;
}

void ShaderDesc::setZClip(bool enabled) {
	depthStencilDesc.DepthEnable = enabled;
}

void ShaderDesc::setZTest(const std::string &op) {
	static const std::pair<std::string, D3D12_COMPARISON_FUNC> zTestMap[] = {
		{ toupper("Less"), D3D12_COMPARISON_FUNC_LESS },
		{ toupper("LEqual"), D3D12_COMPARISON_FUNC_LESS_EQUAL },
		{ toupper("Equal"), D3D12_COMPARISON_FUNC_EQUAL },
		{ toupper("GEqual"), D3D12_COMPARISON_FUNC_GREATER_EQUAL },
		{ toupper("Greater"), D3D12_COMPARISON_FUNC_GREATER },
		{ toupper("NotEqual"), D3D12_COMPARISON_FUNC_NOT_EQUAL },
		{ toupper("Always"), D3D12_COMPARISON_FUNC_ALWAYS },
	};
	D3D12_COMPARISON_FUNC func = getEnum(zTestMap, op);
	assert(func != static_cast<D3D12_COMPARISON_FUNC>(-1));
	depthStencilDesc.DepthFunc = func;
}

void ShaderDesc::setZWrite(bool enabled) {
	depthStencilDesc.DepthWriteMask = enabled ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
}

void ShaderDesc::setPrimitiveType(const std::string &primitiveType) {
	static const std::pair<std::string, D3D12_PRIMITIVE_TOPOLOGY_TYPE> primitiveTypeMap[] = {
		{ toupper("Point"), D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT },
		{ toupper("Line"), D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE },
		{ toupper("Triangle"), D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE },
		{ toupper("Patch"), D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH },
	};
	D3D12_PRIMITIVE_TOPOLOGY_TYPE type = getEnum(primitiveTypeMap, primitiveType);
	assert(type != static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(-1));
	this->primitiveType = type;
}

bool ShaderDesc::checkValid() const {
	if (entryPoints.empty())
		return false;
	return true;
}

auto ShaderDesc::getShaderFileName() const -> const std::string & {
	return shaderFileName;
}

auto ShaderDesc::getEntryPoints() const -> const std::vector<ShaderEntryPoint> &{
	return entryPoints;
}

auto ShaderDesc::getShaderFeatures() const -> const std::vector<std::vector<std::string>> &{
	return shaderFeatures;
}

auto ShaderDesc::getBlendDesc() const -> const D3D12_BLEND_DESC &{
	return blendDesc;
}

auto ShaderDesc::getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC &{
	return rasterizerDesc;
}

auto ShaderDesc::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &{
	return depthStencilDesc;
}

auto ShaderDesc::getPrimitiveType() const -> D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	return primitiveType;
}

bool ShaderDesc::hasShader(ShaderType shaderType) const {
	for (const ShaderEntryPoint &entry : entryPoints) {
		if (entry.shaderType == shaderType)
			return true;
	}
	return false;
}

}
