#pragma once
#include <cstdint>
#include "EffectLab/Pass.h"

namespace Eureka {

class Transform;
class MaterialProperty;

struct RenderObjectSortKey {
	friend bool operator<(const RenderObjectSortKey &lhs, const RenderObjectSortKey &rhs) {
		return lhs.renderQueue < rhs.renderQueue						||
			   lhs.renderPriority < rhs.renderPriority					||
			   lhs.pipelineStateHashCode < rhs.pipelineStateHashCode	||
			   lhs.distanceSqr <= rhs.distanceSqr;
	}
	friend bool operator<=(const RenderObjectSortKey &lhs, const RenderObjectSortKey &rhs) {
		return !(rhs < lhs);
	}
	friend bool operator>(const RenderObjectSortKey &lhs, const RenderObjectSortKey &rhs) {
		return rhs < lhs;
	}
	friend bool operator>=(const RenderObjectSortKey &lhs, const RenderObjectSortKey &rhs) {
		return !(lhs < rhs);
	}
	uint16_t renderQueue = 0;
	uint16_t renderPriority = 0;
	uint32_t pipelineStateHashCode = 0;
	uint32_t distanceSqr = 0;
};

struct RenderObject {
public:
	RenderObject();
	void setPassVariant(PassVariant *pPassVariant);
private:
	bool				_valid = false;
	RenderObjectSortKey _renderObjectSortKey;
	PassVariant *		_pPassVariant;
	MaterialProperty *  _pMaterialProperty;
	Transform *			_pTransform;
};

}
