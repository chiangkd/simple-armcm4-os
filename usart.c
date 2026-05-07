#include "usart.h"

void usart_transmit(const char *str)
{


    // REG_TYPE *usart3_isr = (REG_TYPE *) (USART3_BASEADDR + 0x1C);
    // REG_TYPE *usart3_tdr = (REG_TYPE *) (USART3_BASEADDR + 0x28);

    // while (*str) {
    //     // wait TDR empty
    //     while (!(*usart3_isr & USART_ISR_TXE));

    //     // write data tp TDR
    //     *(usart3_tdr) = (*str & 0xFF);
    //     str++;
    // }

}