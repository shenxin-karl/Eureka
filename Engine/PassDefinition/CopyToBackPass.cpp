#include "CopyToBackPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "EngineDefinition/EngineDefinition.h"
#include "Model/GeometryGenerator/GeometryGenerator.h"
#include "ShaderHelper/ShaderHelper.h"

// shader
#include "CopyToBack_VS.h"
#include "CopyToBack_PS.h"
#include "Dx12lib/Pipeline/DXCShader.h"

namespace Eureka {

CopyToBackPass::CopyToBackPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
: GraphicsPass(passName)
, pScreenMap(this, "ScreenMap")
, pBackBufferMap(this, "BackBufferMap")
{
	auto pShaderDevice = directCtx.getDevice().lock();

	_pPipeline = pShaderDevice->createGraphicsPSO("FXAA");
	_pPipeline->setVertexShader(dx12lib::DXCShader::make(g_CopyToBack_VS));
	_pPipeline->setPixelShader(dx12lib::DXCShader::make(g_CopyToBack_PS));
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

void CopyToBackPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	GraphicsPass::execute(directCtx, view);
	directCtx.setGraphicsPSO(_pPipeline);
	directCtx.setShaderResourceView(StringName("gScreenMap"), pScreenMap->get2dSRV());
	auto mask = rgph::ShaderLayoutMask::Position | rgph::ShaderLayoutMask::TexCoord0;
	_pFullScreenGeometry->bind(directCtx, mask);
	_pFullScreenGeometry->draw(directCtx);
}

void CopyToBackPass::setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) {
	graphicsCtx.setViewport(pScreenMap->getViewport());
	graphicsCtx.setScissorRect(pScreenMap->getScissorRect());
}

void CopyToBackPass::setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) {
	graphicsContext.setRenderTarget(pBackBufferMap->get2dRTV());
}

}
