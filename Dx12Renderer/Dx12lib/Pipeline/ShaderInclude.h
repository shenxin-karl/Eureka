#pragma once
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <Windows.h>
#include <dxcapi.h>
#include <wrl.h>
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {

namespace stdfs = std::filesystem;
namespace WRL = Microsoft::WRL;

class ShaderInclude : public NonCopyable {
public:
	void addSearchDirectory(const stdfs::path &path);
	void addVirtualFile(const std::string &path, std::string_view source);
	void addVirtualFile(const std::string &path, WRL::ComPtr<IDxcBlobEncoding> pBlob);
	auto loadSource(const std::string &path) const -> WRL::ComPtr<IDxcBlobEncoding>;
private:
	using VirtualFileMap = std::unordered_map<std::string, WRL::ComPtr<IDxcBlobEncoding>>;
	std::vector<stdfs::path>	_searchDirectories;
	VirtualFileMap				_virtualFiles;
};

}
