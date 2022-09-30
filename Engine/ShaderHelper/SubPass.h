#pragma once
#include <memory>
#include <string>

namespace Eureka {

struct SubPassDesc;
class SubPass {
public:
	explicit SubPass(std::shared_ptr<SubPassDesc> pSubPassDesc);
	auto getSubPassName() const -> const std::string &;
private:
	std::shared_ptr<SubPassDesc> _pSubPassDesc;
};

}
