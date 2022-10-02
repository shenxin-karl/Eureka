#include <filesystem>
#include <iostream>
#include <sol/sol.hpp>
#include "Shader.h"
#include "ShaderDesc.h"
#include "StringInclude.h"
#include "ShaderVariant.h"

namespace Eureka {

Shader::Shader(std::weak_ptr<dx12lib::Device> pDevice, std::string &&shaderMetaFile) 
: _pDevice(std::move(pDevice)), _shaderMataFile(std::move(shaderMetaFile)) 
{
	sol::state lua;
	lua.open_libraries(sol::lib::base, 
		sol::lib::debug, 
		sol::lib::string, 
		sol::lib::math, 
		sol::lib::table, 
		sol::lib::io
	);

	lua.script(R"(
		function __handleCallError( error_msg )
			print(debug.traceback(error_msg));
		end
	)");

	void (ShaderDesc:: * pSetBlendColor0)(const std::string &, const std::string &) = &ShaderDesc::setBlendColor;
	void (ShaderDesc:: * pSetBlendColor1)(const std::string &, const std::string &, size_t) = &ShaderDesc::setBlendColor;
	void (ShaderDesc:: * pSetBlendAlpha0)(const std::string &, const std::string &) = &ShaderDesc::setBlendAlpha;
	void (ShaderDesc:: * pSetBlendAlpha1)(const std::string &, const std::string &, size_t) = &ShaderDesc::setBlendAlpha;
	void (ShaderDesc:: * pSetBlendOp0)(const std::string &) = &ShaderDesc::setBlendOp;
	void (ShaderDesc:: * pSetBlendOp1)(const std::string &) = &ShaderDesc::setBlendOp;
	void (ShaderDesc:: * pSetColorMask0)(const std::string &) = &ShaderDesc::setColorMask;
	void (ShaderDesc:: * pSetColorMask1)(const std::string &) = &ShaderDesc::setColorMask;
	lua.new_usertype<ShaderDesc>("ShaderDesc",
		"setShaderFileName", &ShaderDesc::setShaderFileName,
		"addShaderFeature", &ShaderDesc::addShaderFeature,
		"setVertexShader", &ShaderDesc::setVertexShader,
		"setHullShader", &ShaderDesc::setHullShader,
		"setDomainShader", &ShaderDesc::setDomainShader,
		"setGeometryShader", &ShaderDesc::setGeometryShader,
		"setPixelShader", &ShaderDesc::setPixelShader,
		"setAlphaToMask", &ShaderDesc::setAlphaToMask,
		"setBlendColor", sol::overload(pSetBlendColor0, pSetBlendColor1),
		"setBlendAlpha", sol::overload(pSetBlendAlpha0, pSetBlendAlpha1),
		"setBlendOp", sol::overload(pSetBlendOp0, pSetBlendOp1),
		"setColorMask", sol::overload(pSetColorMask0, pSetColorMask1),
		"setConservative", &ShaderDesc::setConservative,
		"setCull", &ShaderDesc::setCull,
		"setOffset", &ShaderDesc::setOffset,
		"setZClip", &ShaderDesc::setZClip,
		"setZTest", &ShaderDesc::setZTest,
		"setZWrite", &ShaderDesc::setZWrite,
		"setPrimitiveType", &ShaderDesc::setPrimitiveType
	);

	sol::protected_function_result result = lua.script_file(shaderMetaFile, sol::script_pass_on_error);
	if (!result.valid()) {
		sol::error err = result;
		sol::call_status status = result.status();
		std::cout << "Something went horribly wrong: "
			<< sol::to_string(status) << " error"
			<< "\n\t" << err.what() << std::endl;
		sol_c_assert(!result.valid());	
	}

	sol::protected_function initShaderDesc = lua["InitShaderDesc"];
	if (initShaderDesc) {
		initShaderDesc.set_error_handler(lua["__handleCallError"]);
		_pShaderDesc = std::make_unique<ShaderDesc>();
		auto ret = initShaderDesc(_pShaderDesc.get());
		assert(ret.valid());
	} else {
		std::cerr << "invalid shader meta script: " << shaderMetaFile << std::endl;
		assert(false);
	}

	char error[256];
	std::filesystem::path path(_pShaderDesc->getShaderFileName());
	std::string dir = path.remove_filename().string();
	_pShaderContent = std::unique_ptr<char[]>(stb_include_file(
		const_cast<char *>(_pShaderDesc->getShaderFileName().c_str()),
		nullptr,
		dir.data(),
		error
	));
	_shaderContentLength = std::strlen(_pShaderContent.get());
}

Shader::~Shader() {
}

void Shader::setShaderName(std::string &&shaderName) {
	_shaderName = std::move(shaderName);
}

auto Shader::getShaderContent() const -> std::string_view {
	return std::string_view(_pShaderContent.get(), _shaderContentLength);
}

auto Shader::getShaderVariant(const KeywordBitMask &bitMask) const -> const ShaderVariant * {
	auto iter = _shaderVariants.find(bitMask);
	if (iter != _shaderVariants.end())
		return iter->second.get();
	
	auto pShaderVariant = std::make_unique<ShaderVariant>(this, bitMask);
	auto *pResult = pShaderVariant.get();
	_shaderVariants[bitMask] = std::move(pShaderVariant);
	return pResult;
}

auto Shader::getShaderDesc() const -> const ShaderDesc * {
	return _pShaderDesc.get();
}

auto Shader::getDevice() const -> std::weak_ptr<dx12lib::Device> {
	return _pDevice;
}

auto Shader::getShaderName() const -> const std::string & {
	return _shaderName;
}



}
