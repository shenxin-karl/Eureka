package("antlr4")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "antlr4", "runtime", "Cpp"))
    add_includedirs("include/antlr4-runtime")
    

    on_load(function(package)
        -- if package:config("shared") then
        --     package:set("links", "antlr4-runtime")
        --     package:set("libfiles", path.join(package:installdir("lib"), "antlr4-runtime.lib"))
        -- else
        --     package:set("links", "antlr4-runtime-static")
        --     package:set("libfiles", path.join(package:installdir("lib"), "antlr4-runtime-static.lib"))
        -- end 
    end)

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