#pragma once
#include <unordered_map>
#include <memory>
#include <Dx12lib/Device/Device.h>
#include "Singletion/Singletion.hpp"

namespace Eureka {

class ComputeShader;
class GraphicsShader;
class ShaderManager : public Singletion<ShaderManager> {
public:
	void loading(std::weak_ptr<dx12lib::Device> pDevice);
	auto getComputeShader(const std::string &key) const -> std::shared_ptr<ComputeShader>;
	auto getGraphicsShader(const std::string &key) const -> std::shared_ptr<GraphicsShader>;
private:
	std::unordered_map<std::string, std::shared_ptr<ComputeShader>> _computeShaders;
	std::unordered_map<std::string, std::shared_ptr<GraphicsShader>> _graphicsShaders;
};

}