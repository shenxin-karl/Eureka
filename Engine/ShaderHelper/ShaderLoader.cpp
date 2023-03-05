#include "ShaderLoader.h"
#include "ShaderContentLoader.h"
#include "ShaderInclude.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "Foundation/Exception.h"
#include "Objects/PathManager.h"

namespace Eureka {

const std::string ShaderLoader::CompileMode = EUREKA_COMPILE_MODE;

ShaderLoader::ShaderLoader() : _uuidGenerator(classUUID) {
}

void ShaderLoader::initialize() {
    auto targetDirectory = PathManager::toTempPath(outputDirectory);
    if (!fs::exists(targetDirectory)) {
        fs::create_directory(targetDirectory);
    }
}

std::shared_ptr<dx12lib::DXCShader> ShaderLoader::dxc(const fs::path &filePath,
    const std::string &entryPoint,
    const std::string &target,
    const D3D_SHADER_MACRO *defines)
{
    Exception::Throw(fs::exists(filePath), 
        "ShaderLoader::loadDxc filePath {} not exist!", filePath.string()
    );
    auto shaderCacheKey = calcShaderCacheKey(filePath, defines, entryPoint, target);
    dx12lib::ShaderCacheInfo shaderCacheInfo = getShaderCacheInfo(shaderCacheKey);

    auto pResult = std::make_shared<dx12lib::DXCShader>();
    auto lastWriteTime = fs::last_write_time(filePath);
    if (checkShaderCacheValid(lastWriteTime, shaderCacheInfo)) {
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

std::shared_ptr<dx12lib::DXCShader> ShaderLoader::dxc(const DxcCompileDesc1 &args) {
    auto shaderCacheKey = calcShaderCacheKey(
        args.filePath, 
        args.defines, 
        args.entryPoint, 
        args.target
    );

    auto pResult = std::make_shared<dx12lib::DXCShader>();
    auto lastWriteTime = args.lastWriteTime;
    dx12lib::ShaderCacheInfo shaderCacheInfo = getShaderCacheInfo(shaderCacheKey);
    if (checkShaderCacheValid(lastWriteTime, shaderCacheInfo)) {
        pResult->load(shaderCacheInfo);
        return pResult;
    }

    dx12lib::ShaderCompileDesc desc;
    desc.entryPoint = args.entryPoint;
    desc.target = args.target;
    desc.pInclude = args.include;
    desc.pMacro = args.defines;
    desc.pShaderSource = args.source.data();
    desc.sizeInByte = args.source.size();
    desc.pShaderCacheInfo = &shaderCacheInfo;
    desc.hintName = args.filePath;
    pResult->compile(desc);
    return pResult;
}

bool ShaderLoader::checkShaderCacheValid(const fs::file_time_type &lastWriteTime, const dx12lib::ShaderCacheInfo &cacheInfo) {
    if (!fs::exists(cacheInfo.csoFilePath) ||
        !fs::exists(cacheInfo.pdbFilePath) ||
        !fs::exists(cacheInfo.refFilePath))
    {
        return false;
    }

    if (lastWriteTime > fs::last_write_time(cacheInfo.csoFilePath) ||
        lastWriteTime > fs::last_write_time(cacheInfo.pdbFilePath) ||
        lastWriteTime > fs::last_write_time(cacheInfo.refFilePath) )
    {
        return false;
    }
    return true;
}

std::string ShaderLoader::calcShaderCacheKey(const fs::path &filePath, const D3D_SHADER_MACRO *defines,
                                             const std::string &entryPoint, const std::string &target)
{
    std::error_code errorCode;
    if (!fs::exists(filePath, errorCode)) {
        Exception::Throw("DXCShader::compileFormMemory args.filePath {} not exist", filePath.string());
    }

    std::vector<std::string> macros;
    for (size_t i = 0; defines != nullptr && defines[i].Name != nullptr; ++i) {
        auto key = defines[i].Name;
        auto value = defines[i].Definition == nullptr ? "1" : defines[i].Definition;
        macros.emplace_back(fmt::format("_{}#{}", key, value));
    }

    std::ranges::stable_sort(macros);
    fs::path baseName = filePath.stem();
    std::string targetFileName = std::to_string(fs::hash_value(filePath));
    targetFileName += fmt::format("_{}", baseName.string());
    targetFileName += fmt::format("_{}", entryPoint);
    targetFileName += fmt::format("_{}", target);
    for (auto &m : macros)
        targetFileName += m;
    return targetFileName;
}

dx12lib::ShaderCacheInfo ShaderLoader::getShaderCacheInfo(const std::string &shaderCacheKey) {
    auto csoUUID = UUID::to_string(instance()->_uuidGenerator.newUUID(shaderCacheKey + ".cso"));
    auto pdbUUID = UUID::to_string(instance()->_uuidGenerator.newUUID(shaderCacheKey + ".pdb"));
    auto refUUID = UUID::to_string(instance()->_uuidGenerator.newUUID(shaderCacheKey + ".ref"));
    std::string csoFileName = fmt::format("{}_{}.cso", CompileMode, csoUUID);
    std::string pdbFileName = fmt::format("{}_{}.pdb", CompileMode, pdbUUID);
    std::string refFileName = fmt::format("{}_{}.ref", CompileMode, refUUID);
    dx12lib::ShaderCacheInfo cacheInfo;
    auto cachePath = PathManager::toTempPath(outputDirectory);
    cacheInfo.csoFilePath = cachePath / csoFileName;
    cacheInfo.pdbFilePath = cachePath / pdbFileName;
    cacheInfo.refFilePath = cachePath / refFileName;
    return cacheInfo;
}


}
