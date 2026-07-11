#include "stm32f30x.h"
#include "port.h"
#include "os.h"

void SysTick_Handler(void)
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

