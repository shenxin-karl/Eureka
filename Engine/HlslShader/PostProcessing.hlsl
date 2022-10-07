#pragma shader_feature _ _ENABLE_GAMMA_CORRECTION
#pragma shader_feature _ _ENABLE_ACES_TONE_MAPPING
#pragma shader_feature _ _COLOR_GRADING

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

float3 ACESToneMapping(float3 color, float adaptedLum) {
	const float A = 2.51f;
	const float B = 0.03f;
	const float C = 2.43f;
	const float D = 0.59f;
	const float E = 0.14f;
	color *= adaptedLum;
	return (color * (A * color + B)) / (color * (C * color + D) + E);
}

float3 GammaCorrection(float3 color) {
	const float invGamma = 1.f / 2.2;
	return pow(color, float3(invGamma, invGamma, invGamma));
}

Texture2D gScreenTexture   : register(t0);
Texture2D gColorGradingMap : register(t1);

float4 PS(VertexOut pin) : SV_Target {
	
}