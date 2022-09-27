cmake_minimum_required(VERSION 3.8)	

set(CMAKE_CXX_STANDARD 20)

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc /std:c++latest")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
	set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
	set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()


project(Eureka)

# 获取当前文件夹的子目录
function(GetCMakeSubDir result rootDir)
	file(GLOB_RECURSE allItem LIST_DIRECTORIES true ${rootDir}/*)
	string(LENGTH ${rootDir}/ rootDirLength)
	foreach (dir ${allItem})
		if (IS_DIRECTORY ${dir} AND EXISTS ${dir}/CMakeLists.txt)
			string(SUBSTRING ${dir} ${rootDirLength} -1 subDir)
			list(APPEND allSubDir ${subDir})
		endif()
	endforeach()
	set(${result} ${allSubDir} PARENT_SCPOE)
endfunction()

# 获取相于顶层cmake的相对目录
set(TopDir ${CMAKE_CURRENT_SOURCE_DIR})
function(GetRelativeDir relativeDir)
	STRING(LENGTH ${TopDir}/ strLength)
	STRING(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${strLength} -1 dir)
	set(${relativeDir} ${dir} PARENT_SCOPE)
endfunction()

list(APPEND allSubDir "Dx12Renderer")
list(APPEND allSubDir "Engine")

set(PROJECT_COMPONENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Component)
set(PROJECT_LIBRAIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraies)
set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build)


foreach(dirname ${allSubDir})
	add_subdirectory(${dirname})
endforeach()

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Other")