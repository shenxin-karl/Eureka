#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>

namespace Eureka {

constexpr rgph::TechniqueType kTechGBuffer = rgph::TechniqueType(1);
inline const std::string kGBufferPassName = "GBuffer";

class EurekaApplication;
std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp);

}