#pragma once
#include <bitset>

namespace rgph {

// TechniqueType
// todo: 为什么不直接使用 size_t, 因为这样是类型安全的
struct TechniqueType {
	constexpr TechniqueType() = default;
	constexpr explicit TechniqueType(size_t techniqueType) : _techniqueType(techniqueType) {}
	constexpr TechniqueType(const TechniqueType &) = default;
	constexpr TechniqueType(TechniqueType &&) = default;
	constexpr TechniqueType &operator=(const TechniqueType &) = default;
	constexpr TechniqueType &operator=(TechniqueType &&) = default;
	constexpr ~TechniqueType() = default;

	constexpr operator size_t() const noexcept {
		return _techniqueType;
	}

	constexpr friend TechniqueType operator&(const TechniqueType &lhs, const TechniqueType &rhs) noexcept {
		return TechniqueType{ lhs._techniqueType & rhs._techniqueType };
	}

	constexpr friend TechniqueType operator|(const TechniqueType &lhs, const TechniqueType &rhs) noexcept {
		return TechniqueType{ lhs._techniqueType | rhs._techniqueType };
	}

	constexpr friend TechniqueType operator^(const TechniqueType &lhs, const TechniqueType &rhs) noexcept {
		return TechniqueType{ lhs._techniqueType ^ rhs._techniqueType };
	}

	static TechniqueType None;
	static TechniqueType AllSet;
	constexpr static size_t Count = 64;
private:
	size_t _techniqueType = 0;
};

inline TechniqueType TechniqueType::None{ 0 };
inline TechniqueType TechniqueType::AllSet{ static_cast<size_t>(-1) };

struct TechniqueFlag {
	TechniqueFlag(TechniqueType techniqueType) : _bits(0) {
		if (techniqueType == TechniqueType::AllSet)
			_bits.flip();
		else
			_bits.set(static_cast<size_t>(techniqueType));
	}

	TechniqueFlag &operator=(TechniqueType techniqueType) {
		TechniqueFlag tmp(techniqueType);
		swap(*this, tmp);
		return *this;
	}

	TechniqueFlag(const TechniqueFlag &) = default;
	TechniqueFlag(TechniqueFlag &&) = default;
	TechniqueFlag &operator=(const TechniqueFlag &) = default;
	TechniqueFlag &operator=(TechniqueFlag &&) = default;

	bool test(TechniqueType techniqueType) const {
		return _bits.test(static_cast<size_t>(techniqueType));
	}

	void reset() {
		_bits.reset();
	}

	void set(TechniqueType techniqueType) {
		_bits.set(static_cast<size_t>(techniqueType));
	}

	void flip() {
		_bits.flip();
	}

	friend void swap(TechniqueFlag &lhs, TechniqueFlag &rhs) noexcept {
		using std::swap;
		swap(lhs._bits, rhs._bits);
	}
private:
	constexpr static size_t kBitCount = static_cast<size_t>(TechniqueType::Count);
	std::bitset<kBitCount> _bits;
};

}
