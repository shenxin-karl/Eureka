#pragma once
#include <d3dcommon.h>
#include <string>

namespace Eureka {

class ShaderInclude : public ID3DInclude {
public:
    ShaderInclude(const char *shaderDir, const char *systemDir) : m_ShaderDir(shaderDir), m_SystemDir(systemDir) {}
    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override;
    HRESULT __stdcall Close(LPCVOID pData) override;
private:
    std::string m_ShaderDir;
    std::string m_SystemDir;
};

}
