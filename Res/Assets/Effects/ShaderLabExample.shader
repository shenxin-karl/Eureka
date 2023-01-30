
SourcePath: "Assets/Shaders/FXAA.hlsl"
Properties {
    _Bool0("test bool true", bool) = true
    _Bool1("test bool true", Bool) = false
    _Int0("test int", int) = -10
    _Int1("test int", Int) =1000
    _Int1("test int", Int) =1000
    _Range0("test int", range(-10, 10)) = 1000
    _Range0("test int", Range(-10, +10)) = 0
    _Float0("test int", float) = .7f
    _Range1("test int", Float) = 0.f
}

/*

Pass {
    Vertex: "vert"
    Fragment: "frag"
    ShaderFeature: "aaa"
}

*/