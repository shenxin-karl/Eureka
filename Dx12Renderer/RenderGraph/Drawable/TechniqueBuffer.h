#pragma once
#include <RenderGraph/RenderGraphStd.h>
#include "RenderGraph/Technique/TechniqueType.hpp"

namespace rgph {

class TechniqueBuffer : virtual public NonCopyable {
public:
	TechniqueBuffer() = default;
	~TechniqueBuffer() override = default;
	bool addTechnique(std::shared_ptr<Technique> pTechnique);
	bool hasTechnique(const TechniqueType &techniqueType) const;
	bool removeTechnique(const TechniqueType &techniqueType);
	void setTechniqueActive(const TechniqueType &techniqueType, bool bActivate);
	void clearTechnique();
	const TechniqueFlag &getTechniqueFlag() const;
	const std::vector<std::shared_ptr<Technique>> &getTechniques() const;
private:
	TechniqueFlag _techniqueFlag = TechniqueType::None;
	std::vector<std::shared_ptr<Technique>> _techniques;
};

}
