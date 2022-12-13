cmake_minimum_required(VERSION 3.8)	
project(EffectCompiler)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
	set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
	set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.tab.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp *.lex.cpp *.tab.cpp)
file(GLOB_RECURSE BISON_FILES *.l *.y)

set(AllFile ${HEADER_FILES} ${SOURCE_FILES} ${BISON_FILES})

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

set_property(SOURCE ${BISON_FILES} PROPERTY VS_TOOL_OVERRIDE "FLEX_BISON")	# 设置 hlsl 为 resources 资源文件

target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/
)

set(EXE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Res")
set(EXECUTABLE_OUTPUT_PATH ${EXE_FILE_DIR})
if(NOT EXISTS ${EXE_FILE_DIR}) 
	file(MAKE_DIRECTORY ${EXE_FILE_DIR})
endif()

# 设置工作目录
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${EXE_FILE_DIR}")


if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/FlexBison/output") 
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FlexBison/output")
endif()

set(FlexTool "${EUREKA_TOOL_DIR}/win_flex_bison/win_flex.exe")
set(BisonTool "${EUREKA_TOOL_DIR}/win_flex_bison/win_bison.exe")

add_custom_target(Flex)
add_custom_command(TARGET Flex PRE_BUILD
	COMMAND ${FlexTool} -o ${CMAKE_CURRENT_SOURCE_DIR}/FlexBison/output/FlexEffectParser.cpp --wincompat FlexBison/EffectParser.l
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	VERBATIM
)
add_dependencies(${PROJECT_NAME} Flex)
set_target_properties(Flex PROPERTIES FOLDER "EffectCompiler")


add_custom_target(Bison)
add_custom_command(TARGET Bison PRE_BUILD
	COMMAND ${BisonTool} -d -o ${CMAKE_CURRENT_SOURCE_DIR}/FlexBison/output/BisonEffectParser.cpp FlexBison/EffectParser.y
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	VERBATIM
)
add_dependencies(${PROJECT_NAME} Bison)
set_target_properties(Bison PROPERTIES FOLDER "EffectCompiler")
