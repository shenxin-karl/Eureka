
package("assimp")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "Ext", "assimp"))

    add_configs("build_tools",           {description = "Build the supplementary tools for Assimp.", default = false, type = "boolean"})
    add_configs("double_precision",      {description = "Enable double precision processing.", default = false, type = "boolean"})
    add_configs("no_export",             {description = "Disable Assimp's export functionality (reduces library size).", default = false, type = "boolean"})
    add_configs("android_jniiosysystem", {description = "Enable Android JNI IOSystem support.", default = false, type = "boolean"})
    add_configs("asan",                  {description = "Enable AddressSanitizer.", default = false, type = "boolean"})
    add_configs("ubsan",                 {description = "Enable Undefined Behavior sanitizer.", default = false, type = "boolean"})

    add_deps("cmake", "zlib")
    if is_plat("windows") then
        add_syslinks("advapi32")
    end

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
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))

        local function add_config_arg(config_name, cmake_name)
            table.insert(configs, "-D" .. cmake_name .. "=" .. (package:config(config_name) and "ON" or "OFF"))
        end

        add_config_arg("shared",           "BUILD_SHARED_LIBS")
        add_config_arg("double_precision", "ASSIMP_DOUBLE_PRECISION")
        add_config_arg("no_export",        "ASSIMP_NO_EXPORT")
        add_config_arg("asan",             "ASSIMP_ASAN")
        add_config_arg("ubsan",            "ASSIMP_UBSAN")

        if package:is_plat("windows", "linux", "macosx", "mingw") then
            add_config_arg("build_tools", "ASSIMP_BUILD_ASSIMP_TOOLS")
        else
            table.insert(configs, "-DASSIMP_BUILD_ASSIMP_TOOLS=OFF")
        end

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