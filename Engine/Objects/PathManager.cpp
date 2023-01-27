#include "PathManager.h"

#include <fstream>

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

bool PathManager::exist(const fs::path &filePath) {
	if (fs::exists(filePath))
		return true;
	if (fs::exists(toAssetPath(filePath)))
		return true;
	if (fs::exists(toProjectPath(filePath)))
		return true;
	return false;
}

bool PathManager::open(const fs::path &filePath, std::ifstream &outStream, int mode) {
	if (fs::exists(filePath)) {
		outStream.open(filePath, mode);
		return outStream.is_open();
	}

	auto assetPath = toAssetPath(filePath);
	if (fs::exists(assetPath)) {
		outStream.open(assetPath, mode);
		return outStream.is_open();
	}

	auto projectPath = toProjectPath(filePath);
	if (fs::exists(projectPath)) {
		outStream.open(projectPath, mode);
		return outStream.is_open();
	}

	return false;
}

}
