#include "stm32f30x.h"
#include "port.h"
#include "kernel.h"

void SysTick_Handler(void)
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

// uint32_t get_syscall_num(void *stack)
// {
    
// }

void platform_init()
{
    uint32_t stack_dummy[32];   // dummy stack
    platform_init_env(&stack_dummy[32]);
}

