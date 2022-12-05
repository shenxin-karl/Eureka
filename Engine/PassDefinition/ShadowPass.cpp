#include "ShadowPass.h"

namespace Eureka {

struct OpaqueDrawIndexed {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW      indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	D3D12_DRAW_INDEXED_ARGUMENTS drawIndexedArgs;
};

struct OpaqueDrawArray {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW		 indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	D3D12_DRAW_ARGUMENTS         drawArrayArgs;
};

struct AlphaTestDrawIndexed {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW      indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	uint32_t					 albedoMapIndex;
	D3D12_DRAW_INDEXED_ARGUMENTS drawIndexedArgs;
};

struct AlphaTestDrawArray {
	D3D12_VERTEX_BUFFER_VIEW     vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW      indexBufferView;
	D3D12_GPU_VIRTUAL_ADDRESS    objectCBufferAddress;
	uint32_t					 albedoMapIndex;
	D3D12_DRAW_ARGUMENTS         drawArrayArgs;
};

}
