#pragma once
#include <memory>
#include "EffectLab/ShaderKeyword.h"
#include "Math/MathStd.hpp"
#include "Dx12lib/dx12libStd.h"

namespace Eureka {

class Effect;
class MaterialProperty;
class MaterialKeyword;
class Material {
public:
	Material(std::shared_ptr<Effect> pEffect);
	void setBool(const std::string &name, bool val);
	void setInt(const std::string &name, int val);
	void setFloat(const std::string &name, float val);
	void setFloat2(const std::string &name, const Math::float2 &val);
	void setFloat3(const std::string &name, const Math::float3 &val);
	void setFloat4(const std::string &name, const Math::float4 &val);
	void setMatrix(const std::string &name, const Math::float4x4 &val);
	void setTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> pTexture);
	bool isKeywordEnable(const std::string &keyword) const;
	void disableKeyword(const std::string &keyword);
	void enableKeyword(const std::string &keyword);
private:
	std::shared_ptr<Effect>				_pEffect;
	std::unique_ptr<MaterialProperty>	_pMaterialProperty;
	std::unique_ptr<MaterialKeyword>	_pMaterialKeyword;
};

}
