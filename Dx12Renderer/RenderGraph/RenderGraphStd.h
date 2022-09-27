#pragma once
#include <Dx12lib/Context/CommonContext.h>
#include <Math/MathStd.hpp>

namespace rgph {

struct TechniqueFlag;
class Technique;
class Drawable;
class Bindable;
class Step;
class SubPass;
class RenderQueuePass;
struct Job;
class GraphicsPSOBindable;
struct TechniqueType;
struct DrawArgs;
class Geometry;
class TransformCBufferPtr;
class RenderGraph;

class NonCopyable {
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
	virtual ~NonCopyable() = default;
};

struct IDrawable : virtual public NonCopyable {
	IDrawable() = default;
	~IDrawable() override = default;
	virtual void submit(const TechniqueFlag &techniqueFlag) const = 0;
};

enum class PassType {
	ExecutablePass,			// pass
	ComputablePass,			// compute pass
	GraphicsPass,			// clear present pass
	FullScreenPass,			// full screen
	RenderQueuePass,		// draw call
};

}
