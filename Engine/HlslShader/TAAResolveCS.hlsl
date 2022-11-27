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
#define MIN_VARIANCE_GAMMA 0.75f // under motion
#define MAX_VARIANCE_GAMMA 2.f   // no motion

float HasHistory() {
	return (gDebugFlag & HAS_HISTORY_FLAG) ? 1.0 : 0.0;
}
bool GetEnableClipHistoryClip() {
	return true;
}

// Reinhard tone mapper
float LuminanceRec709(float3 inRGB) {
    return dot( inRGB, float3( 0.2126f, 0.7152f, 0.0722f ) );
}

float3 Reinhard(float3 inRGB) {
	return inRGB / ( 1.0 + LuminanceRec709( inRGB ) );
}

float3 RGB2YCoCg(float3 inRGB) {
    const float y  = dot(inRGB, float3(0.25f, 0.5f, 0.25f) );
    const float co = dot(inRGB, float3(0.5f, 0.f, -0.5f));
    const float cg = dot(inRGB, float3(-0.25f, 0.5f, -0.25f));
    return float3(y, co, cg);
}

float3 YCoCg2RGB(float3 inYCoCg) {
    const float r = dot(inYCoCg, float3(1.f, 1.f, -1.f));
    const float g = dot(inYCoCg, float3(1.f, 0.f, 1.f));
    const float b = dot(inYCoCg, float3(1.f, -1.f, -1.f));
    return float3(r, g, b);
}


#define NUM_THREAD 8
groupshared uint SharedColor[NUM_THREAD+2][NUM_THREAD+2];

Texture2D<float3>              gScreenMap   : register(t0);
Texture2D<float2>              gVelocityMap : register(t1);
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
        const uint2 groupStart = cin.GroupID.xy * NUM_THREAD;
        const uint2 index = cin.GroupThreadID.xy * 2;
	    const float2 uv = (groupStart + index) * gResolution.zw - 0.5 * gResolution.zw;
        const float4 reds = gScreenMap.GatherRed(gSamLinearClamp, uv);
        const float4 greens = gScreenMap.GatherGreen(gSamLinearClamp, uv);
        const float4 blues = gScreenMap.GatherBlue(gSamLinearClamp, uv);
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
    const uint packedRGB = SharedColor[groupThreadID.x][groupThreadID.y];
    return Unpack_R11G11B10_FLOAT(packedRGB);
}

float2 GetVelocity(ComputeIn cin) {
	return gVelocityMap[cin.DispatchThreadID.xy];
}

float GetVelocityConfidenceFactor(float2 velocity) {
	float len = length(velocity.xy * gResolution.xy);
    float factor = len / FRAME_VELOCITY_IN_PIXELS_DIFF;
    return saturate(1.0 - factor);
}

float4 GetHistory(float2 prevScreenUV) {
	return gTemporalMap.SampleLevel(gSamLinearClamp, prevScreenUV, 0);
}

float3 ClipHistoryColor(float3 inCurrentColor, float3 inHistoryColor, uint2 groupST, float inVarianceGamma) {
	[branch] if (!GetEnableClipHistoryClip())
		return inHistoryColor;

    const float rcpDivider = 1.f / 9.f;
	const uint2 offsets[8] = {
        uint2(-1, -1), uint2(-1, +0), uint2(-1, +1), uint2(+0, +1),
        uint2(+1, +1), uint2(+1, +0), uint2(+1, -1), uint2(+0, -1),
	};

    const float3 currentColorInYCoCg = RGB2YCoCg(inCurrentColor);
    float3 moment1 = currentColorInYCoCg;
    float3 moment2 = currentColorInYCoCg * currentColorInYCoCg;
    [unroll] for (uint i = 0; i < 8; ++i) {
	    const uint2 newST = groupST + offsets[i];
        const float3 newColor = RGB2YCoCg(GetCurrentColor(newST));
        moment1 += newColor;
        moment2 += newColor * newColor;
    }

    const float3 mean1 = moment1 * rcpDivider;
    const float3 mean2 = moment2 * rcpDivider;
    const float3 variance = sqrt(mean2 - (mean1 * mean1)) * inVarianceGamma;

    const float3 minC = YCoCg2RGB(mean1 - variance);
    const float3 maxC = YCoCg2RGB(mean1 + variance);
    const float3 toReturn = clamp(inHistoryColor, minC, maxC);
    return toReturn;
}


[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
    StoreCurrentColor(cin);

    const uint2 groupST = cin.GroupThreadID.xy + 1;
    const float3 currentFrameColor = GetCurrentColor(groupST);

    const float2 velocity = GetVelocity(cin);
    float velocityConfidenceFactor = GetVelocityConfidenceFactor(velocity);

    const float2 prevFrameScreenST = cin.DispatchThreadID.xy;
    const float2 prevFrameScreenUV = GetTexcoord(prevFrameScreenST) + velocity;

    const float uvWeight = (all(prevFrameScreenUV >= float2(0.0, 0.0)) && all(prevFrameScreenUV <= float2(1.0, 1.0))) ? 1.0 : 0.0;
    const bool hasValidHistory = (HasHistory() * velocityConfidenceFactor * uvWeight) > 0.001;

    float4 finalColor = 0.0;
    if (hasValidHistory) {
        const float4 rawHistoryColor = GetHistory(prevFrameScreenUV.xy);
        const float variantGamma = lerp(MIN_VARIANCE_GAMMA, MAX_VARIANCE_GAMMA, velocityConfidenceFactor*velocityConfidenceFactor);
        const float3 historyColor = ClipHistoryColor(currentFrameColor, rawHistoryColor.rgb, groupST, variantGamma);
        const float weight = rawHistoryColor.a * velocityConfidenceFactor;
		const float newWeight = saturate(1.f / (2.f - weight));
        finalColor = float4(lerp(currentFrameColor, historyColor.rgb, weight), newWeight);
    } else {
        float3 neighborsColor = currentFrameColor;
        const uint2 offsets[4] = { uint2(+1, -1), uint2(+1, +1), uint2(-1, +1), uint2(-1, -1) };
        [unroll] for (uint i = 0; i < 4; ++i)
			neighborsColor += GetCurrentColor(groupST + offsets[i]);

        neighborsColor *= 0.2;
        finalColor = float4(neighborsColor, 0.5);
    }
    gOutputMap[cin.DispatchThreadID.xy] = finalColor;
}