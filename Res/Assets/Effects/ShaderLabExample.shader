
Properties {
    _Bool0("test bool true", bool) = true
    _Bool1("test bool false", Bool) = false
    _Int0("test int", int) = -10
    _Int1("test int", Int) = 1000
    _Int2("test int", Int) = -1000
    _Range0("test range", range(-10, 10)) = 5
    _Range1("test Range", Range(-10, +10)) = 0
    _Float0("test float", float) = .7f
    _Float1("test Float", Float) = 0.f
    _Float2_0("test float2", float2) = (0, .7f)
    _Float3_0("test float2", float3) = (0, -1, -1)
    _Float4_0("test float2", Float4) = (0, -1, -1, 1)
    _AlbedoTex("albedo texture", 2D) = white
    _NormalTex("normal texture", 2D) = Bump
    _LightMapTex("lightMap texture", 2D) = black
}

HLSLINCLUDE 
    flaot4 getAlbedo() {
        return 1.0;
    }
    struct VertexIn {
        float3 position     : POSITION0;
        float3 normal       : NORMAL0;
        float2 texcoord     : TEXCOORD0;
    };
ENDHLSL

Pass("BasePass") {
    VertexShader: vert
    PixelShader: frag
    ShaderFeature: _AAA _BBB _CCC

    HLSLPROGRAM
        
        #include "generated/include.hlsl"
        VertexOut vert(VertexIn vin) {
            VertexOut vout = (VertexOut)0;
            return vout;
        }
        float4 frag(VertexOut pin) : SV_TARGET {
        }
    ENDHLSL
}
