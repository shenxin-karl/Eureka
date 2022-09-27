#include "TechniqueBuffer.h"
#include "RenderGraph/Technique/Technique.h"

namespace rgph {

bool TechniqueBuffer::addTechnique(std::shared_ptr<Technique> pTechnique) {
	assert(pTechnique);
	if (hasTechnique(pTechnique->getTechniqueType()))
		return false;

	_techniqueFlag.set(pTechnique->getTechniqueType());
	_techniques.push_back(std::move(pTechnique));
	return true;
}

bool TechniqueBuffer::hasTechnique(const TechniqueType &techniqueType) const {
	return _techniqueFlag.test(techniqueType);
}

bool TechniqueBuffer::removeTechnique(const TechniqueType &techniqueType) {
	if (!hasTechnique(techniqueType))
		return false;

	for (auto iter = _techniques.begin(); iter != _techniques.end(); ++iter) {
		if ((*iter)->getTechniqueType() & techniqueType) {
			_techniques.erase(iter);
			return true;
		}
	}

	assert(false);
	return false;
}

void TechniqueBuffer::setTechniqueActive(const TechniqueType &techniqueType, bool bActivate) {
	if (!hasTechnique(techniqueType))
		return;

	for (auto iter = _techniques.begin(); iter != _techniques.end(); ++iter) {
		if ((*iter)->getTechniqueType() & techniqueType) {
			(*iter)->setActive(bActivate);
			return;
		}
	}
}

void TechniqueBuffer::clearTechnique() {
	_techniques.clear();
	_techniqueFlag.reset();
}

const TechniqueFlag & TechniqueBuffer::getTechniqueFlag() const {
	return _techniqueFlag;
}

const std::vector<std::shared_ptr<Technique>> & TechniqueBuffer::getTechniques() const {
	return _techniques;
}

}
