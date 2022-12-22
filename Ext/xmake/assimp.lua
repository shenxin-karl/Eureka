
package("assimp")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "assimp"))
    set_policy("package.install_always", true)
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        table.insert(configs, "-DASSIMP_INSTALL_PDB=OFF")
        import("package.tools.cmake").install(package, configs)
    end)
package_end()