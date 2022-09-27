#pragma once
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {



template<D3D12_INPUT_CLASSIFICATION SlotClass>
struct InputLayoutDescHelper : public D3D12_INPUT_ELEMENT_DESC {
public:
	template<typename Class, typename Member>
	InputLayoutDescHelper(Member (Class::*pMember), 
		std::string_view name, 
		DXGI_FORMAT format,
		UINT semanticIndex = 0, 
		UINT slot = 0) 
	{
		static_assert(std::is_member_pointer_v<decltype(pMember)>, "Pmember must be a member pointer");
		constexpr bool isInstance = SlotClass == D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
		this->SemanticName = name.data();
		this->SemanticIndex = semanticIndex;
		this->Format = format;
		this->InputSlot = slot;
		this->AlignedByteOffset = static_cast<UINT>(reinterpret_cast<std::size_t>((&(static_cast<Class*>(nullptr)->*pMember))));
		this->InputSlotClass = SlotClass;
		this->InstanceDataStepRate = isInstance ? 1 : 0;
	}
};

using VInputLayoutDescHelper = InputLayoutDescHelper<D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA>;
using IInputLayoutDescHelper = InputLayoutDescHelper<D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA>;

class PSO {
public:
	explicit PSO(std::weak_ptr<Device> pDevice, const std::string &name);
	PSO(const PSO &) = delete;
	PSO &operator=(const PSO &) = delete;
	void setRootSignature(std::shared_ptr<RootSignature> pRootSignature);
	std::shared_ptr<RootSignature> getRootSignature() const;
	WRL::ComPtr<ID3D12PipelineState> getPipelineStateObject() const;
	const std::string &getName() const;
	bool isDirty() const;
	virtual void finalize() = 0;
	virtual std::shared_ptr<PSO> clone(const std::string &name) = 0;
	virtual ~PSO() = default;
protected:
	bool                             _dirty = true;
	std::string                      _name;
	std::shared_ptr<RootSignature>   _pRootSignature;
	WRL::ComPtr<ID3D12PipelineState> _pPSO;
	std::weak_ptr<Device>            _pDevice;
};

class GraphicsPSO : public PSO {
public:
	void setBlendState(const D3D12_BLEND_DESC &blendDesc);
	void setRasterizerState(const D3D12_RASTERIZER_DESC &rasterizerDesc);
	void setDepthStencilState(const D3D12_DEPTH_STENCIL_DESC &depthStencilDesc);
	void setSampleMask(UINT sampleMask);
	void setPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType);
	void setDepthTargetFormat(DXGI_FORMAT DSVFormat);
	void setRenderTargetFormat(DXGI_FORMAT RTVFormat, DXGI_FORMAT DSVFormat);
	void setRenderTargetFormats(UINT numRTVFormat, const DXGI_FORMAT *pRTVFormat, DXGI_FORMAT DSVFormat);
	void setRenderTargetFormats(const std::vector<DXGI_FORMAT> &RTVFormats, DXGI_FORMAT DSVFormat);
	void setInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC> &inputLayout);
	void setInputLayout(const std::initializer_list<D3D12_INPUT_ELEMENT_DESC> &inputLayout);
	void setPrimitiveRestart(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBProps);
	
	void setVertexShader(const void *pBinary, size_t size);
	void setPixelShader(const void *pBinary, size_t size);
	void setGeometryShader(const void *pBinary, size_t size);
	void setHullShader(const void *pBinary, size_t size);
	void setDomainShader(const void *pBinary, size_t size);

	void setVertexShader(WRL::ComPtr<ID3DBlob> pByteCode);
	void setPixelShader(WRL::ComPtr<ID3DBlob> pByteCode);
	void setGeometryShader(WRL::ComPtr<ID3DBlob> pByteCode);
	void setHullShader(WRL::ComPtr<ID3DBlob> pByteCode);
	void setDomainShader(WRL::ComPtr<ID3DBlob> pByteCode);

	void setVertexShader(const D3D12_SHADER_BYTECODE &pByteCode);
	void setPixelShader(const D3D12_SHADER_BYTECODE &pByteCode);
	void setGeometryShader(const D3D12_SHADER_BYTECODE &pByteCode);
	void setHullShader(const D3D12_SHADER_BYTECODE &pByteCode);
	void setDomainShader(const D3D12_SHADER_BYTECODE &pByteCode);
	const D3D12_GRAPHICS_PIPELINE_STATE_DESC &getDesc() const;
	virtual void finalize() override;
	virtual std::shared_ptr<PSO> clone(const std::string &name) override; 
protected:
	explicit GraphicsPSO(std::weak_ptr<Device> pDevice, const std::string &name);
private:
	D3D12_SHADER_BYTECODE cacheByteCode(const std::string &name, const void *pData, size_t size);
	D3D12_SHADER_BYTECODE cacheByteCode(const std::string &name, WRL::ComPtr<ID3DBlob> pByteCode);
private:
	D3D12_GRAPHICS_PIPELINE_STATE_DESC            _psoDesc;
	std::shared_ptr<D3D12_INPUT_ELEMENT_DESC[]>   _pInputLayout;
	std::map<std::string, WRL::ComPtr<ID3DBlob>>  _shaderByteCodeCache;
};


class ComputePSO : public PSO {
public:
	void setComputeShader(const void *pBinary, size_t size);
	void setComputeShader(const D3D12_SHADER_BYTECODE &Binary);
	void setComputeShader(WRL::ComPtr<ID3DBlob> pBytecode);
	std::shared_ptr<PSO> clone(const std::string &name) override;
	void finalize() override;
protected:
	ComputePSO(std::weak_ptr<Device> pDevice, const std::string &name);
private:
	std::weak_ptr<Device>             _pDevice;
	WRL::ComPtr<ID3DBlob>             _pCSShaderBytecode;
	D3D12_COMPUTE_PIPELINE_STATE_DESC _psoDesc;
};

}