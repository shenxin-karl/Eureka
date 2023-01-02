--[[
    -- example
    add_rules("utils.build_in", {
        extensions = { ".hlsl", ".hlsli" },
        namespace = "BuildIn",
        output = "BuildInShader",
        include_path = include_dir
    })
]]


rule("utils.build_in")
    set_extensions(".*")
    on_load(function (target)
        target:add("includedirs", target:extraconf("rules", "utils.build_in", "path"))
    end)

    on_buildcmd_files(function(target, batchcmds, sourcebatch, opt)
         local depfiles = {}
         local headerdir = path.join(target:autogendir(), "rules", "utils", "build_in")
         batchcmds:mkdir(headerdir)
         target:add("includedirs", target:extraconf("rules", "utils.build_in", "path"))

        for _, sourcefile_bin in ipairs(sourcebatch.sourcefiles) do
            local headerfile = path.join(headerdir, path.filename(sourcefile_bin) .. ".h")
            batchcmds:show_progress(opt.progress, "${color.build.object}generating.build_in %s", sourcefile_bin)
            local argv = {"lua", "private.utils.bin2c", "-i", path(sourcefile_bin), "-o", path(headerfile)}
            batchcmds:vrunv(os.programfile(), argv, {envs = {XMAKE_SKIP_HISTORY = "y"}})
            table.insert(depfiles, sourcefile_bin)
        end

        import("xmake.modules.build_in_code_gen", { rootdir = os.projectdir() })

        local namespace_name = assert(target:extraconf("rules", "utils.build_in", "namespace"))
        local outputfile = assert(target:extraconf("rules", "utils.build_in", "output"))
        local outputpath = assert(target:extraconf("rules", "utils.build_in", "include_path"))

        -- output header file
        do 
            local header_file_name = path.join(outputpath, outputfile..".h")
            local header_file = io.open(header_file_name, "w")
            batchcmds:mkdir(path.directory(header_file_name))
            header_file:write(string.format(build_in_code_gen.get_header_format(), namespace_name))
            header_file:close()
        end

        -- output source file
        do
            local global_var_definations = {}
            local map_item_definations = {}
            for _, sourcefile_bin in ipairs(sourcebatch.sourcefiles) do
                local filename = path.filename(sourcefile_bin)
                local var_name = string.gsub(filename, "%.", "_")
                local hlsl_inc_name = string.format("#include \"%s\"", filename..".h")
                local item_key = string.gsub(sourcefile_bin, "\\", "/")
                local var_def_str = string.format(build_in_code_gen.get_global_var_format(), var_name, hlsl_inc_name)
                local item_def_str = string.format(build_in_code_gen.get_map_item_format(), item_key, var_name)
                table.insert(global_var_definations, var_def_str)
                table.insert(map_item_definations, item_def_str)
            end

            local var_defination = table.concat(global_var_definations)
            local map_item_defination = table.concat(map_item_definations)
            local source_file_name = path.join(headerdir, outputfile..".cpp")
            local source_file = io.open (source_file_name, "w")
            source_file:write(string.format(
                build_in_code_gen.get_source_format(), 
                namespace_name, 
                var_defination, 
                map_item_defination
            ))
            source_file:close()

            local objectfile = target:objectfile(source_file_name)
            table.insert(target:objectfiles(), objectfile)
            batchcmds:show_progress(opt.progress, "${color.build.object}compile.build_in %s", source_file_name)
            batchcmds:compile(source_file_name, objectfile)

            -- add deps
            batchcmds:add_depfiles(depfiles)
            batchcmds:set_depmtime(os.mtime(objectfile))
            batchcmds:set_depcache(target:dependfile(objectfile))
        end
    end)
rule_end()

