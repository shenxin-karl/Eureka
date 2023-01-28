#pragma once

namespace Eureka {

class PropertyItem;
class PropertyBlock {
private:
	std::vector<std::unique_ptr<PropertyItem>> _items;
};
	
}
