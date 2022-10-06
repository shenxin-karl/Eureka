#include "TextureManager.h"

namespace Eureka {

auto TextureManager::getTexture(const std::string &path) const -> std::shared_ptr<dx12lib::Texture> {
	auto iter = _textureMap.find(path);
	if (iter != _textureMap.end())
		return iter->second;
	return nullptr;
}

void TextureManager::setTexture(const std::string &path, std::shared_ptr<dx12lib::Texture> pTexture) {
	_textureMap[path] = std::move(pTexture);
}

bool TextureManager::remoteTexture(const std::string &path) {
	return _textureMap.erase(path) > 0;
}

void TextureManager::clearTexture() {
	_textureMap.clear();
}

}
