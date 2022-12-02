#include "ShadowPass.h"

namespace Eureka {

struct OpaqueDrawIndex {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW      indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	D3D12_DRAW_INDEXED_ARGUMENTS drawIndexCmd;
};

struct OpaqueDrawArray {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	D3D12_DRAW_ARGUMENTS         drawArrayCmd;
};

struct AlphaTestDrawIndex {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW      indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	uint32_t					 albedoMapIndex;
	D3D12_DRAW_INDEXED_ARGUMENTS drawIndexCmd;
};

struct AlphaTestDrawArray {
	D3D12_VERTEX_BUFFER_VIEW     setVbvCmd;
	D3D12_INDEX_BUFFER_VIEW      setIbvCmd;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	D3D12_GPU_VIRTUAL_ADDRESS    albedoMapIndex;
	D3D12_DRAW_ARGUMENTS         drawArrayCmd;
};

}
