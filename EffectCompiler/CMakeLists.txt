cmake_minimum_required(VERSION 3.8)	
project(EffectCompiler)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
	set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
	set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE SHADER_FILES *.hlsl *.hlsli)
file(GLOB_RECURSE SCRIPT_FILES *.lua)

SET(AllFile ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES} ${SCRIPT_FILES})

message("AllFile: ${AllFile}")

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
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "EffectCompiler")

set(EXE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Res")
set(EXECUTABLE_OUTPUT_PATH ${EXE_FILE_DIR})
if(NOT EXISTS ${EXE_FILE_DIR}) 
	file(MAKE_DIRECTORY ${EXE_FILE_DIR})
endif()

# 设置工作目录
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${EXE_FILE_DIR}")
