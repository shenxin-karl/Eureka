
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CmakeRC.cmake)
cmrc_add_resource_library(Eureka-resources ALIAS Eureka::rc
	NAMESPACE Eureka
	# 打包到 exe 里面的 shader 
	
	"EngineAssets/Shaders/Common.hlsli"
	"EngineAssets/Shaders/Lighting.hlsli"
	"EngineAssets/Shaders/CookTorrance.hlsli"
	"EngineAssets/Shaders/PixelPacking_Velocity.hlsli"

	"EngineAssets/Shaders/DeferredPBR.hlsl"
	"EngineAssets/Shaders/FXAA.hlsl"
	"EngineAssets/Shaders/LightingPassCS.hlsl"
	"EngineAssets/Shaders/PostProcessing.hlsl"	
	"EngineAssets/Shaders/TiledDeferredCS.hlsl"
	"EngineAssets/Shaders/TAAResolveCS.hlsl"
	"EngineAssets/Shaders/SharpenTAACS.hlsl"
)

set_target_properties(Eureka-resources PROPERTIES FOLDER "EngineResource")

target_link_libraries(${PROJECT_NAME} PRIVATE
	Eureka::rc
)