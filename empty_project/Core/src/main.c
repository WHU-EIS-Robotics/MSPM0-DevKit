#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    while(1)
		{
				delay_cycles(32000000);
				DL_GPIO_togglePins(Demo_PORT, Demo_LED_PIN);
    }
}