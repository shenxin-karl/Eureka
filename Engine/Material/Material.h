#pragma once
#include <RenderGraph/Material/Material.h>

namespace Eureka {

class ALMaterial;
struct MaterialDesc {
	std::string materialName;
	const ALMaterial *pAlMaterial;
	std::shared_ptr<rgph::RenderGraph> pRenderGraph;
};

class Material : public rgph::Material {
public:
	Material(const MaterialDesc &desc);
};

}