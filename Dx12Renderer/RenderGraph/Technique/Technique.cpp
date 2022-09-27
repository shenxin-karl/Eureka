#include "Technique.h"

#include "RenderGraph/RenderGraph/RenderGraph.h"

namespace rgph {

Technique::Technique(const std::string &techniqueName, TechniqueType type, bool active)
: _active(active), _techniqueName(techniqueName)
, _techniqueType(type)
{
}

void Technique::addStep(std::unique_ptr<Step> pStep) {
	_steps.push_back(std::move(pStep));
}

void Technique::submit(const TechniqueFlag &techniqueFlag, 
	const Geometry *pGeometry, 
	const TransformCBufferPtr *pTransformCBuffer) const
{
	if (!isActive() || !techniqueFlag.test(_techniqueType))
		return;

	for (auto &pStep : _steps)
		pStep->submit(pGeometry, pTransformCBuffer);
}

void Technique::setActive(bool bActive) {
	_active = bActive;
}

bool Technique::isActive() const {
	return _active;
}

TechniqueType Technique::getTechniqueType() const {
	return _techniqueType;
}

const std::string & Technique::getTechniqueName() const {
	return _techniqueName;
}

}
