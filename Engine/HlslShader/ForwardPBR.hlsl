#include <Common.hlsli>
#include <CookTorrance.hlsli>

cbuffer cbMaterial : register(b0) {
	float4 gDiffuseAlbedo;
	float  gRoughness;
	float  gMetallic;
};

cbuffer cbLight : register(b0, PRE_PASS_SPACE) {
	LightData gLightData;
};

struct VertexIn {
	float3 position  : POSITION0;
	float3 normal	 : NORMAL;
	float2 texCoord0 : TEXCOORD0;
};

struct VertexOut {
	float4 SVPosition : SV_POSITION;
	float3 position   : POSITION0;
	float3 normal	  : NORMAL;
	float2 texCoord0  : TEXCOORD0;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	float4 worldPosition = mul(matWorld, float4(vin.position, 1.0));
	vout.SVPosition = mul(matViewProj, worldPosition);
	vout.position = worldPosition.xyz;
	vout.normal = mul((float3x3)matNormal, vin.normal);
	vout.texCoord0 = vin.texCoord0;
	return vout;
}

Texture2D gAlbedoMap : register(t0);
float4 PS(VertexOut pin) : SV_Target {
	float4 diffuseAlbedo = gDiffuseAlbedo;
	diffuseAlbedo.xyz *= gAlbedoMap.Sample(gSamLinearWrap, pin.texCoord0).rgb;
	MaterialData mat = calcMaterialData(diffuseAlbedo, gRoughness, gMetallic);

	float3 N = normalize(pin.normal);
	float3 V = normalize(gLightData.position - pin.position);
	float3 color = ComputeDirectionLight(gLightData, mat, N, V);
	return float4(color, 1.0);
}