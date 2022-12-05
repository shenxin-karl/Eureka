#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cassert>
#include <iostream>
#include <cmrc/cmrc.hpp>
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Foundation/Exception.h"

CMRC_DECLARE(Eureka);

namespace Eureka {

ShaderInclude::ShaderInclude(std::string &&shaderDir, std::string &&systemDir)
: _shaderDir(std::move(shaderDir)), _systemDir(std::move(systemDir))
{
}

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType,
    LPCSTR pFileName,
    LPCVOID pParentData,
    LPCVOID *ppData,
    UINT *pBytes)
{
    if (IncludeType == D3D_INCLUDE_LOCAL) {
        std::string finalPath = _shaderDir + "/" + pFileName;
        auto view = ShaderLoader::instance()->open(finalPath);
        if (view.length() > 0) {
            *ppData = view.data();
            *pBytes = static_cast<UINT>(view.size());
        }
    }

    if (IncludeType == D3D_INCLUDE_LOCAL || IncludeType == D3D_INCLUDE_SYSTEM) {
        std::string finalPath = _systemDir + "/" + pFileName;
        auto fs = cmrc::Eureka::get_filesystem();
        if (fs.exists(finalPath)) {
            cmrc::file file = fs.open(finalPath);
            *ppData = file.begin();
            *pBytes = static_cast<UINT>(file.size());;
            return S_OK;
        }
    }

    Exception::Throw("include file {} not found", pFileName);
    return E_FAIL;
}

HRESULT ShaderInclude::Close(LPCVOID pData) {
    return S_OK;
}

}