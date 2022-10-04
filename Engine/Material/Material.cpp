#include "Material.h"
#include "HlslShader/ShaderManager.h"

namespace Eureka {

Material::Material(const MaterialDesc &desc) : rgph::Material(desc.materialName) {
	auto *pALMaterial = desc.pAlMaterial;
	auto pDeferredPBRShader = ShaderManager::instance()->getGraphicsShader("DeferredPBR");

	
}

}