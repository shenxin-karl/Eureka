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

char *stb_include_string(char *str, char *inject, char *path_to_includes, char *filename_for_line_directive, char error[256]);

// Concatenate the strings 'strs' and do include-processing on the result. To free the return value, pass it to free()
char *stb_include_strings(char **strs, int count, char *inject, char *path_to_includes, char *filename_for_line_directive, char error[256]);

// Load the file 'filename' and do include-processing on the string therein. note that
// 'filename' is opened directly; 'path_to_includes' is not used. To free the return value, pass it to free()
char *stb_include_file(char *filename, char *inject, char *path_to_includes, char error[256]);