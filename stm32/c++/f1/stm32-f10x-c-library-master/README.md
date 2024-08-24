# STM32F10x C++库

#### 介绍

参考Arduino框架做的底层抽象，并移植了部分Arduino的上层库，目前支持硬件串口收发(支持DMA发送、中断接收)、硬件SPI主机模式、软件I2C主机模式、ADC、GPIO……，移植了Arduino的WString、Adafruit的图形库及OLED和TFT驱动库，还在持续开发中……

#### 软件架构

该项目代码主要分为三层，最底层为单片机硬件库函数，主要为单片机产商提供，例如STM32的库函数；第二层为外设接口层，主要使用C语言，在不同的单片机之间统一接口函数(函数名、输入输出变量、返回值一致)，对底层进行封装；第三层为C++驱动层，以面向对象的思想对第二次进行封装，并引入一些外部的C++库，在此基础上进行外部设备的开发和驱动。应用时既可使用第二层的C语言代码进行开发，也可以使用第三层的C++代码进行开发，在抽象的同时不完全屏蔽底层。
![输入图片说明](https://img-blog.csdnimg.cn/e11ac1f1896b4a9fb326c98b35b3f9e0.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAU2lPMueIseS4ikhG,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

#### 环境介绍

处理器：STM32F103ZE

开发环境：Keil5

编译器版本：V5.06

库函数版本：V3.5

#### 使用说明

在User/User.cpp中添加自己的代码，setup中添加初始化代码，loop中添加循环代码，与Arduino类似。

在Library/examples中有使用示例，可以复制到User.cpp中使用

#### 可能出现的问题

1.我用的是F103ZE，选择的启动文件为startup_stm32f10x_hd.s，如果是其他容量的STM32F10x产品，请选择对应的启动文件。

2.打开项目后更改单片机型号。

3.遇到其他无法解决的问题可以联系我解决：QQ:1461041096 VX:15059339658，CSDN上找我不知道猴年马月才能看到。。

