add_rules("mode.debug", "mode.release")

target("Dx12lib")
    set_languages("c++latest")
    set_kind("static")
    -- 编译命令
    add_cxflags("/MP")
    -- 编译宏
    add_defines("_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING", {public=true})
    -- 头文件和源文件
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_files("**.cpp")
    -- 头文件目录
    add_includedirs(DX12RENDERER_DIR, {public=true})
    add_includedirs(DX12RENDERER_EXT_DIR, {public=true})
    local pixLibDir = path.join(DX12RENDERER_EXT_DIR, "WinPixEventRuntime", "winpixeventruntime.1.0.22081000");
    add_includedirs(path.join(pixLibDir, "Include", "WinPixEventRuntime"), {public=true})

    -- 链接库路径
    add_linkdirs(pixLibDir .. "bin/x64")

    -- 编译 shader 
    before_build(function(target)
        local isDebug = is_mode("debug");
        local shaderFilePath = path.join(os.scriptdir(), "Texture", "GenerateMips_CS.hlsl")
        local csoOutputFile = path.join(EUREKA_BUILD_DIR, "GenerateMips_CS.cso")
        local pdbOutputFile = path.join(EUREKA_BUILD_DIR, "GenerateMips_CS.pdb")
        local outputDir = path.join(EUREKA_BUILD_DIR, "Dx12libShaders")
        if not os.exists(outputDir) then
            os.mkdir(outputDir)
        end
        print("shaderFilePath: "..shaderFilePath)
        print("csoOutputFile: "..csoOutputFile)
        local args = { 
           "/nologo",
           "/Qstrip_rootsignature",
           "/ECS",
           "/Tcs_5_1",
           isDebug and "/Od" or "/O1",
           "/Zi",
           "/Fo " .. csoOutputFile,
           "/Fd " .. pdbOutputFile,
           shaderFilePath,
           "/Vn g_${GenerateMips_CS}",
           "/Fh " .. path.join(outputDir, "GenerateMips_CS.h"),
        }
        os.execv("fxc.exe", args, {PATH = os.curdir()})
    end)

target_end()

