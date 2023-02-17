#include "PropertyBlock.h"
#include "PropertyItem.h"

namespace Eureka {

void PropertyBlock::addItem(std::unique_ptr<PropertyItem> &&item) {
	_items.push_back(std::move(item));
}

void PropertyBlock::finalize() {
	std::vector<std::tuple<std::string, int>> uniformVars;
	for (auto &pItem : _items) {
		auto &uniformName = pItem->getUniformName();
		switch (pItem->getPropertyType()) {
		case PropertyItemType::Bool:
		case PropertyItemType::Int:
		case PropertyItemType::Float:
		case PropertyItemType::Range:
			uniformVars.emplace_back(uniformName, 4);
			break;
		case PropertyItemType::Float2:
			uniformVars.emplace_back(uniformName, sizeof(Math::float2));
			break;
		case PropertyItemType::Float3:
			uniformVars.emplace_back(uniformName, sizeof(Math::float3));
			break;
		case PropertyItemType::Float4:
			uniformVars.emplace_back(uniformName, sizeof(Math::float4));
			break;
		case PropertyItemType::Matrix:
			uniformVars.emplace_back(uniformName, sizeof(Math::float4x4));
			break;
		case PropertyItemType::None:
		case PropertyItemType::Texture2D:
		default:
			break;
		}
	}
}

PropertyBlock::~PropertyBlock() {

}

}
