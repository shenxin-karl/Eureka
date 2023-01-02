#pragma once
#include <Dx12lib/Resource/ResourceView.hpp>
#include <Math/MathStd.hpp>

namespace dx12lib {

class ComputePSO;
struct alignas(16) GenerateMipsCB {
	uint32_t          SrcMipLevel;   // Texture level of source mip
	uint32_t          NumMipLevels;  // Number of OutMips to write: [1-4]
	uint32_t          SrcDimension;  // Width and height of the source texture are even or odd.
	uint32_t          IsSRGB;        // Must apply gamma correction to sRGB textures.
	Math::float2	  TexelSize;     // 1.0 / OutMip1.Dimensions
};

class GenerateMipsPSO {
public:
	GenerateMipsPSO(std::weak_ptr<Device> pDevice);
	auto getPipelineState() const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getDefaultUVA(size_t i) const ->D3D12_CPU_DESCRIPTOR_HANDLE;
private:
	DescriptorAllocation _defaultUAV;
	std::shared_ptr<IShader> _pComputeShader;
	std::shared_ptr<dx12lib::ComputePSO> _pPipelineState;
};

}
