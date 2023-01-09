#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cassert>
#include <iostream>
#include "ShaderInclude.h"

#include "ShaderContentLoader.h"
#include "ShaderLoader.h"
#include "Foundation/Exception.h"


namespace Eureka {

ShaderInclude::ShaderInclude(fs::path parentDirectory)
: _parentDirectory(std::move(parentDirectory)) {

}

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType,
    LPCSTR pFileName,
    LPCVOID pParentData,
    LPCVOID *ppData,
    UINT *pBytes)
{
    fs::path finalPath = _parentDirectory / pFileName;
    auto view = ShaderContentLoader::instance()->open(finalPath);
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