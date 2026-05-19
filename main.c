#include <stdint.h>
#include "stm32f30x.h"
#include "led.h"
#include "uart.h"
#include "port.h"

static char greet[] = "Hello STM32F303ZE via ST-Link (USART3)!\r\n";

void usertask(void)
{
    UART3_SendString("Start user task\r\n");
	UART3_SendString("User Task #1\r\n");

	asm volatile("svc #0");

    UART3_SendString("[2nd] Start user task\r\n");
	UART3_SendString("[2nd] User Task #1\r\n");

	asm volatile("svc #0");

	UART3_SendString("This should not be printed\r\n");

	while (1); /* Never terminate the task */
}

int main(void)
{
	UART3_Config(115200);
    UART3_SendString((greet));

	// In main function, provide a 256 * 4 = 1024 bit array
	// as usertask private sandbox
	unsigned int usertask_stack[256];

	// The address of stack is descneding, so the start point of
	// new stack should be at the last of the array (+256)
	// -16 is reserved for r4 - r11
	unsigned int *usertask_stack_start = usertask_stack + 256 - 16;
	usertask_stack_start[8] = (unsigned int) &usertask;

	UART3_SendString("OS: Starting\r\n");

    usertask_stack_start = activate(usertask_stack_start);

	UART3_SendString("Back to main function\r\n");

    usertask_stack_start = activate(usertask_stack_start);


    turn_on_led_all();


	for(;;);
}
