cmake_minimum_required(VERSION 3.8)	
project(Dx12lib)

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE SHADER_FILES *.hlsli *.hlsl)
SET(AllFile ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

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
set_property(SOURCE ${SHADER_FILES} PROPERTY VS_TOOL_OVERRIDE "shader")		# 设置 hlsl 为 shader 资源文件
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



# 定义宏函数
set(HLSL_SHADER_FILES "")
macro(AddShader shaderPath entryPoint version)
	list(APPEND HLSL_SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}" PROPERTIES EntryPoint "${entryPoint}")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}" PROPERTIES Version "${version}")
endmacro()


# 这里添加 shader
AddShader("Texture/GenerateMips_CS.hlsl" "CS" "cs_5_1")


# 创建一个目录
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/EngineShaders/")

foreach(FILE ${HLSL_SHADER_FILES})
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  get_source_file_property(entryPoint ${FILE} EntryPoint)
  get_source_file_property(version ${FILE} Version)
  add_custom_command(TARGET Dx12lib		# 指定在 Dx12lib 编译前自动构建						
  					 PRE_BUILD
                     COMMAND fxc.exe 
								/nologo 
								/Qstrip_rootsignature
								/E${entryPoint} 					# 进入点
								/T${version} 						# 版本号
								$<IF:$<CONFIG:DEBUG>,/Od,/O1> 		# 如果debug, od, 否则 o1
								/Zi 
								/Fo ${CMAKE_BINARY_DIR}/${FILE_WE}.cso 
								/Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb 
								${FILE} 
								/Vn g_${FILE_WE} 
								/Fh ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.h 
                     MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_BINARY_DIR}/shaders/
)