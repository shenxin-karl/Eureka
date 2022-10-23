#pragma once
#include <Math/MathStd.hpp>
#include "PassDefinition/TileBased.h"
#include "ShaderHelper/CBufferStruct.h"

namespace Eureka {

class ClusterDeferredPass : public TileBased {
public:
	ClusterDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx, 
		size_t maxPointLight = 0, 
		size_t maxSpotLight = 0
	);
	void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
public:
	constexpr static float kDepthSlicing16[17] = {
		0.01f, 20.0f, 29.7f, 44.0f, 65.3f,
		96.9f, 143.7f, 213.2f, 316.2f, 469.1f,
		695.9f, 1032.4f, 1531.5f, 2272.0f, 3370.5f,
		5000.0f, 50000.0f
	};
	constexpr static size_t kTileDimension = 64;

	static size_t calcClusterSize(float zFar) noexcept;

	static size_t calcTileSize(size_t width, size_t height, float zFar);

	struct ClusterFrustum {
		Math::float4 frustumPlanes[6];
	};

	CBUFFER CbParam {
		Math::float4x4 gProj;
		uint32_t	   gRenderTargetWidth;
		uint32_t	   gRenderTargetHeight;
		uint32_t	   gNumCluster;
		float		   padding0;
	};
private:
	void updateClusterFrustums(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view);
private:
	size_t _width = 0;
	size_t _height = 0;
	Math::float4x4 _matProj;
	std::shared_ptr<dx12lib::ComputePSO>  _pPipeline;
	dx12lib::FRConstantBufferPtr<CbParam> _pCbParam;
	std::shared_ptr<dx12lib::ComputePSO>  _pCalcClusterFrustumPipeline;
	std::shared_ptr<dx12lib::IUAStructuredBuffer> _pClusterFrustums;
};

}
