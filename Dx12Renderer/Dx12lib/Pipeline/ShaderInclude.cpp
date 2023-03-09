#include "ShaderInclude.h"
#include "Dx12lib/Tool/DxcModule.h"

namespace dx12lib {

void ShaderInclude::addSearchDirectory(const stdfs::path &path) {
	_searchDirectories.push_back(path);
}

void ShaderInclude::addVirtualFile(const std::string &path, std::string_view source) {
	DxcModule::instance()->getUtils()->CreateBlob(
		source.data(), 
		source.size(), 
		DXC_CP_ACP, 
		&_virtualFiles[path]
	);
}

void ShaderInclude::addVirtualFile(const std::string &path, WRL::ComPtr<IDxcBlobEncoding> pBlob) {
	_virtualFiles[path] = pBlob;
}

auto ShaderInclude::loadSource(const std::string &path) const -> WRL::ComPtr<IDxcBlobEncoding> {
	auto iter = _virtualFiles.find(path);
	if (iter != _virtualFiles.end()) {
		return iter->second;
	}

	for (const auto &directory : _searchDirectories) {
		stdfs::path filePath = directory / path;
		std::error_code errorCode;
		if (stdfs::exists(filePath, errorCode)) {
			WRL::ComPtr<IDxcBlobEncoding> pReturn;
			DxcModule::instance()->getUtils()->LoadFile(
				to_wstring(path).c_str(),
				nullptr,
				&pReturn
			);
			return pReturn;
		}
	}
	return nullptr;
}

}
