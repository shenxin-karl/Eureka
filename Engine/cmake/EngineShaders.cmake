
# 定义宏函数
set(HLSL_SHADER_FILES "")
macro(AddShader shaderPath entryPoint version)
	list(APPEND HLSL_SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}" PROPERTIES EntryPoint "${entryPoint}")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${shaderPath}" PROPERTIES Version "${version}")
endmacro()


# 这里添加 shader
AddShader("HlslShader/LightingPassCS.hlsl" "CS" "cs_5_1")
AddShader("HlslShader/FXAA_cso/FXAA_VS.txt" "VS" "vs_5_1")
AddShader("HlslShader/FXAA_cso/FXAA_PS.txt" "PS" "ps_5_1")
AddShader("HlslShader/UpdateLightBoundingSphere_cso/UpdatePointLightBoundingSphere_CS.txt" "CS" "cs_5_1")
AddShader("HlslShader/UpdateLightBoundingSphere_cso/UpdateSpotLightBoundingSphere_CS.txt" "CS" "cs_5_1")
AddShader("HlslShader/ClusterDeferredCS.hlsl" "CS" "cs_5_1")
AddShader("HlslShader/CalcClusterFrustumCS.hlsl" "CS" "cs_5_1")

add_custom_target(EngineShader)
# 创建一个目录
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/EngineShaders/")

foreach(FILE ${HLSL_SHADER_FILES})
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  get_filename_component(FILE_DIR ${FILE} DIRECTORY)
  get_source_file_property(entryPoint ${FILE} EntryPoint)
  get_source_file_property(version ${FILE} Version)
  add_custom_command(TARGET EngineShader						
                     COMMAND fxc.exe 
					            /I "${CMAKE_CURRENT_SOURCE_DIR}/HlslShader/"
								/nologo 
								/Qstrip_rootsignature
								/E${entryPoint} 					# 进入点
								/T${version} 						# 版本号
								$<IF:$<CONFIG:DEBUG>,/Od,/O1> 		# 如果debug, od, 否则 o1
								/Zi 
								/Fo ${CMAKE_BINARY_DIR}/${FILE_WE}.cso 
								/Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb 
								${FILE} 
								/Vn "g_${FILE_WE}"
								/Fh "${CMAKE_BINARY_DIR}/EngineShaders/${FILE_WE}.h" 
                     MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)

add_dependencies(${PROJECT_NAME} EngineShader)
set_target_properties(EngineShader PROPERTIES FOLDER "EngineResource")

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_BINARY_DIR}
)