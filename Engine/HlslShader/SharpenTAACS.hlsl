
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

// groupshared float groupSharedR[TILE_PIXEL_COUNT];
// groupshared float groupSharedG[TILE_PIXEL_COUNT];
// groupshared float groupSharedB[TILE_PIXEL_COUNT];

[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
	gOutputColorMap[cin.DispatchThreadID.xy] = InverseReinhard(gTemporalColor[cin.DispatchThreadID.xy]);
}