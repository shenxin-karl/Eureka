#pragma once
#include "Asset.h"
#include "Dx12lib/dx12libStd.h"
#include "RenderGraph/Job/ShaderLayout.h"
#include "Math/MathStd.hpp"

namespace Eureka {

class Mesh : public Asset {
public:
	void setVertices(const Math::float3 *pData, size_t count);
	void setNormals(const Math::float3 *pData, size_t count);
	void setTangents(const Math::float4 *pData, size_t count);
	void setColor(const Math::float2 *pData, size_t count);
	void setUV0(const Math::float2 *pData, size_t count);
	void setUV1(const Math::float2 *pData, size_t count);
	void setUV2(const Math::float2 *pData, size_t count);
	void setUV3(const Math::float2 *pData, size_t count);
	void setUV4(const Math::float2 *pData, size_t count);
	void setUV5(const Math::float2 *pData, size_t count);
	void setUV6(const Math::float2 *pData, size_t count);
	void setUV7(const Math::float2 *pData, size_t count);
	void setBoneWeights(const Math::float4 *pData, size_t count);
	void setBoneIndices(const uint8_t *pData, size_t count);
	bool isVertexBufferDirty(size_t index) const;
	bool isIndexBufferDirty() const;
private:
	constexpr static size_t kMaxVertexBufferSize = rgph::ShaderLayoutIndex::getLayoutSize();
	using VertexBufferList = std::array<std::shared_ptr<dx12lib::VertexBuffer>, kMaxVertexBufferSize>;

	template<typename DataT, typename BufferT>
	struct Buffer {
		bool					 dirty;
		std::vector<DataT>		 cpuBuffer;
		std::shared_ptr<BufferT> gpuBuffer;
		Buffer() : dirty(false), cpuBuffer({}), gpuBuffer(nullptr) {
		}
		void setData(const DataT *pData, size_t count) {
			cpuBuffer.assign(pData, pData+count);
			dirty = true;
		}
		bool isDirty() const {
			return dirty;
		}
	};
private:
	Buffer<Math::float3, dx12lib::VertexBuffer>	_verticesBuffer;
	Buffer<Math::float3, dx12lib::VertexBuffer> _normalsBuffer;
	Buffer<Math::float4, dx12lib::VertexBuffer> _tangentsBuffer;
	Buffer<Math::float4, dx12lib::VertexBuffer> _colorsBuffer;
	Buffer<Math::float2, dx12lib::VertexBuffer> _uv0Buffer;

	VertexBufferList						_vertexBufferList;
	std::shared_ptr<dx12lib::IndexBuffer>	_pIndexBuffer;
};

}
