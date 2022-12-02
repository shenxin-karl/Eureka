#pragma once
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {

struct RegisterSlot {
	static const RegisterSlot NONE;
	static const RegisterSlot CBV0, CBV1, CBV2, CBV3, CBV4, CBV5, CBV6, CBV7, CBV8;
	static const RegisterSlot SRV0, SRV1, SRV2, SRV3, SRV4, SRV5, SRV6, SRV7, SRV8;
	static const RegisterSlot UAV0, UAV1, UAV2, UAV3, UAV4, UAV5, UAV6, UAV7, UAV8;
public:
	constexpr RegisterSlot() = default;
	constexpr RegisterSlot(const RegisterSlot &) = default;
	constexpr RegisterSlot(D3D12_DESCRIPTOR_RANGE_TYPE type, size_t baseRegister) : index(baseRegister), type(type) {
	}
	constexpr bool isCBV() const {
		return type == D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	}
	constexpr bool isSRV() const {
		return type == D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	}
	constexpr bool isUAV() const {
		return type == D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	}
	constexpr bool isSampler() const {
		return type == D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
	}
	constexpr size_t getRegisterId() const {
		return index;
	}
	constexpr D3D12_DESCRIPTOR_RANGE_TYPE getDescriptorRangeType() const {
		return type;
	}
	constexpr bool valid() const noexcept {
		return index != -1 || static_cast<int>(type) != -1;
	}
	constexpr friend bool operator==(const RegisterSlot &lhs, const RegisterSlot &rhs) noexcept {
		return lhs.type == rhs.type && lhs.index == rhs.index;
	}
	constexpr friend bool operator!=(const RegisterSlot &lhs, const RegisterSlot &rhs) noexcept {
		return !(lhs == rhs);
	}
	friend constexpr RegisterSlot operator+(const RegisterSlot &lhs, size_t rhs) noexcept {
		assert(lhs.valid());
		return { lhs.type, lhs.index + rhs };
	}
	constexpr explicit operator size_t() const {
		return index;
	}
	constexpr explicit operator bool() const {
		return valid();
	}
public:
	size_t index = -1;
	D3D12_DESCRIPTOR_RANGE_TYPE type = static_cast<D3D12_DESCRIPTOR_RANGE_TYPE>(-1);
};

#pragma region RegisterSlot_Static_defination
inline constexpr RegisterSlot RegisterSlot::NONE{};
inline constexpr RegisterSlot RegisterSlot::CBV0{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0 };
inline constexpr RegisterSlot RegisterSlot::CBV1{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1 };
inline constexpr RegisterSlot RegisterSlot::CBV2{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 2 };
inline constexpr RegisterSlot RegisterSlot::CBV3{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 3 };
inline constexpr RegisterSlot RegisterSlot::CBV4{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 4 };
inline constexpr RegisterSlot RegisterSlot::CBV5{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 5 };
inline constexpr RegisterSlot RegisterSlot::CBV6{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 6 };
inline constexpr RegisterSlot RegisterSlot::CBV7{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 7 };
inline constexpr RegisterSlot RegisterSlot::CBV8{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 8 };

inline constexpr RegisterSlot RegisterSlot::SRV0{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0 };
inline constexpr RegisterSlot RegisterSlot::SRV1{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1 };
inline constexpr RegisterSlot RegisterSlot::SRV2{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 2 };
inline constexpr RegisterSlot RegisterSlot::SRV3{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 3 };
inline constexpr RegisterSlot RegisterSlot::SRV4{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 4 };
inline constexpr RegisterSlot RegisterSlot::SRV5{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 5 };
inline constexpr RegisterSlot RegisterSlot::SRV6{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 6 };
inline constexpr RegisterSlot RegisterSlot::SRV7{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 7 };
inline constexpr RegisterSlot RegisterSlot::SRV8{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 8 };

inline constexpr RegisterSlot RegisterSlot::UAV0{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 0 };
inline constexpr RegisterSlot RegisterSlot::UAV1{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1 };
inline constexpr RegisterSlot RegisterSlot::UAV2{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 2 };
inline constexpr RegisterSlot RegisterSlot::UAV3{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 3 };
inline constexpr RegisterSlot RegisterSlot::UAV4{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 4 };
inline constexpr RegisterSlot RegisterSlot::UAV5{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 5 };
inline constexpr RegisterSlot RegisterSlot::UAV6{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 6 };
inline constexpr RegisterSlot RegisterSlot::UAV7{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 7 };
inline constexpr RegisterSlot RegisterSlot::UAV8{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 8 };
#pragma endregion RegisterSlot_Static_defination

struct ShaderRegister {
	RegisterSlot  slot;
	RegisterSpace space = RegisterSpace::Space0;
public:
	constexpr ShaderRegister() = default;
	constexpr ShaderRegister(const ShaderRegister &) = default;
	constexpr ShaderRegister(ShaderRegister &&) noexcept = default;
	constexpr ShaderRegister &operator=(const ShaderRegister &) = default;
	constexpr ShaderRegister &operator=(ShaderRegister &&) noexcept = default;
	constexpr ShaderRegister(RegisterSlot slot, RegisterSpace space = RegisterSpace::Space0) : slot(slot), space(space) {
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
	friend ShaderRegister &operator+=(ShaderRegister &lhs, size_t rhs) noexcept {
		return (lhs = lhs + rhs);
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