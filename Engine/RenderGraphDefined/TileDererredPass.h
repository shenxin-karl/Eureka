#pragma once
#include "RenderGraph/Pass/ExecutablePass.h"
#include "Dx12lib/Texture/Texture.h"

namespace Eureka {

struct CbTile {
	Math::float4x4	gView;
	Math::float4x4	gProj;
	float gNear;
	float gFar;
	float gFarMultiplyNear;			// far * near
	float gFarMinusNear;			// far - near
};

class TileDeferredPass : public rgph::ExecutablePass {
public:
	TileDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx);
	void preExecute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;

	rgph::PassResourcePtr<dx12lib::Texture> pDepthMap;
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pPointLightLists;
	rgph::PassResourcePtr<dx12lib::IUAStructuredBuffer> pTileLightLists;
private:
	FRConstantBufferPtr<CbTile> _pCbTile;
	std::shared_ptr<dx12lib::ComputePSO> _pPipeline;
};

}
