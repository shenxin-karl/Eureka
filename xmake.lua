
EUREKA_DIR          = os.curdir()
EUREKA_EXT_DIR      = path.join(EUREKA_DIR, "Ext")
EUREKA_BUILD_DIR    = path.join(EUREKA_DIR, "build")
EUREKA_WORK_DIR     = path.join(EUREKA_DIR, "Res")  
EUREKA_BINARY_DIR   = path.join(EUREKA_DIR, "Res")
EUREKA_RENDERER_DIR = path.join(EUREKA_DIR, "Dx12Renderer")
EUREKA_TOOL_DIR     = path.join(EUREKA_DIR, "Tool")

if is_mode("debug") then
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Debug")
elseif is_mode("release") then
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "Release")
else 
    EUREKA_BINARY_DIR = path.join(EUREKA_BINARY_DIR, "ReleaseDbg")
end 


add_rules("mode.debug", "mode.release", "mode.releasedbg")
includes("xmake/rule/utils_dxc.lua")
includes("Dx12Renderer/xmake.lua")
includes("Engine/xmake.lua")