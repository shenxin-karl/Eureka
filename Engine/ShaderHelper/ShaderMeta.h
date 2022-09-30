#pragma once
#include <d3d12.h>
#include <string>
#include <vector>
#include <sol/types.hpp>

namespace Eureka {

struct SubPassDesc;
class ShaderMeta {
public:
	ShaderMeta(const std::string &luaScriptName);
	void setShaderFileName(const std::string &fileName);
	void addSubPassDesc(const SubPassDesc *pDesc);
private:
	std::string _fileName;
	std::vector<std::shared_ptr<SubPassDesc>> _subPassDescs;
};

}
