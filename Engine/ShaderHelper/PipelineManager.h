#pragma once
#include <unordered_map>
#include <memory>
#include <Dx12lib/Device/Device.h>
#include "Singletion/Singletion.hpp"

namespace Eureka {

class ComputePipeline;
class GraphicsPipeline;
class PipelineManager : public Singletion<PipelineManager> {
public:
	void initialize(std::weak_ptr<dx12lib::Device> pDevice);
	auto getComputePipeline(const std::string &key) const -> std::shared_ptr<ComputePipeline>;
	auto getGraphicsPipeline(const std::string &key) const -> std::shared_ptr<GraphicsPipeline>;
private:
	std::unordered_map<std::string, std::shared_ptr<ComputePipeline>> _computeShaders;
	std::unordered_map<std::string, std::shared_ptr<GraphicsPipeline>> _graphicsShaders;
};

}