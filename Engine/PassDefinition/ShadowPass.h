#pragma once
#include "RenderGraph/Pass/RenderQueuePass.h"

namespace Eureka {

class ShadowPass : public rgph::RenderQueuePass {
public:
	explicit ShadowPass(const std::string &passName);
};

}
