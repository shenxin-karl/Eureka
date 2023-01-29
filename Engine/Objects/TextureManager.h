#pragma once
#include <unordered_map>
#include <Dx12lib/Texture/Texture.h>
#include "Foundation/Singletion.hpp"

namespace Eureka {

class TextureManager : public Singletion<TextureManager> {
public:
	auto getTexture(const std::string &path) const -> std::shared_ptr<dx12lib::Texture>;
	void setTexture(const std::string &path, std::shared_ptr<dx12lib::Texture> pTexture);
	bool remoteTexture(const std::string &path);
	void clearTexture();
private:
	std::unordered_map<std::string, std::shared_ptr<dx12lib::Texture>> _textureMap;
};

}
