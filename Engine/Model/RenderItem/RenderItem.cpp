#include <iostream>
#include "RenderItem.h"
#include "Material/Material.h"
#include "Model/IModel.hpp"
#include "RenderGraph/Material/Material.h"
#include "Model/MeshManager.h"
#include <fmt/format.h>

using namespace Math;

template<typename T>
static std::shared_ptr<dx12lib::VertexBuffer> buildVertexDataInputImpl(
	dx12lib::IDirectContext &directCtx,
	const std::string &key,
	const std::vector<T> &data)
{
	if (data.empty()) {
		assert(false);
		return nullptr;
	}

	auto pVertexBuffer = Eureka::MeshManager::instance()->getVertexBuffer(key);
	if (pVertexBuffer == nullptr) {
		pVertexBuffer = directCtx.createVertexBuffer(data.data(), data.size(), sizeof(T));
		Eureka::MeshManager::instance()->cacheVertexBuffer(key, pVertexBuffer);
	}
	return pVertexBuffer;
}

bool Eureka::RenderItem::buildVertexDataInput(dx12lib::IDirectContext &directCtx,
	rgph::Geometry *pGeometry, 
	const rgph::ShaderLayoutIndex &shaderLayoutIndex) 
{
	if (pGeometry->getVertexBuffer(shaderLayoutIndex) != nullptr)
		return true;

	std::string name;
	auto pMesh = pGeometry->getMesh();
	std::shared_ptr<dx12lib::VertexBuffer> pVertexBuffer;
	switch (shaderLayoutIndex) {
	case rgph::ShaderLayoutIndex::Position:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "POSITION");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getPositions());
		break;
	case rgph::ShaderLayoutIndex::Normal:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "NORMAL");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getNormals());
		break;
	case rgph::ShaderLayoutIndex::Tangent:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TANGENT");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTangents());
		break;
	case rgph::ShaderLayoutIndex::Color:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "COLOR");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getColors());
		break;
	case rgph::ShaderLayoutIndex::TexCoord0:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD0");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord0());
		break;
	case rgph::ShaderLayoutIndex::TexCoord1:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD1");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord1());
		break;
	case rgph::ShaderLayoutIndex::TexCoord2:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD2");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord2());
		break;
	case rgph::ShaderLayoutIndex::TexCoord3:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD3");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord3());
		break;
	case rgph::ShaderLayoutIndex::TexCoord4:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD4");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord4());
		break;
	case rgph::ShaderLayoutIndex::TexCoord5:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD5");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord5());
		break;
	case rgph::ShaderLayoutIndex::TexCoord6:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD6");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord6());
		break;
	case rgph::ShaderLayoutIndex::TexCoord7:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "TEXCOORD7");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getTexCoord7());
		break;
	case rgph::ShaderLayoutIndex::BoneIndices:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "BONEINDICES");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getBoneIndices());
		break;
	case rgph::ShaderLayoutIndex::BoneWeights:
		name = fmt::format("{}_{}", pMesh->getMeshName(), "BONEWEIGHTS");
		pVertexBuffer = buildVertexDataInputImpl(directCtx, name, pMesh->getBoneWeight());
		break;
	default:
		assert(false);
		break;
	}

	if (pVertexBuffer == nullptr) {
		std::cerr << "vertex semantic invalid: " << name << std::endl;
		return false;
	}

	size_t index = shaderLayoutIndex;
	pGeometry->setVertexBuffer(index-1, pVertexBuffer);
	return true;
}

namespace Eureka {

RenderItem::RenderItem(dx12lib::IDirectContext &directCtc, 
	const rgph::TransformCBufferPtr &trans,
	std::shared_ptr<rgph::IMesh> pMesh)
{
	_pGeometry = std::make_shared<rgph::Geometry>();
	_pGeometry->setMesh(std::move(pMesh));
	_pGeometry->genDrawArgs();
	_pTransformCBuf = trans;
	buildIndexDataInput(directCtc, _pGeometry.get());
}

auto RenderItem::getMaterial() const -> std::shared_ptr<Material> {
	return _pMaterial;
}

void RenderItem::setMaterial(dx12lib::IDirectContext &directCtx, std::shared_ptr<Material> pMaterial) {
	_pMaterial = std::move(pMaterial);
	auto shaderLayoutMask = _pMaterial->getShaderLayoutMask();
	for (size_t i = rgph::ShaderLayoutIndex::Position; i < rgph::ShaderLayoutIndex::Max; ++i) {
		rgph::ShaderLayoutIndex shaderLayoutIndex(i);
		if (shaderLayoutMask & shaderLayoutIndex)
			buildVertexDataInput(directCtx, _pGeometry.get(), shaderLayoutIndex);
	}
}

void RenderItem::submit(const rgph::TechniqueFlag &techniqueFlag) const {
	if (_pMaterial == nullptr)
		return;
	_pMaterial->submit(techniqueFlag, _pGeometry.get(), &_pTransformCBuf);
}

auto RenderItem::getWorldAABB() const -> const BoundingBox & {
	return _pGeometry->getWorldAABB();
}

void RenderItem::setTransform(const Matrix &matWorld) {
	_pGeometry->applyTransform(matWorld);
}

bool RenderItem::buildIndexDataInput(dx12lib::IDirectContext &directCtx, rgph::Geometry *pGeometry) {
	auto pMesh = pGeometry->getMesh();
	const auto &indices = pMesh->getIndices();
	if (indices.size() < 3) {
		assert(false);
		return false;
	}

	std::shared_ptr<dx12lib::IndexBuffer> pIndexBuffer;
	if (pMesh->getPositions().size() > std::numeric_limits<uint16_t>::max()) {
		std::string key = pMesh->getMeshName() + "_IndexBuffer_uint32";
		pIndexBuffer = MeshManager::instance()->getIndexBuffer(key);
		if (pIndexBuffer == nullptr) {
			pIndexBuffer = directCtx.createIndexBuffer(
				indices.data(),
				indices.size(),
				DXGI_FORMAT_R32_UINT
			);
			MeshManager::instance()->cacheIndexBuffer(key, pIndexBuffer);
		}
	}
	else {
		std::string key = pMesh->getMeshName() + "_IndexBuffer_uint16";
		pIndexBuffer = MeshManager::instance()->getIndexBuffer(key);
		if (pIndexBuffer == nullptr) {
			std::vector<uint16_t> newIndices;
			newIndices.resize(indices.size());
			for (size_t i = 0; i < indices.size()-2; i += 3) {
				newIndices[i+0] = static_cast<uint16_t>(indices[i+0]);
				newIndices[i+1] = static_cast<uint16_t>(indices[i+1]);
				newIndices[i+2] = static_cast<uint16_t>(indices[i+2]);
			}

			pIndexBuffer = directCtx.createIndexBuffer(
				newIndices.data(),
				newIndices.size(),
				DXGI_FORMAT_R16_UINT
			);
			MeshManager::instance()->cacheIndexBuffer(key, pIndexBuffer);
		}
	}
	pGeometry->setIndexBuffer(pIndexBuffer);
	return true;
}

}
