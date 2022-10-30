
struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

Texture2D<float3>  gTemporalColor : register(t0);
Texture2D<float>   gDepthMap	  : register(t1);

RWTexture2D<float3> gOutputColorMap : register(u0);
RWTexture2D<float>  gOutputDepthMap : register(u1);

float LuminanceRec709( float3 inRGB ) {
    return dot( inRGB, float3( 0.2126f, 0.7152f, 0.0722f ) );
}

float3 InverseReinhard( float3 inRGB ) {
    return inRGB / ( 1.f - LuminanceRec709( inRGB ) );
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
	gOutputColorMap[cin.DispatchThreadID.xy] = gTemporalColor[cin.DispatchThreadID.xy];
    gOutputDepthMap[cin.DispatchThreadID.xy] = gDepthMap[cin.DispatchThreadID];

	//int2 groupUL = cin.GroupID.xy * NUM_THREAD - BORDER_SIZE;
    //for (uint i = 0; i < TILE_PIXEL_COUNT; i += GROUP_SIZE) {
	//    int2 st = groupUL + (i % NUM_THREAD);
    //}
}