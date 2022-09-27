#pragma once
#include <RenderGraph/Bindable/Bindable.hpp>
#include <RenderGraph/Pass/PassResourcePtr.hpp>

namespace rgph {

template<typename T>
class PassResourceBindable : public Bindable {
	PassResourceBindable(BindableType bindableType) : Bindable(bindableType) {}

	void bind(dx12lib::IGraphicsContext &graphicsCtx) const override {
		_bindFunc(graphicsCtx);
	}

	template<typename U>
	static std::shared_ptr<PassResourceBindable> makeSRV(
		const dx12lib::ShaderRegister &sr, 
		PassResourcePtr<U> &pPassResource, 
		size_t mipSlice = 0)
	{
		auto pBindable = std::make_shared<PassResourceBindable>(BindableType::PassResourceSRV);
		pBindable->_bindFunc = [=, &pPassResource](dx12lib::IGraphicsContext &graphicsCtx) {
			const auto &srv = pPassResource->getSRV(mipSlice);
			graphicsCtx.setShaderResourceView(sr, srv);
		};
		return pBindable;
	}

	template<typename U>
	static std::shared_ptr<PassResourceBindable> makePlaneSRV(
		const dx12lib::ShaderRegister &sr,
		PassResourcePtr<U> &pPassResource,
		size_t planeSlice,
		size_t mipSlice = 0
	)
	{
		auto pBindable = std::make_shared<PassResourceBindable>(BindableType::PassResourceSRV);
		pBindable->_bindFunc = [=, &pPassResource](dx12lib::IGraphicsContext &graphicsCtx) {
			const auto &srv = pPassResource->getPlaneSRV(planeSlice, mipSlice);
			graphicsCtx.setShaderResourceView(sr, srv);
		};
		return pBindable;
	}
private:
	std::function<void(dx12lib::IGraphicsContext &graphicsCtx)> _bindFunc;
};

}
