#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig≥ı ºªØ
    while(1)
		{
        DL_GPIO_clearPins(Demo_PORT,Demo_LED_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
        DL_GPIO_setPins(Demo_PORT,Demo_LED_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
   }
}