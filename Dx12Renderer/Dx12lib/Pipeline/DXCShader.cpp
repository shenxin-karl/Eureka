#include "DXCShader.h"
#include <format>
#include <filesystem>
#include "Dx12lib/Tool/DxcModule.h"

namespace dx12lib {

thread_local DxcModule gDxcModel;

auto DXCShader::getByteCode() const -> D3D12_SHADER_BYTECODE {
	if (_pByteCode == nullptr)
		return { nullptr, 0 };
	return { _pByteCode->GetBufferPointer(), _pByteCode->GetBufferSize() };
}

struct DXCInclude : public IDxcIncludeHandler {
    ULONG STDMETHODCALLTYPE AddRef(void) final {
	    return 0;
    }
    ULONG STDMETHODCALLTYPE Release(void) final {
		return 0;   
    }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final {
        ppvObject = nullptr;
        return E_FAIL;
    }

	HRESULT STDMETHODCALLTYPE LoadSource(
        _In_z_ LPCWSTR pFilename,                                 // Candidate filename.
        _COM_Outptr_result_maybenull_ IDxcBlob **ppIncludeSource  // Resultant source object for included file, nullptr if not found.
    ) override
	{
        UINT bytes = 0;
        LPCVOID pData = nullptr;
        std::string fileName = to_string(pFilename);
		auto hr = pInclude->Open(D3D_INCLUDE_LOCAL, fileName.c_str(), nullptr, &pData, &bytes);
        if (pData == nullptr) {
	        ppIncludeSource = nullptr;
            return hr;
        }

        WRL::ComPtr<IDxcBlobEncoding> pSource;
        gDxcModel.getDxcUtils()->CreateBlob(pData, bytes, DXC_CP_ACP, &pSource);
        *ppIncludeSource = pSource.Detach();
        return hr;
	}
public:
    ID3DInclude *pInclude;
};

void DXCShader::compileFormMemory(const CompileFormMemoryArgs &args) {
    auto *pUtils = gDxcModel.getDxcUtils();
    auto *pCompiler = gDxcModel.getDxcCompiler3();

    std::wstring filePath = to_wstring(args.filePath);
    std::wstring target = to_wstring(args.target);
    std::wstring entryPoint = to_wstring(args.entryPoint);
    
    auto catchInfo = calcShaderCacheInfo(args);
    auto pdbFilePath = to_wstring(catchInfo.pdbFilePath);
    auto csoFilePath = to_wstring(catchInfo.csoFilePath);
    auto reFilePath = to_wstring(catchInfo.reFilePath);

    std::vector<std::wstring> compileFlags = {
        filePath.c_str(),           
        L"-E", entryPoint.c_str(),  
        L"-T", target.c_str(),      
        L"-Fo", csoFilePath.c_str(), 
        L"-Fd", pdbFilePath.c_str(),
        L"-Fre", reFilePath.c_str(),
        L"-Zi",                     
        L"-Qstrip_rootsignature",
    	L"-nologo",
    };

#if defined(DEBUG) || defined(_DEBUG) 
    args.push_back(L"-Od");
#endif

    if (args.pMacro != nullptr) {
	    size_t i = 0;
	    while (args.pMacro[i].Name != nullptr) {
            auto key = args.pMacro[i].Name;
            auto value = args.pMacro[i].Definition == nullptr ? "1" : args.pMacro[i].Definition;
	        auto flag = std::format("-D%s=%s", key, value);
	        compileFlags.push_back(to_wstring(flag));
        }
    }

    std::vector<LPCWCHAR> pszArgs(compileFlags.size());
    for (size_t i = 0; i < compileFlags.size(); ++i)
        pszArgs.push_back(compileFlags[i].c_str());

    IDxcIncludeHandler *pIncludeHandler;
    WRL::ComPtr<IDxcIncludeHandler> pIncludeHandleCom;
    std::unique_ptr<DXCInclude> pDxcInclude;
    if (args.pInclude == D3D_COMPILE_STANDARD_FILE_INCLUDE) {
        pUtils->CreateDefaultIncludeHandler(&pIncludeHandleCom);
        pIncludeHandler = pIncludeHandleCom.Get();
    } else {
        pDxcInclude = std::make_unique<DXCInclude>();
        pDxcInclude->pInclude = args.pInclude;
        pIncludeHandler = pDxcInclude.get();
	}

    DxcBuffer source;
    source.Ptr = args.pData;
    source.Size = args.sizeInByte;
    source.Encoding = DXC_CP_ACP; // Assume BOM says UTF8 or UTF16 or this is ANSI text.
    WRL::ComPtr<IDxcResult> pResults;
    pCompiler->Compile(
        &source,                // Source buffer.
        pszArgs.data(),         // Array of pointers to arguments.
        pszArgs.size(),         // Number of arguments.
        pIncludeHandler,        // User-provided interface to handle #include directives (optional).
        IID_PPV_ARGS(&pResults) // Compiler output status, buffer, and errors.
    );

    HRESULT hrStatus;
    pResults->GetStatus(&hrStatus);
	ThrowIfFailed(hrStatus);

    WRL::ComPtr<IDxcBlob> pReflectionData;
    pResults->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&pReflectionData), nullptr);
    if (pReflectionData != nullptr) {
        DxcBuffer reflectionData;
        reflectionData.Encoding = DXC_CP_ACP;
        reflectionData.Ptr = pReflectionData->GetBufferPointer();
        reflectionData.Size = pReflectionData->GetBufferSize();
        pUtils->CreateReflection(&reflectionData, IID_PPV_ARGS(&_pShaderReflection));
    }
}

void DXCShader::makeFromByteCode(const void *pData, size_t sizeInByte) {
    NotImplementedException::Throw();
}

}
