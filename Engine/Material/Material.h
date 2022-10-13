#pragma once
#include <RenderGraph/Material/Material.h>
#include <DirectXColors.h>
#include <Dx12lib/Buffer/FRConstantBuffer.hpp>

namespace Eureka {

class ALMaterial;
struct MaterialDesc {
	std::string materialName;
	const ALMaterial *pAlMaterial;
	dx12lib::IGraphicsContext &graphicsCtx;
	std::shared_ptr<rgph::RenderGraph> pRenderGraph;
};

struct CbMaterial {
	Math::float4 diffuseAlbedo	= Math::float4(DX::Colors::White);
	float roughness				= 1.0f;
	float metallic				= 1.0f;
	float ambientOcclusion		= 1.f;
	float padding0				= 0.f;
};

class Material final : public rgph::Material {
public:
	Material(const MaterialDesc &desc);
	FRConstantBufferPtr<CbMaterial> pCbMaterial;
private:
	static rgph::SubPass *getGBufferSubPass(const MaterialDesc &desc, std::shared_ptr<dx12lib::GraphicsPSO> pso);
};

}