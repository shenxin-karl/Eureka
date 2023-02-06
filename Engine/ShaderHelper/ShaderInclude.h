#pragma once
#include "EngineDefinition/EngineDefinition.h"
#include <d3dcommon.h>

namespace Eureka {

class ShaderInclude : public ID3DInclude {
public:
    ShaderInclude(fs::path parentDirectory);
    STDMETHOD(Open)(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override;
    STDMETHOD(Close)(THIS_ LPCVOID pData) override;
private:
    fs::path _parentDirectory;
};

}