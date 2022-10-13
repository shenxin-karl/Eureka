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
	ShaderLayoutMask getShaderLayoutMask() const;
	~Material() override;
	void submit(const TechniqueFlag &techniqueFlag, 
		const Geometry *pGeometry, 
		const TransformCBufferPtr *pTransformCBuffer
	) const;
protected:
	std::string _materialName;
	ShaderLayoutMask _shaderLayoutMask;
	std::vector<std::shared_ptr<Technique>> _techniques;
};

}
