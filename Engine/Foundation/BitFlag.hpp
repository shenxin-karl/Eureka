#pragma once
#include <concepts>
#include <string>
#include <bit>

namespace Eureka {

template<std::integral T>
class BitFlag {
public:
	constexpr static std::size_t kCapacity = sizeof(T) * 8;

	BitFlag(T v = T()) noexcept : value(v) {
	}
	void set(T v) noexcept {
		value |= v;
	}
	bool test(T v) noexcept {
		return value & v;
	}
	void reset(T v) noexcept {
		value &= ~v;
	}
	void clear() noexcept {
		value = T();
	}
	void fill() noexcept {
		for (auto &byte : byteArray)
			byte = 0xFF;
	}
	size_t count() noexcept {
		return std::popcount(value);
	}
	static constexpr size_t capacity() noexcept {
		return kCapacity;
	}
	operator T() const noexcept {
		return value;
	}
	std::string toString() const noexcept {
		T flag = T(1);
		size_t index = kCapacity - 1;
		std::string toReturn(kCapacity, '0');
		for (size_t i = 0; i < kCapacity; ++i) {
			bool b = (flag & value);
			toReturn[index] = b ? '1' : '0';
			--index;
			flag <<= 1;
		}
		return toReturn;
	}
	friend auto operator<=>(const BitFlag &, const BitFlag &) noexcept = default;
public:
	union {
		T			  value;
		unsigned char byteArray[sizeof(T)];
	};
};

}
