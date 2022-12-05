#include "Common.hlsli"

cbuffer FXAASetting : register(b0) {
    float gMinThreshold;            // 最小亮度差阈值;    　    default:    0.0312f
    float gThreshold;               // 最大亮度差阈值    　     default:    0.125f;
    float gConsoleTangentScale;     // 边缘切线上的缩放         default:    0.5f
    float gSharpness;               // 当切向量垂直时上的缩放    default:    8.f
};

struct VertexIn {
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VertexOut {
	float4 SVPosition : SV_POSITION;
	float2 texcoord	  : TEXCOORD;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	vout.SVPosition = float4(vin.position.x, vin.position.y, 0.0, 1.0);
	vout.texcoord = vin.texcoord;
	return vout;
}

Texture2D gScreenMap : register(t0);
float CalcLuminance(float3 color) {
    return dot(color, float3(0.299, 0.587, 0.114));
}

float4 PS(VertexOut pin) : SV_Target {
	float s = pin.texcoord.x;
    float t = pin.texcoord.y;

    float width;
    float height;
    gScreenMap.GetDimensions(width, height);

    float invWidth  = 1.0 / width;
    float invHeight = 1.0 / height;

    float invHalfWidth  = invWidth * 0.5;
    float invHalfHeight = invHeight * 0.5;

    float4 pixelColor = gScreenMap.SampleLevel(gSamLinearClamp, float2(s, t), 0.0);
    float M  = CalcLuminance(pixelColor.rgb);
    float NW = CalcLuminance(gScreenMap.SampleLevel(gSamLinearClamp, float2(s-invHalfWidth, t+invHalfHeight), 0.0).rgb);
    float NE = CalcLuminance(gScreenMap.SampleLevel(gSamLinearClamp, float2(s+invHalfWidth, t+invHalfHeight), 0.0).rgb);
    float SW = CalcLuminance(gScreenMap.SampleLevel(gSamLinearClamp, float2(s-invHalfWidth, t-invHalfHeight), 0.0).rgb);
    float SE = CalcLuminance(gScreenMap.SampleLevel(gSamLinearClamp, float2(s+invHalfWidth, t-invHalfHeight), 0.0).rgb);
    float maxLuma = max(max(NW, NE), max(SW, SE));
    float minLuma = min(min(NW, NE), min(SW, SE));
    float contrast = max(maxLuma, M) - min(minLuma, M);
    if (contrast < max(gMinThreshold, maxLuma*gThreshold))
        return pixelColor;
    
    float2 N = float2((NE+SE) - (NW+SW), (NW+NE) - (SW+SE));
    float2 tangent = float2(-N.y, N.x);
    float2 dir = normalize(tangent);
    float2 dir1 = dir * float2(invWidth, invHeight) * gConsoleTangentScale;
    
    float4 S0 = gScreenMap.SampleLevel(gSamLinearClamp, float2(s, t) + dir1, 0.0);
    float4 L0 = gScreenMap.SampleLevel(gSamLinearClamp, float2(s, t) - dir1, 0.0);
    float4 result1 = (S0 + L0) * 0.5;
    
    float minDirAbsAxis = min(abs(dir.x), abs(dir.y)) * gSharpness;
    float2 dir2 = clamp(dir / minDirAbsAxis, -2, +2) * 2 * float2(invWidth, invHeight);
    float4 S1 = gScreenMap.SampleLevel(gSamLinearClamp, float2(s, t) + dir2, 0.0);
    float4 L1 = gScreenMap.SampleLevel(gSamLinearClamp, float2(s, t) - dir2, 0.0);
    float4 result2 = result1 * 0.5 + (S1 + L1) * 0.25;
    if (CalcLuminance(result2.rgb) >= minLuma && CalcLuminance(result2.rgb) <= maxLuma)
        result1 = result2;
        
    return result1;
}