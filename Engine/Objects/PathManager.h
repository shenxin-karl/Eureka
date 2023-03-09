#pragma once 
#include <filesystem>
#include "Foundation/Singletion.hpp"

namespace stdfs = std::filesystem;

namespace Eureka {

class PathManager : public Singletion<PathManager> {
public:
	PathManager(stdfs::path assetPath, stdfs::path assetCachePath);
	static auto getAssetPath() -> const stdfs::path &;
	static auto getAssetCachePath() -> const stdfs::path &;
	static void setAssetPath(stdfs::path assetPath);
	static void setAssetCachePath(stdfs::path tempPath);
	static auto toAssetPath(const stdfs::path &relativePath) -> stdfs::path;
	static auto toAssetCachePath(const stdfs::path &relativePath) -> stdfs::path;
	static bool exist(const stdfs::path &filePath, bool checkTempFile = false);
	static bool open(const stdfs::path &filePath, std::ifstream &outStream, int mode, bool checkCache = false);
private:
	stdfs::path _assetPath;
	stdfs::path _tempPath;
};

}