# 部署MSPM0 SDK

本章节介绍MSPM0官方SDK(Software Development Kit软件开发工具包)。请注意，本例程代码在未安装SDK的情况下也能正常编译下载，当使用者需要使用sysconfig工具自己配置其他功能时才需要连同sysconfig一起安装。

## 1. 下载和安装

从官方网站下载[MSPM0 SDK](https://www.ti.com/tool/download/MSPM0-SDK/1.20.01.06)并安装。

记住安装路径，非常重要！

## 2. 工具介绍

该SDK包含MSPM0的硬件驱动库、代码构建工具、例程、实时操作系统等。

实际上有用的部分只有CMSIS内核驱动库和MSPM0硬件外设驱动库。

* CMSIS内核驱动库在`<SDK_PATH>/source/third_party/CMSIS`目录下
* MSPM0外设驱动库源码在`<SDK_PATH>/source/ti/driverlib`目录下

至此已完成SDK的环境部署，如何使用SDK，请参阅[开发者指南](/Developer_Guidelines/New_Project)