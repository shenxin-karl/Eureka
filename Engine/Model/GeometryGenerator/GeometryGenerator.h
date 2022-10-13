#pragma once
#include "PartMesh.h"
#include "Defined/EngineDefined.h"
#include "Singletion/Singletion.hpp"

namespace Eureka {

class GeometryGenerator : public Singletion<GeometryGenerator> {
public:
	auto createCylinder(float bottomRadius, float topRadius, float height, uint32 stackCount, uint32 sliceCount) const -> std::shared_ptr<PartMesh>;
	auto createBox(float width, float height, float depth, uint32 numSubdivisions = 1) const -> std::shared_ptr<PartMesh>;
	auto createSphere(float radius, uint32 numSubdivisions = 1) const -> std::shared_ptr<PartMesh>;
	auto createGrid(float width, float depth, uint32 m, uint32 n) const -> std::shared_ptr<PartMesh>;
	auto createQuad(float x, float y, float w, float h, float depth) const -> std::shared_ptr<PartMesh>;
	auto createBoxGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask) const -> std::shared_ptr<rgph::Geometry>;
	auto createSphereGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask) const -> std::shared_ptr<rgph::Geometry>;
	auto createGridGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask) const -> std::shared_ptr<rgph::Geometry>;
	auto createQuadGeometry(dx12lib::IDirectContext &directCtx, rgph::ShaderLayoutMask mask) const -> std::shared_ptr<rgph::Geometry>;
	void loading();
	auto createGeometry(dx12lib::IDirectContext &directCtx, 
		rgph::ShaderLayoutMask mask, 
		std::shared_ptr<PartMesh> pPartMesh
	) const -> std::shared_ptr<rgph::Geometry>;
private:
	std::shared_ptr<PartMesh> _pBoxMesh;
	std::shared_ptr<PartMesh> _pSphereMesh;
	std::shared_ptr<PartMesh> _pGridMesh;
	std::shared_ptr<PartMesh> _pQuadMesh;
};

}
