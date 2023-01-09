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

struct DxcInclude : public IDxcIncludeHandler {
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
        gDxcModel.getUtils()->CreateBlob(pData, bytes, DXC_CP_ACP, &pSource);
        *ppIncludeSource = pSource.Detach();
        return hr;
	}
public:
    ID3DInclude *pInclude = nullptr;
};

void DXCShader::compile(const ShaderCompileDesc &desc) {
    std::vector<std::wstring> compileFlags = {
	    L"-E", to_wstring(desc.entryPoint),
	    L"-T", to_wstring(desc.target),
	    L"-Zi",
	    L"-Qstrip_rootsignature",
	    L"-nologo",
    };

    if (desc.pShaderCacheInfo != nullptr) {
        if (!desc.pShaderCacheInfo->csoFilePath.empty()) {
			compileFlags.push_back(L"-Fo");
            compileFlags.push_back(to_wstring(desc.pShaderCacheInfo->csoFilePath.string()));
        }
        if (!desc.pShaderCacheInfo->pdbFilePath.empty()) {
            compileFlags.push_back(L"-Fd");
            compileFlags.push_back(to_wstring(desc.pShaderCacheInfo->pdbFilePath.string()));
        }
        if (!desc.pShaderCacheInfo->reFilePath.empty()) {
            compileFlags.push_back(L"-Fre");
            compileFlags.push_back(to_wstring(desc.pShaderCacheInfo->reFilePath.string()));
        }
    }

    std::vector<LPCWSTR> arguments;
    for (const auto &flag : compileFlags)
        arguments.push_back(flag.c_str());

    Exception::Throw(desc.pShaderCacheInfo != nullptr, "DXCShader::compile desc.pShaderSource is nullptr");
    Exception::Throw(desc.sizeInByte != 0, "DXCShader::compile desc.sizeInByte is zero");

    DxcBuffer source {
        .Ptr = desc.pShaderSource,
        .Size = desc.sizeInByte,
        .Encoding =  DXC_CP_ACP,
    };

    IDxcIncludeHandler *pIncludeHandler;
    WRL::ComPtr<IDxcIncludeHandler> pIncludeHandleCom;
    std::unique_ptr<DxcInclude> pDxcInclude;
    if (desc.pInclude == D3D_COMPILE_STANDARD_FILE_INCLUDE) {
        gDxcModel.getUtils()->CreateDefaultIncludeHandler(&pIncludeHandleCom);
        pIncludeHandler = pIncludeHandleCom.Get();
    } else {
        pDxcInclude = std::make_unique<DxcInclude>();
        pDxcInclude->pInclude = desc.pInclude;
        pIncludeHandler = pDxcInclude.get();
    }

    WRL::ComPtr<IDxcResult> pResults;
    gDxcModel.getCompiler3()->Compile(
        &source,                
        arguments.data(),
        arguments.size(),
        pIncludeHandler,        
        IID_PPV_ARGS(&pResults) 
    );

    HRESULT compileStatus;
    pResults->GetStatus(&compileStatus);
    if (FAILED(compileStatus)) {
        WRL::ComPtr<IDxcBlobUtf8> pErrorMsg;
        pResults->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&pErrorMsg), nullptr);
        std::string errorMessage(
            static_cast<char*>(pErrorMsg->GetBufferPointer()), 
            pErrorMsg->GetBufferSize()
        );
        D3DException::Throw(compileStatus, errorMessage);
    }

    WRL::ComPtr<IDxcBlob> pReflectionData;
    pResults->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&pReflectionData), nullptr);
    if (pReflectionData != nullptr) {
        DxcBuffer reflectionData {
            .Ptr = pReflectionData->GetBufferPointer(),
            .Size = pReflectionData->GetBufferSize(),
            .Encoding = DXC_CP_ACP,
        };
        gDxcModel.getUtils()->CreateReflection(&reflectionData, IID_PPV_ARGS(&_pShaderReflection));
    }
}

void DXCShader::load(const ShaderCacheInfo &cacheInfo) {
    std::wstring csoFilePath = to_wstring(cacheInfo.csoFilePath.string());
    std::wstring reFilePath = to_wstring(cacheInfo.reFilePath.string());

    // load cso info
    WRL::ComPtr<IDxcBlobEncoding> pCsoBlob;
    gDxcModel.getLibrary()->CreateBlobFromFile(
        csoFilePath.c_str(),
        DXC_CP_ACP,
        &pCsoBlob
    );
    _pByteCode = pCsoBlob.Detach();

    // load shader reflection info
    WRL::ComPtr<IDxcBlobEncoding> pReflectionData;
    gDxcModel.getLibrary()->CreateBlobFromFile(
        csoFilePath.c_str(),
        DXC_CP_ACP,
        &pReflectionData
    );
    Exception::Throw(pReflectionData != nullptr, "DXCShader::load pReflectionData == nullptr");
    DxcBuffer reflectionData{
	    .Ptr = pReflectionData->GetBufferPointer(),
	    .Size = pReflectionData->GetBufferSize(),
	    .Encoding = DXC_CP_ACP,
    };
    gDxcModel.getUtils()->CreateReflection(&reflectionData, IID_PPV_ARGS(&_pShaderReflection));
}

}
