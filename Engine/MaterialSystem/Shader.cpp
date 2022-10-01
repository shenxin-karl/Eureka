#include <filesystem>
#include <iostream>
#include "Shader.h"
#include "StringInclude.h"
#include "ShaderMeta.h"
#include "SubPass.h"

namespace Eureka {

Shader::Shader(const ShaderMeta &shaderMeta) {
	char error[256];
	std::filesystem::path path(shaderMeta.getFileName());
	std::string dir = path.remove_filename().string();
	_pShaderContent = std::unique_ptr<char[]>(stb_include_file(
		const_cast<char *>(shaderMeta.getFileName().c_str()), 
		nullptr, 
		dir.data(), 
		error
	));

	if (_pShaderContent == nullptr) {
		std::cerr << error << std::endl;
		assert(false);
	}
	_shaderContentLength = strlen(_pShaderContent.get());
	for (auto &pSubPassDesc : shaderMeta.getSubPassDescs())
		_subPasses.push_back(std::make_unique<SubPass>(pSubPassDesc));
}

Shader::~Shader() {
}

auto Shader::getShaderContent() const -> std::string_view {
	return std::string_view(_pShaderContent.get(), _shaderContentLength);
}

auto Shader::getSubPass(const std::string &subPassName) const -> const SubPass * {
	for (auto &pSubPass : _subPasses) {
		if (pSubPass->getSubPassName() == subPassName)
			return pSubPass.get();
	}
	return nullptr;
}

}
