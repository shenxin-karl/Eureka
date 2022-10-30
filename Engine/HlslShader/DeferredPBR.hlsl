#include "Common.hlsli"

#define PACKING_VELOCITY_UINT32
#include "PixelPacking_Velocity.hlsli"

#pragma shader_feature _ _ENABLE_ALPHA_CUTOFF
#pragma shader_feature _ _ENABLE_DIFFUSE_MAP
#pragma shader_feature _ _ENABLE_NORMAL_MAP
#pragma shader_feature _ _ENABLE_ROUGHNESS_MAP _ENABLE_SPECULAR_MAP
#pragma shader_feature _ _ENABLE_METALLIC_MAP _ENABLE_METALLIC_ROUGHNESS_MAP_G _ENABLE_LIGHT_MAP_G
#pragma shader_feature _ _ENABLE_AO_MAP _ENABLE_LIGHT_MAP

struct VertexIn {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 texcoord : TEXCOORD0;
#if defined(_ENABLE_NORMAL_MAP)
	float4 tangent	  : TANGENT;
#endif
};

struct VertexOut {
	float4 SVPosition   : SV_POSITION;
	float4 position     : POSITION;
	float2 texcoord     : TEXCOORD;
	float3 normal	    : NORMAL;
#if defined(_ENABLE_NORMAL_MAP)
	float4 tangent	    : TANGENT;
#endif
	float4 currViewportPos : TEXCOORD1;
	float4 prevViewportPos : TEXCOORD2;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	float4 worldPosition = mul(gMatWorld, float4(vin.position, 1.0));
	vout.SVPosition = mul(gMatJitterViewProj, worldPosition);
	vout.position = worldPosition;
	vout.texcoord = vin.texcoord;
	vout.normal = mul((float3x3)gMatNormal, vin.normal);
	#if defined(_ENABLE_NORMAL_MAP)
		vout.tangent.xzy = mul((float3x3)gMatWorld, vin.tangent.xyz);
		vout.tangent.w = vin.tangent.w;
	#endif

	vout.currViewportPos = mul(gMatViewport, worldPosition);
	vout.prevViewportPos = mul(gMatPreViewport, mul(gMatPreFrameWorld, float4(vin.position, 1.0)));
	return vout;
}

struct PixelOut {
	float4 gBuffer0	: SV_TARGET0;			// .rgb albedo 								.a unused
	float4 gBuffer1	: SV_TARGET1;			// .rgb normal								.a unused
	float4 gBuffer2 : SV_TARGET2;			// .r ao 	.g roughness 	.b metallic		.a unused
	packed_velocity_t velocity : SV_TARGET3;			
};

cbuffer cbMaterial : register(b0) {
	float4 gDiffuseAlbedo;
	float  gRoughness;
	float  gMetallic;
	float  gAo;
	float  gAlphaCutoff;
};

Texture2D gDiffuseMap 	: register(t0);
Texture2D gNormalMap	: register(t1);

#if defined(_ENABLE_ROUGHNESS_MAP)
	Texture2D gRoughnessMap : register(t2);
#elif defined(_ENABLE_SPECULAR_MAP)
	Texture2D gSpecularMap  : register(t2);
#endif

Texture2D gMetallicMap	: register(t3);

#if defined(_ENABLE_LIGHT_MAP)
	Texture2D gLightMap		: register(t4);
#else
	Texture2D gAoMap 		: register(t4);
#endif

float4 getAlbedo(VertexOut pin) {
	float3 albedo = gDiffuseAlbedo.rgb;
	float4 albedoBuffer = (float4)1.0;
	#if defined(_ENABLE_DIFFUSE_MAP)
		albedoBuffer = gDiffuseMap.Sample(gSamLinearWrap, pin.texcoord);
		albedo *= albedoBuffer.xyz;
	#endif

	#if defined(_ENABLE_ALPHA_CUTOFF)
		float alpha = albedoBuffer.a * gDiffuseAlbedo.a;
		clip(alpha - gAlphaCutoff);
	#endif
	return float4(albedo, 1.0);
}

float4 getNormal(VertexOut pin) {
	float3 N = normalize(pin.normal);
	#if defined(_ENABLE_NORMAL_MAP)
		float3 T = normalize(pin.tangent.xyz);
		float3 B = cross(N, T) * pin.tangent.w;
		float3 sampleNormal = gNormalMap.Sample(gSamLinearWrap, pin.texcoord).xyz * 2.0 - 1.0;
		N = T * sampleNormal.x +
			B * sampleNormal.y +
			N * sampleNormal.z ;
		N = normalize(N);
	#endif
	return float4(N * 0.5f + 0.5f, 1.0);
}

float4 getAoRoughnessMetallic(VertexOut pin) {
	float ao = gAo;
	float metallic = gMetallic;
	float roughness = gRoughness;

	#if defined(_ENABLE_AO_MAP)
		ao *= gAoMap.Sample(gSamLinearWrap, pin.texcoord).r;
	#elif defined(_ENABLE_LIGHT_MAP)
		ao *= gLightMap.Sample(gSamLinearWrap, pin.texcoord).r;
	#endif

	float2 roughnessMapColor = 1.0;
	#if defined(_ENABLE_ROUGHNESS_MAP)
		roughnessMapColor = gRoughnessMap.Sample(gSamLinearWrap, pin.texcoord).rg;
		roughness *= roughnessMapColor.r * 2.f;
	#elif defined(_ENABLE_SPECULAR_MAP)
		roughness *= 1.0 - gSpecularMap.Sample(gSamLinearWrap, pin.texcoord).r;
	#endif

	#if defined(_ENABLE_METALLIC_MAP)
		metallic *= gMetallicMap.Sample(gSamLinearWrap, pin.texcoord).r;
	#elif defined(_ENABLE_METALLIC_ROUGHNESS_MAP_G)
		metallic *= roughnessMapColor.g * 2.f;
	#elif defined(_ENABLE_LIGHT_MAP_G)
		metallic *= gLightMap.Sample(gSamLinearWrap, pin.texcoord).g;
	#endif

	return float4(ao, roughness, metallic, 1.0);
}


packed_velocity_t GetVelocity(VertexOut pin) {
	float4 currPos = pin.currViewportPos;
	float4 prevPos = pin.prevViewportPos;
	currPos.xy /= currPos.w;
	prevPos.xy /= prevPos.w;
	float3 packed = float3(prevPos.xy - currPos.xy, prevPos.z);
	return PackVelocity(packed);
}

PixelOut PS(VertexOut pin) {
	PixelOut pout;
	pout.gBuffer0 = getAlbedo(pin);
	pout.gBuffer1 = getNormal(pin);
	pout.gBuffer2 = getAoRoughnessMetallic(pin);
	pout.velocity = GetVelocity(pin);
	return pout;
}