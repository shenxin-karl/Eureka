#include "Common.hlsli"
#include "PixelPacking_Velocity.hlsli"

// Difference in pixels for velocity after which the pixel is marked as no-history valid for 1920x1080

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

cbuffer CBData : register(b0) {
    float4 gResolution;         // width, height, 1/width, 1/height
    float2 gJitter;
    uint   gFrameNumber;
	uint   gDebugFlag;
};

#define HAS_HISTORY_FLAG        (1 << 0)
#define ENABLE_BICUBIC_SAMPLE   (1 << 1)

float HasHistory() {
	return (gDebugFlag & HAS_HISTORY_FLAG) ? 1.0 : 0.0;
}

bool GetEnableBicubicSample() {
	return false;
}

// Reinhard tone mapper
float LuminanceRec709( float3 inRGB ) {
    return dot( inRGB, float3( 0.2126f, 0.7152f, 0.0722f ) );
}

float3 Reinhard(float3 inRGB) {
	return inRGB / ( 1.0 + LuminanceRec709( inRGB ) );
}

#define NUM_THREAD 8
groupshared uint SharedColor[NUM_THREAD+2][NUM_THREAD+2];

Texture2D<float3>              gScreenMap   : register(t0);
Texture2D<packed_velocity_t>   gVelocityMap : register(t1);
Texture2D<float4>              gTemporalMap : register(t2);
RWTexture2D<float4>            gOutputMap   : register(u0);

void StoreCurrentColor(ComputeIn cin) {
	/*  http://wojtsterna.blogspot.com/2018/02/directx-11-hlsl-gatherred.html
	 *  Gather Method, 当前像素在 w 上
	 *  +----+----+
	 *	| w  |  z |
	 *	|----+----| 
	 *  | x  |  y |
	*	+----+----+
    */  
    if (cin.GroupThreadID.x < 5 && cin.GroupThreadID.y < 5) {
        uint2 groupStart = cin.GroupID.xy * NUM_THREAD;
        uint2 index = cin.GroupThreadID.xy * 2;
	    float2 uv = (groupStart + index) * gResolution.zw - 0.5 * gResolution.zw;
        float4 reds = gScreenMap.GatherRed(gSamLinearClamp, uv);
        float4 greens = gScreenMap.GatherGreen(gSamLinearClamp, uv);
        float4 blues = gScreenMap.GatherBlue(gSamLinearClamp, uv);
        SharedColor[index.x+0][index.y+0] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.w, greens.w, blues.w)));
        SharedColor[index.x+1][index.y+0] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.z, greens.z, blues.z)));
        SharedColor[index.x+0][index.y+1] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.x, greens.x, blues.x)));
        SharedColor[index.x+1][index.y+1] = Pack_R11G11B10_FLOAT(Reinhard(float3(reds.y, greens.y, blues.y)));
    }
    GroupMemoryBarrierWithGroupSync();
}

float2 GetTexcoord(float2 dispatchID) {
    return (dispatchID + 0.5) * gResolution.zw;
}

float3 GetCurrentColor(uint2 groupThreadID) {
    uint packedRGB = SharedColor[groupThreadID.x][groupThreadID.y];
    return Unpack_R11G11B10_FLOAT(packedRGB);
}

float3 GetVelocity(ComputeIn cin) {
	return UnpackVelocity(gVelocityMap[cin.DispatchThreadID.xy]);
}

float4 cubic(float x) {
    float4 w;
    float x2 = x * x;
    float x3 = x2 * x;
    w.x = -x3 + 3.0 * x2 - 3.0 * x + 1.0;
    w.y = +3.0 * x3 - 6.0 * x2 + 4.0;
    w.z = -3.0 * x3 + 3.0 * x2 + 3.0 * x + 1.0;
    w.w = +x3;
    return w / 6.0;
}

float4 BicubicTexture(in float2 texcoord) {
	float2 resolution = gResolution.xy;
	texcoord *= resolution;

	float fx = frac(texcoord.x);
    float fy = frac(texcoord.y);
    texcoord.x -= fx;
    texcoord.y -= fy;

    fx -= 0.5;
    fy -= 0.5;

    float4 xcubic = cubic(fx);
    float4 ycubic = cubic(fy);

    float4 c = float4(texcoord.x - 0.5, texcoord.x + 1.5, texcoord.y - 0.5, texcoord.y + 1.5);
    float4 s = float4(xcubic.x + xcubic.y, xcubic.z + xcubic.w, ycubic.x + ycubic.y, ycubic.z + ycubic.w);
    float4 offset = c + float4(xcubic.y, xcubic.w, ycubic.y, ycubic.w) / s;

    float4 sample0 = gTemporalMap.SampleLevel(gSamLinearClamp, float2(offset.x, offset.z) * gResolution.zw, 0);
    float4 sample1 = gTemporalMap.SampleLevel(gSamLinearClamp, float2(offset.y, offset.z) * gResolution.zw, 0);
    float4 sample2 = gTemporalMap.SampleLevel(gSamLinearClamp, float2(offset.x, offset.w) * gResolution.zw, 0);
    float4 sample3 = gTemporalMap.SampleLevel(gSamLinearClamp, float2(offset.y, offset.w) * gResolution.zw, 0);

    float sx = s.x / (s.x + s.y);
    float sy = s.z / (s.z + s.w);
    return lerp(lerp(sample3, sample2, sx), lerp(sample1, sample0, sx), sy);
}

float4 GetHistory(float2 prevScreenUV) {
	if (GetEnableBicubicSample()) {
	    return BicubicTexture(prevScreenUV);
	} else {
		return gTemporalMap.SampleLevel(gSamLinearClamp, prevScreenUV, 0);
	}
}


[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
    StoreCurrentColor(cin);

    uint2 groupST = cin.GroupThreadID.xy + 1;
    float3 currentFrameColor = GetCurrentColor(groupST);

    float3 velocity = GetVelocity(cin);
    float velocityConfidenceFactor = GetVelocityConfidenceFactor(velocity);

    float2 prevFrameScreenST = cin.DispatchThreadID.xy + velocity;
    float2 prevFrameScreenUV = float3(GetTexcoord(prevFrameScreenST), velocity.z);

    const float uvWeight = (all(prevFrameScreenUV >= 0.0) && all(prevFrameScreenUV <= 1.0)) ? 1.0 : 0.0;
    const bool hasValidHistory = (HasHistory() * velocityConfidenceFactor * uvWeight) > 0.001;

    float4 finalColor = 0.0;
    if (hasValidHistory) {
        float4 historyColor = GetHistory(prevFrameScreenUV);
        float weight = historyColor.a * velocityConfidenceFactor;
		const float newWeight = saturate( float( 1.f ) / ( float( 2.f ) - weight ) );

        finalColor = float4(lerp(currentFrameColor, historyColor.rgb, weight), newWeight);
    } else {
        float3 neighbourhoodsColor = currentFrameColor;
        uint2 offsets[4] = { uint2(+1, -1), uint2(+1, +1), uint2(-1, +1), uint2(-1, -1) };
        [unroll] for (uint i = 0; i < 4; ++i)
			neighbourhoodsColor += GetCurrentColor(groupST + offsets[i]);

        neighbourhoodsColor *= 0.2;
        finalColor = float4(neighbourhoodsColor, 0.5);
    }
    gOutputMap[cin.DispatchThreadID.xy] = finalColor;
}