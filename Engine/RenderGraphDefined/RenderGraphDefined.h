#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>
#include "RenderGraphDefined/GBufferPass.h"

namespace Eureka {

constexpr rgph::TechniqueType kTechGBuffer = rgph::TechniqueType(1);
inline const std::string kGBufferPassName = "GBuffer";

class EurekaApplication;
std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp, dx12lib::IDirectContext &directCtx);

}
