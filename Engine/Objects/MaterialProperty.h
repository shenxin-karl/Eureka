#pragma once
#include <Dx12lib/Buffer/BufferStd.h>
#include "Foundation/NonCopyable.h"

namespace Math {

class float4x4;
class float4;
class float3;
class float2;

}

namespace Eureka {

class Material;
class MaterialProperty : private NonCopyable {
public:
	explicit MaterialProperty(Material *pMaterial);
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
private:
	struct TextureToBind {
		std::string name;
		std::shared_ptr<dx12lib::Texture> pTexture;
	};
private:
	Material *						_pMaterial;
	dx12lib::FRRawConstantBufferPtr _pConstantBuffer;
	std::vector<TextureToBind>      _textures;
};

}
