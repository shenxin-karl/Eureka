#include "Common.hlsli"

#pragma shader_feature _ _COLOR_GRADING

float3 ACESToneMapping(float3 color, float adaptedLum) {
	const float A = 2.51f;
	const float B = 0.03f;
	const float C = 2.43f;
	const float D = 0.59f;
	const float E = 0.14f;
	color *= adaptedLum;
	return (color * (A * color + B)) / (color * (C * color + D) + E);
}

float3 GammaCorrection(float3 color) {
	const float invGamma = 1.f / 2.2;
	return pow(color, float3(invGamma, invGamma, invGamma));
}

Texture2D<float4>	gScreenTexture : register(t0);
RWTexture2D<float4> gOutputMap	   : register(u0);

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           // 3D index of the thread group in the dispatch.
    uint3 GroupThreadID     : SV_GroupThreadID;     // 3D index of local thread ID in a thread group.
    uint3 DispatchThreadID  : SV_DispatchThreadID;  // 3D index of global thread ID in the dispatch.
    uint  GroupIndex        : SV_GroupIndex;        // Flattened local index of the thread within a thread group.
};

float2 CalcTexcoord(ComputeIn cin) {
	float2 texDimes;
	gScreenTexture.GetDimensions(texDimes.x, texDimes.y);
	return (cin.DispatchThreadID.xy) / (texDimes - 1.0);
}

// 每个 lut 都是 256x16 内部有 16 个 16x16 的块.
// 从左到的块, 由 b 通道决定. 块内 u 坐标由 r 通道决定
// 块内 v 坐标由 g 通道决定.
// floor(c * 15.0) / 15.0 向下取整到 0~15 之间
// 240是最后一块的起始位置, 最后除以 256 归一化到 0~1
#define S_NORMALIZE_FACTOR (1.0 / 255.0)
#define T_NORMALIZE_FACTOR (1.0 / 15.0)
float FloorPixel(float c) {
	return floor(c * 15.0) * (1.0 / 15.0) * 15.0;
}

float FloorBlock(float b) {
	return floor(b * 15.0) * (1.0 / 15.0) * 240.0;
}

float CeilPixel(float c) {
	return ceil(c * 15.0) * (1.0 / 15.0) * 15.0;
}
float CeilBlock(float b) {
	return ceil(b * 15.0) * (1.0 / 15.0) * 240.0;
}

Texture2D gColorLutMap : register(t1);
float3 ColorLut(float3 color) {
	float u0 = (FloorBlock(color.b) + FloorPixel(color.r)) * S_NORMALIZE_FACTOR;
	float v0 = FloorPixel(color.g) * T_NORMALIZE_FACTOR;
	float3 left = gColorLutMap.SampleLevel(gSamPointClamp, float2(u0, v0), 0).rgb;

	float u1 = (CeilBlock(color.b) + CeilPixel(color.r)) * S_NORMALIZE_FACTOR;
	float v1 = CeilPixel(color.g) * T_NORMALIZE_FACTOR;
	float3 right = gColorLutMap.SampleLevel(gSamPointClamp, float2(u1, v1), 0).rgb;

	color.r = lerp(left.r, right.r, frac(color.r * 15.0));
	color.g = lerp(left.g, right.g, frac(color.g * 15.0));
	color.b = lerp(left.b, right.b, frac(color.b * 15.0));
	return color;
}


[numthreads(16, 16, 1)]
void CS(ComputeIn cin) {
	float2 uv = CalcTexcoord(cin);
	float4 sampleColor = gScreenTexture.SampleLevel(gSamPointClamp, uv, 0);
	float3 screenColor = sampleColor.rgb;
	float alpha = sampleColor.a;

#if !defined(DO_NOTHING)
	screenColor = ACESToneMapping(screenColor, 1.0);

	#if defined(_COLOR_GRADING)
		screenColor = ColorLut(screenColor);
	#endif

	screenColor = GammaCorrection(screenColor);
#endif
	gOutputMap[cin.DispatchThreadID.xy] = float4(screenColor, alpha);
}