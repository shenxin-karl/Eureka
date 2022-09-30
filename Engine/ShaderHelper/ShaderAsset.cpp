#include "ShaderAsset.h"
#include <unordered_map>
#include <sol/sol.hpp>

namespace Eureka {

void SubPassDesc::addShaderFeature(const sol::as_table_t<std::vector<std::string>> &strings) {
	shaderFeatures.push_back(strings.value());
}

void SubPassDesc::setVertexShader(const std::string &entryPoint) {
	entryPoints.push_back({ "vs_5_1", entryPoint });
}

void SubPassDesc::setHullShader(const std::string &entryPoint) {
	entryPoints.push_back({ "hs_5_1", entryPoint });
}

void SubPassDesc::setDomainShader(const std::string &entryPoint) {
	entryPoints.push_back({ "ds_5_1", entryPoint });
}

void SubPassDesc::setGeometryShader(const std::string &entryPoint) {
	entryPoints.push_back({ "gs_5_1", entryPoint });
}

void SubPassDesc::setPixelShader(const std::string &entryPoint) {
	entryPoints.push_back({ "ps_5_1", entryPoint });
}

void SubPassDesc::setComputeShader(const std::string &entryPoint) {
	entryPoints.push_back({ "gs_5_1", entryPoint });
}

void SubPassDesc::setAlphaToMask(bool enabled) {
	blendDesc.AlphaToCoverageEnable = true;
}

void SubPassDesc::setBlend(const std::string &srcOp, const std::string &dstOp) {
	//static std::unordered_map<std::string, D3D12_BLEND> blendMap = {
	//	{ "One", D3D12_BLEND_ONE },
	//	{ "Zero", D3D12_BLEND_ZERO },
	//	{ "SrcColor", D3D12_BLEND_SRC_COLOR },
	//	{ "SrcAlpha", D3D12_BLEND_SRC_ALPHA },
	//};
}

void SubPassDesc::setBlendOp(const std::string &op) {
}

void SubPassDesc::setColorMask(const std::string &channel, int renderTarget) {
}

void SubPassDesc::setConservative(const std::string &enabled) {
}

void SubPassDesc::setCull(const std::string &state) {
}

void SubPassDesc::setOffset(float offset) {
}

void SubPassDesc::setZClip(bool enabled) {
}

void SubPassDesc::setZTest(const std::string &op) {
}

void SubPassDesc::setZWrite(bool enabled) {
}

void SubPassDesc::finalized() {

}

ShaderMeta::ShaderMeta(const std::string &luaScriptName) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::io);

	lua.script(R"(
		function got_problems( error_msg )
			return debug.traceback() .. error_msg
		end
	)");

	lua.new_usertype<ShaderMeta>("ShaderMeta",
		"setShaderFileName", &ShaderMeta::setShaderFileName
	);

	lua.new_usertype<SubPassDesc>("SubPassDesc",
		sol::constructors<SubPassDesc()>(),
		"addShaderFeature", &SubPassDesc::addShaderFeature,
		"setVertexShader", &SubPassDesc::setVertexShader,
		"setHullShader", &SubPassDesc::setHullShader,
		"setDomainShader", &SubPassDesc::setDomainShader,
		"setGeometryShader", &SubPassDesc::setGeometryShader,
		"setPixelShader", &SubPassDesc::setPixelShader,
		"setComputeShader", &SubPassDesc::setComputeShader,
		"setAlphaToMask", &SubPassDesc::setAlphaToMask
	);

	lua.script_file(luaScriptName);
	sol::protected_function initMaterialFunc = lua["initMaterial"];
	if (initMaterialFunc) {
		initMaterialFunc.set_error_handler(lua["got_problems"]);
		auto firstwoof = initMaterialFunc(this);
		if (!firstwoof.valid()) {
			// An error has occured
			sol::error err = firstwoof;
			std::string what = err.what();
			std::cout << what << std::endl;
		}
	}
}

void ShaderMeta::setShaderFileName(const std::string &fileName) {
	_fileName = fileName;
}

}
