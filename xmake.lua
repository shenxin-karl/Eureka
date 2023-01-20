
EUREKA_DIR          = os.curdir()
EUREKA_EXT_DIR      = path.join(EUREKA_DIR, "Ext")
EUREKA_BUILD_DIR    = path.join(EUREKA_DIR, "build")
EUREKA_BINARY_DIR   = path.join(EUREKA_DIR, "Res")
EUREKA_RENDERER_DIR = path.join(EUREKA_DIR, "Dx12Renderer")
EUREKA_TOOL_DIR     = path.join(EUREKA_DIR, "Tool")

add_defines("NOMINMAX", "UNICODE", "_UNICODE")

if is_mode("debug") then
    set_runtimes("MDd")
    add_defines("DEBUG", "_DEBUG", "EUREKA_COMPILE_MODE=\"Debug\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Debug", "bin")
elseif is_mode("release") then
    set_runtimes("MT")
    add_defines("RELEASE", "_RELEASE", "EUREKA_COMPILE_MODE=\"Release\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Release", "bin")
else 
    set_runtimes("MDd")
    add_defines("RELWITHDEBINFO", "_RELWITHDEBINFO", "EUREKA_COMPILE_MODE=\"ReleaseDbg\"")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "ReleaseDbg", "bin")
end 

add_rules("mode.debug", "mode.releasedbg")
includes("xmake/rule/utils_dxc.lua")
includes("xmake/rule/utiles_build_in.lua")

includes("Dx12Renderer/xmake.lua")
includes("Engine/xmake.lua")