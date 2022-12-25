#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cassert>
#include <iostream>
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Foundation/Exception.h"


namespace Eureka {

ShaderInclude::ShaderInclude(std::string &&shaderDir)
: _shaderDir(std::move(shaderDir)) {

}

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType,
    LPCSTR pFileName,
    LPCVOID pParentData,
    LPCVOID *ppData,
    UINT *pBytes)
{
    std::string finalPath = _shaderDir + "/" + pFileName;
    auto view = ShaderLoader::instance()->open(finalPath);
    if (view.length() > 0) {
        *ppData = view.data();
        *pBytes = static_cast<UINT>(view.size());
        return S_OK;
    }

    Exception::Throw("include file {} not found", pFileName);
    return E_FAIL;
}

HRESULT ShaderInclude::Close(LPCVOID pData) {
    return S_OK;
}

}