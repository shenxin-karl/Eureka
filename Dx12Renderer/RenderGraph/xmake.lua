
target("RenderGraph")
    set_languages("c++20")
    set_group("Dx12Renderer")
    set_kind("static")
    add_cxflags("/MP")
    add_headerfiles("**.h")
    add_headerfiles("**.hpp")
    add_files("**.cpp")
    add_includedirs(DX12RENDERER_DIR)
    add_includedirs(DX12RENDERER_EXT_DIR)
    add_deps("Dx12lib")
target_end()