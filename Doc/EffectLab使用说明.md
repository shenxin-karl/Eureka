# EffectLab 使用说明

基本格式

```cc
SourcePath: "Assets/Shaders/FXAA.hlsl"
Properties {
    // Property
   ...
}

Pass("PassName") {
   ...
}
```

## Property 类型

Property 使用下面的格式定义

```cc
_UniformName( "Property Description", Type) = Value
```

| 类型                    | 值                                 |
| ----------------------- | ---------------------------------- |
| `bool`                  | `ture/false`                       |
| `int`                   | `int`                              |
| `range(number, number)` | `number`                           |
| `float`                 | `number`                           |
| `float2`                | `(number, number)`                 |
| `float3`                | `(number, number, number)`         |
| `float4`                | `(number, number, number, number)` |
| `2D`                    | `white/bump/black`                 |
| `matrix`                | `Identity`                         |

# Pass 定义

```cc
Pass("BasePass") {
    ...
}
```

使用方式:

```cc
Keyword: parameters
```

| 关键字           | 参数                                                         |
| ---------------- | ------------------------------------------------------------ |
| `VertexShader`   | Vertex 入口                                                  |
| `HullShader`     | Hull 入口                                                    |
| `DomainShader`   | Domain 入口                                                  |
| `GeometryShader` | Geometry 入口                                                |
| `PixelShader`    | Pixel 入口                                                   |
| `RenderQueue     | 渲染队列ID, 支持`BackGround/Geometry/Opaque/AlphaTest/Transparent/Overlay`,<br />默认是 `Opaque` |
| `ShaderFeature`  | 指定 Shader 的变体宏                                         |
| `Cull`           | 开启背面剔除, 支持 `Off/Front/Back` 默认是 `Back`            |
| `ZClip`          | 开启深度裁剪, 支持 `ture/false` 默认是 `true`                |
| `Offset`         | 光栅化深度偏移, `Offset bias slopeScaleDepthBias` 默认是 `0, 0` |
| `Conservative`   | 开启保守光栅化, 可选 `true/false` 默认是 `false`             |
| `ZWrite`         | 开启深度写入, 可选 `On/Off` 默认是 `On`                      |
| `ZTest`          | 深度比较函数, 可选 `Never/Less/Equal/LEqual/GEqual/NotEqual/Greater/Always` <br />默认是 `Less` |

