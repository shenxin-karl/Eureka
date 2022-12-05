#include "Common.hlsli"

struct VertexIn {
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VertexOut {
	float4 SVPosition : SV_POSITION;
	float2 texcoord	  : TEXCOORD;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	vout.SVPosition = float4(vin.position.x, vin.position.y, 0.0, 1.0);
	vout.texcoord = vin.texcoord;
	return vout;
}

Texture2D<float4> gScreenMap : register(t0);
float4 PS(VertexOut pin) : SV_Target {
	return gScreenMap.Sample(gSamPointClamp, pin.texcoord);
}