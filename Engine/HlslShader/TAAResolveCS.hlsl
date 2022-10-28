#include "Common.hlsli"

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

cbuffer CBData : register(b0) {
    float4 gResolution;         //width, height, 1/width, 1/height
    float2 gJitter;
    uint   gFrameNumber;
	uint   padding0;
};



// Reinhard tone mapper
float LuminanceRec709( float3 inRGB ) {
    return dot( inRGB, float3( 0.2126f, 0.7152f, 0.0722f ) );
}

float3 Reinhard(float3 inRGB) {
    return inRGB / ( 1.0 + LuminanceRec709( inRGB ) );
}

float3 InverseReinhard( float3 inRGB ) {
    return inRGB / ( 1.0 - LuminanceRec709( inRGB ) );
}

#define NUM_THREAD 8
groupshared uint SharedColor[NUM_THREAD+2][NUM_THREAD+2];
Texture2D<float3> gScreenMap : register(t0);

void StoreCurrentColor(ComputeIn cin) {
	/*  http://wojtsterna.blogspot.com/2018/02/directx-11-hlsl-gatherred.html
	 *  Gather Method, 当前像素在 w 上
	 *  w---------z
	 *	|         |
	 *	|         | 
	 *  |         |
	  *	x---------y
	  *
	  * +---+
	  * |   |
      * +---c
      * 从把当前像素的 uv 变成左上角, 减去 float2(1, 1)
    */  
    if (cin.GroupThreadID.x < 5 && cin.GroupThreadID.y < 5) {
        uint2 index = cin.GroupThreadID.xy * 2;
	    float2 uv = (cin.GroupID.xy * NUM_THREAD + index - 1) * gResolution.zw;
        float4 reds = gScreenMap.GatherRed(gSamLinearClamp, uv);
        float4 greens = gScreenMap.GatherGreen(gSamLinearClamp, uv);
        float4 blues = gScreenMap.GatherBlue(gSamLinearClamp, uv);
        SharedColor[index.x-1][index.y-1] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.w, greens.w, blues.w)));
        SharedColor[index.x+0][index.y-1] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.z, greens.z, blues.z)));
        SharedColor[index.x-1][index.y+0] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.x, greens.x, blues.x)));
        SharedColor[index.x+0][index.y+0] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.y, greens.y, blues.y)));
    }
    GroupMemoryBarrierWithGroupSync();
}

float3 GetCurrentColor(uint2 groupThreadID) {
	uint2 index = groupThreadID.xy + 1;
    return Unpack_R11G11B10_FLOAT(SharedColor[index.x][index.y]);
}

RWTexture2D<float3> gOutputMap : register(u0);

[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
    StoreCurrentColor(cin);
    gOutputMap[cin.DispatchThreadID.xy] = InverseReinhard(GetCurrentColor(cin.GroupThreadID.xy));
}