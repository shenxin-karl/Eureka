## 框架搭建

- [x] 自动解析顶点输入

- [x] 自动生成 RootSignature

- [x] BoundResource 反射

- [x] PBR 材质类

- [x] 相机引入

- [x] Shader Include 处理

- [x] Assimp 加载 PBR

- [x] Shader 支持 shader_feature 生成变体

- [ ] 确定好 RenderGraph 中获取 CbPrePass 的方式

    * step 是否加入 linkPass 方法


- [x] 好用的 ShaderLayout 枚举 包装类

- [x] mipmap 生成

  参考资料: [Learning DirectX 12 – Lesson 4 – Textures | 3D Game Engine Programming (3dgep.com)](https://www.3dgep.com/learning-directx-12-4/#Generate_Mipmaps_Compute_Shader)

- [x] 加入一个 GeometryGenerator 提供基本几何体

- [x] PSO 反射保存根参数偏移, 直接设置

- [x] ComputeShader 支持变体

- [ ] 新增 PartModel 用来渲染基础的几何体物体

从 ndc depth 转换到 线性深度

[www.humus.name/temp/Linearize depth.txt](http://www.humus.name/temp/Linearize depth.txt)
$$
\rm {(n * f) / (f - z * (f - n))}
$$

## PBR

- [x] 主应用定义好渲染 RenderGraph
- [x] 定义好 GBuffer 的作用
- [x] 渲染到 GBuffer
- [x] Compute Shader 计算方向光



参考资料:

[延迟着色法 - LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/05 Advanced Lighting/08 Deferred Shading/)

[光照 - LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/07 PBR/02 Lighting/)

[深度还原到世界坐标](https://stackoverflow.com/questions/32227283/getting-world-position-from-depth-buffer-value)



dx 中使用逆矩阵深度图还原到世界空间的方法

```cc
// uv 是屏幕空间的 uv
float4 CalcWorldPosition(float2 uv)
{
    // 特别注意, zNdc 保持 0~1 即可
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float4 pos = float4(uv * 2.0 - 1.0, zNdc, 1.0);
    pos.y *= -1.0;										// 这里要乘上 -1.0
    float4 worldPos = mul(gInvViewProj, pos);
    worldPos.xyz /= worldPos.w;
    return worldPos;
}
```



## ACES / ColorGrading / Gamma矫正



https://zhuanlan.zhihu.com/p/21983679

[HDR Tone Mapping - xiaOp的博客 (xiaoiver.github.io)](https://xiaoiver.github.io/coding/2019/02/05/HDR-Tone-Mapping.html)

[ColorGrading](https://github.com/lettier/3d-game-shaders-for-beginners/blob/master/sections/lookup-table.md)

- [x] Compute 后处理
- [ ] 使用 mipmap 生成，计算出整个屏幕的亮度， 更准确的 aces 调整

## FXAA

- [x] 做 FXAA 的同时，写回到 backBuffer 中

## Tile Based Deferred Rendering



[当前和未来渲染管线的延迟渲染 (intel.com)](https://www.intel.com/content/www/us/en/developer/articles/technical/deferred-rendering-for-current-and-future-rendering-pipelines.html)

https://zhuanlan.zhihu.com/p/62030747

https://zhuanlan.zhihu.com/p/85447953

https://www.cnblogs.com/X-Jun/p/16023346.html

https://zhuanlan.zhihu.com/p/71932575

https://zhuanlan.zhihu.com/p/339109155

 [Advancements-In-Tiled-Rendering.pdf](Advancements-In-Tiled-Rendering.pdf) 

点光源和聚光灯都使用包围球, 快速求交

- [x] 生成大量的点光源

- [x] 屏幕光源空间划分

- [x] compute 计算点光源

- [ ] compute 计算聚光灯

- [ ] 如果每帧需要更新光源的ViewSpacePosition数量太多时, 使用 ComputeShader 来更新

- [ ] 升级为按簇划分屏幕

compute shader 提取视锥体的方式

[momose_d blog: 2014年3月 (cocolog-nifty.com)](http://momose-d.cocolog-nifty.com/blog/2014/03/index.html)

intel 给出的的 demo 是错误的, 需要使用下面的计算方式

```cc
 // Work out scale/bias from [0, 1]    
float2 tileNum = float2(gRenderTargetSize.xy) * rcp(float2(TILE_SIZE_X, TILE_SIZE_Y));    
float2 tileCenterOffset = float2(groupId.xy) * 2 + float2(1.0f, 1.0f) - tileNum;     
// Now work out composite projection matrix    
// Relevant matrix columns for this tile frusta    
float4 c1 = float4(-gProj._11 * tileNum.x, 0.0f, tileCenterOffset.x, 0.0f);    
float4 c2 = float4(0.0f, -gProj._22 * tileNum.y, -tileCenterOffset.y, 0.0f);    
float4 c4 = float4(0.0f, 0.0f, 1.0f, 0.0f);     
// Derive frustum planes    
float4 frustumPlanes[6];    
// Sides    
frustumPlanes[0] = c4 - c1;    
frustumPlanes[1] = c4 + c1;    
frustumPlanes[2] = c4 - c2;    
frustumPlanes[3] = c4 + c2;     
// Near/far    
frustumPlanes[4] = float4(0.0f, 0.0f,  1.0f, -minTileZ);    
frustumPlanes[5] = float4(0.0f, 0.0f, -1.0f,  maxTileZ);        
// Normalize frustum planes (near/far already normalized)    
[unroll] for (uint i = 0; i < 4; ++i)   
    frustumPlanes[i] *= rcp(length(frustumPlanes[i].xyz));   
```





## TAA 

https://zhuanlan.zhihu.com/p/64993622

https://zhuanlan.zhihu.com/p/142922246

[Temporal Anti-Aliasing (sardinefish.com)](https://www.sardinefish.com/blog/444)

[Temporal Anti Aliasing – Step by Step | ziyad barakat's programming blog (wordpress.com)](https://ziyadbarakat.wordpress.com/2020/07/28/temporal-anti-aliasing-step-by-step/)

[Temporal Anti-Aliasing - Mali GPU and Vulkan - Graphics, Gaming, and VR blog - Arm Community blogs - Arm Community](https://community.arm.com/arm-community-blogs/b/graphics-gaming-and-vr-blog/posts/temporal-anti-aliasing)

代码参考

[GameTechDev/TAA: Intel® Graphics Optimized Temporal Anti-Aliasing (TAA) (github.com)](https://github.com/GameTechDev/TAA)

[Temporal AA and the quest for the Holy Trail – The Code Corsair (elopezr.com)](https://www.elopezr.com/temporal-aa-and-the-quest-for-the-holy-trail/)



双三次线性插值

GPU-精粹2

[6-Point Star Filter + Bloom (shadertoy.com)](https://www.shadertoy.com/view/XtKfRV)

```glsl
vec4 cubic(float x)
{
    float x2 = x * x;
    float x3 = x2 * x;
    vec4 w;
    w.x =   -x3 + 3.0*x2 - 3.0*x + 1.0;
    w.y =  3.0*x3 - 6.0*x2       + 4.0;
    w.z = -3.0*x3 + 3.0*x2 + 3.0*x + 1.0;
    w.w =  x3;
    return w / 6.0;
}

vec4 BicubicTexture(in sampler2D tex, in vec2 coord)
{
	vec2 resolution = iResolution.xy;

	coord *= resolution;

	float fx = fract(coord.x);
    float fy = fract(coord.y);
    coord.x -= fx;
    coord.y -= fy;

    fx -= 0.5;
    fy -= 0.5;

    vec4 xcubic = cubic(fx);
    vec4 ycubic = cubic(fy);

    vec4 c = vec4(coord.x - 0.5, coord.x + 1.5, coord.y - 0.5, coord.y + 1.5);
    vec4 s = vec4(xcubic.x + xcubic.y, xcubic.z + xcubic.w, ycubic.x + ycubic.y, ycubic.z + ycubic.w);
    vec4 offset = c + vec4(xcubic.y, xcubic.w, ycubic.y, ycubic.w) / s;

    vec4 sample0 = texture(tex, vec2(offset.x, offset.z) / resolution);
    vec4 sample1 = texture(tex, vec2(offset.y, offset.z) / resolution);
    vec4 sample2 = texture(tex, vec2(offset.x, offset.w) / resolution);
    vec4 sample3 = texture(tex, vec2(offset.y, offset.w) / resolution);

    float sx = s.x / (s.x + s.y);
    float sy = s.z / (s.z + s.w);

    return mix( mix(sample3, sample2, sx), mix(sample1, sample0, sx), sy);
}
```





## CSM 



## PCSS 



## IBL 



## GTAO

##  



## GTRO 



## SSR 



## 物理的天空渲染

[Volumetric Light Rendering (sardinefish.com)](https://www.sardinefish.com/blog/432)

## 体积云



## 体积雾