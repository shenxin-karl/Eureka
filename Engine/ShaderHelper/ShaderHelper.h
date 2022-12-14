#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <RenderGraph/Job/ShaderLayout.h>

namespace Eureka {

namespace WRL = Microsoft::WRL;

constexpr size_t kStaticSamplerCount = 8;

class ShaderHelper {
public:
	static void generateRootSignature(std::shared_ptr<dx12lib::Device> pDevice,
		std::vector<std::shared_ptr<dx12lib::IShader>> shaders,
		std::shared_ptr<dx12lib::PSO> pso
	);

	static void generateRootSignature(std::shared_ptr<dx12lib::GraphicsPSO> pso);
	static void generateRootSignature(std::shared_ptr<dx12lib::ComputePSO> pso);

	static void generateVertexInput(std::shared_ptr<dx12lib::GraphicsPSO> pGraphicsPSO);

	static rgph::ShaderLayoutMask calcShaderLayoutMask(const std::vector<D3D12_INPUT_ELEMENT_DESC> &inputLayout);

	static CD3DX12_STATIC_SAMPLER_DESC getPointWrapStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getPointClampStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getLinearWrapStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getLinearClampStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getAnisotropicWrapStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getAnisotropicClampStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getLinearShadowCompareStaticSampler(UINT shaderRegister);
	static CD3DX12_STATIC_SAMPLER_DESC getPointShadowCompareStaticSampler(UINT shaderRegister);
	static const std::array<CD3DX12_STATIC_SAMPLER_DESC, 8> &getStaticSamplers();
};

}