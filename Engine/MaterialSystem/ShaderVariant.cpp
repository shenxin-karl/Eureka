#include <iostream>
#include "Shader.h"
#include "ShaderHelper.h"
#include "ShaderVariant.h"
#include "ShaderDesc.h"
#include <Dx12lib/Pipeline/RootSignature.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <Dx12lib/Device/Device.h>
#include <RenderGraph/job/ShaderLayout.h>

namespace Eureka {

ShaderVariant::ShaderVariant(const Shader *pShader, const KeywordBitMask &bitMask) : _pShader(pShader) {

	size_t index = 0;
	std::vector<D3D_SHADER_MACRO> macros;
	const auto &pShaderDesc = pShader->getShaderDesc();
	for (const auto &features : pShaderDesc->getShaderFeatures()) {
		for (const auto &key : features) {
			if (bitMask.test(index)) {
				macros.push_back(D3D_SHADER_MACRO{
					.Name = key.c_str(),
					.Definition = nullptr,
				});
			}
		}
	}
	macros.push_back(D3D_SHADER_MACRO{ nullptr, nullptr });

	auto shaderContent = pShader->getShaderContent();
	for (const auto &entry : pShaderDesc->getEntryPoints()) {
		switch (entry.shaderType) {
		case ShaderType::VS:
			_pVertexShader = ShaderHelper::compile(
				shaderContent.data(),
				shaderContent.length(),
				macros.data(),
				entry.entryPoint.c_str(),
				"vs_5_1"
			);
			break;
		case ShaderType::HS:
			_pHullShader = ShaderHelper::compile(
				shaderContent.data(),
				shaderContent.length(),
				macros.data(),
				entry.entryPoint.c_str(),
				"hs_5_1"
			);
			break;
		case ShaderType::DS:
			_pDomainShader = ShaderHelper::compile(
				shaderContent.data(),
				shaderContent.length(),
				macros.data(),
				entry.entryPoint.c_str(),
				"ds_5_1"
			);
			break;
		case ShaderType::GS:
			_pGeometryShader = ShaderHelper::compile(
				shaderContent.data(),
				shaderContent.length(),
				macros.data(),
				entry.entryPoint.c_str(),
				"gs_5_1"
			);
			break;
		case ShaderType::PS:
			_pPixelShader = ShaderHelper::compile(
				shaderContent.data(),
				shaderContent.length(),
				macros.data(),
				entry.entryPoint.c_str(),
				"ps_5_1"
			);
			break;
		default:
			assert(false);
			break;
		}
	}

	generateShaderReflectionInfo(pShader->getDevice().lock());
}

auto ShaderVariant::getPSO(const RenderTargetFormats &mrtFormats) const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	auto iter = _psoMap.find(mrtFormats);
	if (iter != _psoMap.end())
		return iter->second;

	auto pGraphicsPSO = _pShader->getDevice().lock()->createGraphicsPSO(_pShader->getShaderName());
	pGraphicsPSO->setVertexShader(_pVertexShader);
	pGraphicsPSO->setHullShader(_pHullShader);
	pGraphicsPSO->setDomainShader(_pDomainShader);
	pGraphicsPSO->setGeometryShader(_pGeometryShader);
	pGraphicsPSO->setPixelShader(_pPixelShader);
	pGraphicsPSO->setRootSignature(_pRootSignature);

}

void ShaderVariant::generateShaderReflectionInfo(std::shared_ptr<dx12lib::Device> pDevice) {
	WRL::ComPtr<ID3D12ShaderReflection> shaderRefs[5];
	WRL::ComPtr<ID3DBlob> shaders[5] = {
		_pVertexShader,
		_pHullShader,
		_pDomainShader,
		_pGeometryShader,
		_pPixelShader
	};


	auto handleVertexInput = [&](WRL::ComPtr<ID3D12ShaderReflection> pShaderRef, const D3D12_SHADER_DESC &desc) {
		D3D12_SIGNATURE_PARAMETER_DESC signDesc;
		for (size_t i = 0; i < desc.InputParameters; ++i) {
			pShaderRef->GetInputParameterDesc(i, &signDesc);
			std::string semanticName = std::format("{}{}", signDesc.SemanticName, signDesc.SemanticIndex);
			rgph::ShaderLayoutIndex index = rgph::ShaderLayoutIndex::stringToEnum(semanticName);
			assert(index != rgph::ShaderLayoutIndex(rgph::ShaderLayoutIndex::Nothing));
			_shaderLayoutMask |= index;
		}
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

		// Vertex Shader Input
		if (i == 0)
			handleVertexInput(shaderRefs[i], desc);

		for (UINT j = 0; j < desc.BoundResources; j++) {
			D3D12_SHADER_INPUT_BIND_DESC  resourceDesc;
			shaderRefs[i]->GetResourceBindingDesc(j, &resourceDesc);
			auto shaderVarName = resourceDesc.Name;
			// todo: 跳过 Common.hlsl 的静态采样器
			if (resourceDesc.Type == D3D_SIT_SAMPLER && resourceDesc.Space == 0)
				continue;
			boundResources[shaderVarName] = resourceDesc;
		}
	}

	std::vector<ShaderInput> cbvs;
	std::vector<ShaderInput> srvs;
	std::vector<ShaderInput> uavs;
	dx12lib::ShaderRegister shaderRegister;
	for (auto &&[name, desc] : boundResources) {
		switch (desc.Type) {
		case D3D_SIT_CBUFFER:
		{
			shaderRegister.slot = (dx12lib::RegisterSlot::Slot)((int)dx12lib::RegisterSlot::CBV0 + desc.BindPoint);
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			cbvs.emplace_back(shaderInput);
			_shaderInputViews.push_back(shaderInput);
			break;
		}
		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		{
			shaderRegister.slot = (dx12lib::RegisterSlot::Slot)((int)dx12lib::RegisterSlot::SRV0 + desc.BindPoint);
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			srvs.emplace_back(shaderInput);
			_shaderInputViews.push_back(shaderInput);
			break;
		}
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_RWTYPED:
		{
			shaderRegister.slot = (dx12lib::RegisterSlot::Slot)((int)dx12lib::RegisterSlot::UAV0 + desc.BindPoint);
			shaderRegister.space = (dx12lib::RegisterSpace)((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			ShaderInput shaderInput = { desc.Name, desc.BindCount, shaderRegister };
			uavs.emplace_back(shaderInput);
			_shaderInputViews.push_back(shaderInput);
			break;
		}
		case D3D_SIT_SAMPLER:
		default:
			assert(false);
			break;
		}
	}

	std::vector<ShaderInput> preObjectViews;
	std::vector<ShaderInput> prePassViews;
	auto sortViews = [&](std::vector<ShaderInput> &views) {
		std::sort(views.begin(), views.end(), [](const ShaderInput &lhs, const ShaderInput &rhs) {
			if (lhs.shaderRegister.space < lhs.shaderRegister.space)
				return true;
			return lhs.shaderRegister.slot.getRegisterId() < rhs.shaderRegister.slot.getRegisterId();
		});

		for (const auto &input : views) {
			if ((int)input.shaderRegister.space == kPrePassSpaceIndex)
				prePassViews.push_back(input);
			else
				preObjectViews.push_back(input);
		}
	};
	sortViews(cbvs);
	sortViews(srvs);
	sortViews(uavs);

	_pRootSignature = pDevice->createRootSignature(2, kStaticSamplerCount);
	_pRootSignature->initStaticSampler(0, getStaticSamplers());
	_pRootSignature->at(0).initAsDescriptorTable(preObjectViews.size());
	for (size_t i = 0; i < preObjectViews.size(); ++i) {
		_pRootSignature->at(0).setTableRange(i, 
			preObjectViews[i].shaderRegister,
			preObjectViews[i].bindCount
		);
	}

	_pRootSignature->at(1).initAsDescriptorTable(prePassViews.size());
	for (size_t i = 0; i < prePassViews.size(); ++i) {
		_pRootSignature->at(1).setTableRange(i,
			prePassViews[i].shaderRegister,
			prePassViews[i].bindCount
		);
	}
	_pRootSignature->finalize();
}

}