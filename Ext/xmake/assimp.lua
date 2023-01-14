
package("assimp")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "assimp"))
    on_install(function (package)
        local configs = {
            "-DASSIMP_BUILD_SAMPLES=OFF",
            "-DASSIMP_BUILD_TESTS=OFF",
            "-DASSIMP_BUILD_DOCS=OFF",
            "-DASSIMP_BUILD_FRAMEWORK=OFF",
            "-DASSIMP_INSTALL_PDB=ON",
            "-DASSIMP_INJECT_DEBUG_POSTFIX=ON",
            "-DASSIMP_BUILD_ZLIB=ON",
            "-DSYSTEM_IRRXML=ON",
            "-DASSIMP_WARNINGS_AS_ERRORS=OFF",
            "-DASSIMP_BUILD_ASSIMP_TOOLS=OFF",
        }
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
        -- copy pdb
        if package:is_plat("windows") then
            if package:config("shared") then
                os.trycp(path.join(package:buildir(), "bin", "**.pdb"), package:installdir("bin"))
            else
                os.trycp(path.join(package:buildir(), "lib", "**.pdb"), package:installdir("lib"))
            end
        end
    end)
package_end()