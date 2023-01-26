
ENGINE_DIR = path.join(EUREKA_DIR, "Engine")

includes(path.join(EUREKA_EXT_DIR, "xmake", "assimp.lua"))
includes(path.join(EUREKA_EXT_DIR, "xmake", "stduuid.lua"))
includes(path.join(EUREKA_EXT_DIR, "xmake", "antlr4.lua"))

local isDebug = is_mode("debug")
local vsRuntime = is_mode("release") and "MT" or "MDd"
add_requires("assimp",  { configs = { debug = isDebug, vs_runtime = vsRuntime, shared = false }})
add_requires("antlr4",  { configs = { debug = isDebug, vs_runtime = vsRuntime, shared = false }})
add_requires("stduuid", { configs = { debug = isDebug, vs_runtime = vsRuntime }})

function CopyEngineDLL(target) 
    function CopyDxcDLL(target) 
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
            os.cp(srcFilename0, dstFilename0)
            os.cp(srcFilename1, dstFilename1)
        end
    end
    function CopyPixDLL(target) 
        local binDir = nil
        local pixDir = path.join(
            target:values("EUREKA_RENDERER_DIR"), 
            "Ext", 
            "WinPixEventRuntime", 
            "winpixeventruntime.1.0.22081000"
        )
        if is_arch("x64", "x86_64") then
            binDir = path.join(pixDir, "bin", "x64")
        elseif is_arch("arm64") then
            binDir = path.join(pixDir, "bin", "ARM64")
        else 
            assert(false)
        end
    
        local srcFilename = path.join(binDir, "WinPixEventRuntime.dll")
        local dstFilename = path.join(target:targetdir(), "WinPixEventRuntime.dll")
        if not os.exists(dstFilename) then
            os.cp(srcFilename, dstFilename)
        end
    end 

    if not os.isdir(target:values("EUREKA_RENDERER_DIR")) then
        os.mkdir(target:values("EUREKA_RENDERER_DIR"))
    end

    CopyDxcDLL(target)
    CopyPixDLL(target)
end

target("Engine")
    set_languages("c++latest")
    set_kind("binary")
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_headerfiles("**.inc")
    add_files("**.cpp")
    add_includedirs(ENGINE_DIR)
    
    add_packages("assimp")
    add_packages("stduuid")
    add_packages("antlr4")

    add_deps("RenderGraph")

    set_targetdir(EUREKA_BINARY_DIR)

    set_values("EUREKA_RENDERER_DIR", EUREKA_RENDERER_DIR)
    before_run(CopyEngineDLL)
target_end()