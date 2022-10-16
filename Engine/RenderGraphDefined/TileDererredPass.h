#pragma once
#include "RenderGraph/Pass/ExecutablePass.h"

namespace Eureka {

class TileDeferredPass : public rgph::ExecutablePass {
public:
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pPointLightLists;
	
};

}
