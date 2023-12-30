# C语言代码规范

## 缩写
```cpp
---------------------
缩写         外设单元
---------------------
ADC         模数转换器
BKP         备份寄存器
CAN         控制器局域网模块
DMA         直接内存存取控制器
EXTI        外部中断事件控制器
FLASH       闪存存储器
GPIO        通用输入输出
I2C         内部集成电路
IWDG        独立看门狗
NVIC        嵌套中断向量列表控制器
PWR         电源/功耗控制
RCC         复位与时钟控制器
RTC         实时时钟
SPI         串行外设接口
SysTick     系统嘀嗒定时器
TIM         通用定时器
TIM1        高级控制定时器
USART       通用同步异步接收发射端
WWDG        窗口看门狗
```
常见缩写，需要熟记
```
Cmd    Command    命令
En     Enable     使能
Temp   Temperary  临时
Proc   Process    处理
Conf   Configure  配置       
```
## 命名规则
### **文件**
* **给每个外设的文件夹命名为“器件类型-器件型号”，必须全英文小写命名。单词与单词之间用空格隔开而不是下划线。**

    >如`temperature and humidity sensor-sht31`表示该器件是型号为SHT31的温湿度传感器;`laser radar-a1m8`表示型号为A1M8的激光雷达;`wifi module-esp32`表示型号为ESP32的无线网络模组。每个用户外设单独建立一个文件夹保存相应代码，详见后文“工程文件结构”。因为不同系统对文件名大小写处理会不同，建议文件命名统一采用小写字符。
* **系统、源程序文件和头文件命名都以工程名（或其缩写）作为开头.**
    >例如：`botcar_motor_control.h`
* **文件命名均将上级模块名称写在前面，下级模块名称写在后面。**
    >例如：`botcar_radar_communication.h`、`botcar_radar_dataprocess.h`
* **文件名只用小写字母和下划线组成**

<br>


---
### **宏定义**
* **仅被应用于一个文件的，定义于该文件中。被应用于多个文件的，在对应头文件中定义。所有常量都由英文字母大写书写。**

<br>


---
### **函数**
* **外设函数的命名以该外设的英文名称加下划线为开头。每个单词的第一个字母都由英文字母大写书写.**

    >例如：SPI_SendData。在函数名中，只允许存在一个下划线，用以分隔外设名称和函数名的其他部分。若外设名称包含多个单词的，名称的多个单词之间不加下划线。示例：
    >* `PPP_Init()`： 根据指定的参数初始化外设PPP。
    >* `PPP_Cmd()`： 使能或失能外设PPP
    >* `LaserRadar_GetInfoOnce()`：获取一次雷达数据
    >* `Motor_SetFrontLeftSpeed()`：设置左前方电机速度
    >* `BLE_SendOneByte()`：蓝牙（BLE）发送1字节数据
    >* `SHT31_GetTempAndHumi()`：温湿度传感器（型号SHT31）同时读取一次温度和湿度

    >说明：这种命名方法与STM32固件库和HAL库代码的风格一致，故整体风格协调统一。
* **函数名称前缀要清晰明了。**

    >函数名称前缀即外设器件名称，要使用别人一眼就明白这是什么器件的名称，一般是器件类型而不是器件型号，如`LaserRadar`。但是如果器件名称非常长就使用器件型号或其他简短的、有代表性的名称。如`Temperature and Humidity Sensor`就太长，可以考虑使用其型号`SHT31`。
* **多用“Get”、“Set”、“Send”、“Config”等动词加名词的结构，** 示例：
```cpp
void Motor_SetSpeed();
void Motor_GetFrontLeftSpeed();
void LaserRadar_SendCmd();
void TFTScreen_ConfigWindow();
```

<br>

---
### **变量**
* **不用下划线，仅英文单词组合，每个单词首字母大写，如`TargetInfo`、`RequestPack`**
* **布尔类型的变量一般以“is”开头**
    >例如：`isNumeric`、`isPrime`、`isActing`，这样的好处是当我们在使用该变量进行if条件判断时更容易从字面意思来阅读，例：
```cpp
if(isHolding)
{
    Car_SetDirection(90);
    Car_SetSpeed(30);
}
else
{
    ...  // program code
}
```
* **标识符的命名要清晰、明了，有明确含义，同时使用完整的单词或大家基本可以理解的缩写，避免使人产生误解**
* **除了常见的通用缩写以外，不使用单词缩写，不得使用汉语拼音**
* **尽量避免名字中出现数字编号，除非逻辑上的确需要编号**

<br>

---
### **结构体**
* **使用全小写字母和下划线组成，每个结构体建议都使用typedef定义别名。每个结构体的名称应该都以`_t`结尾。例：**
```cpp
typedef struct lidar_t
{
    uint8_t* header; 
    uint16_t* body;
    lidar_rawinfo_T* Next;

}lidar_t;
```

<br>

---
### **枚举类型**
* **同结构体**

<br>

## DEBUG
* **对应的用户外设（如蓝牙、Wi-Fi、电机等）和外设的每个功能模块应该用宏定义`#define DEBUG_xxx 1`启用对该用户外设或外设的某个功能模块的调试。设置`#define DEBUG_xxx 0`关闭对该用户外设或外设的某个功能模块的调试。在对应起作用的代码块应用宏定义判断。例如**：
```cpp
#define DEBUG_RADAR 1
#define DEBUG_RADAR_READ 1
#if DEBUG_RADAR==0
    #define DEBUG_RADAR_READ 0    // 若debug总使能DEBUG_RADAR未开启，则关闭RADAR下属调试模块
#endif

void Radar_ReadInfo()
{
    ...
#if DEBUG_RADAR
    printf("Current Read Info:%d", info);
#endif
    ...
}
```
## 代码排版
* **程序块要采用缩进风格编写，缩进的空格数为4个。**
* **相对独立的程序块之间、变量说明之后必须加空行。**

示例：以下例子不符合规范。
```cpp
if (!flag)
{
    ... // Program code.
}
variable_a = data_buffer[index].a;
variable_b = data_buffer[index].b;
```
应如下书写：
```cpp
if (!flag)
{
    ... // Program code.
}

variable_a = data_buffer[index].a;
variable_b = data_buffer[index].b;
/* 注意花括号后空了一行 */
```

* **较长的语句（大于80字符）要分成多行书写，长表达式要在低优先级操作符处划分新行，操作符放在旧行之尾，划分出的新行要进行适当的缩进，使排版整齐，语句可读。**

示例：
```cpp
data_package.length = DATA_PACKAGE_HEAD_LENGTH + DATA_PACKAGE_TAIL_LENGTH +
    DATA_LENGTH_PER_BYTE * sizeof(data_byte_sum);

action_task_table[frame_id * ACTION_TASK_CHECK_NUMBER + index].occupied =
    task_table[index].occupied;

report_or_not_flag = ((task_index < ACTION_TASK_MAX_NUMBER) &&
    (judgeTaskIndexIsValid(task_index)) &&
    (action_task_table[task_index].result_data != 0));
```
* **循环、判断等语句中若有较长的表达式或语句，则要进行适应的划分，长表达式要在低优先级操作符处划分新行，操作符放在旧行之尾。**

示例：
```cpp
if ((variable_a <= DATA_BUFFER_MAX_NUMBER) &&
    (variable_b != getFunctionValue(parameter_a)))
{
    ... // Program code.
}

for (i = 0, j = 0; (i < data_buffer[index].length) &&
    (j < data_buffer[index].length); i++, j++)
{
    ... // Program code.
}

for (i = 0, j = 0;
    (i < first_word_length) && (j < second_word_length);
    i++, j++)
{
    ... // Program code.
}
```
* **若函数或过程中的参数较长，则要进行适当的划分。**
```cpp
void testFunction((BYTE *)parameter_a + sizeof(parameter_c),
                  (BYTE *)parameter_b + sizeof(parameter_c),
                  data_buffer[index]);
```

* **不允许把多个短语句写在一行中，即一行只写一条语句。**

示例：以下例子不符合规范
```cpp
rect.length = 0; rect.width = 0;
```
应如下书写：
```cpp
rect.length = 0;
rect.width  = 0;
```
* **`if`、`for`、`do`、`while`、`case`、`switch`、`default`等语句自占一行，且 `if`、`for`、`do`、`while`等语句的执行语句部分无论多少都要加括号`{}`。**

示例：以下例子不符合规范。
```cpp
if (a == NULL) return;
```
应如下书写：
```cpp
if (a == NULL)
{
    return;
}
```
* **对齐只能使用空格键，不能使用TAB键。**

    >说明：以免用不同的编辑器阅读程序时，因TAB键所设置的空格数目不同而造成程序布局不整齐。

* **函数或过程的开始、结构的定义及循环、判断等语句中的代码都要采用缩进风格，case 语句下的情况处理语句也要遵从语句缩进要求。**
* **程序块的分界符（如C/C++语言的大括号{和}）应各独占一行并且位于同一列，同时与引用它们的语句左对齐。在函数体的开始、类的定义、结构的定义、枚举的定义以及if、for、do、while、switch、case语句中的程序都要采用如上的缩进方式。**

示例：以下例子不符合规范。
```cpp
for (...) {
    ... // Program code.
}

if (...)
 {
   ... // Program code.
 }

void testFunction(void)
 {
   ... // Program code.
 }
```
应如下书写：
```cpp
for (...)
{
    ... // Program code.
}

if (...)
{
    ... // Program code.
}

void testFunction(void)
{
    ... // Program code.
}
```
* **在两个以上的关键字、变量、常量进行对等操作时，它们之间的操作符之前、之后或者前后要加空格。进行非对等操作时，如果是关系密切的立即操作符（如->），后不应加空格。**

    >说明：采用这种松散方式编写代码的目的是使代码更加清晰。由于留空格所产生的清晰性是相对的，所以在已经非常清晰的语句中没有必要再留空格，如果语句已足够清晰，则括号内侧（即左括号后面和右括号前面）不需要加空格，多重括号间不必加空格，因为在C/C++语言中括号已经是最清晰的标志了。

    >在长语句中，如果需要加的空格非常多，那么应该保持整体清晰，而在局部不加空格。给操作符留空格时不要连续留两个以上空格。

示例：

（1）逗号、分号只在后面加空格。
```cpp
int a, b, c;
```
* **比较操作符，赋值操作符（`=`、`+=`），算术操作符（`+`、`%`），逻辑操作符（`&&`、`&`），位域操作符（`<<`、`^`）等双目操作符的前后加空格。**
```cpp
if (a >= b && b != 0)
{
    c = a + b;
    d = c ^ 2;
}
```
* **`!`、`~`、`++`、`--`、`&`（地址运算符）等单目操作符前后不加空格。**
```cpp
*p = 1;
a = !b;
p = &a;
i++;
```
* **`->`、`.`前后不加空格**
```cpp
p->id = 1;
```

* **`if`、`for`、`while`、`switch`等与后面的括号间应加空格，使if等关键字更为突出和明显。**
```cpp
if (a >= b && c > d)
```
* **一行程序以小于80字符为宜，不要写得过长。**
## 代码注释
* **只能用英文注释**

    >说明：在不同编辑器或者不同电脑环境之间，文本的编码方式可能不一样，有些是以UTF-8格式保存和打开文件的，有些是以
GBK格式保存和打开文件的，中文无法兼容两种编码方式，即用UTF-8编码格式保存的文件用GBK格式打开时中文就会乱码。
但是英文不管在哪种编码格式下都能正常打开，所以我们用英文注释可以避免这种情况

* **不要删除其他人的注释，可以在其后补充说明。**
* **行注释双斜杠后面要加一个空格，不然文字和双斜杠连在一起，看的快的时候很难看清文字。**
* **行注释`/**/`文字和两端符号之间要隔一个空格。错误示例：`/*used as temp var*/`。正确示例：`/* used as temp var */`**
* **对于大段代码的注释统一使用此模板:**
```cpp
/*********************************
 * 1.xxxxxxxxxxxxxxxxxxx
 * 2.xxxxxxxxxxxxxxxxxxx
 * 3.xxxxxxxxxxxxxxxxxxx
 ********************************/
```
示例：注意上下的星号要比文字长度略长，上下星号长度对齐，注释文字太长要换行
```cpp
void Radar_ReadInfo()
{
    ... // program code
    /*************************************************
     * 1.first step is to send request information
     * 2.second step, MCU must wait for respond pack
     * 3.third step, save pack data into information
     *   struct RadarInfo
     *************************************************/
    ... /program code
}
```
* **说明性文件（如.h文件、.icf文件、.txt文件等）头部应进行注释，注释必须列出：版权说明、版本号、生成日期、作者、内容、功能、与其他文件的关系、修改日志等。头文件的注释中还应有函数功能简要说明。**

示例：下面这段头文件的头注释比较标准。当然，并不局限于此格式，但上述信息建议要包含在内。
```cpp
/****************************************************************************
Copyright (C), 2017-2018, Team MicroDynamics <microdynamics@126.com>

// 文件名。
File name:

// 作者、版本及完成日期。
Author:    Version:    Date:

// 用于详细说明此程序文件完成的主要功能，与其他模块或函数的接口，输出值、取值范围、
// 含义及参数间的控制、顺序、独立或依赖等关系。
Description:

// 其他内容的说明。
Others:

// 主要函数列表，每条记录应包括函数名及功能简要说明。
Function List:
1. ....

// 修改历史记录列表，每条修改记录应包括修改日期、修改者及修改内容简述。
History:
1. Date:
   Author:
   Modification:
2. ...
****************************************************************************/
```
* **源文件头部应进行注释，列出：版权说明、版本号、生成日期、作者、模块目的/功能、主要函数及其功能、修改日志等。**

示例：下面这段源文件的头注释比较标准，当然，并不局限于此格式，但上述信息建议要包含在内。
```cpp
/****************************************************************************
Copyright (C), 2017-2018, Team MicroDynamics <microdynamics@126.com>

// 文件名。
FileName:

// 作者、版本及完成日期。
Author:    Version:    Date:

// 模块描述
Description:

// 版本信息
Version:

// 主要函数及其功能
Function List:
1. ...

// 历史修改记录
History:
<author>    <time>    <version>    <desc>
...
****************************************************************************/
```
说明：Description 一项用于描述本文件的内容、功能、内部各部分之间的关系及本文件与其他文件关系等。History 是修改历史记录列表，每条修改记录应包括修改日期、修改者及修改内容简述。

以Team MicroDynamics目前使用的源码头注释为例：
```cpp
/*****************************************************************************
THIS PROGRAM IS FREE SOFTWARE. YOU CAN REDISTRIBUTE IT AND/OR MODIFY IT
UNDER THE TERMS OF THE GNU GPLV3 AS PUBLISHED BY THE FREE SOFTWARE FOUNDATION.

Copyright (C), 2017-2018, Team MicroDynamics <microdynamics@126.com>

Filename:    stm32f10x_driver_sys.c
Author:      maksyuki
Version:     0.1.0.20161231_release
Create date: 2016.8.3
Description: Define the bitband operation
Others:      none
Function List:
             none
History:
1. <author>    <date>         <desc>
   maksyuki  2016.11.29     modify the module
*****************************************************************************/
```
* **函数头部应进行注释，列出：函数的目的/功能、输入参数、输出参数、返回值、调用关系（函数、表）等。**

示例：下面这段函数的注释比较标准，当然，并不局限于此格式，但上述信息建议要包含在内。
```cpp
/****************************************************************************
Function:       // 函数名称。
Description:    // 函数功能、性能等的描述。
Calls:          // 被本函数调用的函数清单。
Called By:      // 调用本函数的函数清单。
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）。
Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）。
Input:          // 输入参数说明，包括每个参数的作。
                // 用、取值说明及参数间关系。
Output:         // 对输出参数的说明。
Return:         // 函数返回值的说明。
Others:         // 其他说明。
****************************************************************************/
```
小规模工程使用如下函数注释模板：(可直接复制粘贴)
```cpp
/****************************************************************************
@function:      // 函数名称
@params:        // 参数(parameter)说明,包含名称、变量类型、取值范围、作用、单位等
@retval:        // 返回值(return value)说明
@brief:         // 函数作用及功能简介
@author:        // 函数作者
****************************************************************************/
```

示例：
```cpp
/****************************************************************************
@function: Radar_InfoProcess
@params:1.SourceInfo: raw info package from laser radar, containing package
            header and tail, between which are angles and distance information.
        2.ProcessedInfo: contains distance of diffrent angles.
@retval: none
@brief: from hearder information the function knows what the type of package
        is, by which the function calculates the distance of diffrent angles.
        Finally write data to the pointer 'ProcessedData'. 
@author: Pansamic(WangGengJie)
****************************************************************************/
void Radar_InfoProcess(struct RADAR_RAWINFO* SourceInfo,
                       struct RADAR_INFO* ProcessedInfo)
{
    ... // program code
}
```
* **数据结构声明（包括数组、结构、枚举等），如果其命名不是充分自注释的，必须加以注释。对数据结构的注释应放在其上方相邻位置，不可放在下面。对结构中的每个域的注释放在此域的右方。**
```cpp
// USART Ring Data buffer struct.
typedef struct USART_RingBuffer
{
    u8  *buffer;   // Data buffer pointer.
    u16  mask;     // Data mask.
    vu16 index_rd; // Data read index.
    vu16 index_wt; // Data write index.
} USART_RingBuffer;
```
* **注释与所描述内容进行同样的缩排。**

示例：以下例子不符合规范，排版不整齐，阅读稍感不方便。
```cpp
void testFunction(void)
{
  // Code one comments.
    program code one;

      // Code two comments.
     program code two;
}
```
应改为如下布局：
```cpp
void testFunction(void)
{
    // Code one comments.
    program code one;

    // Code two comments.
    program code two;
}
```
* **将注释与其上面的代码用空行隔开。**

示例：以下例子不符合规范，代码显得过于紧凑。
```cpp
// Code one comments.
program code one;
// Code two comments.
program code two;
```
应如下书写：
```cpp
// Code one comments.
program code one;

// Code two comments.
program code two;
```

## STM32 C工程规范
### **变量**
* **禁止使用全局变量**
    
    >使用全局变量可能在某些文件中比较好用，但是从整个工程的角度来看，使用全局变量不具有很好的可移植性，而且各个功能模块之间的兼容性可能也不太好。
### 

<br>

---
### **功能模块**
* **功能模块应封装起来**

    >封装功能模块是指其内部的几乎所有变量对外不可见，即其他功能模块或系统不能直接获取模块内的变量值、静态函数等。只有一些希望被其他功能模块调用的函数或宏定义等对外可见。

* **功能模块应该具有较强的可移植性**

    >对某一个外设器件所编写的驱动代码或某个算法的代码应该具有通用的输入参数定义、函数接口等，以便其他项目用到该器件或算法时只需考虑其输入输出数据格式及相应的函数接口即可，而不必每次都为新项目写新代码。

### **头文件**

<br>

---
* **各个外设的功能模块头文件**

    >包含功能模块所有的宏定义、函数、结构体、枚举类型等<br>对外不可见的函数、结构体、枚举类型需设置为static<br>对外不可见的宏定义写在c文件中<br>功能模块也不允许使用全局变量

* **在代码文件夹“Code”根目录下设置“<工程名>_Config.h”**

    >该头文件中包含对该项目中所有外设器件的参数配置、DEBUG接口、功能配置等。<br>include所有外设器件和算法的头文件<br>main.c中只需包含该头文件即可

* **STM32工程配置中只将“Code”文件夹纳入头文件查找文件夹列表**

* **头文件引用一律为./<外设器件文件夹>/<外设器件头文件>.h的格式**
    
    >不在工程配置中把所有代码文件夹的子文件夹全部纳入头文件搜索文件夹列表然后只#include <外设器件头文件>.h的原因是当所有工程人员交换代码时必须要繁琐地把所有子文件夹纳入工程头文件搜索文件夹列表，甚至有时候因此而报错也没能及时发现而延误工期。上述做法可移植性差，故头文件引用一律为./<外设器件文件夹>/<外设器件头文件>.h的格式，而只需将“Code“文件夹纳入头文件搜索文件夹列表即可