#include <stdint.h>
#include <stdbool.h>
#include "kernel.h"
#include "uart.h"

static bool syscall_flag;

void set_syscall_flag(void)
{
    syscall_flag = true;
}

void reset_syscall_flag(void)
{
    syscall_flag = false;
}

bool get_syscall_flag(void)
{
    return syscall_flag;
}


void syscall_handler(uint32_t *svc_args)
{
    uint32_t syscall_num = svc_args[3];

    switch (syscall_num)
    {
    case SYS_UART_WRITE:
        char *str = (char *)svc_args[0];
                            UART3_SendString("[Syscall] ");
        UART3_SendString(str);
        break;
    case SYS_LED_TOGGLE:
        break;
    default:
        svc_args[0] = -1;   // Unknown syscall
        break;
    }
}