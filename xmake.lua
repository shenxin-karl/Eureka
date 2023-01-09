
EUREKA_DIR          = os.curdir()
EUREKA_EXT_DIR      = path.join(EUREKA_DIR, "Ext")
EUREKA_BUILD_DIR    = path.join(EUREKA_DIR, "build")
EUREKA_WORK_DIR     = path.join(EUREKA_DIR, "Res")  
EUREKA_BINARY_DIR   = path.join(EUREKA_DIR, "Res")
EUREKA_RENDERER_DIR = path.join(EUREKA_DIR, "Dx12Renderer")
EUREKA_TOOL_DIR     = path.join(EUREKA_DIR, "Tool")

add_defines("NOMINMAX", "UNICODE", "_UNICODE")

if is_mode("debug") then
    set_runtimes("MDd")
    add_defines("DEBUG", "_DEBUG")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Debug")
elseif is_mode("release") then
    set_runtimes("MD")
    add_defines("RELEASE", "_RELEASE")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Release")
else 
    set_runtimes("MDd")
    add_defines("RELWITHDEBINFO", "_RELWITHDEBINFO")
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "ReleaseDbg")
end 

add_rules("mode.debug", "mode.release", "mode.releasedbg")
includes("xmake/rule/utils_dxc.lua")
includes("xmake/rule/utiles_build_in.lua")

includes("Dx12Renderer/xmake.lua")
includes("Engine/xmake.lua")