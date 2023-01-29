
SourcePath: "xxx.hlsl"
Properties {
    _MainTex("this is main texture", 2D) = white 
    _Cutoff("alpha test cutoff", float) = 0.5
    _Float2Test("float2 111", float2) = (0.5, 1)
    
}

/*

Pass {
    Vertex: "vert"
    Fragment: "frag"
    ShaderFeature: "aaa"
}

*/