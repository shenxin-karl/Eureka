add_rules("mode.debug", "mode.release")
target("Dx12lib")
    set_languages("c++latest")
    set_kind("static")
    add_rules("utils.bin2c", {extensions = {".hlsl"}})
    -- 编译命令
    add_cxflags("/MP")
    -- 编译宏
    add_defines("_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING", {public=true})
    -- 头文件
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    -- 源文件
    add_files("**.cpp")
    -- 头文件目录
    add_includedirs(DX12RENDERER_DIR, {public=true})
    add_includedirs(DX12RENDERER_EXT_DIR, {public=true})
    local pixLibDir = path.join(DX12RENDERER_EXT_DIR, "WinPixEventRuntime", "winpixeventruntime.1.0.22081000");
    add_includedirs(path.join(pixLibDir, "Include", "WinPixEventRuntime"), {public=true})
    -- 链接库路径
    add_linkdirs(path.join(pixLibDir, "bin", "x64"))
    -- 链接库
    add_links("d3dcompiler")
    add_links("D3D12")
    add_links("dxgi")
    add_links("WinPixEventRuntime.lib")
target_end()

