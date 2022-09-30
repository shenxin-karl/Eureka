#pragma once
#include <memory>
#include <Dx12lib/dx12libStd.h>
#include "ShaderHelper/KeywordMask.h"

namespace Eureka {

class ShaderMeta;
class SubPass;

class Shader {
public:
	Shader(const ShaderMeta &shaderMeta);
	~Shader();
	auto getShaderContent() const -> const char *;
	auto getSubPass() const -> const SubPass *;
private:
	std::vector<SubPass> _subPasses;
	std::unique_ptr<char[]>	_pShaderContent;
};

}
