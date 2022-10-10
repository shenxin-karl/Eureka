#pragma once
#include <cstring>
#include <xutility>

namespace dx12lib {

struct RenderProfiler {
	union {
		struct {
			size_t drawCall;
			size_t triangles;
			size_t dispatchCall;
			size_t setPSOCall;
			size_t setCBVCall;
			size_t setSRVCall;
			size_t setUAVCall;
			size_t setConstant32BitCall;
			size_t setVertexBufferCall;
			size_t setIndexBufferCall;
		};
		size_t data[10];
	};
public:
	RenderProfiler() noexcept {
		std::memset(this, 0, sizeof(data));
	}

	RenderProfiler(const RenderProfiler &other) noexcept {
		std::memcpy(this, &other, sizeof(*this));
	}

	friend RenderProfiler &operator+=(RenderProfiler &lhs, const RenderProfiler &rhs) noexcept {
		for (size_t i = 0; i < std::size(rhs.data); ++i)
			lhs.data[i] += rhs.data[i];
		return lhs;
	}

	friend RenderProfiler operator+=(const RenderProfiler &lhs, const RenderProfiler &rhs) noexcept {
		auto tmp = lhs;
		return (tmp += rhs);
	}
};
}
