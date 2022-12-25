CompileShaderConfig = CompileShaderConfig or {}

if not CompileShaderConfig.shader_list then
    CompileShaderConfig.shader_list = {
        ["CopyToBack.hlsl"] = {
            { entryPoint = "VS", target = "vs_6_0" },
            { entryPoint = "PS", target = "ps_6_0" },
        },
        ["ClusterDeferredCS.hlsl"] = {
            { entryPoint = "CS", target = "cs_6_0" },
        },
        ["CalcClusterFrustumCS"] = {
            { entryPoint = "CS", target = "cs_6_0" },
        },
        ["FXAA.hlsl"] = {
            { entryPoint = "VS", target = "vs_6_0" },
            { entryPoint = "PS", target = "ps_6_0" },
        },
        ["LightingPassCS.hlsl"] = {
            { entryPoint = "CS", target = "cs_6_0" },
        },
        ["SharpenTAACS.hlsl"] = {
            { entryPoint = "CS", target = "cs_6_0" },
        },
        ["TAAResolveCS.hlsl"] = {
            { entryPoint = "CS", target = "cs_6_0" },
        },
        ["UpdateLightBoundingSphere.hlsl"] = {
            { entryPoint = "CS", target = "cs_6_0", macros = { UPDATE_POINT_LIGHT = 1 }, output = "UpdatePointLightBoundingSphere_CS" },
            { entryPoint = "CS", target = "cs_6_0", macros = { UPDATE_SPOT_LIGHT = 1 }, output = "UpdateSpotLightBoundingSphere_CS"   },
        },
    }
end

function get_include_dirs() 
    local currDir = path.absolute(os.scriptdir())
    return { currDir }
end

function get_compile_infos(sourcefile_bin) 
    local filename = path.filename(sourcefile_bin)
    return CompileShaderConfig.shader_list[filename]
end

return CompileShaderConfig