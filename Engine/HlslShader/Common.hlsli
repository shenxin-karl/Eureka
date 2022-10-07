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
    float4   gFogColor;						
	float    gFogStart;
    float    gFogEnd;
    float2   gCbPerPassPad1;
};

cbuffer CbPreObject : register(b8, PRE_OBJ_SPACE) {
    float4x4 gMatWorld;
    float4x4 gMatInvWorld;
    float4x4 gMatNormal;
    float4x4 gMatInvNormal;
};

SamplerState gSamPointWrap					   : register(s0, space0);
SamplerState gSamPointClamp					   : register(s1, space0);
SamplerState gSamLinearWrap					   : register(s2, space0);
SamplerState gSamLinearClamp				   : register(s3, space0);
SamplerState gSamAnisotropicWrap			   : register(s4, space0);
SamplerState gSamAnisotropicClamp			   : register(s5, space0);
SamplerComparisonState gSamLinearShadowCompare : register(s6, space0);
SamplerComparisonState gSamPointShadowCompare  : register(s7, space0);

#endif