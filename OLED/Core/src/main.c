#include "ti_msp_dl_config.h"
#include <oled.h>

int main(void)
{
    SYSCFG_DL_init();//Sysconfig│§╩╝╗»
    OLED_Display_On();
    OLED_ShowChar(3,3,'a');
    while(1)
		{
        
    }
}