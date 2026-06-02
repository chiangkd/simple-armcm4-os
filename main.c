#include <stdint.h>
#include <stddef.h>
#include "stm32f30x.h"
#include "led.h"
#include "uart.h"
#include "port.h"

/* Size of our user task stacks in words */
#define STACK_SIZE 256

/* Number of user task */
#define TASK_LIMIT 2

static char greet[] = "Hello STM32F303ZE via ST-Link (USART3)!\r\n";

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

unsigned int *create_task(unsigned int *stack, void (*start)(void))
{
	stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push */
	stack[8] = (unsigned int) THREAD_PSP;
	stack[15] = (unsigned int) start;
	stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit */
	stack = activate(stack);

	return stack;
}

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

void task1_func(void)
{
	UART3_SendString("task1: Created!\r\n");
	UART3_SendString("task1: Now, return to kernel mode\r\n");
	syscall();
	while (1) {
		UART3_SendString("task1: Executed!\r\n");
		UART3_SendString("task1: Now, return to kernel mode\r\n");
		syscall(); /* return to kernel mode */
	}
}

void task_init(void)
{
	unsigned int empty[32];
	task_init_env(empty + 32);
}

void task2_func(void)
{
	UART3_SendString("task2: Created!\r\n");
	UART3_SendString("task2: Now, return to kernel mode\r\n");
	syscall();
	while (1) {
		UART3_SendString("task2: Executed!\r\n");
		UART3_SendString("task2: Now, return to kernel mode\r\n");
		syscall(); /* return to kernel mode */
	}
}

int main(void)
{
	UART3_Config(115200);
    UART3_SendString((greet));

	size_t task_count = 0;
	size_t current_task = 0;

	unsigned int user_stacks[TASK_LIMIT][STACK_SIZE];
	unsigned int *usertasks[TASK_LIMIT];

	task_init();

	if (SysTick_Config(SystemCoreClock / 100)) {
		UART3_SendString("OS: SysTick Configuration Failed!\n");
		while (1);
	}

		UART3_SendString("OS: Starting...\r\n");
		UART3_SendString("OS: First create task 1\r\n");
		usertasks[0] = create_task(user_stacks[0], &task1_func);
		task_count += 1;
		UART3_SendString("OS: Back to OS, create task 2\r\n");
		usertasks[1] = create_task(user_stacks[1], &task2_func);
		task_count += 1;


	for (int i = 0; i < 5; i++) {
		UART3_SendString("--> OS: Activate next task\r\n");
		usertasks[current_task] = activate(usertasks[current_task]);
		UART3_SendString("--> OS: Back to OS\r\n");

		current_task = current_task == (task_count - 1) ? 0 : current_task + 1;
	}

    turn_on_led_all();


	for(;;);
}

void SysTick_Handler(void)
{
	UART3_SendString("Interrupt from System Timer\r\n");
}
