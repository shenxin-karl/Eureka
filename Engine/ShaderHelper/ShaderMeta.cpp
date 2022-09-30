#include "ShaderMeta.h"
#include <sol/sol.hpp>
#include <locale>
#include <unordered_set>
#include "ShaderHelper/SubPassDesc.h"

namespace Eureka {

ShaderMeta::ShaderMeta(const std::string &luaScriptName) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::debug, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::io);

	lua.script(R"(
		function __handleCallError( error_msg )
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
		sol::constructors<SubPassDesc(const std::string &)>(),
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
		initShaderMeta.set_error_handler(lua["__handleCallError"]);
		auto ret = initShaderMeta(this);
		assert(ret.valid());
	} else {
		std::cerr << "invalid shader meta script: " << luaScriptName << std::endl;
		assert(false);
	}
}

void ShaderMeta::setShaderFileName(const std::string &fileName) {
	_fileName = fileName;
}

void ShaderMeta::addSubPassDesc(const SubPassDesc *pDesc) {
	assert(pDesc != nullptr);
	if (!pDesc->checkValid())
		assert(false);
	_subPassDescs.push_back(std::make_shared<SubPassDesc>(*pDesc));
}

}
