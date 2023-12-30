#include "ti_msp_dl_config.h"
uint8_t data;

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig��ʼ��
    NVIC_ClearPendingIRQ(UART1_INT_IRQn);
    NVIC_EnableIRQ(UART1_INT_IRQn);

    while (1) 
    {
    }
}

void  UART1_IRQHandler()
{
   switch (DL_UART_Main_getPendingInterrupt(UART1)) //����Ƿ񴮿��ж�
		 {
        case DL_UART_MAIN_IIDX_RX:
            data = DL_UART_Main_receiveData(UART1);  //���ͽ��յ�������
            DL_UART_Main_transmitData(UART1, data);
            break;
        default:
            break;
    }
}