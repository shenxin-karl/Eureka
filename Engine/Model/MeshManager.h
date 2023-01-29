#pragma once
#include <memory>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include "Foundation/Singletion.hpp"

namespace Eureka {

class MeshManager : public Singletion<MeshManager> {
public:
	MeshManager();
	~MeshManager();
	std::shared_ptr<dx12lib::VertexBuffer>  getVertexBuffer(const std::string &key) const;
	std::shared_ptr<dx12lib::IndexBuffer> getIndexBuffer(const std::string &key) const;
	void cacheVertexBuffer(const std::string &key, std::weak_ptr<dx12lib::VertexBuffer> pVertexBuffer);
	void cacheIndexBuffer(const std::string &key, std::weak_ptr<dx12lib::IndexBuffer> pIndexBuffer);
private:
	std::unordered_map<std::string, std::weak_ptr<dx12lib::VertexBuffer>> _vertexBufferCache;
	std::unordered_map<std::string, std::weak_ptr<dx12lib::IndexBuffer>> _indexBufferCache;
};

}