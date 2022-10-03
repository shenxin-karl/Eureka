#include "Material.h"

namespace Eureka {

Material::Material(MaterialDesc &&desc) : rgph::Material(std::move(desc.materialName)) {

}

}