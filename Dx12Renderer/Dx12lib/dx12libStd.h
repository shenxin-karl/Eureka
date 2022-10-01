#pragma once
#define NOMINMAX
#include <cassert>
#include <cstdint>
#include <wrl.h>
#include <exception>
#include "Tool/D3Dx12.h"
#include <comdef.h>
#include <Windows.h>
#include <d3dcompiler.h>
#include <memory>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <source_location>
#include <mutex>
#include <dxgi.h>
#include <DirectXMath.h>
#include <bitset>
#include <functional>
#include <array>
#include <Dx12lib/Common/Common.h>

#ifndef interface
	#define interface struct
#endif

namespace DX = DirectX;
namespace WRL = Microsoft::WRL;

namespace dx12lib {

namespace WRL = Microsoft::WRL;
namespace DX = DirectX;

using uint8 = std::uint8_t;
using uin16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using int8 = std::int8_t;
using in16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using size_t = std::size_t;

enum class CubeFace : size_t {
	Right		= 0,
	Left		= 1,
	Top			= 2,
	Bottom		= 3,
	Back		= 4,
	Front		= 5,
	POSITIVE_X	= 0,
	NEGATIVE_X	= 1,
	POSITIVE_Y	= 2,
	NEGATIVE_Y	= 3,
	POSITIVE_Z	= 4,
	NEGATIVE_Z	= 5,
};

enum class BufferType {
	DefaultBuffer,
	UploadBuffer,
	ConstantBuffer,
	VertexBuffer,
	IndexBuffer,
	StructuredBuffer,
	ReadBackBuffer,
};

struct ShaderRegister;
enum class RegisterSpace : size_t {
	Space0 = 0, Space1 = 1, Space2 = 2,
	Space3 = 3, Space4 = 4, Space5 = 5,
	Space6 = 6, Space7 = 7, Space8 = 8,
};

constexpr static std::size_t kSwapChainBufferCount	= 2;			// 2个交换缓冲区
constexpr static std::size_t kFrameResourceCount = 3;				// 3个帧资源
constexpr static std::size_t kMaxDescriptorTables = 64;				// 64个描述符表项
constexpr static std::size_t kDynamicDescriptorPerHeap = 1024;		// 1024个动态堆描述符
constexpr static std::size_t kDynamicDescriptorHeapCount = 2;		// 2中堆(Shader资源堆, 采样器堆)
constexpr static std::size_t kVertexBufferSlotCount = 16;			// 16个顶点槽位
constexpr static std::size_t kMaxRenderTargetCount = 8;				// 最多8个渲染目标

class FrameIndexProxy {
	static inline std::atomic_size_t _frameIndex = 0;
public:
	static const std::atomic_size_t &getConstantFrameIndexRef() noexcept {
		return _frameIndex;
	}
private:
	friend class FrameResourceQueue;
	static void startNewFrame() noexcept {
		_frameIndex = (_frameIndex + 1) % kFrameResourceCount;
	}
};

struct DeviceInitDesc;
class Adapter;
class CommandList;
class CommandQueue;
class ConstantBuffer;
class DefaultBuffer;
class DescriptorAllocation;
class DescriptorAllocatorPage;
class DescriptorAllocator;
class Device;
class FrameResourceItem;
class FrameResourceQueue;
class IndexBuffer;
class VertexBuffer;
class SwapChain;
class UploadBuffer;
class ResourceStateTracker;
class DynamicDescriptorHeap;
class RootSignatureDescHelper;
class RootSignature;
class PSO;
class GraphicsPSO;
class ComputePSO;

interface IContext;
interface ICommonContext;
interface IGraphicsContext;
interface IComputeContext;
interface IDirectContext;

class SRStructuredBuffer;
class UAStructuredBuffer;
class ReadBackBuffer;

interface IResource;
interface IBufferResource;
interface IConstantBuffer;
interface IVertexBuffer;
interface IIndexBuffer;
interface ISRStructuredBuffer;
interface IUAStructuredBuffer;
interface IReadBackBuffer;

class Texture;

struct NonCopyable {
	NonCopyable() = default;
	NonCopyable(NonCopyable &&) = default;
	NonCopyable &operator=(NonCopyable &&) = default;
	virtual ~NonCopyable() = default;
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
};

struct RawData;

// frame resource constant buffer template
template<typename T = RawData>
class FRConstantBuffer;

using FRRawConstantBufferPtr = std::shared_ptr<FRConstantBuffer<RawData>>;

template<typename T>
using FRConstantBufferPtr = std::shared_ptr<FRConstantBuffer<T>>;


// frame resource structured buffer template
template<typename T = RawData>
class FRSRStructuredBuffer;

using FRRawStructuredBufferPtr = std::shared_ptr<FRSRStructuredBuffer<RawData>>;

template<typename T>
using FRStructuredBufferPtr = std::shared_ptr<FRSRStructuredBuffer<T>>;

std::wstring to_wstring(const std::string &str);
std::string to_string(const std::wstring &str);

}

using dx12lib::FRRawConstantBufferPtr;
using dx12lib::FRConstantBufferPtr;
using dx12lib::FRRawStructuredBufferPtr;
using dx12lib::FRStructuredBufferPtr;


