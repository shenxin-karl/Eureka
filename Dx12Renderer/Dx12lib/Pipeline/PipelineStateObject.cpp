#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Tool/MakeObejctTool.hpp>

namespace dx12lib {

PSO::PSO(std::weak_ptr<Device> pDevice, const std::string &name) : _name(name) {
	std::hash<std::string> hasher;
	_hashCode = hasher(name);
}

void PSO::setRootSignature(std::shared_ptr<RootSignature> pRootSignature) {
	assert(pRootSignature->isFinalized());
	_pRootSignature = pRootSignature;
	_dirty = true;
}

std::shared_ptr<RootSignature> PSO::getRootSignature() const {
	return _pRootSignature;
}

WRL::ComPtr<ID3D12PipelineState> PSO::getPipelineStateObject() const {
	return _pPSO;
}

const std::string &PSO::getName() const {
	return _name;
}

bool PSO::isDirty() const {
	return _dirty;
}

auto PSO::getHashCode() const {
	return _hashCode;
}

GraphicsPSO::GraphicsPSO(std::weak_ptr<Device> pDevice, const std::string &name) : PSO(pDevice, name) {
	_pDevice = pDevice;
	/// graphics pipeline static object has default state
	std::memset(&_psoDesc, 0, sizeof(_psoDesc));
	_psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	_psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	_psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	_psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	_psoDesc.SampleMask = 0xffffffff;
	_psoDesc.SampleDesc.Count = 1;
	_psoDesc.SampleDesc.Quality = 0;
}

void GraphicsPSO::setBlendState(const D3D12_BLEND_DESC& blendDesc) {
	_psoDesc.BlendState = blendDesc;
	_dirty = true;
}

void GraphicsPSO::setRasterizerState(const D3D12_RASTERIZER_DESC& rasterizerDesc) {
	_psoDesc.RasterizerState = rasterizerDesc;
	_dirty = true;
}

void GraphicsPSO::setDepthStencilState(const D3D12_DEPTH_STENCIL_DESC &depthStencilDesc) {
	_psoDesc.DepthStencilState = depthStencilDesc;
	_dirty = true;
}

void GraphicsPSO::setSampleMask(UINT sampleMask) {
	_psoDesc.NodeMask = sampleMask;
	_dirty = true;
}

void GraphicsPSO::setPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType) {
	_psoDesc.PrimitiveTopologyType = primitiveType;
	_dirty = true;
}

void GraphicsPSO::setDepthTargetFormat(DXGI_FORMAT DSVFormat) {
	setRenderTargetFormats(0, nullptr, DSVFormat);
}

void GraphicsPSO::setRenderTargetFormat(DXGI_FORMAT RTVFormat, DXGI_FORMAT DSVFormat) {
	setRenderTargetFormats(1, &RTVFormat, DSVFormat);
}

void GraphicsPSO::setRenderTargetFormats(UINT numRTVFormat, const DXGI_FORMAT *pRTVFormat, DXGI_FORMAT DSVFormat) 
{
	assert((numRTVFormat != 0 && pRTVFormat != nullptr) || (numRTVFormat == 0));
	for (UINT i = 0; i < numRTVFormat; ++i) {
		assert(pRTVFormat[i] != DXGI_FORMAT_UNKNOWN);
		_psoDesc.RTVFormats[i] = pRTVFormat[i];
	}
	for (UINT i = numRTVFormat; i < _psoDesc.NumRenderTargets; ++i)
		_psoDesc.RTVFormats[i] = DXGI_FORMAT_UNKNOWN;
	_psoDesc.NumRenderTargets = numRTVFormat;
	_psoDesc.DSVFormat = DSVFormat;
	_psoDesc.SampleDesc.Count = 1;
	_psoDesc.SampleDesc.Quality = 0;
	_dirty = true;
}

void GraphicsPSO::setRenderTargetFormats(const std::vector<DXGI_FORMAT> &RTVFormats, DXGI_FORMAT DSVFormat) {
	if (RTVFormats.empty()) {
		setDepthTargetFormat(DSVFormat);
		return;
	}

	setRenderTargetFormats(
		static_cast<UINT>(RTVFormats.size()),
		RTVFormats.data(),
		DSVFormat
	);
}

void GraphicsPSO::setInputLayout(std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout) {
	_dirty = true;
	if (inputLayout.empty()) {
		_psoDesc.InputLayout.NumElements = 0;
		_psoDesc.InputLayout.pInputElementDescs = nullptr;
		return;
	}

	_inputLayout = std::move(inputLayout);
	_psoDesc.InputLayout.NumElements = static_cast<UINT>(_inputLayout.size());
	_psoDesc.InputLayout.pInputElementDescs = _inputLayout.data();
}

void GraphicsPSO::setInputLayout(const std::initializer_list<D3D12_INPUT_ELEMENT_DESC> &inputLayout) {
	_dirty = true;
	if (!inputLayout.size()) {
		_psoDesc.InputLayout.NumElements = 0;
		_psoDesc.InputLayout.pInputElementDescs = nullptr;
		return;
	}

	_inputLayout = std::vector<D3D12_INPUT_ELEMENT_DESC>(inputLayout.begin(), inputLayout.end());
	_psoDesc.InputLayout.NumElements = static_cast<UINT>(_inputLayout.size());
	_psoDesc.InputLayout.pInputElementDescs = _inputLayout.data();
}

void GraphicsPSO::setPrimitiveRestart(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBProps) {
	_psoDesc.IBStripCutValue = IBProps;
	_dirty = true;
}
void GraphicsPSO::setVertexShader(const void *pBinary, size_t size) {
	_psoDesc.VS = cacheByteCode("VS", pBinary, size);
}
void GraphicsPSO::setPixelShader(const void *pBinary, size_t size) {
	_psoDesc.PS = cacheByteCode("PS", pBinary, size);
}
void GraphicsPSO::setGeometryShader(const void *pBinary, size_t size) {
	_psoDesc.GS = cacheByteCode("GS", pBinary, size);
}
void GraphicsPSO::setHullShader(const void *pBinary, size_t size) {
	_psoDesc.HS = cacheByteCode("HS", pBinary, size);
}
void GraphicsPSO::setDomainShader(const void *pBinary, size_t size) {
	_psoDesc.DS = cacheByteCode("DS", pBinary, size);
}

const D3D12_GRAPHICS_PIPELINE_STATE_DESC &GraphicsPSO::getDesc() const {
	return _psoDesc;
}

void GraphicsPSO::setVertexShader(WRL::ComPtr<ID3DBlob> pByteCode) {
	_psoDesc.VS = cacheByteCode("VS", pByteCode);
}
void GraphicsPSO::setPixelShader(WRL::ComPtr<ID3DBlob> pBytecode) {
	_psoDesc.PS = cacheByteCode("PS", pBytecode);
}
void GraphicsPSO::setGeometryShader(WRL::ComPtr<ID3DBlob> pByteCode) {
	_psoDesc.GS = cacheByteCode("GS", pByteCode);
}
void GraphicsPSO::setHullShader(WRL::ComPtr<ID3DBlob> pByteCode) {
	_psoDesc.HS = cacheByteCode("HS", pByteCode);
}
void GraphicsPSO::setDomainShader(WRL::ComPtr<ID3DBlob> pByteCode) {
	_psoDesc.DS = cacheByteCode("DS", pByteCode);
}

void GraphicsPSO::setVertexShader(const D3D12_SHADER_BYTECODE &pByteCode) {
	setVertexShader(pByteCode.pShaderBytecode, pByteCode.BytecodeLength);
}
void GraphicsPSO::setPixelShader(const D3D12_SHADER_BYTECODE &pByteCode) {
	setPixelShader(pByteCode.pShaderBytecode, pByteCode.BytecodeLength);
}
void GraphicsPSO::setGeometryShader(const D3D12_SHADER_BYTECODE &pByteCode) {
	setGeometryShader(pByteCode.pShaderBytecode, pByteCode.BytecodeLength);
}
void GraphicsPSO::setHullShader(const D3D12_SHADER_BYTECODE &pByteCode) {
	setHullShader(pByteCode.pShaderBytecode, pByteCode.BytecodeLength);
}
void GraphicsPSO::setDomainShader(const D3D12_SHADER_BYTECODE &pByteCode) {
	setDomainShader(pByteCode.pShaderBytecode, pByteCode.BytecodeLength);
}

auto GraphicsPSO::getVertexShader() const -> WRL::ComPtr<ID3DBlob> {
	auto iter = _shaderByteCodeCache.find("VS");
	if (iter != _shaderByteCodeCache.end())
		return iter->second;
	return nullptr;
}
auto GraphicsPSO::getPixelShader() const -> WRL::ComPtr<ID3DBlob> {
	auto iter = _shaderByteCodeCache.find("PS");
	if (iter != _shaderByteCodeCache.end())
		return iter->second;
	return nullptr;
}
auto GraphicsPSO::getGeometryShader() const -> WRL::ComPtr<ID3DBlob> {
	auto iter = _shaderByteCodeCache.find("GS");
	if (iter != _shaderByteCodeCache.end())
		return iter->second;
	return nullptr;
}
auto GraphicsPSO::getHullShader() const -> WRL::ComPtr<ID3DBlob> {
	auto iter = _shaderByteCodeCache.find("HS");
	if (iter != _shaderByteCodeCache.end())
		return iter->second;
	return nullptr;
}
auto GraphicsPSO::getDomainShader() const -> WRL::ComPtr<ID3DBlob> {
	auto iter = _shaderByteCodeCache.find("DS");
	if (iter != _shaderByteCodeCache.end())
		return iter->second;
	return nullptr;
}

auto GraphicsPSO::getInputLayout() const -> const std::vector<D3D12_INPUT_ELEMENT_DESC> & {
	return _inputLayout;
}

void GraphicsPSO::finalize() {
	if (!_dirty)
		return;
	
	assert(_pRootSignature != nullptr && "No root signature is provided");
	assert(!_inputLayout.empty() && "No vertex input is provided");
	_psoDesc.pRootSignature = _pRootSignature->getRootSignature().Get();
	ThrowIfFailed(_pDevice.lock()->getD3DDevice()->CreateGraphicsPipelineState(
		&_psoDesc,
		IID_PPV_ARGS(&_pPSO)
	));
	_pPSO->SetName(to_wstring(getName()).c_str());
	_dirty = false;
}

std::shared_ptr<PSO> GraphicsPSO::clone(const std::string &name) {
	auto pRes = std::make_shared<dx12libTool::MakeGraphicsPSO>(_pDevice, name);
	pRes->_dirty = this->_dirty;
	pRes->_pPSO = this->_pPSO;
	pRes->_psoDesc = this->_psoDesc;
	pRes->_pRootSignature = this->_pRootSignature;
	pRes->_shaderByteCodeCache = this->_shaderByteCodeCache;
	pRes->_inputLayout = this->_inputLayout;
	return std::static_pointer_cast<PSO>(pRes);
}

D3D12_SHADER_BYTECODE GraphicsPSO::cacheByteCode(const std::string &name, const void *pData, size_t size) {
	if (pData == nullptr) {
		_shaderByteCodeCache.erase(name);
		return { nullptr, 0 };
	}
	_dirty = true;
	WRL::ComPtr<ID3DBlob> pBuffer;
	ThrowIfFailed(D3DCreateBlob(size, &pBuffer));
	std::memcpy(pBuffer->GetBufferPointer(), pData, size);
	_shaderByteCodeCache[name] = pBuffer;
	return { pBuffer->GetBufferPointer(), pBuffer->GetBufferSize() };
}

D3D12_SHADER_BYTECODE GraphicsPSO::cacheByteCode(const std::string &name, WRL::ComPtr<ID3DBlob> pByteCode) {
	if (pByteCode == nullptr) {
		_shaderByteCodeCache.erase(name);
		return { nullptr, 0 };
	}
	_dirty = true;
	_shaderByteCodeCache[name] = pByteCode;
	return { pByteCode->GetBufferPointer(), pByteCode->GetBufferSize() };
}

/* ****************************************************************************************** */

void ComputePSO::setComputeShader(const void *pBinary, size_t size) {
	WRL::ComPtr<ID3DBlob> pBuffer;
	ThrowIfFailed(D3DCreateBlob(size, &pBuffer));
	std::memcpy(pBuffer->GetBufferPointer(), pBinary, size);
	setComputeShader(pBuffer);
}

void ComputePSO::setComputeShader(const D3D12_SHADER_BYTECODE &Binary) {
	WRL::ComPtr<ID3DBlob> pBuffer;
	ThrowIfFailed(D3DCreateBlob(Binary.BytecodeLength, &pBuffer));
	std::memcpy(pBuffer->GetBufferPointer(), Binary.pShaderBytecode, Binary.BytecodeLength);
	setComputeShader(pBuffer);
}

void ComputePSO::setComputeShader(WRL::ComPtr<ID3DBlob> pBytecode) {
	_dirty = true;
	_psoDesc.CS = { pBytecode->GetBufferPointer(), pBytecode->GetBufferSize() };
	_pCSShaderBytecode = pBytecode;
}

std::shared_ptr<PSO> ComputePSO::clone(const std::string &name) {
	auto pRes = std::make_shared<dx12libTool::MakeComputePSO>(_pDevice, name);
	pRes->_psoDesc = _psoDesc;
	pRes->_pCSShaderBytecode = _pCSShaderBytecode;
	return pRes;
}

void ComputePSO::finalize() {
	auto pDevice = _pDevice.lock()->getD3DDevice();
	_psoDesc.pRootSignature = _pRootSignature->getRootSignature().Get();
	ThrowIfFailed(pDevice->CreateComputePipelineState(&_psoDesc, IID_PPV_ARGS(&_pPSO)));
	_pPSO->SetName(to_wstring(getName()).c_str());
	_dirty = false;
}

ComputePSO::ComputePSO(std::weak_ptr<Device> pDevice, const std::string &name)
: PSO(pDevice, name), _pDevice(pDevice), _psoDesc({})
{
	_psoDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	_psoDesc.NodeMask = 0;
}

}
