#pragma once
#include <memory>
#include "Math/MathStd.hpp"
#include "Dx12lib/dx12libStd.h"
#include "Foundation/NonCopyable.h"

namespace Eureka {

class Effect;
class MaterialProperty;
class MaterialKeyword;
class Material : private NonCopyable {
	friend MaterialKeyword;
	friend MaterialProperty;
public:
	explicit Material(std::shared_ptr<Effect> pEffect);
	~Material();
	bool setBool(const std::string &name, bool val);
	bool setInt(const std::string &name, int val);
	bool setFloat(const std::string &name, float val);
	bool setFloat2(const std::string &name, const Math::float2 &val);
	bool setFloat3(const std::string &name, const Math::float3 &val);
	bool setFloat4(const std::string &name, const Math::float4 &val);
	bool setMatrix(const std::string &name, const Math::float4x4 &val);
	bool setTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> pTexture);
	bool getBool(const std::string &name, bool &outVal) const;
	bool getInt(const std::string &name, int &outVal) const;
	bool getFloat(const std::string &name, float &outVal) const;
	bool getFloat2(const std::string &name, Math::float2 &outVal) const;
	bool getFloat3(const std::string &name, Math::float3 &outVal) const;
	bool getFloat4(const std::string &name, Math::float4 &outVal) const;
	bool getMatrix(const std::string &name, Math::float4x4 &outMatrix) const;
	bool getTexture(const std::string &name, std::shared_ptr<dx12lib::Texture> &outTexture) const;
	bool isKeywordEnable(const std::string &keyword) const;
	bool disableKeyword(const std::string &keyword, bool flushPassVariant = true);
	bool enableKeyword(const std::string &keyword, bool flushPassVariant = true);
	void flushPassVariant();
	bool isRenderObjectDirty() const;
	void resetRenderObjectDirty();
	bool isPassEnable(size_t index) const;
	bool enablePass(size_t index);
	bool disablePass(size_t index);
private:
	std::shared_ptr<Effect>				_pEffect;
	std::unique_ptr<MaterialProperty>	_pMaterialProperty;
	std::unique_ptr<MaterialKeyword>	_pMaterialKeyword;
	bool								_renderObjectDirty = true;
	std::bitset<32>						_passMask;
};

}
