# Temporal filtering

将样本分布到多个帧当中



## 步骤1

### 调整投影矩阵

```cc
ProjMatrix[2][0] += ( SampleX * 2.0f – 1.0f ) / ViewRect.Width();
ProjMatrix[2][1] += ( SampleY * 2.0f – 1.0f ) / ViewRect.Height();
```

### 样本模式

要一个低差异序列, 在空间和时间上都没有聚集

普通样本

![](image-20221024131055593.png)



Halton (2,3) 样本

![image-20221024131326652](image-20221024131326652.png)