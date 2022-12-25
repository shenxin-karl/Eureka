
function get_dxc_config(target) 
    local configPath = assert(target:values("ShaderCompileConfigPath"))
    includes(configPath)
    return CompileShaderConfig
end

rule("utils.dxc")
    set_extensions(".hlsl")
    on_load(function (target)
        local headerdir = path.join(target:autogendir(), "rules", "utils", "dxc")
        if not os.isdir(headerdir) then
            os.mkdir(headerdir)
        end
        target:add("includedirs", headerdir)
    end)

    before_buildcmd_file(function(target, batchcmds, sourcefile_bin, opt)
        function get_dxc_config(target) 
            local configPath = assert(target:values("ShaderCompileConfigPath"))
            local configName = assert(target:values("ShaderCompileConfigName"))
            import(configName, { rootdir = configPath, alias = "config" })
            return config
        end

        local config = get_dxc_config(target)
        local compile_infos = config.get_compile_infos(sourcefile_bin)
        if not compile_infos then
            return
        end
        
        local headerdir = path.absolute(path.join(target:autogendir(), "rules", "utils", "dxc"))
        target:add("includedirs", headerdir)
        batchcmds:mkdir(headerdir)

        -- add commands
        batchcmds:show_progress(opt.progress, "${color.build.object}generating.dxc %s", sourcefile_bin)

        -- find program
        import("xmake.modules.find_dxc", { rootdir = os.projectdir() })
        local program = find_dxc.find_program(target)

        for _, compile_info in ipairs(compile_infos) do
            local args = { "/Qstrip_rootsignature", "/nologo", "/Zi" }
            table.insert(args, "/E" .. compile_info.entryPoint)

            local includedirs = config.get_include_dirs()
            if includedirs then
                for _, dir in ipairs(includedirs) do
                    table.insert(args, "/I "..dir)
                end
            end
            
            if is_mode("debug") then
                table.insert(args, "/Od")
            end

            for k, v in pairs(compile_info.macros or {}) do
                table.insert(args, string.format("/D%s=%s", tostring(k), tostring(v)))
            end

            local output = compile_info.output
            if not output then
                output = string.format("%s_%s", path.basename(sourcefile_bin), compile_info.entryPoint)
            end
            
            local headerfile = path.join(headerdir, output .. ".h")
            local outputPdbFileName =  path.join(headerdir, output .. ".pdb")
            table.insert(args, "/Fh " .. headerfile)
            table.insert(args, "/Fd " .. outputPdbFileName)
            table.insert(args, "/Vn " .. ("g_" .. output))
            table.insert(args, "/T" .. compile_info.target)
            table.insert(args, path.absolute(sourcefile_bin))
            batchcmds:vrunv(program, args)

            -- add deps
            batchcmds:add_depfiles(sourcefile_bin)
            batchcmds:set_depmtime(os.mtime(headerfile))
            batchcmds:set_depcache(target:dependfile(headerfile))
        end
    end)
rule_end()