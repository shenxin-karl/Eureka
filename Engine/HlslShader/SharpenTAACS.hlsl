#include "Common.hlsli"

cbuffer CBData : register(b0) {
    float4 gResolution;         // width, height, 1/width, 1/height
};

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

Texture2D<float3>   gTemporalColor : register(t0);
RWTexture2D<float3> gOutputColorMap : register(u0);

float LuminanceRec709( float3 inRGB ) {
    return dot( inRGB, float3( 0.2126f, 0.7152f, 0.0722f ) );
}

float3 InverseReinhard( float3 inRGB ) {
    const float3 currentColor = inRGB / (1.f - LuminanceRec709(inRGB));
    return max(currentColor, 0.0);
}

#define NUM_THREAD       8
#define BORDER_SIZE      1
#define GROUP_SIZE       (NUM_THREAD * NUM_THREAD)
#define TILE_PIXEL_COUNT ((NUM_THREAD + BORDER_SIZE) * (NUM_THREAD + BORDER_SIZE))

groupshared float4 SharedColor[NUM_THREAD+2][NUM_THREAD+2];
void StoreCurrentColor(ComputeIn cin) {
    if (cin.GroupThreadID.x < 5 && cin.GroupThreadID.y < 5) {
        const uint2 groupStart = cin.GroupID.xy * NUM_THREAD;
        const uint2 index = cin.GroupThreadID.xy * 2;
	    const float2 uv = (groupStart + index) * gResolution.zw - 0.5 * gResolution.zw;
        const float4 reds = gTemporalColor.GatherRed(gSamLinearClamp, uv);
        const float4 greens = gTemporalColor.GatherGreen(gSamLinearClamp, uv);
        const float4 blues = gTemporalColor.GatherBlue(gSamLinearClamp, uv);
        const float4 alphas = gTemporalColor.GatherAlpha(gSamLinearClamp, uv);
        SharedColor[index.x+0][index.y+0] = float4(InverseReinhard(float3(reds.w, greens.w, blues.w)), alphas.w);
        SharedColor[index.x+1][index.y+0] = float4(InverseReinhard(float3(reds.z, greens.z, blues.z)), alphas.z);
        SharedColor[index.x+0][index.y+1] = float4(InverseReinhard(float3(reds.x, greens.x, blues.x)), alphas.x);
        SharedColor[index.x+1][index.y+1] = float4(InverseReinhard(float3(reds.y, greens.y, blues.y)), alphas.y);
    }
    GroupMemoryBarrierWithGroupSync();
}

float4 GetColor(uint2 groupST) {
    return SharedColor[groupST.x][groupST.y];
}

[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
	StoreCurrentColor(cin);
    uint2 groupST = cin.GroupThreadID.xy + 1;
    float4 currentColor = GetColor(groupST);

    /*  0  1  0
     *  1 -4  1
     *  0  1  0
     */ 
    float3 sharpenColor = currentColor.rgb * -4.0    +
		GetColor(groupST + uint2(+1, -1)).rgb +
	    GetColor(groupST + uint2(-1, +0)).rgb +
	    GetColor(groupST + uint2(+1, +0)).rgb +
	    GetColor(groupST + uint2(+0, +1)).rgb ;
	//float3 filterColor = lerp(currentColor.rgb, sharpenColor, currentColor.a * 0.2);
    // gOutputColorMap[cin.DispatchThreadID.xy] = filterColor;
    gOutputColorMap[cin.DispatchThreadID.xy] = currentColor;
}