#pragma once
#include <memory>
#include <string>
#include <vector>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Eureka {

class ALNode;

class ALTexture {
public:
	std::string path;
	std::string textureExtName;
	std::shared_ptr<char[]> pTextureData;
	size_t textureDataSize;
public:
	bool valid() const;
};

class ALMaterial {
public:
	void init(const std::string &directory, const aiScene *pAiScene, const aiMaterial *pAiMaterial);
	const ALTexture &getDiffuseMap() const;
	const ALTexture &getNormalMap() const;
	const ALTexture &getRoughnessMap() const;
	const ALTexture &getMetallicMap() const;
	const ALTexture &getAmbientOcclusionMap() const;
	static ALMaterial sDefaultMaterial;
private:
	static void processTexture(ALTexture &texture, 
		const std::string &direction,
		const aiScene *pAiScene, 
		const aiMaterial *pAiMaterial, 
		aiTextureType type
	);
private:
	ALTexture _albedoMap;
	ALTexture _normalMap;
	ALTexture _roughnessMap;
	ALTexture _metallicMap;
	ALTexture _ambientOcclusionMap;
};

class ALTree {
public:
	constexpr static int kDefaultLoadFlag = (
		aiProcessPreset_TargetRealtime_MaxQuality |
		aiProcess_ConvertToLeftHanded		      | 
		aiProcess_OptimizeGraph		              |
		aiProcess_GenBoundingBoxes
	);
	ALTree(const std::string &path, int flag = kDefaultLoadFlag);
	~ALTree();
	ALTree(const ALTree &) = delete;
	size_t getNumMaterial() const;
	const ALMaterial *getMaterial(size_t idx) const;
	const ALNode *getRootNode() const;
	void saveToObj(const std::string &direction) const;
private:
	std::vector<ALMaterial> _materials;
	std::unique_ptr<ALNode> _pRootNode;
};

}
