#include "FXAAPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "ShaderHelper/GraphicsPipeline.h"
#include "Model/MeshManager.h"
#include "Model/GeometryGenerator/GeometryGenerator.h"
#include "ShaderHelper/ShaderHelper.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "ShaderHelper/ShaderLoader.h"

namespace Eureka {

FXAAPass::FXAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
: GraphicsPass(passName)
, pBackBuffer(this, "BackBuffer")
, pScreenMap(this, "ScreenMap")
{
	auto pShaderDevice = directCtx.getDevice().lock();

	_pPipeline = pShaderDevice->createGraphicsPSO("FXAA");
	_pPipeline->setVertexShader(ShaderLoader::dxc(
		"Assets/Shaders/FXAA.hlsl",
		"VS",
		"vs_6_0"
	));
	_pPipeline->setPixelShader(ShaderLoader::dxc(
		"Assets/Shaders/FXAA.hlsl",
		"PS",
		"ps_6_0"
	));
	_pPipeline->setRenderTargetFormat(kSwapChainRenderTargetFormat, kSwapChainDepthStencilFormat);
	CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc(D3D12_DEFAULT);
	depthStencilDesc.DepthEnable = false; 
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	_pPipeline->setDepthStencilState(depthStencilDesc);
	CD3DX12_RASTERIZER_DESC rasterizerDesc(D3D12_DEFAULT);
	rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE; 
	_pPipeline->setRasterizerState(rasterizerDesc); 
	ShaderHelper::generateVertexInput(_pPipeline);
	ShaderHelper::generateRootSignature(_pPipeline);
	_pPipeline->finalize();

	auto pMesh = GeometryGenerator::instance()->createQuad(-1.f, -1.f, 2.f, 2.f, 0.f);
	rgph::ShaderLayoutMask mask = rgph::ShaderLayoutMask::Position | rgph::ShaderLayoutMask::TexCoord0;
	_pFullScreenGeometry = GeometryGenerator::instance()->createGeometry(directCtx, mask, pMesh);
}

void FXAAPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	GraphicsPass::execute(directCtx, view);

	directCtx.setGraphicsPSO(_pPipeline);
	directCtx.setConstantBufferView(StringName("FXAASetting"), pCbFXAASetting->getCBV());
	directCtx.setShaderResourceView(StringName("gScreenMap"), pScreenMap->get2dSRV());
	auto mask = rgph::ShaderLayoutMask::Position | rgph::ShaderLayoutMask::TexCoord0;
	_pFullScreenGeometry->bind(directCtx, mask);
	_pFullScreenGeometry->draw(directCtx);
}

void FXAAPass::setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) {
	graphicsCtx.setViewport(pScreenMap->getViewport());
	graphicsCtx.setScissorRect(pScreenMap->getScissorRect());
}

void FXAAPass::setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) {
	graphicsContext.setRenderTarget(pBackBuffer->get2dRTV());
}

}
