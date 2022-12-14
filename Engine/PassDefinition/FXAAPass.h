#pragma once
#include <RenderGraph/Pass/GraphicsPass.h>

namespace Eureka {

class FXAAPass : public rgph::GraphicsPass {
public:
    FXAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx);
    void execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) override;
    void setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) override;
    void setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) override;
public:
    rgph::PassResourcePtr<dx12lib::Texture>  pBackBuffer;
    rgph::PassResourcePtr<dx12lib::Texture>  pScreenMap;
    std::shared_ptr<dx12lib::ConstantBuffer> pCbFXAASetting;
private:
    std::shared_ptr<rgph::Geometry>         _pFullScreenGeometry;
    std::shared_ptr<dx12lib::GraphicsPSO>   _pPipeline;
};

}
