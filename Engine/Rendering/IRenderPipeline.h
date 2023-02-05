#pragma once

namespace Eureka {

class IRenderPipeline {
public:
	IRenderPipeline() = default;
	IRenderPipeline(const IRenderPipeline &) = delete;
	IRenderPipeline &operator=(const IRenderPipeline &) =  delete;
	virtual ~IRenderPipeline() = default;

	virtual void onRegisterPass() {
	}
	virtual void onInitialize() {
	}
	virtual void onResize(size_t width, size_t height) {
	}
	virtual void onRender() {
	}
};

}
