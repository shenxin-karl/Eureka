#include "IShader.h"

#include <filesystem>
#include <fstream>

namespace dx12lib {

auto IShader::getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection> {
    return _pShaderReflection;
}

void IShader::compileFormFile(const CompileFormFileArgs &args) {
    std::ifstream fin(args.filePath, std::ios::in);
    if (!fin.is_open())
        return;

	std::stringstream sbuf;
	sbuf << fin.rdbuf();
    auto content = sbuf.str();

    CompileFormMemoryArgs memoryArgs;
	static_cast<CompileFormFileArgs &>(memoryArgs) = args;
    memoryArgs.pData = content.data();
    memoryArgs.sizeInByte = content.length();
    compileFormMemory(memoryArgs);
    fin.close();
}

IShader::ShaderCacheInfo IShader::calcShaderCacheInfo(const CompileFormFileArgs &args) {
    namespace fs = std::filesystem;
    fs::path filePath(args.filePath);
    fs::path directory = filePath.parent_path();
    fs::path outputDirectory(args.outputDirectory);

    namespace fs = std::filesystem;
    std::error_code errorCode;
    if (!fs::exists(filePath, errorCode)) {
        Exception::Throw(
            "DXCShader::compileFormMemory args.filePath {} not exist",
            args.filePath
        );
    }
    if (!fs::is_directory(outputDirectory, errorCode)) {
        Exception::Throw(
            "DXCShader::compileFormMemory args.outputDirectory {} invalid",
            args.outputDirectory
        );
    }

    std::vector<std::string> macros;
    if (args.pMacro != nullptr) {
	    size_t i = 0;
	    while (args.pMacro[i].Name != nullptr) {
            auto key = args.pMacro[i].Name;
            auto value = args.pMacro[i].Definition == nullptr ? "1" : args.pMacro[i].Definition;
            macros.emplace_back(std::format("_{}#{}", key, value));
        }
        ++i;
    }

    std::stable_sort(macros.begin(), macros.end());
    fs::path baseName = filePath.stem();
    std::string targetFileName = (directory / baseName).string();
    targetFileName += std::format("_{}", args.entryPoint);
    targetFileName += std::format("_{}", args.target);
    for (auto &m : macros)
        targetFileName += m;

    ShaderCacheInfo cacheInfo;
    cacheInfo.csoFilePath = (outputDirectory / std::format("{}.cso", targetFileName)).string();
    cacheInfo.pdbFilePath = (outputDirectory / std::format("{}.pdb", targetFileName)).string();
    cacheInfo.reFilePath = (outputDirectory / std::format("{}.re", targetFileName)).string();
    return cacheInfo;
}

}
