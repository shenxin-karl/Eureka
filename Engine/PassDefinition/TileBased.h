#pragma once
#include <Dx12lib/Context/CommonContext.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <RenderGraph/Pass/PassResourcePtr.hpp>
#include <RenderGraph/Pass/ExecutablePass.h>

namespace rgph {
struct RenderView;
}

namespace Eureka {

class TileBased : public rgph::ExecutablePass {
protected:
	TileBased(const std::string &passName, dx12lib::IDirectContext &directCtx, size_t maxPointLights, size_t maxSpotLights);
	void execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
	void postExecute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) override;
	void onResize(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) override;
protected:
	bool _needUpdateTile = true;
	size_t _maxSpotLights;
	size_t _maxPointLights;
	Math::float4x4 _matView = Math::float4x4::identity();					
	std::shared_ptr<dx12lib::UAStructuredBuffer> _pSpotLightBoundingSpheres;
	std::shared_ptr<dx12lib::UAStructuredBuffer> _pPointLightBoundingSpheres;
	std::shared_ptr<dx12lib::ComputePSO> _pUpdateSpotLightBoundingSpherePipeline;
	std::shared_ptr<dx12lib::ComputePSO> _pUpdatePointLightBoundingSpherePipeline;
public:
	rgph::PassResourcePtr<dx12lib::ISRStructuredBuffer> pPointLightLists;
	rgph::PassResourcePtr<dx12lib::IUAStructuredBuffer> pTileLightLists;
};

}
