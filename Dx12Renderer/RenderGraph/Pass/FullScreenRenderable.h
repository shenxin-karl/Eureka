#pragma once
#include <Dx12lib/dx12libStd.h>
#include <RenderGraph/Drawable/Drawable.h>

namespace rgph {

class FullScreenRenderable : public NonCopyable {
public:
	FullScreenRenderable(std::weak_ptr<dx12lib::GraphicsPSO> pGraphicsPSO);
	auto getName() const -> const std::string &;
	void setGraphicsPSO(std::weak_ptr<dx12lib::GraphicsPSO> pGraphicsPSO);
	auto getGraphicsPSO() const -> std::shared_ptr<dx12lib::GraphicsPSO>;
	void setVertexBuffer(std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer);
	auto getVertexBuffer() const -> std::shared_ptr<dx12lib::VertexBuffer>;
	void setVertexInputSlot(size_t slot);
	auto getVertexInputSlot() const -> size_t;
	void addBindable(std::shared_ptr<Bindable> pBindable);
	void clearBindables();
	void execute(dx12lib::IGraphicsContext &graphicsCtx);
private:
	std::string _name;
	size_t _vertexInputSlot = 0;
	std::weak_ptr<dx12lib::GraphicsPSO> _pGraphicsPSO;
	std::shared_ptr<dx12lib::VertexBuffer> _pVertexBuffer;
	std::vector<std::shared_ptr<Bindable>> _bindables;
};

}
