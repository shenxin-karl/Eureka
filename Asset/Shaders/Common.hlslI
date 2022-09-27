struct CbPrePass : register(b0, space8) {
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
	float		   totalTime;
	float		   deltaTime;

    /// fog
    float4   fogColor;						
	float          fogStart;
    float          fogEnd;
    float2   cbPerPassPad1;
};

struct CbPreObject : register(b1, space8) {
    float4x4 matWorld;
    float4x4 matInvWorld;
    float4x4 matNormal;
    float4x4 matInvNormal;
};
