#ifndef __OLED_H
#define __OLED_H

#include "ti_msp_dl_config.h"



// ----------------------------------------------------------模拟I2C引脚定义
//SCL IIC接口的时钟信号
#define OLED_SCLK_Clr() (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_1))
#define OLED_SCLK_Set() (DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_1))
//SDA IIC接口的数据信号
#define OLED_SDIN_Clr() (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_0))
#define OLED_SDIN_Set() (DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_0))
// -----------------------------------------------------------

#define OLED_I2C_SELECT 1
#define OLED_CMD 0
#define OLED_DATA 1
#define Max_Column	128
#define OLED_ADDRESS (0x78>>1)

void OLED_WR_Byte(uint8_t data,uint8_t cmd);
void OLED_Init();
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowString(uint8_t x,uint8_t y,char *chr,uint8_t Char_Size);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_Clear(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_Showdecimal(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t size2);
extern const unsigned char F6x8[][6];
extern const char F8X16[];
void OLED_ShowNumber(uint8_t x,uint8_t y,uint16_t num,uint8_t len,uint8_t size2);

#endif


