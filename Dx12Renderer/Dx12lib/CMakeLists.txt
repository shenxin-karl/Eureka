cmake_minimum_required(VERSION 3.8)	
project(Dx12lib)

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
SET(AllFile ${HEADER_FILES} ${SOURCE_FILES})

if (MSVC)
	add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)	## enable wstring_convert
endif(MSVC)

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

add_library(${PROJECT_NAME} STATIC ${AllFile})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Dx12Renderer")

target_include_directories(${PROJECT_NAME} PUBLIC 
	${DX12RENDERER_DIR}/
	${DX12RENDERER_DIR}/Ext
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
	d3dcompiler
	D3D12
	dxgi
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	DirectXTex
)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")
