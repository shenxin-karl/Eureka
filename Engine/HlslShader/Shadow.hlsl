#include "Common.hlsli"
#pragma shader_feature _ ENABLE_ALPHA_TEST

struct VertexIn {
	float3 position : POSITION;
#ifdef ENABLE_ALPHA_TEST
	float2 texcoord : TEXCOORD;
#endif
};

struct VertexOut {
	float4 SVPosition : SV_Position;
#ifdef ENABLE_ALPHA_TEST
	float2 texcoord   : TEXCOORD;
#endif
};

cbuffer RootConstants : register(b0) {
	float4x4 gViewProj;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	float4 worldPosition = mul(gMatWorld, float4(vin.position, 1.0));
	vout.SVPosition = mul(gViewProj, worldPosition);
	#ifdef ENABLE_ALPHA_TEST
		vout.texcoord = vin.texcoord;
	#endif
	return vout;
}

cbuffer cbMaterial : register(b0) {
	float4 gDiffuseAlbedo;
	float  gRoughness;
	float  gMetallic;
	float  gAo;
	float  gAlphaCutoff;
};

Texture2D<float4> gAlbedoMap : register(b0);
void PS(VertexOut pin) {
	#ifdef ENABLE_ALPHA_TEST
		float alpha = gDiffuseAlbedo.a * gAlbedoMap.Sample(gSamPointWrap, pin.texcoord).a;
		clip(alpha - gAlphaCutoff);
	#endif
}