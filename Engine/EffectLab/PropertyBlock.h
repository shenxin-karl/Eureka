#pragma once
#include <memory>
#include <vector>

namespace Eureka {

class PropertyItem;
class PropertyBlock {
public:
	void addItem(std::unique_ptr<PropertyItem> &&item);
	~PropertyBlock();
private:
	std::vector<std::unique_ptr<PropertyItem>> _items;
};
	
}
