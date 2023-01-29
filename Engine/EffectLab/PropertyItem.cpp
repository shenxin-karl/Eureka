#include "PropertyItem.h"

namespace Eureka {

PropertyItem::PropertyItem(std::string uniformName)
: _uniformName(std::move(uniformName)), _propertyType(PropertyItemType::None) {

}

}
