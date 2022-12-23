
ENGINE_DIR = path.join(EUREKA_DIR, "Engine")

includes(path.join(EUREKA_EXT_DIR, "xmake", "assimp.lua"))

local isDebug = is_mode("debug")
local vsRuntime = isDebug and "MDd" or "MD"
add_requires("assimp", { configs = { debug = isDebug, vs_runtime = vsRuntime }})

function CompileEngineShader(target) 
    add_rules("utils.dxc")
    add_files("EngineAssets/Shaders/TiledDeferredCS.hlsl")
end

target("Engine")
    set_languages("c++latest")
    set_kind("binary")
    add_rules("utils.bin2c", {extensions = {".hlsl", ".hlsli"}})
    add_cxflags("/MP")
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_files("**.cpp")
    add_includedirs(ENGINE_DIR)
    add_packages("assimp")
    add_deps("RenderGraph")
    before_build(CompileEngineShader)
target_end()