#include "DXCShader.h"
#include <format>
#include <filesystem>
#include <fstream>
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
        if (!desc.pShaderCacheInfo->refFilePath.empty()) {
            compileFlags.push_back(L"-Fre");
            compileFlags.push_back(to_wstring(desc.pShaderCacheInfo->refFilePath.string()));
        }
    }

    for (size_t i = 0; desc.pMacro != nullptr && desc.pMacro[i].Name != nullptr; ++i) {
        auto key = desc.pMacro[i].Name;
        auto value = desc.pMacro[i].Definition == nullptr ? "1" : desc.pMacro[i].Definition;
        compileFlags.emplace_back(to_wstring(std::format("-D{}={}", key, value)));
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

    // byteCode
    WRL::ComPtr<IDxcBlob> pByteCode = nullptr;
    pResults->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&pByteCode), nullptr);
    D3DException::Throw(pByteCode != nullptr, "DXCShader::compile pByteCode is nullptr");
    _pByteCode = pByteCode.Detach();

    // reflection 
    WRL::ComPtr<IDxcBlob> pReflectionData;
    pResults->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&pReflectionData), nullptr);
    D3DException::Throw(pReflectionData != nullptr, "DXCShader::compile pReflectionData is nullptr");
    DxcBuffer reflectionData {
        .Ptr = pReflectionData->GetBufferPointer(),
        .Size = pReflectionData->GetBufferSize(),
        .Encoding = DXC_CP_ACP,
    };
    gDxcModel.getUtils()->CreateReflection(&reflectionData, IID_PPV_ARGS(&_pShaderReflection));

    // pdb
    WRL::ComPtr<IDxcBlob> pdb = nullptr;
    pResults->GetOutput(DXC_OUT_PDB, IID_PPV_ARGS(&pdb), nullptr);
    D3DException::Throw(pdb != nullptr, "DXCShader::compile pdb is nullptr");

    // white to file
    if (desc.pShaderCacheInfo != nullptr) {
        if (!desc.pShaderCacheInfo->csoFilePath.empty()) {
            std::fstream csoFile(desc.pShaderCacheInfo->csoFilePath, std::ios::binary | std::ios::out);
            Exception::Throw(csoFile.is_open(), "can not write cso file {}", desc.pShaderCacheInfo->csoFilePath.string());
            csoFile.write(static_cast<const char*>(_pByteCode->GetBufferPointer()), _pByteCode->GetBufferSize());
            csoFile.close();
        }
        if (!desc.pShaderCacheInfo->pdbFilePath.empty()) {
            std::fstream pdbFile(desc.pShaderCacheInfo->pdbFilePath, std::ios::binary | std::ios::out);
            Exception::Throw(pdbFile.is_open(), "can not write pdb file {}", desc.pShaderCacheInfo->pdbFilePath.string());
            pdbFile.write(static_cast<const char *>(pdb->GetBufferPointer()), pdb->GetBufferSize());
            pdbFile.close();
        }
        if (!desc.pShaderCacheInfo->refFilePath.empty()) {
            std::fstream pdbFile(desc.pShaderCacheInfo->refFilePath, std::ios::binary | std::ios::out);
            Exception::Throw(pdbFile.is_open(), "can not write pdb file {}", desc.pShaderCacheInfo->refFilePath.string());
            pdbFile.write(static_cast<const char *>(pReflectionData->GetBufferPointer()), pReflectionData->GetBufferSize());
            pdbFile.close();
        }
    }
}

void DXCShader::load(const ShaderCacheInfo &cacheInfo) {
    std::wstring csoFilePath = to_wstring(cacheInfo.csoFilePath.string());
    std::wstring reFilePath = to_wstring(cacheInfo.refFilePath.string());

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
