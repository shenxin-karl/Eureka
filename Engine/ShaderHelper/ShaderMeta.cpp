#include "ShaderMeta.h"
#include <sol/sol.hpp>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <unordered_set>

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

static bool checkShader(const std::vector<ShaderEntryPoint> &entryPoints, std::string_view version) {
	for (const auto &entry : entryPoints) {
		if (entry.version == version) {
			assert(false);
			return false;
		}
	}
	return true;
}

void SubPassDesc::addShaderFeature(const sol::as_table_t<std::vector<std::string>> &strings) {
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

void SubPassDesc::setVertexShader(const std::string &entryPoint) {
	checkShader(entryPoints, "vs_5_1");
	entryPoints.push_back({ "vs_5_1", entryPoint });
}

void SubPassDesc::setHullShader(const std::string &entryPoint) {
	checkShader(entryPoints, "hs_5_1");
	entryPoints.push_back({ "hs_5_1", entryPoint });
}

void SubPassDesc::setDomainShader(const std::string &entryPoint) {
	checkShader(entryPoints, "ds_5_1");
	entryPoints.push_back({ "ds_5_1", entryPoint });
}

void SubPassDesc::setGeometryShader(const std::string &entryPoint) {
	checkShader(entryPoints, "gs_5_1");
	entryPoints.push_back({ "gs_5_1", entryPoint });
}

void SubPassDesc::setPixelShader(const std::string &entryPoint) {
	checkShader(entryPoints, "ps_5_1");
	entryPoints.push_back({ "ps_5_1", entryPoint });
}

void SubPassDesc::setComputeShader(const std::string &entryPoint) {
	checkShader(entryPoints, "cs_5_1");
	entryPoints.push_back({ "cs_5_1", entryPoint });
}

void SubPassDesc::setAlphaToMask(bool enabled) {
	blendDesc.AlphaToCoverageEnable = enabled;
}

void SubPassDesc::setBlendColor(const std::string &srcOp, const std::string &dstOp) {
	setBlendColor(srcOp, dstOp, 0);
}

void SubPassDesc::setBlendColor(const std::string &srcOp, const std::string &dstOp, size_t renderTarget) {
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

void SubPassDesc::setBlendAlpha(const std::string &srcOp, const std::string &dstOp) {
	setBlendAlpha(srcOp, dstOp, 0);
}

void SubPassDesc::setBlendAlpha(const std::string &srcOp, const std::string &dstOp, size_t renderTarget) {
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

void SubPassDesc::setBlendOp(const std::string &op) {
	setBlendOp(op, 0);
}

void SubPassDesc::setBlendOp(const std::string &op, size_t renderTarget) {
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

void SubPassDesc::setColorMask(const std::string &channel) {
	setColorMask(channel, 0);
}

void SubPassDesc::setColorMask(const std::string &channel, int renderTarget) {
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

void SubPassDesc::setConservative(bool enabled) {
	rasterizerDesc.ConservativeRaster = enabled ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}

void SubPassDesc::setCull(const std::string &state) {
	static const std::pair<std::string, D3D12_CULL_MODE> cullMap[] = {
		{ toupper("Off"), D3D12_CULL_MODE_NONE },
		{ toupper("Front"), D3D12_CULL_MODE_FRONT },
		{ toupper("Back"), D3D12_CULL_MODE_BACK },
	};
	D3D12_CULL_MODE mode = getEnum(cullMap, state);
	assert(mode != static_cast<D3D12_CULL_MODE>(-1));
	rasterizerDesc.CullMode = mode;
}

void SubPassDesc::setOffset(float slopeScaledDepthBias, INT depthBias) {
	rasterizerDesc.SlopeScaledDepthBias = slopeScaledDepthBias;
	rasterizerDesc.DepthBias = depthBias;
}

void SubPassDesc::setZClip(bool enabled) {
	depthStencilDesc.DepthEnable = enabled;
}

void SubPassDesc::setZTest(const std::string &op) {
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

void SubPassDesc::setZWrite(bool enabled) {
	depthStencilDesc.DepthWriteMask = enabled ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
}

void SubPassDesc::setPrimitiveType(const std::string &primitiveType) {
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

bool SubPassDesc::checkValid() const {
	if (entryPoints.empty())
		return false;
	return true;
}

ShaderMeta::ShaderMeta(const std::string &luaScriptName) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::debug, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::io);

	lua.script(R"(
		function got_problems( error_msg )
			print(debug.traceback(error_msg));
		end
	)");

	lua.new_usertype<ShaderMeta>("ShaderMeta",
		"setShaderFileName", &ShaderMeta::setShaderFileName,
		"addSubPassDesc", &ShaderMeta::addSubPassDesc
	);

	void (SubPassDesc:: * pSetBlendColor0)(const std::string &, const std::string &) = &SubPassDesc::setBlendColor;
	void (SubPassDesc:: * pSetBlendColor1)(const std::string &, const std::string &, size_t) = &SubPassDesc::setBlendColor;
	void (SubPassDesc:: * pSetBlendAlpha0)(const std::string &, const std::string &) = &SubPassDesc::setBlendAlpha;
	void (SubPassDesc:: * pSetBlendAlpha1)(const std::string &, const std::string &, size_t) = &SubPassDesc::setBlendAlpha;
	void (SubPassDesc:: * pSetBlendOp0)(const std::string &) = &SubPassDesc::setBlendOp;
	void (SubPassDesc:: * pSetBlendOp1)(const std::string &) = &SubPassDesc::setBlendOp;
	void (SubPassDesc:: * pSetColorMask0)(const std::string &) = &SubPassDesc::setColorMask;
	void (SubPassDesc:: * pSetColorMask1)(const std::string &) = &SubPassDesc::setColorMask;
	lua.new_usertype<SubPassDesc>("SubPassDesc",
		sol::constructors<SubPassDesc()>(),
		"addShaderFeature", &SubPassDesc::addShaderFeature,
		"setVertexShader", &SubPassDesc::setVertexShader,
		"setHullShader", &SubPassDesc::setHullShader,
		"setDomainShader", &SubPassDesc::setDomainShader,
		"setGeometryShader", &SubPassDesc::setGeometryShader,
		"setPixelShader", &SubPassDesc::setPixelShader,
		"setComputeShader", &SubPassDesc::setComputeShader,
		"setAlphaToMask", &SubPassDesc::setAlphaToMask,
		"setBlendColor", sol::overload(pSetBlendColor0, pSetBlendColor1),
		"setBlendAlpha", sol::overload(pSetBlendAlpha0, pSetBlendAlpha1),
		"setBlendOp", sol::overload(pSetBlendOp0, pSetBlendOp1),
		"setColorMask", sol::overload(pSetColorMask0, pSetColorMask1),
		"setConservative", &SubPassDesc::setConservative,
		"setCull", &SubPassDesc::setCull,
		"setOffset", &SubPassDesc::setOffset,
		"setZClip", &SubPassDesc::setZClip,
		"setZTest", &SubPassDesc::setZTest,
		"setZWrite", &SubPassDesc::setZWrite,
		"setPrimitiveType", &SubPassDesc::setPrimitiveType
	);

	lua.script_file(luaScriptName);
	sol::protected_function initShaderMeta = lua["InitShaderMeta"];
	if (initShaderMeta) {
		initShaderMeta.set_error_handler(lua["got_problems"]);
		initShaderMeta(this);
	} else {
		std::cerr << "invalid shader meta script: " << luaScriptName << std::endl;
	}
}

void ShaderMeta::setShaderFileName(const std::string &fileName) {
	_fileName = fileName;
}

void ShaderMeta::addSubPassDesc(const SubPassDesc *pDesc) {
	assert(pDesc != nullptr);
	if (!pDesc->checkValid())
		assert(false);
	_subPassDescs.push_back(*pDesc);
}

}
