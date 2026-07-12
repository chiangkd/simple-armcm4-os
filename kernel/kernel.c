#include <stdint.h>
#include "kernel.h"
#include "uart.h"


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