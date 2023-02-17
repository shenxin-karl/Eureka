#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

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
	std::vector<std::unique_ptr<PropertyItem>>  _items;
	size_t									    _cbufferSize = 0;
	std::unordered_map<std::string, UniformVar> _uniformVars;
};
	
}
