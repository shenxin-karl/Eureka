
function link_dxc_compiler() 
    local dxcDir = path.join(DX12RENDERER_EXT_DIR, "dxc")
    add_includedirs(path.join(dxcDir, "inc"), {public=true})
    local libDir = nil
    if is_arch("x86") then
        libDir = path.join(dxcDir, "lib", "x86")
    elseif is_arch("x64", "x86_64") then
        libDir = path.join(dxcDir, "lib", "x64")
    elseif is_arch("arm64") then
        libDir = path.join(dxcDir, "lib", "arm64")
    end
    add_linkdirs(libDir)
    add_links("dxcompiler")
end

add_requires("fmt")

target("Dx12lib")
    set_languages("c++latest")
    set_group("Dx12Renderer")
    set_kind("static")
    add_rules("utils.bin2c", {extensions = {".hlsl"}})
    add_defines("_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING", {public=true})
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_files("**.cpp")
    add_files("Texture/*.hlsl")
    add_includedirs(DX12RENDERER_DIR, {public=true})
    add_includedirs(DX12RENDERER_EXT_DIR, {public=true})
    local pixLibDir = path.join(DX12RENDERER_EXT_DIR, "WinPixEventRuntime", "winpixeventruntime.1.0.22081000");
    add_includedirs(path.join(pixLibDir, "Include", "WinPixEventRuntime"), {public=true})
    add_linkdirs(path.join(pixLibDir, "bin", "x64"))
    add_syslinks("d3dcompiler")
    add_syslinks("D3D12")
    add_syslinks("dxgi")
    add_links("WinPixEventRuntime")
    add_deps("DirectXTex")
    add_packages("fmt", {public=true})
    link_dxc_compiler()
target_end()

