#include "Common.hlsli"

#define PACKING_VELOCITY_UINT32
#include "PixelPacking_Velocity.hlsli"

// Difference in pixels for velocity after which the pixel is marked as no-history valid for 1920x1080
#define FRAME_VELOCITY_IN_PIXELS_DIFF 128   

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

cbuffer CBData : register(b0) {
    float4 gResolution;         // width, height, 1/width, 1/height
    float4 gZBufferParam;       // near, far, (near * far), (far - near)
    float2 gJitter;
    uint   gFrameNumber;
	uint   gFlag;
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
Texture2D<float3>              gScreenMap   : register(t0);
Texture2D<packed_velocity_t>   gVelocityMap : register(t1);
Texture2D<float3>              gTemporalMap : register(t3);


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
	    float2 uv = (cin.GroupID.xy * NUM_THREAD + index - 0.5) * gResolution.zw;
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

float2 GetTexcoord(float2 dispatchID) {
    return (dispatchID + 0.5) * gResolution.zw;
}

float3 GetCurrentColor(uint2 groupThreadID) {
	uint2 index = groupThreadID.xy + 1;
    return Unpack_R11G11B10_FLOAT(SharedColor[index.x][index.y]);
}

float3 GetVelocity(ComputeIn cin) {
	return UnpackVelocity(gVelocityMap[cin.DispatchThreadID.xy]);
}

float3 GetHistory(float2 prevScreenST) {
	// 双三次插值: https://stackoverflow.com/questions/13501081/efficient-bicubic-filtering-code-in-glsl
	const float2 rcpResolution = gResolution.zw;
    const float2 fractional = frac( prevScreenST );
    const float2 uv = ( floor( prevScreenST ) + float2( 0.5f, 0.5f ) ) * rcpResolution;

    // 5-tap bicubic sampling (for Hermite/Carmull-Rom filter) -- (approximate from original 16->9-tap bilinear fetching) 
    const float2 t =  fractional;
    const float2 t2 = fractional * fractional;
    const float2 t3 = t2 * fractional;
    const float s = 0.5;

    const float2 w0 = -s * t3 + 2.f * s * t2 - s * t;
    const float2 w1 = (2.f - s ) * t3 + (s - 3.f) * t2 + 1.f;
    const float2 w2 = (s - 2.f) * t3 + (3 - 2.f * s ) * t2 + s * t;
    const float2 w3 = s * t3 - s * t2;
    const float2 s0 = w1 + w2;
    const float2 f0 = w2 / ( w1 + w2 );
    const float2 m0 = uv + f0 * rcpResolution;
    const float2 tc0 = uv - 1.f * rcpResolution;
    const float2 tc3 = uv + 2.f * rcpResolution;

    const float3 A = gTemporalMap.SampleLevel(gSamLinearClamp, float2(m0.x,  tc0.y), 0);
    const float3 B = gTemporalMap.SampleLevel(gSamLinearClamp, float2(tc0.x, m0.y),  0);
    const float3 C = gTemporalMap.SampleLevel(gSamLinearClamp, float2(m0.x,  m0.y),  0);
    const float3 D = gTemporalMap.SampleLevel(gSamLinearClamp, float2(tc3.x, m0.y),  0);
    const float3 E = gTemporalMap.SampleLevel(gSamLinearClamp, float2(m0.x,  tc3.y), 0);
    const float3 color = ( 0.5 * (A + B) * w0.x + A * s0.x + 0.5 * (A + B) * w3.x ) * w0.y + 
						 ( B * w0.x + C * s0.x + D * w3.x ) * s0.y                                               + 
                         ( 0.5 * (B + E) * w0.x + E * s0.x + 0.5 * (D + E) * w3.x ) * w3.y;
    return color;
}

RWTexture2D<float3> gOutputMap : register(u0);
[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
    StoreCurrentColor(cin);
    float3 currentFrameColor = GetCurrentColor(cin.GroupThreadID.xy);

    float3 velocity = GetVelocity(cin);
    float velocityConfidenceFactor = saturate(1.0 - (length(velocity.xy) / FRAME_VELOCITY_IN_PIXELS_DIFF));

    float2 prevFrameScreenST = cin.DispatchThreadID.xy + velocity.xy + gJitter;
    float3 prevFrameScreenUV = float3(GetTexcoord(prevFrameScreenST), velocity.z);

    const float uvWeight = (all(prevFrameScreenUV >= 0.0) && all(prevFrameScreenUV <= 1.0)) ? 1.0 : 0.0;
    const bool hasValidHistory = velocityConfidenceFactor * uvWeight;
    gOutputMap[cin.DispatchThreadID.xy] = hasValidHistory * currentFrameColor;
}