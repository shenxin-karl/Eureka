#include "PropertyBlock.h"
#include "PropertyItem.h"
#include "Objects/TextureManager.h"
#include "Math/MathHelper.h"

namespace Eureka {

void PropertyBlock::addItem(std::unique_ptr<PropertyItem> &&item) {
	_items.push_back(std::move(item));
}

void PropertyBlock::finalize() {
	struct UniformInfo {
		std::string name;
		size_t		stride;
		PropertyItemType type;
	};

	std::vector<UniformInfo> uniformInfos;
	for (auto &pItem : _items) {
		auto &uniformName = pItem->getUniformName();
		switch (pItem->getPropertyType()) {
		case PropertyItemType::Bool:
		case PropertyItemType::Int:
		case PropertyItemType::Float:
		case PropertyItemType::Range:
			uniformInfos.push_back({ uniformName, static_cast<size_t>(4), pItem->getPropertyType() });
			break;
		case PropertyItemType::Float2:
			uniformInfos.push_back({ uniformName, sizeof(Math::float2), pItem->getPropertyType() });
			break;
		case PropertyItemType::Float3:
			uniformInfos.push_back({ uniformName, sizeof(Math::float3), pItem->getPropertyType() });
			break;
		case PropertyItemType::Float4:
			uniformInfos.push_back({ uniformName, sizeof(Math::float4), pItem->getPropertyType() });
			break;
		case PropertyItemType::Matrix:
			uniformInfos.push_back({ uniformName, sizeof(Math::float4x4), pItem->getPropertyType() });
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
		for (auto iter = uniformInfos.rbegin(); iter != uniformInfos.rend(); ++iter) {
			if (iter->stride <= stride) {
				return (iter - uniformInfos.rend());
			}
		}
		return std::nullopt;
	};

	std::sort(uniformInfos.begin(), uniformInfos.end(), [](UniformInfo &lhs, UniformInfo &rhs) {
		return lhs.stride <= rhs.stride;
	});

	size_t offset = 0;
	size_t expectSize = sizeof(Math::float4);
	while (!uniformInfos.empty()) {
		if (auto pFindResult = findExpectStrideVar(expectSize)) {
			auto &var = uniformInfos[*pFindResult];
			_uniformVars[var.name] = { offset, var.stride };
			uniformInfos.erase(uniformInfos.begin() + *pFindResult);
			_cbufferSize = offset + var.stride;
			offset += expectSize;
			expectSize = sizeof(Math::float4);
			continue;
		}

		auto &var = uniformInfos.back();
		_cbufferSize = offset + var.stride;
		offset = Math::MathHelper::alignTo16(offset);
		_uniformVars[var.name] = { offset, var.stride, var.type };
		expectSize = (var.stride == sizeof(Math::float4x4)) ? 0 : (sizeof(Math::float4) - var.stride);
		uniformInfos.pop_back();
	}

	_pCbufferInitBuffer = std::make_unique<char[]>(_cbufferSize);
	char *ptr = _pCbufferInitBuffer.get();
	for (auto &&[name, var] : _uniformVars) {
		switch (var.type) {
		case PropertyItemType::Bool:
			*reinterpret_cast<bool *>(ptr + offset) = getItemValue<bool>(name);
			break;
		case PropertyItemType::Int: 
			*reinterpret_cast<int *>(ptr + offset) = getItemValue<int>(name);
			break;
		case PropertyItemType::Float: 
		case PropertyItemType::Range: 
			*reinterpret_cast<float *>(ptr + offset) = getItemValue<float>(name);
			break;
		case PropertyItemType::Float2: 
			*reinterpret_cast<Math::float2 *>(ptr + offset) = getItemValue<Math::float2>(name);
			break;
		case PropertyItemType::Float3: 
			*reinterpret_cast<Math::float3 *>(ptr + offset) = getItemValue<Math::float3>(name);
			break;
		case PropertyItemType::Float4: 
			*reinterpret_cast<Math::float4 *>(ptr + offset) = getItemValue<Math::float4>(name);
			break;
		case PropertyItemType::Matrix: 
			*reinterpret_cast<Math::float4x4 *>(ptr + offset) = Math::float4x4::Identity;
			break;
		default:
			break;
		}
	}
}

auto PropertyBlock::getCBufferSize() const -> size_t {
	return _cbufferSize;
}

auto PropertyBlock::getCBufferInitPtr() const -> void * {
	return _pCbufferInitBuffer.get();
}

PropertyBlock::~PropertyBlock() = default;

}
 