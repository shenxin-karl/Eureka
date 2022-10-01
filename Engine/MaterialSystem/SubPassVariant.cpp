#include "SubPassVariant.h"
#include "SubPassDesc.h"
#include "SubPass.h"
#include "Shader.h"
#include "ShaderHelper.h"

Eureka::SubPassVariant::SubPassVariant(const SubPass *pSubPass, const KeywordBitMask &bitMask) : _pSubPass(pSubPass) {
	const auto &pSubPassDesc = pSubPass->getSubPassDesc();
	assert(pSubPassDesc != nullptr);

	std::vector<D3D_SHADER_MACRO> macros;
	size_t index = 0;
	for (const auto &features : pSubPassDesc->getShaderFeatures()) {
		for (const auto &key : features) {
			if (bitMask.test(index)) {
				macros.push_back(D3D_SHADER_MACRO {
					.Name = key.c_str(),
					.Definition = nullptr,
				});
			}
		}
	}
	macros.push_back(D3D_SHADER_MACRO{ nullptr, nullptr });

	auto shaderContent = pSubPass->getShader()->getShaderContent();
	for (const auto &entry : pSubPassDesc->getEntryPoints()) {
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
	
	generateShaderReflectionInfo();
}

void Eureka::SubPassVariant::generateShaderReflectionInfo() {
	WRL::ComPtr<ID3D12ShaderReflection> shaderRefs[5];
	WRL::ComPtr<ID3DBlob> shaders[5] = {
		_pVertexShader,
		_pHullShader,
		_pDomainShader,
		_pGeometryShader,
		_pPixelShader
	};

	struct CBufferDesc {
		ID3D12ShaderReflectionConstantBuffer *pCBufferRefPtr;
		D3D12_SHADER_BUFFER_DESC cbufferDesc;
	};

	std::unordered_map<std::string, D3D12_SHADER_INPUT_BIND_DESC> boundResources;
	std::unordered_map<std::string, CBufferDesc> cbuffers;

	for (size_t i = 0; i < 5; ++i) {
		if (!shaders[i])
			continue;

		ThrowIfFailed(D3DReflect(shaders[i]->GetBufferPointer(),
			shaders[i]->GetBufferSize(),
			IID_PPV_ARGS(&shaderRefs[i])
		));

		if (shaderRefs[i])
			continue;

		D3D12_SHADER_DESC desc;
		shaderRefs[i]->GetDesc(&desc);
		for (UINT i = 0; i < desc.ConstantBuffers; ++i) {
			ID3D12ShaderReflectionConstantBuffer *buffer = shaderRefs[i]->GetConstantBufferByIndex(i);
			D3D12_SHADER_BUFFER_DESC bufferDesc;
			buffer->GetDesc(&bufferDesc);
			CBufferDesc &cbufferDesc = cbuffers[bufferDesc.Name];
			cbufferDesc.cbufferDesc = bufferDesc;
			cbufferDesc.pCBufferRefPtr = buffer;
		}

		for (UINT i = 0; i < desc.BoundResources; i++) {
			D3D12_SHADER_INPUT_BIND_DESC  resourceDesc;
			shaderRefs[i]->GetResourceBindingDesc(i, &resourceDesc);
			auto shaderVarName = resourceDesc.Name;
			boundResources[shaderVarName] = resourceDesc;
		}
	}

	auto handleCBuffer = [&](const std::string &name, dx12lib::ShaderRegister sr) {
		
	};

	auto handleResources = [&](const D3D12_SHADER_INPUT_BIND_DESC &desc) {

	};

	for (auto &&[name, desc] : boundResources) {
		if (desc.Type == D3D_SIT_CBUFFER) {
			dx12lib::ShaderRegister sr;
			sr.slot = dx12lib::RegisterSlot::CBV0;
			sr.space = dx12lib::RegisterSpace((int)dx12lib::RegisterSpace::Space0 + desc.Space);
			sr += desc.BindPoint;
			handleCBuffer(name, sr);
		}
		handleResources(desc);
	}
}
