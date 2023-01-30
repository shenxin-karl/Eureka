#include "PathManager.h"

#include <fstream>

namespace Eureka {


PathManager::PathManager(fs::path projectPath, fs::path assetPath, fs::path tempPath) {
	_projectPath = std::move(projectPath);
	_assetPath = std::move(assetPath);
	_tempPath = std::move(tempPath);
	if (!fs::exists(_tempPath)) {
		fs::create_directory(_tempPath);
	}
}

auto PathManager::getProjectPath() -> const fs::path & {
	return instance()->_projectPath;
}

auto PathManager::getAssetPath() -> const fs::path & {
	return instance()->_assetPath;
}

auto PathManager::getTempPath() -> const fs::path & {
	return instance()->_tempPath;
}

void PathManager::setProjectPath(fs::path projectPath) {
	instance()->_projectPath = std::move(projectPath);
}

void PathManager::setAssetPath(fs::path assetPath) {
	instance()->_assetPath = std::move(assetPath);
}

void PathManager::setTempPath(fs::path tempPath) {
	instance()->_tempPath = std::move(tempPath);
}

auto PathManager::toAssetPath(const fs::path &relativePath) -> fs::path {
	return getAssetPath() / relativePath;
}

auto PathManager::toProjectPath(const fs::path &relativePath) -> fs::path {
	return getProjectPath() / relativePath;
}

auto PathManager::toTempPath(const fs::path &relativePath) -> fs::path {
	return getTempPath() / relativePath;
}

bool PathManager::exist(const fs::path &filePath, bool checkTempFile) {
	if (fs::exists(filePath))
		return true;
	if (fs::exists(toAssetPath(filePath)))
		return true;
	if (fs::exists(toProjectPath(filePath)))
		return true;
	if (checkTempFile && fs::exists(toTempPath(filePath)))
		return true;
	return false;
}

bool PathManager::open(const fs::path &filePath, std::ifstream &outStream, int mode, bool checkTempFile) {
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

	if (checkTempFile) {
		auto tempPath = toTempPath(filePath);
		outStream.open(tempPath, mode);
		return outStream.is_open();
	}
	return false;
}

}
