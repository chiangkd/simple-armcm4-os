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

	UART3_SendString("This should not be printed\r\n");

	while (1); /* Never terminate the task */
}

int main(void)
{
	UART3_Config(115200);
    UART3_SendString((greet));

	unsigned int usertask_stack[256];
	unsigned int *usertask_stack_start = usertask_stack + 256 - 16;
	usertask_stack_start[8] = (unsigned int) &usertask;

    activate(usertask_stack_start);


	UART3_SendString("Back to main function\r\n");
    turn_on_led_all();


	for(;;);
}
