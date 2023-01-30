#include "PropertyBlock.h"
#include "PropertyItem.h"

namespace Eureka {

void PropertyBlock::addItem(std::unique_ptr<PropertyItem> &&item) {
	_items.push_back(std::move(item));
}

PropertyBlock::~PropertyBlock() {

}

}
