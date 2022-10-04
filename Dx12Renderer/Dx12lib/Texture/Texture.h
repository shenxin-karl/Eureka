#pragma once
#include <variant>
#include <Dx12lib/dx12libStd.h>
#include "Dx12lib/Resource/IResource.h"

namespace dx12lib {

enum class TextureDimension {
	UNKNOWN = 0,
	TEXTURE_1D,
	TEXTURE_2D,
	TEXTURE_3D,
};

class Texture : public IResource {
public:
	Texture(std::weak_ptr<Device> pDevice, const D3D12_RESOURCE_DESC &desc, const D3D12_CLEAR_VALUE *pClearValue = nullptr);
	Texture(std::weak_ptr<Device> pDevice, 
		WRL::ComPtr<ID3D12Resource> pResource, 
		D3D12_RESOURCE_STATES state,  
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
	auto getD3DResource() const ->WRL::ComPtr<ID3D12Resource> override;
	auto getDimension() const -> TextureDimension;
	auto getDesc() const -> const D3D12_RESOURCE_DESC &;
	auto getArraySize() const -> size_t;
	auto get2dSRV(size_t mipSlice = 0) const -> const ShaderResourceView &;
	auto get2dUAV(size_t mipSlice = 0) const -> const UnorderedAccessView &;
	auto get2dRTV(size_t mipSlice = 0) const -> const RenderTargetView &;
	auto get2dDSV(size_t mipSlice = 0) const -> const DepthStencilView &;
	auto getPlaneSRV(size_t planeSlice, size_t mipSlice = 0) const -> const ShaderResourceView &;
	auto getPlaneUAV(size_t planeSlice, size_t mipSlice = 0) const -> const UnorderedAccessView &;
	auto getPlaneRTV(size_t planeSlice, size_t mipSlice = 0) const -> const RenderTargetView &;
	auto getPlaneDSV(size_t planeSlice, size_t mipSlice = 0) const -> const DepthStencilView &;
	auto getCubeSRV(size_t mipSlice = 0) const -> const ShaderResourceView &;
	auto getArraySRV(size_t mipSlice = 0) const -> const ShaderResourceView &;
	auto getArrayUAV(size_t mipSlice = 0) const -> const UnorderedAccessView &;
	auto getArrayRTV(size_t mipSlice = 0) const -> const RenderTargetView &;
	auto getArrayDSV(size_t mipSlice = 0) const -> const DepthStencilView &;
	auto getMipLevels() const -> size_t;
	auto getDepthOrArraySize() const -> size_t;
	auto getClearValue() const -> const D3D12_CLEAR_VALUE &;
	~Texture() override;
	static D3D12_RESOURCE_DESC make2D(DXGI_FORMAT format, size_t width, size_t height,
		D3D12_RESOURCE_FLAGS flags, size_t numMipMap = 1
	);
	static D3D12_RESOURCE_DESC makeArray(DXGI_FORMAT format, size_t width, size_t height, size_t arraySize,
		D3D12_RESOURCE_FLAGS flags, size_t numMipMap = 1
	);
	static D3D12_RESOURCE_DESC makeCube(DXGI_FORMAT format, size_t width, size_t height,
		D3D12_RESOURCE_FLAGS flags, size_t numMipMap = 1
	);
	bool checkSRVSupport() const;
	bool checkUAVSupport() const;
	bool checkRTVSupport() const;
	bool checkDSVSupport() const;
	bool checkFormatSupport(D3D12_FORMAT_SUPPORT1 formatSupport1) const;
	bool checkFormatSupport(D3D12_FORMAT_SUPPORT2 formatSupport2) const;
private:
	enum class ViewType {
		Unknown = 0,
		SRV = 1,
		UAV = 2,
		RTV = 3,
		DSV = 4,
	};

	enum class ViewDimension {
		Unknown		= 0,
		VD_2D		= 1,
		VD_ARRAY	= 2,
		VD_CUBE		= 3,
		VD_3D		= 4,
	};

	struct ViewKey {
		ViewType viewType;
		ViewDimension dimension;
		size_t mipSlice;
		size_t first;

		struct Hasher {
			using result_type = std::size_t;
			result_type operator()(const ViewKey &key) const {
				std::hash<std::string_view> hasher;
				auto strView = std::string_view(reinterpret_cast<const char *>(&key), sizeof(key));
				return hasher(strView);
			}
		};
	public:
		ViewKey() {
			std::memset(this, 0, sizeof(*this));
		}
		friend bool operator==(const ViewKey &lhs, const ViewKey &rhs) {
			return std::memcmp(&lhs, &rhs, sizeof(ViewKey)) == 0;
		}
	};

	using ViewMap = std::unordered_map<ViewKey,
		std::variant<ShaderResourceView, UnorderedAccessView, RenderTargetView, DepthStencilView>,
		ViewKey::Hasher
	>;
	void initClearValue(const D3D12_CLEAR_VALUE *pClearValue);
	void initFeatureSupport(ID3D12Device *pDevice, DXGI_FORMAT format);
private:
	mutable ViewMap _viewMap;
	D3D12_CLEAR_VALUE _clearValue;
	D3D12_RESOURCE_DESC _resourceDesc;
	WRL::ComPtr<ID3D12Resource> _pResource;
	D3D12_FEATURE_DATA_FORMAT_SUPPORT _formatSupport;
	bool _isSupportRTV = false;
	bool _isSupportDSV = false;
	bool _isSupportUAV = false;
	bool _isSupportSRV = false;
};

bool hasAlpha(DXGI_FORMAT format);
bool isUAVCompatibleFormat(DXGI_FORMAT format);
bool isSRGBFormat(DXGI_FORMAT format);
bool isBGRFormat(DXGI_FORMAT format);
bool isDepthFormat(DXGI_FORMAT format);
bool hasStencilFormat(DXGI_FORMAT format);
DXGI_FORMAT getDepthDSVFormat(DXGI_FORMAT format);
DXGI_FORMAT getDepthSRVFormat(DXGI_FORMAT format);
DXGI_FORMAT getSRGBFormat(DXGI_FORMAT format, bool hasStencil);
DXGI_FORMAT getUAVCompatableFormat(DXGI_FORMAT format);
DXGI_FORMAT getTypelessFormat(DXGI_FORMAT format);


}


