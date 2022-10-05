#include <filesystem>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <RenderGraph/Job/ShaderLayout.h>
#include "ShaderHelper.h"
#include "ShaderInclude.h"

namespace Eureka {

WRL::ComPtr<ID3DBlob> ShaderHelper::compile(
	const std::wstring &fileName,
	const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint,
	const std::string &target)
{
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	auto path = std::filesystem::path(fileName).parent_path();
	std::unique_ptr<ShaderInclude> pShaderInclude = std::make_unique<ShaderInclude>(path.string(), EUREKA_HLSL_SHADER_PATH);

	using Microsoft::WRL::ComPtr;
	HRESULT hr = S_OK;
	ComPtr<ID3DBlob> byteCode;
	ComPtr<ID3DBlob> errors;
	hr = D3DCompileFromFile(
		fileName.c_str(),
		defines,
		pShaderInclude.get(),
		entryPoint.c_str(),
		target.c_str(),
		compilesFlags,
		0,
		&byteCode,
		&errors
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<char *>(errors->GetBufferPointer()));
		ThrowIfFailed(hr);
	}
	return byteCode;
}

WRL::ComPtr<ID3DBlob> ShaderHelper::compile(
	const char *fileContext,
	std::size_t sizeInByte,
	const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint,
	const std::string &target)
{
	UINT compilesFlags = 0;
#if defined(DEBUG) || defined(_DEBUG) 
	compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;
	WRL::ComPtr<ID3DBlob> byteCode;
	WRL::ComPtr<ID3DBlob> errors;
	hr = D3DCompile(fileContext,
		sizeInByte,
		nullptr,
		defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint.c_str(),
		target.c_str(),
		compilesFlags,
		0,
		&byteCode,
		&errors
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<char *>(errors->GetBufferPointer()));
		ThrowIfFailed(hr);
	}
	return byteCode;
}

void ShaderHelper::generateGraphicsRootSignature(std::shared_ptr<dx12lib::Device> pDevice, 
	std::shared_ptr<dx12lib::GraphicsPSO> pGraphicsPSO) 
{
	WRL::ComPtr<ID3D12ShaderReflection> shaderRefs[5];
	WRL::ComPtr<ID3DBlob> shaders[5] = {
		pGraphicsPSO->getVertexShader(),
		pGraphicsPSO->getHullShader(),
		pGraphicsPSO->getDomainShader(),
		pGraphicsPSO->getGeometryShader(),
		pGraphicsPSO->getPixelShader()
	};

	std::unordered_map<std::string, D3D12_SHADER_INPUT_BIND_DESC> boundResources;
	for (size_t i = 0; i < 5; ++i) {
		if (!shaders[i])
			continue;

		ThrowIfFailed(D3DReflect(shaders[i]->GetBufferPointer(),
			shaders[i]->GetBufferSize(),
			IID_PPV_ARGS(&shaderRefs[i])
		));

		if (!shaderRefs[i])
			continue;

		D3D12_SHADER_DESC desc;
		shaderRefs[i]->GetDesc(&desc);
		for (UINT j = 0; j < desc.BoundResources; j++) {
			D3D12_SHADER_INPUT_BIND_DESC  resourceDesc;
			shaderRefs[i]->GetResourceBindingDesc(j, &resourceDesc);
			auto shaderVarName = resourceDesc.Name;
			if (resourceDesc.Type == D3D_SIT_SAMPLER)
				continue;
			boundResources[shaderVarName] = resourceDesc;
		}
	}

	struct ShaderInput {
		std::string name;
		UINT bindCount;
		dx12lib::ShaderRegister shaderRegister;
	};

	struct SpaceViews {
		std::vector<ShaderInput> cbvs;
		std::vector<ShaderInput> srvs;
	};

	std::map<size_t, SpaceViews> spaceViews;


	dx12lib::ShaderRegister shaderRegister;
	for (auto &&[name, desc] : boundResources) {
		switch (desc.Type) {
		case D3D_SIT_CBUFFER:
		{
			shaderRegister.slot = (dx12lib::RegisterSlot::Slot)((int)dx12lib::RegisterSlot::CBV0 + desc.BindPoint);
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			spaceViews[desc.Space].cbvs.push_back(shaderInput);
			break;
		}
		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		{
			shaderRegister.slot = (dx12lib::RegisterSlot::Slot)((int)dx12lib::RegisterSlot::SRV0 + desc.BindPoint);
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			spaceViews[desc.Space].srvs.push_back(shaderInput);
			break;
		}
		case D3D_SIT_SAMPLER:
		default:
			assert(false);
			break;
		}
	}

	auto sortViews = [&](std::vector<ShaderInput> &views) {
		std::sort(views.begin(), views.end(), [](const ShaderInput &lhs, const ShaderInput &rhs) {
			if (lhs.shaderRegister.space < lhs.shaderRegister.space)
				return true;
			return lhs.shaderRegister.slot.getRegisterId() < rhs.shaderRegister.slot.getRegisterId();
		});
	};

	auto pRootSignature = pDevice->createRootSignature(spaceViews.size(), kStaticSamplerCount);
	pRootSignature->initStaticSampler(0, getStaticSamplers());
	
	size_t rootIndex = 0;
	for (auto &&[space, views] : spaceViews) {
		size_t rootParamOffset = 0;
		sortViews(views.cbvs);
		sortViews(views.srvs);
		pRootSignature->at(rootIndex).initAsDescriptorTable(views.cbvs.size() + views.srvs.size());
		
		size_t tableIndex = 0;
		for (size_t i = 0; i < views.cbvs.size(); ++i, ++tableIndex) {
			pRootSignature->at(rootIndex).setTableRange(tableIndex,
				views.cbvs[i].shaderRegister,
				views.cbvs[i].bindCount
			);
		}
		for (size_t i = 0; i < views.srvs.size(); ++i, ++tableIndex) {
			pRootSignature->at(rootIndex).setTableRange(tableIndex,
				views.srvs[i].shaderRegister,
				views.srvs[i].bindCount
			);
		}
		++rootIndex;
	}

	pRootSignature->finalize();
	pGraphicsPSO->setRootSignature(pRootSignature);
}

void ShaderHelper::generateVertexInput(std::shared_ptr<dx12lib::GraphicsPSO> pGraphicsPSO) {
	WRL::ComPtr<ID3D12ShaderReflection> pShaderRef;
	auto pVertexBuffer = pGraphicsPSO->getVertexShader();
	ThrowIfFailed(D3DReflect(pVertexBuffer->GetBufferPointer(),
		pVertexBuffer->GetBufferSize(),
		IID_PPV_ARGS(&pShaderRef)
	));

	assert(pShaderRef != nullptr);
	D3D12_SHADER_DESC desc;
	pShaderRef->GetDesc(&desc);
	
	D3D12_SIGNATURE_PARAMETER_DESC signDesc;
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
	for (UINT i = 0; i < desc.InputParameters; ++i) {
		pShaderRef->GetInputParameterDesc(i, &signDesc);
		std::string semantic = std::format("{}{}", signDesc.SemanticName, signDesc.SemanticIndex);
		rgph::ShaderLayoutIndex index = rgph::ShaderLayoutIndex::stringToEnum(semantic);
		assert(index != rgph::ShaderLayoutIndex::Nothing);
		auto inputDesc = rgph::ShaderLayoutIndex::getInputLayoutByEnum(index);
		inputLayout.push_back(inputDesc);
	}

	pGraphicsPSO->setInputLayout(inputLayout);
}

rgph::ShaderLayoutMask ShaderHelper::calcShaderLayoutMask(const std::vector<D3D12_INPUT_ELEMENT_DESC> &inputLayout) {
	rgph::ShaderLayoutMask mask;
	for (const auto &desc : inputLayout) {
		std::string semantic = std::format("{}{}", desc.SemanticName, desc.SemanticIndex);
		rgph::ShaderLayoutIndex index = rgph::ShaderLayoutIndex::stringToEnum(semantic);
		assert(index != rgph::ShaderLayoutIndex::Nothing);
		mask |= index;
	}
	return mask;
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getPointWrapStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_MIN_MAG_MIP_POINT,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getPointClampStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_MIN_MAG_MIP_POINT,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getLinearWrapStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getLinearClampStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getAnisotropicWrapStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_ANISOTROPIC,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getAnisotropicClampStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister,
		D3D12_FILTER_ANISOTROPIC,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getLinearShadowCompareStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister, // shaderRegister
		D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressW
		0.0f,                               // mipLODBias
		16,                                 // maxAnisotropy
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE
	);
}

CD3DX12_STATIC_SAMPLER_DESC ShaderHelper::getPointShadowCompareStaticSampler(UINT shaderRegister) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		shaderRegister, // shaderRegister
		D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressW
		0.0f,                               // mipLODBias
		16,                                 // maxAnisotropy
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE
	);
}

const std::array<CD3DX12_STATIC_SAMPLER_DESC, 8> &ShaderHelper::getStaticSamplers() {
	static std::array<CD3DX12_STATIC_SAMPLER_DESC, 8> samplers = {
		getPointWrapStaticSampler(0),
		getPointClampStaticSampler(1),
		getLinearWrapStaticSampler(2),
		getLinearClampStaticSampler(3),
		getAnisotropicWrapStaticSampler(4),
		getAnisotropicClampStaticSampler(5),
		getLinearShadowCompareStaticSampler(6),
		getPointShadowCompareStaticSampler(7)
	};
	return samplers;
}


}