package("antlr4")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "antlr4", "runtime", "Cpp"))
    add_includedirs("include/antlr4-runtime")
    add_defines("ANTLR4CPP_STATIC", { public = true })
    on_install(function (package)
        local configs = { "-DANTLR_BUILD_CPP_TESTS=OFF" }
        if is_mode("debug") then
            table.insert(configs, "-DCMAKE_BUILD_TYPE=Debug")
            table.insert(configs, "-DWITH_STATIC_CRT=OFF")
        elseif is_mode("release") then
            table.insert(configs, "-DCMAKE_BUILD_TYPE=Release")
        else
            table.insert(configs, "-DCMAKE_BUILD_TYPE=RelWithDebInfo")
            table.insert(configs, "-DWITH_STATIC_CRT=OFF")
        end
        import("package.tools.cmake").install(package, configs)
    end)
package_end()