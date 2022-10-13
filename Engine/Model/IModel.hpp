#pragma once
#include <RenderGraph/Drawable/Drawable.h>
#include <RenderGraph/Bindable/ConstantBufferBindable.h>
#include "Model/IBound.hpp"
#include <memory>
#include <functional>

namespace rgph {

struct IMesh;
class TransformCBufferPtr;

}

namespace Eureka {

class Material;
class RenderItem;
class ALMaterial;

using MaterialCreator = std::function< std::shared_ptr<Material>(const ALMaterial *)>;

interface INode : protected dx12lib::NonCopyable {
	virtual void submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const = 0;
	virtual size_t getNumRenderItem() const = 0;
	virtual RenderItem *getRenderItem(size_t idx) const = 0;
	virtual void setParentTransform(const Math::Matrix4 &matWorld) = 0;
	virtual const rgph::TransformCBufferPtr &getTransformCBuffer() const = 0;
	virtual std::shared_ptr<rgph::IMesh> getMesh(size_t idx) const = 0;
};

interface IModel : protected dx12lib::NonCopyable {
	virtual void submit(const IBounding &bounding, const rgph::TechniqueFlag &techniqueFlag) const = 0;
	virtual void setModelTransform(const Math::float4x4 &matWorld) = 0;
};

}
