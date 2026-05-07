#include "stm32f303xe.h"

// #define USART_ISR_TXE   (1U << 7)
// #define USART_ISR_TE    (1U << 6)
// #define USART_CR1_UE    (1U << 0)
// #define USART_CR1_TE    (1U << 3)
// #define USART_CR1_RE    (1U << 2)

void usart_transmit(const char *str);
