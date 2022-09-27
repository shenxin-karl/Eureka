
cbuffer cbPreCamera : register(b0) {
	float4x4 gViewProj;
	float	 gRoughness;
};

struct VertexIn {
	float3 position : POSITION;
};

struct VertexOut {
	float4 SVPosition    : SV_POSITION;
	float3 localPosition : POSITION;
};

VertexOut VS(VertexIn vin) {
	VertexOut vout;
	vout.SVPosition = mul(gViewProj, vin.position);
	vout.localPosition = vin.position;
	return vout;
}

TextureCube gEnvMap         : register(t0);
SamplerState gSamLinearWrap	: register(s0);

static const uint kSampleCount = 1024;


float RadicalInverseVDC(uint bits) {
	bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

/**
 * \brief    计算低差异序列随机数    
 * \param i  当前样本索引
 * \param N  样本数
 * \return   返回随机数
 */
float2 Hammersley(uint i, uint N) {
    return float2(float(i)/float(N), RadicalInverseVDC(i));
}

/**
 * \brief       		计算GGX重要性采样向量    
 * \param Xi    		低差异序列生成的随机数
 * \param N     		表面法线(归一化)
 * \param roughness		粗糙度
 * \param TBN           切线空间矩阵
 * \return      		采样向量
 */
static const float PI = 3.141592654;
float3 ImportanceSampleGGX(float2 Xi, float roughness, float3x3 TBN) {
	float a = roughness;
    float phi = 2.0 * PI * Xi.x;
    float cosTh = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float sinTh = sqrt(1.0 - cosTh * cosTh);
    float cosPh = cos(phi);
    float sinPh = sin(phi);
    float3 H = {
		sinTh * cosPh,
        sinTh * sinPh,
        cosTh,
    };
    return mul(H, TBN);
}

float4 PS(VertexOut pin) {
	float3 N = normalize(pin.localPosition);
    float3 up = abs(N.z) < 0.999 ? float3(0, 0, 1) : float3(1, 0, 0);
    float3 tangent = normalize(cross(up, N));
    float3 bitangent = normalize(cross(N, tangent));
    float3x3 TBN = float3x3(tangent, bitangent, N);

	float3 V = N;
    float3 colorSum = 0.0;
    float weightSum = 0.0;
	for (uint i = 0; i < kSampleCount; ++i) {
		float2 Xi = Hammersley(i, kSampleCount);
	    float3 H = ImportanceSampleGGX(Xi, gRoughness, TBN);
	    float3 L = normalize(2.0 * dot(V, H) * H - V);
	    float NdotL = dot(N, L);
	    if (NdotL > 0.0) {
		    colorSum += gEnvMap.SampleLevel(gSamLinearWrap, L, 0).rgb * NdotL;
	        weightSum += NdotL;
	    }
	}

	return float4(colorSum / weightSum, 1.0);
}