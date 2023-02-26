#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "Dx12lib/Texture/Texture.h"

namespace Eureka {

class PropertyItem;
class PropertyBlock {
public:
	void addItem(std::unique_ptr<PropertyItem> &&item);
	void finalize();
	~PropertyBlock();
private:
	struct UniformVar {
		size_t offset;
		size_t sizeInByte;
	};
private:
	using TextureMap = std::unordered_map<std::string, std::shared_ptr<dx12lib::Texture>>;
	std::vector<std::unique_ptr<PropertyItem>>  _items;
	size_t									    _cbufferSize = 0;
	std::unique_ptr<char[]>						_pCbufferInitBuffer;
	std::unordered_map<std::string, UniformVar> _uniformVars;
	TextureMap									_textureMap;
};
	
}
