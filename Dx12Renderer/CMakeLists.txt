cmake_minimum_required(VERSION 3.8)	
project(Dx12Renderer)

option(GROUP_BY_EXPLORER ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
	set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
	set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

set(DX12LIB_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Ext)

LIST(APPEND ComponentAllSubDir "Dx12lib")
LIST(APPEND ComponentAllSubDir "Ext/DirectXTex")
LIST(APPEND ComponentAllSubDir "Math")
LIST(APPEND ComponentAllSubDir "RenderGraph")

if (MSVC)
	add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)	## enable wstring_convert
endif(MSVC)

set(DX12RENDERER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(AllTestDir "")
foreach(dirname ${ComponentAllSubDir}) 
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${dirname}/CMakeLists.txt")
		add_subdirectory(${dirname})
		LIST(APPEND AllTestDir "${dirname}")
	endif()
endforeach()
