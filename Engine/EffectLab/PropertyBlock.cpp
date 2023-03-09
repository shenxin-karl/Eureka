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

	size_t registerIndex = 0;
	std::string textureDefinition;

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
			textureDefinition += fmt::format("Texture2D {} : register(t{}, space{});\n",
				uniformName,
				registerIndex,
				_spaceId
			);
			++registerIndex;
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


	std::string uniformDefinition;
	static std::string_view declareFmtStrs[] = {
		"\tbool     {];\n",		// PropertyItemType::Bool
		"\tint      {};\n",		// PropertyItemType::Int
		"\tfloat    {};\n",		// PropertyItemType::Float
		"\tfloat    {};\n",		// PropertyItemType::Range
		"\tfloat2   {};\n",		// PropertyItemType::Float2
		"\tfloat3   {};\n",		// PropertyItemType::Float3
		"\tfloat4   {};\n",		// PropertyItemType::Float4
		"\tfloat4x4 {};\n",		// PropertyItemType::Matrix
	};

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
			auto formatStr = declareFmtStrs[static_cast<size_t>(var.type) - 1];
			uniformDefinition += fmt::format(formatStr.data(), var.name);
			continue;
		}

		auto &var = uniformInfos.back();
		auto formatStr = declareFmtStrs[static_cast<size_t>(var.type) - 1];
		uniformDefinition += fmt::format(formatStr.data(), var.name);

		_cbufferSize = offset + var.stride;
		offset = Math::MathHelper::alignTo16(offset);
		_uniformVars[var.name] = { offset, var.stride, var.type };
		expectSize = (var.stride == sizeof(Math::float4x4)) ? 0 : (sizeof(Math::float4) - var.stride);
		uniformInfos.pop_back();
	}

	std::string_view finalFormatString;
	std::string generatedMaterialInclude;
	if (!_uniformVars.empty()) {
		finalFormatString =
		"cbuffer _GeneartedMaterialCBuffer : register(b0, space{}) {\n"
			"{}"
		"};\n"
		"\n"
		"{}\n";
		generatedMaterialInclude = fmt::format(
			finalFormatString.data(),
			_spaceId,
			uniformDefinition,
			textureDefinition
		);
	} else if (!textureDefinition.empty()) {
		generatedMaterialInclude = fmt::format("{}\n", textureDefinition);
	}

	dx12lib::DxcModule::instance()->getUtils()->CreateBlob(
		generatedMaterialInclude.data(),
		generatedMaterialInclude.size(),
		DXC_CP_ACP,
		&_pHlslPropertyContent
	);

	buildInitBuffer();
}

auto PropertyBlock::getCBufferSize() const -> size_t {
	return _cbufferSize;
}

auto PropertyBlock::getCBufferInitPtr() const -> void * {
	return _pCbufferInitBuffer.get();
}

auto PropertyBlock::getGeneratedPropertiesContent() const -> WRL::ComPtr<IDxcBlobEncoding> {
	return _pHlslPropertyContent;
}

PropertyBlock::~PropertyBlock() = default;

void PropertyBlock::buildInitBuffer() {
	_pCbufferInitBuffer = std::make_unique<char[]>(_cbufferSize);
	char *ptr = _pCbufferInitBuffer.get();
	for (auto &&[name, var] : _uniformVars) {
		char *pSrc = ptr + var.offset;
		switch (var.type) {
		case PropertyItemType::Bool:
			*reinterpret_cast<bool *>(pSrc) = getItemValue<bool>(name);
			break;
		case PropertyItemType::Int:
			*reinterpret_cast<int *>(pSrc) = getItemValue<int>(name);
			break;
		case PropertyItemType::Float:
		case PropertyItemType::Range:
			*reinterpret_cast<float *>(pSrc) = getItemValue<float>(name);
			break;
		case PropertyItemType::Float2:
			*reinterpret_cast<Math::float2 *>(pSrc) = getItemValue<Math::float2>(name);
			break;
		case PropertyItemType::Float3:
			*reinterpret_cast<Math::float3 *>(pSrc) = getItemValue<Math::float3>(name);
			break;
		case PropertyItemType::Float4:
			*reinterpret_cast<Math::float4 *>(pSrc) = getItemValue<Math::float4>(name);
			break;
		case PropertyItemType::Matrix:
			*reinterpret_cast<Math::float4x4 *>(pSrc) = Math::float4x4::Identity;
			break;
		default:
			break;
		}
	}
}

}
 