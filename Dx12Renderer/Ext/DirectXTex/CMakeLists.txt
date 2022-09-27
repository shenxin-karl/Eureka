cmake_minimum_required( VERSION 3.16.1 ) # Latest version of CMake when this file was created.
project(DirectXTex)

#set( PUBLIC_HEADER_FILES 
#    DirectXTex/DirectXTex.h
#    DirectXTex/DirectXTex.inl
#)

#source_group( "Header Files" FILES ${PUBLIC_HEADER_FILES} )

#set( PRIVATE_HEADER_FILES
#    DirectXTex/BC.h
#    DirectXTex/BCDirectCompute.h
#    DirectXTex/d3dx12.h
#    DirectXTex/DDS.h
#    DirectXTex/DirectXTexP.h
#    DirectXTex/Filters.h
#    DirectXTex/scoped.h
#)

#set( SOURCE_FILES
#    DirectXTex/DirectXTexWIC.cpp
#    DirectXTex/BC.cpp
#    DirectXTex/BC4BC5.cpp
#    DirectXTex/BC6HBC7.cpp
#    DirectXTex/BCDirectCompute.cpp
#    DirectXTex/DirectXTexCompress.cpp
#    DirectXTex/DirectXTexCompressGPU.cpp
#    DirectXTex/DirectXTexConvert.cpp
#    DirectXTex/DirectXTexD3D11.cpp
#    DirectXTex/DirectXTexD3D12.cpp
#    DirectXTex/DirectXTexDDS.cpp
#    DirectXTex/DirectXTexFlipRotate.cpp
#    DirectXTex/DirectXTexHDR.cpp
#    DirectXTex/DirectXTexImage.cpp
#    DirectXTex/DirectXTexMipmaps.cpp
#    DirectXTex/DirectXTexMisc.cpp
#    DirectXTex/DirectXTexNormalMaps.cpp
#    DirectXTex/DirectXTexPMAlpha.cpp
#    DirectXTex/DirectXTexResize.cpp
#    DirectXTex/DirectXTexTGA.cpp
#    DirectXTex/DirectXTexUtil.cpp
#)

#source_group( "Source Files" FILES ${PRIVATE_HEADER_FILES} ${SOURCE_FILES} )

#set( SHADER_FILES
#    DirectXTex/Shaders/BC6HEncode.hlsl
#    DirectXTex/Shaders/BC7Encode.hlsl
#    DirectXTex/Shaders/CompileShaders.cmd
#)

#source_group( "Source Files\\Shaders" FILES ${SHADER_FILES} )

#set( COMPILED_SHADER_FILES
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode137CS.inc
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode456CS.inc
#    DirectXTex/Shaders/Compiled/BC6HEncode_EncodeBlockCS.inc
#    DirectXTex/Shaders/Compiled/BC6HEncode_TryModeG10CS.inc
#    DirectXTex/Shaders/Compiled/BC6HEncode_TryModeLE10CS.inc
#    DirectXTex/Shaders/Compiled/BC7Encode_EncodeBlockCS.inc
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode02CS.inc
#)

#source_group( "Source Files\\Shaders\\Compiled" FILES ${COMPILED_SHADER_FILES} )

#set( SHADER_SYMBOL_FILES
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode137CS.pdb
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode456CS.pdb
#    DirectXTex/Shaders/Compiled/BC6HEncode_EncodeBlockCS.pdb
#    DirectXTex/Shaders/Compiled/BC6HEncode_TryModeG10CS.pdb
#    DirectXTex/Shaders/Compiled/BC6HEncode_TryModeLE10CS.pdb
#    DirectXTex/Shaders/Compiled/BC7Encode_EncodeBlockCS.pdb
#    DirectXTex/Shaders/Compiled/BC7Encode_TryMode02CS.pdb
#)

#source_group( "Source Files\\Shaders\\Symbols" FILES ${SHADER_SYMBOL_FILES} )

#set_source_files_properties( ${SHADER_FILES}
#    PROPERTIES 
#        HEADER_FILE_ONLY ON
#)

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.c *.cpp *.cc)
file(GLOB_RECURSE SHADER_FILES *.hlsl)
set(AllFile ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

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


add_library( DirectXTex STATIC ${AllFile})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Dx12Renderer/Ext")
set_property(SOURCE ${SHADER_FILES} PROPERTY VS_TOOL_OVERRIDE "shader")	# 设置 hlsl 为 shader 资源文件

target_include_directories( DirectXTex
    PUBLIC DirectXTex
)

#add_custom_command( OUTPUT ${COMPILED_SHADER_FILES} ${SHADER_SYMBOL_FILES}
#    COMMAND CompileShaders.cmd
#    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/DirectXTex/Shaders"
#    DEPENDS ${SHADER_FILES}
#)