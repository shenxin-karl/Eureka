#include "PathManager.h"

#include <fstream>

namespace Eureka {


PathManager::PathManager(stdfs::path assetPath, stdfs::path assetCachePath) {
	_assetPath = std::move(assetPath);
	_tempPath = std::move(assetCachePath);
	if (!stdfs::exists(_tempPath)) {
		stdfs::create_directory(_tempPath);
	}
}

auto PathManager::getAssetPath() -> const stdfs::path & {
	return instance()->_assetPath;
}

auto PathManager::getAssetCachePath() -> const stdfs::path & {
	return instance()->_tempPath;
}

void PathManager::setAssetPath(stdfs::path assetPath) {
	instance()->_assetPath = std::move(assetPath);
}

void PathManager::setAssetCachePath(stdfs::path tempPath) {
	instance()->_tempPath = std::move(tempPath);
}

auto PathManager::toAssetPath(const stdfs::path &relativePath) -> stdfs::path {
	return getAssetPath() / relativePath;
}

auto PathManager::toAssetCachePath(const stdfs::path &relativePath) -> stdfs::path {
	return getAssetCachePath() / relativePath;
}

bool PathManager::exist(const stdfs::path &filePath, bool checkTempFile) {
	if (stdfs::exists(filePath)) {
		return true;
	}

	auto assetPath = toAssetPath(filePath);
	if (stdfs::exists(assetPath)) {
		return true;
	}

	if (checkTempFile && stdfs::exists(toAssetCachePath(filePath))) {
		return true;
	}
	return false;
}

bool PathManager::open(const stdfs::path &filePath, std::ifstream &outStream, int mode, bool checkCache) {
	if (stdfs::exists(filePath)) {
		outStream.open(filePath, mode);
		return outStream.is_open();
	}

	auto assetPath = toAssetPath(filePath);
	if (stdfs::exists(assetPath)) {
		outStream.open(assetPath, mode);
		return outStream.is_open();
	}

	if (checkCache) {
		auto tempPath = toAssetCachePath(filePath);
		outStream.open(tempPath, mode);
		return outStream.is_open();
	}
	return false;
}

}
