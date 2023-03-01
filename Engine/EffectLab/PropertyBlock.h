#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "PropertyItem.h"
#include "Dx12lib/Texture/Texture.h"

namespace Eureka {

class PropertyItem;
class PropertyBlock {
public:
	void addItem(std::unique_ptr<PropertyItem> &&item);
	void finalize();
	auto getCBufferSize() const -> size_t;
	auto getCBufferInitPtr() const -> void *;
	~PropertyBlock();
private:
	struct UniformVar {
		size_t			 offset;
		size_t			 sizeInByte;
		PropertyItemType type;
	};
private:
	using TextureMap = std::unordered_map<std::string, std::shared_ptr<dx12lib::Texture>>;
	template<typename T>
	T getItemValue(const std::string &name) {
		for (auto &pItem : _items) {
			if (pItem->getUniformName() == name) {
				return std::get<T>(pItem->getPropertyValue());
			}
		}
		return T{};
	}
private:
	std::vector<std::unique_ptr<PropertyItem>>  _items;
	size_t									    _cbufferSize = 0;
	std::unique_ptr<char[]>						_pCbufferInitBuffer;
	std::unordered_map<std::string, UniformVar> _uniformVars;
	TextureMap									_textureMap;
};
	
}
