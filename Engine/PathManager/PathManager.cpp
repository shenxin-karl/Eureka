#include "PathManager.h"

namespace Eureka {

static std::unique_ptr<PathManager> pInst = std::make_unique<PathManager>();

auto PathManager::getProjectPath() -> const fs::path & {
	return pInst->_projectPath;
}

auto PathManager::getAssetPath() -> const fs::path & {
	return pInst->_assetPath;
}

void PathManager::setProjectPath(fs::path projectPath) {
	pInst->_projectPath = std::move(projectPath);
}

void PathManager::setAssetPath(fs::path assetPath) {
	pInst->_assetPath = std::move(assetPath);
}

auto PathManager::toAssetPath(const fs::path &relativePath) -> fs::path {
	return getAssetPath() / relativePath;
}

auto PathManager::toProjectPath(const fs::path &relativePath) -> fs::path {
	return getProjectPath() / relativePath;
}

}
