#pragma once
#include <RenderGraph/Material/Material.h>

namespace Eureka {

class ALMaterial;

class Material : public rgph::Material {
public:
	Material(const std::string &materialName, const ALMaterial *pALMaterial);
};

}