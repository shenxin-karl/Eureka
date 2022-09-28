cmake_minimum_required(VERSION 3.8)	
project(Engine)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
	set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
	set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE SHADER_FILES *.hlsl *.hlsli)
SET(AllFile ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

foreach(fileItem ${AllFile})       
	# Get the directory of the source file
	get_filename_component(PARENT_DIR "${fileItem}" DIRECTORY)
	# Remove common directory prefix to make the group
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	# Make sure we are using windows slashes
	string(REPLACE "/" "\\" GROUP "${GROUP}")
	# Group into "Source Files" and "Header Files"
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${fileItem}")
endforeach()

add_executable(${PROJECT_NAME} ${AllFile})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "")

target_include_directories(${PROJECT_NAME} PUBLIC 
	${PROJECT_FUNCTION_DIR}/
	${PROJECT_RENDERER_DIR}/
	${PROJECT_EXT_DIR}/assimp/include
	${PROJECT_BUILD_DIR}/Ext/assimp/include/
)

set_property(SOURCE ${SHADER_FILES} PROPERTY VS_TOOL_OVERRIDE "shader")	# 设置 hlsl 为 shader 资源文件

## 定义 库 shader 提供文件
add_definitions(-DEUREKA_HLSL_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/HlslShader") 

include(CmakeRC.cmake)
cmrc_add_resource_library(Eureka-resources ALIAS Eureka::rc
	NAMESPACE Eureka
	# 打包到 exe 里面的 shader 
	"HlslShader/Common.hlsli"
)

set_target_properties(Eureka-resources PROPERTIES FOLDER "EngineResource")

target_link_libraries(${PROJECT_NAME} PUBLIC
	Dx12lib
	assimp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Eureka::rc
)

# 设置工作目录
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${EUREKA_WORK_DIR}")