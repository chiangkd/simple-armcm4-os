#ifndef __UART_H_
#define __UART_H_

#include "stm32f30x.h"

void UART3_Config(uint32_t baudrate);
void UART3_SendChar(char ch);
void UART3_SendString(char* str);
void UART3_Printf(const char *format, ...);

#endif
