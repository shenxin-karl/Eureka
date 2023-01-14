
package("stduuid")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "stduuid"))
    set_policy("package.install_always", true)
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()