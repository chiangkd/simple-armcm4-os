#include <stdint.h>
#include <stddef.h>
#include "stm32f30x.h"
#include "led.h"
#include "uart.h"
#include "port.h"
#include "thread.h"

static char greet[] = "Hello STM32F303ZE via ST-Link (USART3)!\r\n";

uint32_t *current_task_psp = NULL;
volatile int syscall_pending = 0;
uint32_t curr_task_idx;


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

static void delay(volatile int count)
{
	count *= 50000;
	while (count--);
}

static void busy_loop(void *str)
{
	while (1) {
		UART3_SendString(str);
		UART3_SendString(": Running...\r\n");
		delay(100);
	}
}

void task1_func(void *userdata)
{
	busy_loop(userdata);	
}


void task2_func(void *userdata)
{
	busy_loop(userdata);	
}

void task3_func(void *userdata)
{
	busy_loop(userdata);	
}


#define CPU_CLOCK_HZ 72000000
int main(void)
{
	UART3_Config(115200);
    UART3_SendString((greet));

	const char *str1 = "Task 1", *str2 = "Task 2", *str3 = "Task 3";

	UART3_SendString("--------------------------\r\n");
	UART3_SendString("OS: Starting...\r\n");

	if (thread_create(task1_func, (void *) str1) == -1)
		UART3_SendString("Thead 1 creation failed \r\n");

	if (thread_create(task2_func, (void *) str2) == -1)
		UART3_SendString("Thead 2 creation failed \r\n");

	if (thread_create(task3_func, (void *) str3) == -1)
		UART3_SendString("Thead 3 creation failed \r\n");

	// if (SysTick_Config(SystemCoreClock / 1000)) {
	// 	UART3_SendString("OS: SysTick Configuration Failed!\n");
	// 	while (1);
	// }

	// Make sure pendsv IRQ has lower priority
	NVIC_SetPriority(PendSV_IRQn, 15);

	curr_task_idx = 0;

	platform_init();

	while (1) {
		uint32_t *user_psp = tasks[curr_task_idx].stack;
		switch_to_task(user_psp);
		curr_task_idx = (curr_task_idx + 1) % 3;	// Simple schedular
	}

	// Never runs here
    turn_on_led_all();


	for(;;);
}

