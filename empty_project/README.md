# 说明
1. 这个工程在sysconfig里面更改了设置后不需要手动点保存ti_msp_dl_config.c和ti_msp_dl_config.h文件到Core文件夹。
更改后，只需要保存sysconfig,然后点keil的Build/ReBuild即可自动更新ti_msp_dl_config.c和ti_msp_dl_config.h文件
2. 空工程，目前里面只有一个LED闪烁的示例，更改好syscfg.bat后，新建工程只需要复制粘贴这个空工程，改个文件夹名字就行

# 需要修改的部分
在syscfg.bat中修改两个地方即可：  
1. 第二行这里改成自己电脑上sysconfig_1.18.1\sysconfig_cli.bat文件的绝对路径
```
set SYSCFG_PATH="D:\Programs\ti\sysconfig_1.18.1\sysconfig_cli.bat"
```


2. 最后一行把里面的product.json这个文件也改成自己电脑上的绝对路径
```
%SYSCFG_PATH% -o "%PROJ_DIR%.." -s "D:\Programs\ti\mspm0_sdk_1_20_01_06\.metadata\product.json" --compiler keil "%PROJ_DIR%..\%SYSCFG_FILE%"
```