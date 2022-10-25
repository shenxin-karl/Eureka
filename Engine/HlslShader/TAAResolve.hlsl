#include "Common.hlsli"

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};


#define NUM_THREAD 8

// The standard 32-bit HDR color format.  Each float has a 5-bit exponent and no sign bit.
uint Pack_R11G11B10_FLOAT( float3 rgb ) {
    // Clamp upper bound so that it doesn't accidentally round up to INF 
    // Exponent=15, Mantissa=1.11111
    rgb = min(rgb, asfloat(0x477C0000));  
    uint r = ((f32tof16(rgb.x) + 8) >> 4) & 0x000007FF;
    uint g = ((f32tof16(rgb.y) + 8) << 7) & 0x003FF800;
    uint b = ((f32tof16(rgb.z) + 16) << 17) & 0xFFC00000;
    return r | g | b;
}

float3 Unpack_R11G11B10_FLOAT( uint rgb ) {
    float r = f16tof32((rgb << 4 ) & 0x7FF0);
    float g = f16tof32((rgb >> 7 ) & 0x7FF0);
    float b = f16tof32((rgb >> 17) & 0x7FE0);
    return float3(r, g, b);
}

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

groupshared uint SharedColor[NUM_THREAD+2][NUM_THREAD+2];

Texture2D<float3> gScreenMap : register(t0);

void StoreCurrentColor(float2 uv, uint2 groupThreadID) {
	/*
	 *  +--------+
	 *	|        |
	 *	|        |
	  *	+--------+
    */
    float3 color = gScreenMap.SampleLevel(gSamPointClamp, uv, 0).rgb;
    uint2 index = groupThreadID + 1;
    SharedColor[index.x][index.y] = Pack_R11G11B10_FLOAT(Reinhard(color));
}


float2 CalcTexCoord(ComputeIn cin) {
	float2 texDimes;
    gScreenMap.GetDimensions(texDimes.x, texDimes.y);
    return cin.DispatchThreadID.xy / (texDimes - 1.0);
}

[numthreads(NUM_THREAD, NUM_THREAD, 1)]
void CS(ComputeIn cin) {
	float2 uv = CalcTexCoord(cin);
    StoreCurrentColor(uv, cin.GroupThreadID.xy);
}