#pragma once
#include "TileBased.h"
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

class TileDeferredPass : public TileBased {
public:
	TileDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx,
		size_t maxPointLights = 0,
		size_t maxSpotLights = 0);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
	rgph::PassResourcePtr<dx12lib::Texture> pDepthMap;
private:
	FRConstantBufferPtr<CbTile> _pCbTile;
	std::shared_ptr<dx12lib::ComputePSO> _pPipeline;
};

}
