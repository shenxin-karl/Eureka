#include "PropertyBlock.h"
#include "PropertyItem.h"
#include "Objects/TextureManager.h"

namespace Eureka {

void PropertyBlock::addItem(std::unique_ptr<PropertyItem> &&item) {
	_items.push_back(std::move(item));
}

void PropertyBlock::finalize() {
	struct UniformInfo {
		std::string name;
		size_t		stride;
	};

	std::vector<UniformInfo> uniformInfos;
	for (auto &pItem : _items) {
		auto &uniformName = pItem->getUniformName();
		switch (pItem->getPropertyType()) {
		case PropertyItemType::Bool:
		case PropertyItemType::Int:
		case PropertyItemType::Float:
		case PropertyItemType::Range:
			uniformInfos.emplace_back(uniformName, 4);
			break;
		case PropertyItemType::Float2:
			uniformInfos.emplace_back(uniformName, sizeof(Math::float2));
			break;
		case PropertyItemType::Float3:
			uniformInfos.emplace_back(uniformName, sizeof(Math::float3));
			break;
		case PropertyItemType::Float4:
			uniformInfos.emplace_back(uniformName, sizeof(Math::float4));
			break;
		case PropertyItemType::Matrix:
			uniformInfos.emplace_back(uniformName, sizeof(Math::float4x4));
			break;
		case PropertyItemType::Texture2D: {
			std::string defaultTexturePath = pItem->getTexture2DPath();
			auto pTexture = TextureManager::instance()->getTexture(defaultTexturePath);
			_textureMap[uniformName] = pTexture;
			break;
		}
		case PropertyItemType::None:
		default:
			break;
		}
	}

	auto findExpectStrideVar = [&](size_t stride) -> std::optional<size_t> {
		for (size_t i = 0; i < uniformInfos.size(); ++i) {
			if (uniformInfos[i].stride == stride) {
				return i;
			}
		}
		return std::nullopt;
	};

	std::ranges::sort(uniformInfos, [](UniformInfo &lhs, UniformInfo &rhs) {
		return lhs.stride <= rhs.stride;
	});

	// todo: ¼ÆËãºÃ uniform µÄ offset
	 
}

PropertyBlock::~PropertyBlock() {

}

}
