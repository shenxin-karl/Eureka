#include <fstream>
#include <cassert>
#include <iostream>
#include <cmrc/cmrc.hpp>
#include "ShaderInclude.h"

CMRC_DECLARE(Eureka);

namespace Eureka {

ShaderInclude::ShaderInclude(std::string &&shaderDir, std::string &&systemDir)
: _shaderDir(std::move(shaderDir)), _systemDir(std::move(systemDir))
{
}

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType, 
    LPCSTR pFileName, 
    LPCVOID pParentData, 
    LPCVOID*ppData,
    UINT *pBytes)
{
    if (IncludeType == D3D_INCLUDE_LOCAL) {
        try {
            std::string finalPath = _shaderDir + "/" + pFileName;
            std::ifstream includeFile(finalPath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
            if (includeFile.is_open()) {
                UINT fileSize = static_cast<UINT>(includeFile.tellg());
                char *buf = new char[fileSize];
                includeFile.seekg(0, std::ios::beg);
                includeFile.read(buf, fileSize);
                includeFile.close();
                *ppData = buf;
                *pBytes = fileSize;
                return S_OK;
            }
        } catch (std::exception &e) {
            std::cerr << __FUNCTION__ << ": " << e.what() << std::endl;
            return E_FAIL;
        }
    }

    if (IncludeType == D3D_INCLUDE_LOCAL || IncludeType == D3D_INCLUDE_SYSTEM) {
        std::string finalPath = _systemDir + "/" + pFileName;
        auto fs = cmrc::Eureka::get_filesystem();
        if (fs.exists(finalPath)) {
            cmrc::file file = fs.open(finalPath);
            UINT fileSize = static_cast<UINT>(file.size());
            char *buf = new char[fileSize];
            std::memcpy(buf, file.begin(), file.size());
            *ppData = buf;
            *pBytes = fileSize;
            return S_OK;
        }
    }
    return E_FAIL;
}

HRESULT ShaderInclude::Close(LPCVOID pData) {
    const char *buf = static_cast<const char *>(pData);
    delete[] buf;
    return S_OK;
}
}
