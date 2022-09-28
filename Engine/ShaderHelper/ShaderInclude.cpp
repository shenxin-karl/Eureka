#include <fstream>
#include <cassert>
#include <iostream>
#include <cmrc/cmrc.hpp>
#include "ShaderInclude.h"

CMRC_DECLARE(Eureka);

namespace Eureka {

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType, 
	LPCSTR pFileName, 
	LPCVOID pParentData, 
	LPCVOID*ppData,
	UINT *pBytes)
{
    try {
        std::string finalPath;
        switch (IncludeType) {
        case D3D_INCLUDE_LOCAL:
            finalPath = m_ShaderDir + "\\" + pFileName;
            break;
        case D3D_INCLUDE_SYSTEM:
            finalPath = m_SystemDir + "\\" + pFileName;
            break;
        default:
            assert(0);
        }

        std::ifstream includeFile(finalPath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

        if (includeFile.is_open()) {
            UINT fileSize = static_cast<UINT>(includeFile.tellg());
            char *buf = new char[fileSize];
            includeFile.seekg(0, std::ios::beg);
            includeFile.read(buf, fileSize);
            includeFile.close();
            *ppData = buf;
            *pBytes = fileSize;
        } else {
            return E_FAIL;
        }
        return S_OK;
    } catch (std::exception &e) {
        std::cerr << __FUNCTION__ << ": " << e.what() << std::endl;
        return E_FAIL;
    }

}

HRESULT ShaderInclude::Close(LPCVOID pData) {
    const char *buf = static_cast<const char *>(pData);
    delete[] buf;
    return S_OK;
}
}
