# 文件架构及编译规范

## 文件架构

对于每一个单项工程，建议采用如下文件架构：

```
├── BSP
│   ├── inc
│   └── src
├── Core
│   ├── inc
│   └── src
├── Driver
│   ├── CMSIS
│   │   └── Core
│   │       └── Include
│   └── ti
│       ├── devices
│       └── driverlib
└── keil
```