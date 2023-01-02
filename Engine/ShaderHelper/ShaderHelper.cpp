#include <filesystem>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <RenderGraph/Job/ShaderLayout.h>
#include "ShaderHelper.h"
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "Dx12lib/Pipeline/FXCShader.h"
#include "Foundation/Exception.h"

namespace Eureka {

std::shared_ptr<dx12lib::IShader> ShaderHelper::DXCCompile(const std::string &fileName, const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint, const std::string &target)
{
	auto shaderContentView = ShaderLoader::instance()->open(fileName);
	if (shaderContentView.empty())
		Exception::Throw("ShaderHelper::compile can't open the file {}", fileName);

	return compileImpl(
		ShaderType::DXC,
		shaderContentView.data(),
		shaderContentView.length(),
		fileName,
		defines,
		entryPoint,
		target
	);
}

std::shared_ptr<dx12lib::IShader> ShaderHelper::DXCCompile(const char *fileContent, std::size_t sizeInByte,
	const std::string &sourceName, const D3D_SHADER_MACRO *defines, const std::string &entryPoint,
	const std::string &target)
{
	return compileImpl(
		ShaderType::DXC,
		fileContent,
		sizeInByte,
		sourceName,
		defines,
		entryPoint,
		target
	);
}

std::shared_ptr<dx12lib::IShader> ShaderHelper::FXCCompile(const std::string &fileName, const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint, const std::string &target)
{
	auto shaderContentView = ShaderLoader::instance()->open(fileName);
	if (shaderContentView.empty())
		Exception::Throw("ShaderHelper::compile can't open the file {}", fileName);

	return compileImpl(
		ShaderType::FXC,
		shaderContentView.data(),
		shaderContentView.length(),
		fileName,
		defines,
		entryPoint,
		target
	);
}

std::shared_ptr<dx12lib::IShader> ShaderHelper::FCXCompile(const char *fileContent, std::size_t sizeInByte,
	const std::string &sourceName, const D3D_SHADER_MACRO *defines, const std::string &entryPoint,
	const std::string &target)
{
	return compileImpl(
		ShaderType::FXC,
		fileContent,
		sizeInByte,
		sourceName,
		defines,
		entryPoint,
		target
	);
}

void ShaderHelper::generateRootSignature(std::shared_ptr<dx12lib::Device> pDevice,
	std::vector<std::shared_ptr<dx12lib::IShader>> shaders,
    std::shared_ptr<dx12lib::PSO> pso) 
{
	std::vector<WRL::ComPtr<ID3D12ShaderReflection>> shaderRefs(shaders.size(), nullptr);
	std::unordered_map<std::string, D3D12_SHADER_INPUT_BIND_DESC> boundResources;
	for (size_t i = 0; i < shaders.size(); ++i) {
		if (!shaders[i])
			continue;

		shaderRefs[i] = shaders[i]->getReflect();
		if (shaderRefs[i] == nullptr)
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
		std::vector<ShaderInput> uavs;
	};

	std::map<size_t, SpaceViews> spaceViews;


	dx12lib::ShaderRegister shaderRegister;
	for (auto &&[name, desc] : boundResources) {
		switch (desc.Type) {
		case D3D_SIT_CBUFFER:
		{
			shaderRegister.slot = dx12lib::RegisterSlot::CBV0 + desc.BindPoint;
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			spaceViews[desc.Space].cbvs.push_back(shaderInput);
			break;
		}
		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		{
			shaderRegister.slot = dx12lib::RegisterSlot::SRV0 + desc.BindPoint;
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			spaceViews[desc.Space].srvs.push_back(shaderInput);
			break;
		}
		case D3D_SIT_UAV_RWTYPED:
		case D3D_SIT_UAV_RWSTRUCTURED:
		{
			shaderRegister.slot = dx12lib::RegisterSlot::UAV0 + desc.BindPoint;
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			spaceViews[desc.Space].uavs.push_back(shaderInput);
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
		sortViews(views.cbvs);
		sortViews(views.srvs);
		sortViews(views.uavs);

		pRootSignature->at(rootIndex).initAsDescriptorTable(views.cbvs.size() + views.srvs.size() + views.uavs.size());

		size_t tableIndex = 0;
		auto setupTableRange = [&](const std::vector<ShaderInput> &inputs) mutable {
			for (size_t i = 0; i < inputs.size(); ++i, ++tableIndex) {
				pRootSignature->at(rootIndex).setTableRange(tableIndex,
					inputs[i].shaderRegister,
					inputs[i].bindCount
				);
			}
		};

		setupTableRange(views.cbvs);
		setupTableRange(views.srvs);
		setupTableRange(views.uavs);
		++rootIndex;
	}

	pRootSignature->finalize();
	pso->setRootSignature(pRootSignature);
}

void ShaderHelper::generateRootSignature(std::shared_ptr<dx12lib::GraphicsPSO> pso) {
	std::vector<std::shared_ptr<dx12lib::IShader>> shaders {
		pso->getVertexShader(),
		pso->getHullShader(),
		pso->getHullShader(),
		pso->getGeometryShader(),
		pso->getPixelShader()
	};
	generateRootSignature(pso->getDevice().lock(), shaders, pso);
}

void ShaderHelper::generateRootSignature(std::shared_ptr<dx12lib::ComputePSO> pso) {
	std::vector<std::shared_ptr<dx12lib::IShader>> shaders{ pso->getComputeShader() };
	generateRootSignature(pso->getDevice().lock(), shaders, pso);
}

void ShaderHelper::generateVertexInput(std::shared_ptr<dx12lib::GraphicsPSO> pGraphicsPSO) {
	auto pVertexBuffer = pGraphicsPSO->getVertexShader();
	WRL::ComPtr<ID3D12ShaderReflection> pShaderRef = pVertexBuffer->getReflect();

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

std::shared_ptr<dx12lib::IShader> ShaderHelper::compileImpl(ShaderType shaderType, const char *fileContent,
	std::size_t sizeInByte, const std::string &sourceName, const D3D_SHADER_MACRO *defines,
	const std::string &entryPoint, const std::string &target)
{
	std::shared_ptr<dx12lib::IShader> pShader;
	if (shaderType == ShaderType::DXC)
		pShader = std::make_shared<dx12lib::DXCShader>();
	else
		pShader = std::make_shared<dx12lib::FXCShader>();

	auto path = std::filesystem::path(sourceName).lexically_normal();
	std::unique_ptr<ShaderInclude> pShaderInclude = std::make_unique<ShaderInclude>(path.string());
	dx12lib::CompileFormMemoryArgs compileArgs;
	compileArgs.fileName = sourceName;
	compileArgs.target = target;
	compileArgs.entryPoint = entryPoint;
	compileArgs.pInclude = pShaderInclude.get();
	compileArgs.pMacro = defines;
	compileArgs.pData = fileContent;
	compileArgs.sizeInByte = sizeInByte;
	pShader->compileFormMemory(compileArgs);
	return pShader;
}


}
