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


- [ ] 好用的 枚举 包装类
- [ ] mipmap 生成
- [ ] 加入一个 GeometryGenerator 提供基本几何体

## PBR 

- [x] 主应用定义好渲染 RenderGraph
- [x] 定义好 GBuffer 的作用
- [x] 渲染到 GBuffer
- [ ] Compute Shader 计算方向光

参考资料:

[延迟着色法 - LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/05 Advanced Lighting/08 Deferred Shading/)

[光照 - LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/07 PBR/02 Lighting/)

## ACES / ColorGrading / Gamma矫正

https://zhuanlan.zhihu.com/p/21983679

- [ ] Compute 后处理
- [ ] 使用 mipmap 生成，计算出整个屏幕的亮度， 更准去的 aces 调整

## FXAA

- [ ] 做 FXAA 的同时，写回到 backBuffer 中

## Tile Based Deferred Rendering

https://zhuanlan.zhihu.com/p/62030747

https://zhuanlan.zhihu.com/p/85447953

https://www.cnblogs.com/X-Jun/p/16023346.html

https://zhuanlan.zhihu.com/p/71932575

https://zhuanlan.zhihu.com/p/339109155

## TAA 

https://zhuanlan.zhihu.com/p/64993622

https://zhuanlan.zhihu.com/p/142922246

## CSM 



## PCSS 



## IBL 



## GTAO

##  



## GTRO 



## SSR 



## 物理的天空渲染



## 体积云



## 体积雾