#pragma once
#include "EngineDefinition/EngineDefinition.h"
#include <d3dcommon.h>

namespace Eureka {

class ShaderInclude : public ID3DInclude {
public:
    ShaderInclude(fs::path parentDirectory);
    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override;
    HRESULT __stdcall Close(LPCVOID pData) override;
private:
    fs::path _parentDirectory;
};

}