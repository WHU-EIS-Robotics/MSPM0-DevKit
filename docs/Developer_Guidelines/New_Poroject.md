# 从零创建新工程

## 1. 准备所需的文件

新建一个文件夹，例如：`C:\MSPM0_workspace\my_project`。

在该目录下创建子文件夹，最终文件夹结构如下所示：

```
├── BSP   // Board Specific Peripheral板级外设驱动
│   ├── inc // 头文件
│   └── src // 源文件
├── Core  // 单片机核心文件
│   ├── inc // 头文件
│   └── src // 源文件
├── Driver // 单片机驱动文件
│   ├── CMSIS // Cortex-M系列CPU驱动库
│   └── ti
└── keil // Keil MDK文件
```

### 1.1 MSPM0硬件驱动库

复制`<SDK_PATH>/source/ti/driverlib`文件夹到`C:\MSPM0_workspace\my_project\Driver\ti`。删除`C:\MSPM0_workspace\my_project\Driver\ti\driverlib\lib`这个文件夹。

### 1.2 MSPM0设备标识文件

复制`<SDK_PATH>/source/ti/devices`文件夹到`C:\MSPM0_workspace\my_project\Driver\ti`。删除以下文件夹:
1. `C:\MSPM0_workspace\my_project\Driver\ti\devices\msp\m0p\linker_files`
2. `C:\MSPM0_workspace\my_project\Driver\ti\devices\msp\m0p\startup_system_files`

### 1.3 CMSIS

复制`<SDK_PATH>/source/third_party/CMSIS/Core/`到`C:\MSPM0_workspace\my_project\Driver\CMSIS\`

### 1.4 Startup及链接文件

复制`<SDK_PATH>/source/ti/devices/msp/m0p/linker_files/keil/mspm0l1306.sct`到`C:\MSPM0_workspace\my_project\keil\`目录下。

复制`<SDK_PATH>/source/ti/devices/msp/m0p/startup_system_files/keil/startup_mspm0l1306_uvision.s`到`C:\MSPM0_workspace\my_project\keil\`目录下。

## 2. 新建工程

打开Keil，点开最上方的工具栏的`Project`创建新的Keil工程。

## 3. 配置工程

1. 选择芯片，MSPM0L1306

2. 

## 4. 