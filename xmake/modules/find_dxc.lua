
find_dxc = find_dxc or {}
function find_program(target) 
    local dxcdir = path.join(os.projectdir(), "Dx12Renderer", "Ext", "dxc", "bin")
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

return find_dxc