#pragma once
#include <RenderGraph/RenderGraphStd.h>

namespace Eureka {

class EurekaApplication;
std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp);

}