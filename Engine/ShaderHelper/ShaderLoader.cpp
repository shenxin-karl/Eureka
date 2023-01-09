#include "ShaderLoader.h"
#include "ShaderContentLoader.h"
#include "ShaderInclude.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "Foundation/Exception.h"

namespace Eureka {

static bool checkShaderCacheValid(const fs::path &sourcePath, const dx12lib::ShaderCacheInfo &cacheInfo) {
    if (!fs::exists(cacheInfo.csoFilePath) || 
        !fs::exists(cacheInfo.pdbFilePath) || 
        !fs::exists(cacheInfo.reFilePath)  ) 
    {
	    return false;
    }

    auto sourceLastWriteTime = fs::last_write_time(sourcePath);
    if (sourceLastWriteTime > fs::last_write_time(cacheInfo.csoFilePath) ||
        sourceLastWriteTime > fs::last_write_time(cacheInfo.pdbFilePath) ||
        sourceLastWriteTime > fs::last_write_time(cacheInfo.reFilePath)) 
    {
	    return false;
    }
    return true;
}

static fs::path outputDirectory = ".shaderCache";
static dx12lib::ShaderCacheInfo calcShaderCacheInfo(const fs::path &filePath,
    const D3D_SHADER_MACRO *defines,
    const std::string &entryPoint, const std::string &target)
{
    fs::path cachePath = outputDirectory;
    std::error_code errorCode;
    if (!fs::exists(filePath, errorCode)) {
        Exception::Throw("DXCShader::compileFormMemory args.filePath {} not exist", filePath.string());
    }

    std::vector<std::string> macros;
    if (defines != nullptr) {
        size_t i = 0;
        while (defines[i].Name != nullptr) {
            auto key = defines[i].Name;
            auto value = defines[i].Definition == nullptr ? "1" : defines[i].Definition;
            macros.emplace_back(std::format("_{}#{}", key, value));
        }
        ++i;
    }

    std::stable_sort(macros.begin(), macros.end());
    fs::path baseName = filePath.stem();
    std::string targetFileName = std::to_string(fs::hash_value(filePath));
    targetFileName += std::format("_{}", baseName.string());
    targetFileName += std::format("_{}", entryPoint);
    targetFileName += std::format("_{}", target);
    for (auto &m : macros)
        targetFileName += m;

    dx12lib::ShaderCacheInfo cacheInfo;
    cacheInfo.csoFilePath = (outputDirectory / std::format("{}.cso", targetFileName));
    cacheInfo.pdbFilePath = (outputDirectory / std::format("{}.pdb", targetFileName));
    cacheInfo.reFilePath = (outputDirectory / std::format("{}.re", targetFileName));
    return cacheInfo;
}

auto ShaderLoader::instance() -> ShaderLoader *{
    static ShaderLoader inst;
    return &inst;
}

std::shared_ptr<dx12lib::DXCShader> ShaderLoader::dxc(const fs::path &filePath,
    const std::string &entryPoint,
    const std::string &target,
    const D3D_SHADER_MACRO *defines)
{
    Exception::Throw(fs::exists(filePath), "ShaderLoader::loadDxc filePath {} not exist!", filePath.string());
    auto shaderCacheInfo = calcShaderCacheInfo(filePath, defines, entryPoint, target);

    auto pResult = std::make_shared<dx12lib::DXCShader>();
    if (checkShaderCacheValid(filePath, shaderCacheInfo)) {
        pResult->load(shaderCacheInfo);
        return pResult;
    } 

    auto pInclude = std::make_unique<ShaderInclude>(filePath.parent_path());
    auto shaderSource = ShaderContentLoader::instance()->open(filePath);

    dx12lib::ShaderCompileDesc desc;
    desc.entryPoint = entryPoint;
    desc.target = target;
    desc.pInclude = pInclude.get();
    desc.pMacro = defines;
    desc.pShaderSource = shaderSource.data();
    desc.sizeInByte = shaderSource.size();
    desc.pShaderCacheInfo = &shaderCacheInfo;
    desc.hintName = filePath.string();
    pResult->compile(desc);
    return pResult;
}


}
