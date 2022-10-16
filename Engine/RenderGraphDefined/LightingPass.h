#pragma once
#include <RenderGraph/Pass/ExecutablePass.h>
#include <Dx12lib/Texture/Texture.h>
#include "ShaderHelper/CBufferStruct.h"

namespace Eureka {

class LightingPass : public rgph::ExecutablePass {
public:
	LightingPass(const std::string &passName, std::shared_ptr<dx12lib::Device> pDevice);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
private:
	std::shared_ptr<dx12lib::ComputePSO> _pLightingPSO;
public:
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer0;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer1;
	rgph::PassResourcePtr<dx12lib::Texture> pGBuffer2;
	rgph::PassResourcePtr<dx12lib::Texture> pDepthMap;
	FRConstantBufferPtr<CbLighting>			pCbLighting;
	rgph::PassResourcePtr<dx12lib::Texture> pLightingBuffer;
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pPointLightLists;
	rgph::PassResourcePtr<dx12lib::IUAStructuredBuffer> pTileLightLists;
};

}
