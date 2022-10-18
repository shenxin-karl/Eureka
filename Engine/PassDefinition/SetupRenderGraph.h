#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Technique/TechniqueType.hpp>

namespace Eureka {

constexpr rgph::TechniqueType kTechGBuffer = rgph::TechniqueType(1);
inline const std::string kGBufferPassName			= "GBuffer";
inline const std::string kTileDeferredPassName		= "TileDeferred";
inline const std::string kLightingPassName			= "Lighting";
inline const std::string kPostProcessingPassName	= "PostProcessing";

class EurekaApplication;
std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp, dx12lib::IDirectContext &directCtx);

}
