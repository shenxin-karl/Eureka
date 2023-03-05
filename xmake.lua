
EUREKA_DIR          = os.curdir()
EUREKA_EXT_DIR      = path.join(EUREKA_DIR, "Ext")
EUREKA_BUILD_DIR    = path.join(EUREKA_DIR, "build")
EUREKA_BINARY_DIR   = path.join(EUREKA_DIR, "Res")
EUREKA_RENDERER_DIR = path.join(EUREKA_DIR, "Dx12Renderer")
EUREKA_TOOL_DIR     = path.join(EUREKA_DIR, "Tool")
ERUEKA_VS_RUNTIME   = nil

set_toolset("cc", "clang-cl")
set_toolset("cxx", "clang-cl")

add_cxxflags("-std:c++20", {tools = { "clang-cl" }})
add_defines("__cpp_consteval", {tools = { "clang-cl" }})
add_defines("NOMINMAX", "UNICODE", "_UNICODE")
set_arch("x64")

if is_mode("debug") then
    ERUEKA_VS_RUNTIME  = "MDd"
    add_defines("DEBUG", "_DEBUG", "EUREKA_COMPILE_MODE=\"Debug\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Debug", "bin")
elseif is_mode("release") then
    ERUEKA_VS_RUNTIME  = "MT"
    add_defines("RELEASE", "_RELEASE", "EUREKA_COMPILE_MODE=\"Release\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Release", "bin")
else 
    ERUEKA_VS_RUNTIME = "MD"
    add_defines("RELWITHDEBINFO", "_RELWITHDEBINFO", "EUREKA_COMPILE_MODE=\"ReleaseDbg\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "ReleaseDbg", "bin")
end 

set_runtimes(ERUEKA_VS_RUNTIME)


add_rules("mode.debug", "mode.releasedbg")
includes("xmake/rule/utils_dxc.lua")
includes("xmake/rule/utiles_build_in.lua")

includes("Dx12Renderer/xmake.lua")
includes("Engine/xmake.lua")