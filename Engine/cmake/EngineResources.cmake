
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CmakeRC.cmake)
cmrc_add_resource_library(Eureka-resources ALIAS Eureka::rc
	NAMESPACE Eureka
	# 打包到 exe 里面的 shader 
	"HlslShader/Common.hlsli"
)

set_target_properties(Eureka-resources PROPERTIES FOLDER "EngineResource")

target_link_libraries(${PROJECT_NAME} PRIVATE
	Eureka::rc
)