# tinyraytracer
一个超简易的光线追踪demo

基本参考ray tracing in one weenkend实现，其中的基础数据结构vector的实现参考了https://github.com/doyubkim/fluid-engine-dev

后续可能会学习ray tracing这个系列的剩下两个教程

## 开发环境
win10 + vs2019

## 运行
首先在visual studio中生成项目，然后在命令行中输入
```
tinyraytracer.exe > image.ppm
```
完成后会在同目录下得到image.ppm文件，可以通过其他工具转化为jpg等格式查看。

在本机上，单线程执行共需2983.71s，采用onetbb并行加速后只需430.159s
运行环境： i7-11800h（8核16线程）；win10；8GB×2 DDR4双通道内存
## 结果展示
![image](https://github.com/tlcui/tinyraytracer/blob/master/results.jpeg)
