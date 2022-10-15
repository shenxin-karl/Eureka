
#ifndef USE_CARTOON_SHADING
    #define DIFF_SHADING_FACTOR(NdotL) (NdotL)
    #define SPEC_SHADING_FACTOR(NdotH) (NdotH)
#else
    float CarToonDiffShadingFactor(float NdotL) {
        return NdotL <= 0.f ? 0.4 : (NdotL <= 0.5 ? 0.6 : 1.0);
    }

    float CarToonSpecShadingFactor(float NdotH) {
        return NdotH <= 0.1 ? 0.0 : (NdotH <= 0.8 ? 0.5 : 0.8);
    }
    #define DIFF_SHADING_FACTOR(NdotL) CarToonDiffShadingFactor(NdotL)
    #define SPEC_SHADING_FACTOR(NdotH) CarToonSpecShadingFactor(NdotH)
#endif


struct MaterialData {
    float3 diffuseAlbedo;   // 反照率
    float  roughness;       // 粗糙度
    float3 fresnelFactor;   
    float  metallic;        // 金属度
};

MaterialData calcMaterialData(float4 diffuseAlbedo, float roughness, float metallic) {
    MaterialData mat;
    mat.diffuseAlbedo = diffuseAlbedo.xyz;
    mat.roughness = max(roughness, 0.00001);
    mat.fresnelFactor = lerp(float3(0.04, 0.04, 0.04), diffuseAlbedo.rgb, metallic);
    mat.metallic = metallic;
    return mat;
}

struct LightData {
    float3 strength;        // 辐射强度
    float  falloffStart;    // 点光源/聚光灯:衰减开始距离
    float3 direction;       // 方向光/聚光灯:光源方向
    float  falloffEnd;      // 点光源/聚光灯:衰减结束距离
    float3 position;        // 点光源位置
    float  spotPower;       // 聚光灯 pow 指数
};


static const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = SPEC_SHADING_FACTOR(max(dot(N, H), 0.0));
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySmith(float3 N, float3 V, float3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

// ----------------------------------------------------------------------------
float3 FresnelSchlick(float cosTheta, float3 F0) {
    return F0 + (1.0 - F0) * pow(saturate(1.0 - cosTheta), 5.0);
}

float3 BRDFLambert(float3 diffuse)
{
    return diffuse / PI;
}

// ----------------------------------------------------------------------------
float3 CookTorrance(float3 radiance, float3 L, float3 N, float3 V, MaterialData mat) {
    // Cook-Torrance BRDF
    float3 H = normalize(V + L);
    float NDF = DistributionGGX(N, H, mat.roughness);
    float G = GeometrySmith(N, V, L, mat.roughness);
    float3 F = FresnelSchlick(saturate(dot(H, V)), mat.fresnelFactor);

    float3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
    float3 specular = numerator / denominator;

    // kS is equal to Fresnel
    float3 kS = F;
    float3 kD = 1.0 - kS;
    kD *= 1.0 - mat.metallic;
    return (BRDFLambert(kD * mat.diffuseAlbedo) + specular) * radiance;
}

// ----------------------------------------------------------------------------
float CalcAttenuation(float d, float falloffStart, float falloffEnd) {
    return 1.0 - saturate((d - falloffStart) / (falloffEnd - falloffStart));
}

// ----------------------------------------------------------------------------
float3 ComputeDirectionLight(LightData light, MaterialData mat, float3 N, float3 V) {
    float3 L = light.direction;
    float NdotL = DIFF_SHADING_FACTOR(saturate(dot(N, L)));
    float3 lightStrength = light.strength * NdotL;
    return CookTorrance(lightStrength, L, N, V, mat);
}

// ----------------------------------------------------------------------------
float3 ComputePointLight(LightData light, MaterialData mat, float3 N, float3 V, float3 worldPosition) {
    float3 lightVec = light.position - worldPosition;
    float dis = length(lightVec);
    if (dis > light.falloffEnd)
        return 0.f;

    float3 L = lightVec / dis;
    float NdotL = DIFF_SHADING_FACTOR(saturate(dot(N, L)));
    float attenuation = CalcAttenuation(dis, light.falloffStart, light.falloffEnd);
    float3 lightStrength = light.strength * NdotL * attenuation;
    return CookTorrance(lightStrength, L, N, V, mat);
}

// ----------------------------------------------------------------------------
float3 ComputeSpotLight(LightData light, MaterialData mat, float3 N, float3 V, float3 worldPosition) {
    float3 lightVec = light.position - worldPosition;
    float dis = length(lightVec);
    if (dis > light.falloffEnd)
        return 0.f;

    float3 L = lightVec / dis;
    float NdotL = DIFF_SHADING_FACTOR(saturate(dot(N, L)));
    float3 lightStrength = light.strength * NdotL;
    float attenuation = CalcAttenuation(dis, light.falloffStart, light.falloffEnd);
    lightStrength *= attenuation;
    float spotFactor = pow(saturate(dot(L, light.direction)), light.spotPower);
    lightStrength *= spotFactor;
    return CookTorrance(lightStrength, L, N, V, mat);
}
