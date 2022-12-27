
ENGINE_DIR = path.join(EUREKA_DIR, "Engine")

includes(path.join(EUREKA_EXT_DIR, "xmake", "assimp.lua"))

local isDebug = is_mode("debug")
local vsRuntime = isDebug and "MDd" or "MD"
add_requires("assimp", { configs = { debug = isDebug, vs_runtime = vsRuntime }})

function CompileEngineShader() 
    add_rules("utils.dxc")
    set_values("ShaderCompileConfigPath", path.absolute("EngineAssets/Shaders"))
    set_values("ShaderCompileConfigName", "CompileShaderConfig")
    add_headerfiles("EngineAssets/Shaders/CompileShaderConfig.lua")
    add_files("**.hlsl")
    add_headerfiles("**.hlsl")
    add_headerfiles("**.hlsli")
end

function CopyEngineDLL(target) 
    local dxcDir = path.join(target:values("EUREKA_RENDERER_DIR"), "Ext", "dxc")
    local binDir = nil
    if is_arch("x86") then
        binDir = path.join(dxcDir, "bin", "x86")
    elseif is_arch("x64", "x86_64") then
        binDir = path.join(dxcDir, "bin", "x64")
    elseif is_arch("arm64") then
        binDir = path.join(dxcDir, "bin", "arm64")
    else 
        assert(false)
    end

    local srcFilename0 = path.join(binDir, "dxcompiler.dll")
    local srcFilename1 = path.join(binDir, "dxil.dll")
    local dstFilename0 = path.join(target:targetdir(), "dxcompiler.dll")
    local dstFilename1 = path.join(target:targetdir(), "dxil.dll")
    if not os.exists(dstFilename0) or not os.exists(dstFilename1) then
        os.cp(srcFilename0, target:targetdir())
        os.cp(srcFilename1, target:targetdir())
    end
end

target("Engine")
    set_languages("c++20")
    set_kind("binary")
    add_cxflags("/MP /std:c++latest /Wall /sdl /W4")
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_files("**.cpp")
    add_includedirs(ENGINE_DIR)
    add_packages("assimp")
    add_deps("RenderGraph")

    set_targetdir(EUREKA_BINARY_DIR)
    set_rundir(EUREKA_WORK_DIR)
    CompileEngineShader()

    set_values("EUREKA_RENDERER_DIR", EUREKA_RENDERER_DIR)
    before_run(CopyEngineDLL)
target_end()