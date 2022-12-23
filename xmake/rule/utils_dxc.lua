
function get_dxc_program(target) 
    local dxcdir = path.join(os.porjectdir(), "Ext", "dxc", "bin")
    if target:is_arch("arm64") then
        dxcdir = path.join(dxcdir, "arm64")
    elseif target:is_arch("x86") then
        dxcdir = path.join(dxcdir, "x86")
    elseif target:is_arch("x64", "x86_64") then
        dxcdir = path.join(dxcdir, "x64")
    else
        assert(false, "Unknown system architecture")
    end
    import("lib.detect.find_program")
    local program = find_program("dxc.exe", { pathes = { dxcdir } })
    return assert(program)
end

rule("utils.dxc")
    set_extensions(".hlsl", "hlsli")
    on_load(function (target)
        local headerdir = path.join(target:autogendir(), "rules", "utils", "dxc")
        if not os.isdir(headerdir) then
            os.mkdir(headerdir)
        end
        target:add("includedirs", headerdir)
    end)
    before_buildcmd_file(function(target, batchcmds, sourcefile_bin, opt)
        print(debug.traceback())
        local entryPoint = opt.entryPoint
        local target = opt.target
        local macros = opt.macros
        local outputFileName = opt.output

        assert(entryPoint, "rule.utils.dxc.before_buildcmd_file invalid opt.entryPoint")
        assert(target, "rule.utils.dxc.before_buildcmd_file invalid opt.target")

        -- get header file
        if not outputFileName then
            outputFileName = path.filename(sourcefile_bin) .. entryPoint .. ".h"
        end

        local headerdir = path.join(target:autogendir(), "rules", "utils", "dxc")
        local headerfile = path.join(headerdir, outputFileName)
        target:add("includedirs", headerdir)

        -- add commands
        batchcmds:show_progress(opt.progress, "${color.build.object}generating.dxc %s", sourcefile_bin)
        batchcmds:mkdir(headerdir)

        local program = get_dxc_program(target)
        
        -- local argv = {"lua", "private.utils.bin2c", "-i", path(sourcefile_bin), "-o", path(headerfile)}
        -- local linewidth = target:extraconf("rules", "utils.bin2c", "linewidth")
        -- if linewidth then
        --     table.insert(argv, "-w")
        --     table.insert(argv, tostring(linewidth))
        -- end
        -- batchcmds:vrunv(os.programfile(), argv, {envs = {XMAKE_SKIP_HISTORY = "y"}})

        -- add deps
        batchcmds:add_depfiles(sourcefile_bin)
        batchcmds:set_depmtime(os.mtime(headerfile))
        batchcmds:set_depcache(target:dependfile(headerfile))
    end)
rule_end()