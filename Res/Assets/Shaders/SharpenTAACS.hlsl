#include "Common.hlsli"

cbuffer CBData : register(b0) {
    float4 gResolution;         // width, height, 1/width, 1/height
    float  gSharpenFactor;       
};

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

Texture2D<float4>   gTemporalColor : register(t0);
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
#define TILE_SIZE_X      (NUM_THREAD + 2 * BORDER_SIZE)
#define TILE_SIZE_Y      (NUM_THREAD + 2 * BORDER_SIZE)
#define TILE_PIXEL_COUNT (TILE_SIZE_X * TILE_SIZE_Y)

groupshared float gs_R[TILE_PIXEL_COUNT];
groupshared float gs_G[TILE_PIXEL_COUNT];
groupshared float gs_B[TILE_PIXEL_COUNT];

float3 LoadSample(uint ldsIndex) {
    return float3(gs_R[ldsIndex], gs_G[ldsIndex], gs_B[ldsIndex]);
}

[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
	const int2 groupUL = cin.GroupID.xy * uint2(NUM_THREAD, NUM_THREAD) - BORDER_SIZE;
    for (uint i = cin.GroupIndex; i < TILE_PIXEL_COUNT; i += GROUP_SIZE) {
	    int2 ST = groupUL + int2(i % TILE_SIZE_X, i / TILE_SIZE_X);
        float4 color = gTemporalColor[ST];
        const float3 colorNoAlpha = InverseReinhard(color.rgb);
        color.rgb = log2(1.0 + colorNoAlpha);
        gs_R[i] = color.r;
        gs_G[i] = color.g;
        gs_B[i] = color.b;
    }
    GroupMemoryBarrierWithGroupSync();

    const uint localIndex = (cin.GroupThreadID.x + BORDER_SIZE) + (cin.GroupThreadID.y + BORDER_SIZE) * TILE_SIZE_X;
    const float3 center = LoadSample(localIndex);
    const float3 neighbors = LoadSample(localIndex - 1)           + 
					         LoadSample(localIndex + 1)           + 
                             LoadSample(localIndex - TILE_SIZE_X) +
                             LoadSample(localIndex + TILE_SIZE_X) ;

    const float3 edgeColor = gSharpenFactor * (center - 0.25 * neighbors);
    const float3 finalColor = exp2(max(0, center + edgeColor)) - 1.0;
    gOutputColorMap[cin.DispatchThreadID.xy] = finalColor;
}