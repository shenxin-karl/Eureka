#pragma once
#include <memory>
#include <Dx12lib/dx12libStd.h>
#include "MaterialSystem/MaterialSystemStd.h"

namespace Eureka {

class ShaderMeta;
class SubPass;

class Shader {
public:
	Shader(const ShaderMeta &shaderMeta);
	~Shader();
	auto getShaderContent() const -> std::string_view;
	auto getSubPass(const std::string &subPassName) const -> const SubPass *;
private:
	size_t _shaderContentLength;
	std::unique_ptr<char[]>	_pShaderContent;
	std::vector<std::unique_ptr<SubPass>> _subPasses;
};

}
