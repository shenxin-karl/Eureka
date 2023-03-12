#include "Asset.h"

namespace Eureka {

auto Asset::getUUID() const -> UUID128 {
	return _uuid128;
}

}
