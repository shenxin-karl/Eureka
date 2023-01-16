#pragma once 
#include <filesystem>

namespace fs = std::filesystem;

namespace Eureka {

class PathManager {
public:
	static auto getProjectPath() -> const fs::path &;
	static auto getAssetPath() -> const fs::path &;
	static void setProjectPath(fs::path projectPath);
	static void setAssetPath(fs::path assetPath);
	static auto toAssetPath(const fs::path &relativePath) -> fs::path;
	static auto toProjectPath(const fs::path &relativePath) -> fs::path;
private:
	fs::path _assetPath;
	fs::path _projectPath;
};

}