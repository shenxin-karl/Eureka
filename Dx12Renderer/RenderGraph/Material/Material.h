#pragma once
#include <string>
#include <RenderGraph/RenderGraphStd.h>
#include <RenderGraph/Job/Geometry.h>

namespace rgph {

class Material : virtual public NonCopyable {
public:
	Material(std::string name);
	const std::string &getMaterialName() const;
	size_t getNumTechnique() const;
	std::shared_ptr<Technique> getTechnique(size_t idx) const;
	VertexInputSlots getVertexInputSlots() const;
	~Material() override;
protected:
	std::string _materialName;
	VertexInputSlots _vertexInputSlots;
	std::vector<std::shared_ptr<Technique>> _techniques;
};

}
