#pragma once 
#include <filesystem>
#include "Foundation/Singletion.hpp"

namespace fs = std::filesystem;

namespace Eureka {

class PathManager : public Singletion<PathManager> {
public:
	PathManager(fs::path projectPath, fs::path assetPath, fs::path tempPath);
	static auto getProjectPath() -> const fs::path &;
	static auto getAssetPath() -> const fs::path &;
	static auto getTempPath() -> const fs::path &;
	static void setProjectPath(fs::path projectPath);
	static void setAssetPath(fs::path assetPath);
	static void setTempPath(fs::path tempPath);
	static auto toAssetPath(const fs::path &relativePath) -> fs::path;
	static auto toProjectPath(const fs::path &relativePath) -> fs::path;
	static auto toTempPath(const fs::path &relativePath) -> fs::path;
	static bool exist(const fs::path &filePath, bool checkTempFile = false);
	static bool open(const fs::path &filePath, std::ifstream &outStream, int mode, bool checkTempFile = false);
private:
	fs::path _assetPath;
	fs::path _projectPath;
	fs::path _tempPath;
};

}