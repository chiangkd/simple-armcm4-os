#include "../uart.h"
#include <stddef.h>

void my_fault_handler_c(uint32_t fault_type, uint32_t *msp, uint32_t *psp, uint32_t lr)
{
    // uint32_t *fault_stack = NULL;
    // char msg[128];

    // 1. 根據 LR 暗號，判斷出事時是用 MSP 還是 PSP
    // 0xF 開頭的位數，只要看最低 4 位（最低位元組是否為 0xD）
    if ((lr & 0xF) == 0xD) {
        // fault_stack = psp;
        UART3_SendString("\r\n!!! Fault occurred in USER TASK (PSP) !!!\r\n");
    } else {
        // fault_stack = msp;
        UART3_SendString("\r\n!!! Fault occurred in KERNEL/IRQ (MSP) !!!\r\n");
    }

    // 2. 印出發生錯誤時的暫存器快照 (從硬體壓棧區撈取)
    UART3_SendString("==== Register Dump ====\r\n");
    
    // sprintf(msg, "R0  = 0x%08lx\r\n", fault_stack[0]); UART3_SendString(msg);
    // sprintf(msg, "R1  = 0x%08lx\r\n", fault_stack[1]); UART3_SendString(msg);
    // sprintf(msg, "R2  = 0x%08lx\r\n", fault_stack[2]); UART3_SendString(msg);
    // sprintf(msg, "R3  = 0x%08lx\r\n", fault_stack[3]); UART3_SendString(msg);
    // sprintf(msg, "R12 = 0x%08lx\r\n", fault_stack[4]); UART3_SendString(msg);
    // sprintf(msg, "LR  = 0x%08lx\r\n", fault_stack[5]); UART3_SendString(msg);
    
    // // 3. 核心大招：印出當初殺死 CPU 的那行代碼位址 (PC)
    // sprintf(msg, "PC  = 0x%08lx (Error Location)\r\n", fault_stack[6]); UART3_SendString(msg);
    // sprintf(msg, "xPSR= 0x%08lx\r\n", fault_stack[7]); UART3_SendString(msg);
    
    UART3_SendString("=======================\r\nHalting system...\r\n");
    
    // 進入無窮迴圈當機，等待開發者用 GDB 連進來看
    while(1);
}