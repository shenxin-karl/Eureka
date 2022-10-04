#include <Common.hlsli>

// shader_feature _ _ENALBE_DIFFUSE_MAP
// shader_feature _ _ENABLE_NORMAL_MAP
// shader_feature _ _ENABLE_ROUGHNESS_MAP
// shader_feature _ _ENALBE_METALLIC_MAP
// shader_feature _ _ENABLE_AO_MAP


struct VertexIn {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float3 texcoord : TEXCOORD0;
#if defined(_ENABLE_NORMAL_MAP)
	float4 tangent	  : TANGENT;
#endif
};

struct VertexOut {
	float4 SVPosition : SV_POSITION;
	float4 position   : POSITION;
	float2 texcoord   : TEXCOORD;
	float3 normal	  : NORMAL;
#if defined(_ENABLE_NORMAL_MAP)
	float4 tangent	  : TANGENT;
#endif
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	float4 worldPosition = mul(matWorld, float4(vin.position, 1.0));
	vout.SVPosition = mul(matViewProj, worldPosition);
	vout.position = worldPosition;
	vout.texcoord = vin.texcoord;
	vout.normal = mul((float3x3)matNormal, vin.normal);
	#if define(_ENABLE_NORMAL_MAP)
		vout.tangent.xzy = mul((float3x3)matWorld, vin.tangent.xyz);
		vout.tangent.w = vin.tangent.w;
	#endif
	return vout;
}


struct PixelOut {
	float4 gBuffer0 : SV_TARGET0;			// .rgb albedo 								.a unused
	float4 gBuffer1 : SV_TARGET1;			// .rgb normal								.a unused
	float3 gBuffer2 : SV_TARGET2;			// .r ao 	.g roughness 	.b metallic		.a unused
};

cbuffer cbMaterial : register(b0) {
	float4 gDiffuseAlbedo;
	float  gRoughness;
	float  gMetallic;
	float  gAo;
	float  padding1;
};

Texture2D gDiffuseMap 	: register(t0);
Texture2D gNormalMap	: register(t1);
Texture2D gRoughnessMap : register(t2);
Texture2D gMetallicMap	: register(t3);
Texture2D gAoMap 		: register(t4);

float3 getAlbedo(VertexIn pin) {
	float3 albedo = gDiffuseAlbedo.rgb;
	#if defined(_ENALBE_DIFFUSE_MAP)
		albedo *= gDiffuseMap.Sample(gSamLinearClamp, pin.texcoord);
	#endif
	return albedo;
}

float3 getNormal(VertexIn pin) {
	float3 N = normalize(pin.normal);
	#if defined(_ENABLE_NORMAL_MAP)
		float3 T = normalize(pin.tangent.xyz);
		float3 B = cross(N, T) * pin.tangent.w;
		float3 sampleNormal = gNormalMap.Sample(gSamLinearClamp, pin.texcoord).xyz * 2.0 - 1.0;
		N = T * sampleNormal.x +
			B * sampleNormal.y +
			N * sampleNormal.z ;
	#endif
	return N;
}

float3 getAoRoughnessMetallic(VertexOut pin) {
	float ao = gAo;
	#if defined(_ENABLE_AO_MAP)
		ao *= gAoMap.sampleNormal(gSamLinearClamp, pin.texcoord).r;
	#endif

	float roughness = gRoughness;
	#if defined(_ENABLE_ROUGHNESS_MAP)
		roughness *= gRoughnessMap.Sample(gSamLinearClamp, pin.texcoord).r;
	#endif

	float metallic = gMetallic;
	#if defined(_ENALBE_METALLIC_MAP)
		metallic *= gMetallicMap.Sample(gSamLinearClamp, pin.texcoord).r;
	#endif

	return float3(ao, roughness, metallic);
}


PixelOut PS(VertexOut pin) {
	PixelOut pout;
	pout.gBuffer0 = getAlbedo(pin);
	pout.gBuffer1 = getNormal(pin);
	pout.gBuffer2 = getAoRoughnessMetallic(pin);
}