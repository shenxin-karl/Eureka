#ifndef __COMMON_HLSLI_
#define __COMMON_HLSLI_

#define PRE_PASS_SPACE			space8
#define PRE_OBJ_SPACE			space0

cbuffer CbPrePass : register(b8, PRE_PASS_SPACE) {
    // camera
	float4x4 gMatView;
	float4x4 gMatInvView;
	float4x4 gMatProj;
	float4x4 gMatInvProj;
	float4x4 gMatViewProj;
	float4x4 gMatInvViewProj;
	float3   gCameraPos;
	float	 gNearClip;
    float3   gCameraLookUp;
	float	 gFarClip;
	float4   gCameraLookAt;

    // RenderTarget
	float2   gRenderTargetSize;
	float2   gInvRenderTargetSize;

    /// time
	float	gTotalTime;
	float	gDeltaTime;

    /// fog
	float    gFogStart;
    float    gFogEnd;
    float4   gFogColor;						

	// TAA
	float4x4 gMatJitterViewProj;	// 抖动的 ViewProj
	float4x4 gMatViewport;			// 未抖动 world to viewport
	float4x4 gMatPreViewport;		// 上一帧为抖动 world to viewport
};

cbuffer CbPreObject : register(b8, PRE_OBJ_SPACE) {
    float4x4 gMatWorld;
    float4x4 gMatInvWorld;
    float4x4 gMatNormal;
    float4x4 gMatInvNormal;
	float4x4 gMatPreFrameWorld;
};

SamplerState gSamPointWrap					   : register(s0, space0);
SamplerState gSamPointClamp					   : register(s1, space0);
SamplerState gSamLinearWrap					   : register(s2, space0);
SamplerState gSamLinearClamp				   : register(s3, space0);
SamplerState gSamAnisotropicWrap			   : register(s4, space0);
SamplerState gSamAnisotropicClamp			   : register(s5, space0);
SamplerComparisonState gSamLinearShadowCompare : register(s6, space0);
SamplerComparisonState gSamPointShadowCompare  : register(s7, space0);

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

#endif