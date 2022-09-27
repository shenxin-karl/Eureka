#ifndef __COMMON_HLSLI_
#define __COMMON_HLSLI_

#define PRE_PASS_SPACE			space8
#define PRE_OBJ_SPACE			space0

struct CbPrePass : register(b8, PASS_SPACE) {
    // camera
	float4x4 matView;
	float4x4 matInvView;
	float4x4 matProj;
	float4x4 matInvProj;
	float4x4 matViewProj;
	float4x4 matInvViewProj;
	float3   cameraPos;
	float	 nearClip;
    float3   cameraLookUp;
	float	 farClip;
    float4   cameraLookAt

    // RenderTarget
	float2   renderTargetSize;
	float2   invRenderTargetSize;

    /// time
	float	totalTime;
	float	deltaTime;

    /// fog
    float4   fogColor;						
	float    fogStart;
    float    fogEnd;
    float2   cbPerPassPad1;
};

struct CbPreObject : register(b8, OBJ_SPACE) {
    float4x4 matWorld;
    float4x4 matInvWorld;
    float4x4 matNormal;
    float4x4 matInvNormal;
};

#endif