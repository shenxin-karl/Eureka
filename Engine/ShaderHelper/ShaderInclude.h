#pragma once
#include <d3dcommon.h>
#include <string>

namespace Eureka {

class ShaderInclude : public ID3DInclude {
public:
    ShaderInclude(std::string &&shaderDir, std::string &&systemDir);
    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override;
    HRESULT __stdcall Close(LPCVOID pData) override;
private:
    std::string _shaderDir;
    std::string _systemDir;
};

}
