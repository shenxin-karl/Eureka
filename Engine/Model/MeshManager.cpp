#include "MeshManager.h"
#include <Dx12lib/Buffer/VertexBuffer.h>
#include <Dx12lib/Buffer/IndexBuffer.h>
#include "Defined/EngineDefined.h"

namespace Eureka {

MeshManager::MeshManager() {
}

MeshManager::~MeshManager() {
}

std::shared_ptr<dx12lib::VertexBuffer> MeshManager::getVertexBuffer(const std::string &key) const {
	auto iter = _vertexBufferCache.find(key);
	if (iter != _vertexBufferCache.end())
		return iter->second.lock();
	return nullptr;
}

std::shared_ptr<dx12lib::IndexBuffer> MeshManager::getIndexBuffer(const std::string &key) const {
	auto iter = _indexBufferCache.find(key);
	if (iter != _indexBufferCache.end())
		return iter->second.lock();
	return nullptr;
}

void MeshManager::cacheVertexBuffer(const std::string &key, std::weak_ptr<dx12lib::VertexBuffer> pVertexBuffer) {
	_vertexBufferCache[key] = std::move(pVertexBuffer);
}

void MeshManager::cacheIndexBuffer(const std::string &key, std::weak_ptr<dx12lib::IndexBuffer> pIndexBuffer) {
	_indexBufferCache[key] = std::move(pIndexBuffer);
}

}
