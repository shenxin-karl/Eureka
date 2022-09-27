#pragma once
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {

struct RegisterSlot {
	enum Slot : size_t {
		NONE = -1,
		CBVBegin = 0, SRVBegin = 10, UAVBegin = 20, SamplerBegin = 30,
		CBV0 = 0, SRV0 = 10, UAV0 = 20, Sampler0 = 30,
		CBV1 = 1, SRV1 = 11, UAV1 = 21, Sampler1 = 31,
		CBV2 = 2, SRV2 = 12, UAV2 = 22, Sampler2 = 32,
		CBV3 = 3, SRV3 = 13, UAV3 = 23, Sampler3 = 33,
		CBV4 = 4, SRV4 = 14, UAV4 = 24, Sampler4 = 34,
		CBV5 = 5, SRV5 = 15, UAV5 = 25, Sampler5 = 35,
		CBV6 = 6, SRV6 = 16, UAV6 = 26, Sampler6 = 36,
		CBV7 = 7, SRV7 = 17, UAV7 = 27, Sampler7 = 37,
		CBV8 = 8, SRV8 = 18, UAV8 = 28, Sampler8 = 38,
		CBVEnd = 9, SRVEnd = 19, UAVEnd = 29, SamplerEnd = 39,
	};
public:
	constexpr RegisterSlot(Slot slot) : slot(slot) {
	}

	constexpr RegisterSlot(D3D12_DESCRIPTOR_RANGE_TYPE type, size_t baseRegister) {
		assert(baseRegister < 9);
		switch (type) {
		case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
			slot = static_cast<Slot>(CBVBegin + baseRegister);
			break;
		case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
			slot = static_cast<Slot>(UAVBegin + baseRegister);
			break;
		case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
			slot = static_cast<Slot>(SRVBegin + baseRegister);
			break;
		case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
			slot = static_cast<Slot>(SamplerBegin + baseRegister);
			break;
		default:
			assert(false);
			break;
		}
	}
	constexpr RegisterSlot(const RegisterSlot &) = default;

	constexpr bool isCBV() const {
		return slot >= CBVBegin && slot < CBVEnd;
	}

	constexpr bool isSRV() const {
		return slot >= SRVBegin && slot < SRVEnd;
	}

	constexpr bool isUAV() const {
		return slot >= UAVBegin && slot < UAVEnd;
	}

	constexpr bool isSampler() const {
		return slot >= SamplerBegin && slot < SamplerEnd;
	}

	size_t getRegisterId() const {
		if (isCBV())
			return slot - CBVBegin;
		if (isSRV())
			return slot - SRVBegin;
		if (isUAV())
			return slot - UAVBegin;
		if (isSampler())
			return slot - SamplerBegin;
		assert(false);
		return static_cast<size_t>(-1);
	}

	D3D12_DESCRIPTOR_RANGE_TYPE getDescriptorRangeType() const {
		if (isCBV())
			return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		if (isSRV())
			return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		if (isUAV())
			return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		if (isSampler())
			return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
		assert(false);
		return static_cast<D3D12_DESCRIPTOR_RANGE_TYPE>(-1);
	}

	bool valid() const noexcept {
		return isCBV() || isSRV() || isUAV() || isSampler();
	}

	constexpr friend bool operator==(const RegisterSlot &lhs, const RegisterSlot &rhs) noexcept {
		return lhs.slot == rhs.slot;
	}

	constexpr friend bool operator!=(const RegisterSlot &lhs, const RegisterSlot &rhs) noexcept {
		return !(lhs == rhs);
	}

	friend RegisterSlot operator+(const RegisterSlot &lhs, size_t rhs) noexcept {
		RegisterSlot res(static_cast<RegisterSlot::Slot>(lhs.slot + rhs));
		assert(res.getRegisterId() != static_cast<size_t>(-1));
		return res;
	}

	constexpr explicit operator size_t() const {
		return static_cast<size_t>(slot);
	}

	explicit operator bool() const {
		return valid();
	}
public:
	Slot slot;
};

struct ShaderRegister {
	RegisterSlot  slot   = RegisterSlot::NONE;
	RegisterSpace space  = RegisterSpace::Space0;
public:
	constexpr ShaderRegister() = default;
	constexpr ShaderRegister(const ShaderRegister &) = default;
	constexpr ShaderRegister(ShaderRegister &&) noexcept = default;
	constexpr ShaderRegister &operator=(const ShaderRegister &) = default;
	constexpr ShaderRegister &operator=(ShaderRegister &&) noexcept = default;
	constexpr ShaderRegister(RegisterSlot::Slot slot) : slot(slot), space(RegisterSpace::Space0) {
	}
	constexpr ShaderRegister(RegisterSlot slot, RegisterSpace space) : slot(slot), space(space) {
	};
	constexpr friend bool operator==(const ShaderRegister &lhs, const ShaderRegister &rhs) {
		return lhs.slot == rhs.slot && lhs.space == rhs.space;
	}
	constexpr friend bool operator!=(const ShaderRegister &lhs, const ShaderRegister &rhs) {
		return !(lhs == rhs);
	}
	friend ShaderRegister operator+(ShaderRegister lhs, size_t rhs) noexcept {
		RegisterSlot slot = lhs.slot + rhs;
		return { slot, lhs.space };
	}
};

struct ShaderRegisterHasher {
	size_t operator()(const ShaderRegister &shaderRegister) const noexcept {
		std::hash<size_t> hasher;
		size_t hashValue0 = hasher(static_cast<size_t>(shaderRegister.slot));
		size_t hashValue1 = hasher(static_cast<size_t>(shaderRegister.space));
		return hashValue0 ^ (hashValue1 >> 1);
	}
};

}

namespace std {

template<>
struct hash<dx12lib::ShaderRegister> {
	using result_type = std::size_t;
	result_type operator()(const dx12lib::ShaderRegister &s) const noexcept {
		dx12lib::ShaderRegisterHasher hasher;
		return hasher(s);
	}
};

}