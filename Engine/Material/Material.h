#pragma once
#include <RenderGraph/Material/Material.h>
#include <DirectXColors.h>

namespace Eureka {

class ALMaterial;
struct MaterialDesc {
	std::string materialName;
	const ALMaterial *pAlMaterial;
	std::shared_ptr<rgph::RenderGraph> pRenderGraph;
};

struct CbMaterial {
	Math::float4 diffuseAlbedo	= Math::float4(DX::Colors::White);
	float roughness				= 0.5f;
	float metallic				= 0.5f;
	float ambientOcclusion		= 0.f;
	float padding0				= 0.f;
};

class Material : public rgph::Material {
public:
	Material(const MaterialDesc &desc);
};

}