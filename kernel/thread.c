#include <stdint.h>
#include "os.h"
#include "thread.h"
#include "malloc.h"
#include "port.h"

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

typedef struct {
	void *stack;
	void *orig_stack;
	uint8_t in_use;
} tcb_t;

static tcb_t tasks[MAX_TASKS];
static int last_task;

void __attribute__((naked)) PendSV_Handler(void)
{
	/* Save the old task's context[1]*/
	asm volatile("mrs   r0, psp\n"
	             "stmdb r0!, {r4-r11, lr}\n");
	/* To get the task pointer address from result r0 */
	asm volatile("mov   %0, r0\n" : "=r" (tasks[last_task].stack));

	/* Find a new task to run */
	while (1) {
		last_task++;
		if (last_task == MAX_TASKS)
			last_task = 0;
		if (tasks[last_task].in_use) {
			/* Move the task's stack pointer address into r0 */
			asm volatile("mov r0, %0\n" : : "r" (tasks[last_task].stack));
			/* Restore the new task's context and jump to the task */
			asm volatile("ldmia r0!, {r4-r11, lr}\n"
			             "msr psp, r0\n"
			             "bx lr\n");
		}
	}
}

/* As PendSV does, this function also switches context and
 * maintain assembly on its own. This avoids the compiler
 * modifying register at prologue/epilogue sequences and
 * corrupts inline-assembly usage.
 */
void __attribute__((naked)) thread_start()
{
	last_task = 0;

	/* Reset APSR before context switch.
	 * Make sure we have a _clean_ PSR for the task.
	 */
	asm volatile("mov r0, #0\n"
	             "msr APSR_nzcvq, r0\n");
	/* To bridge the variable in C and the register in ASM,
	 * move the task's stack pointer address into r0.
	 * http://www.ethernut.de/en/documents/arm-inline-asm.html
	 */
	asm volatile("mov r0, %0\n" : : "r" (tasks[last_task].stack));
	asm volatile("msr psp, r0\n"
	             "mov r0, #3\n"
	             "msr control, r0\n"
	             "isb\n");
	/* This is how we simulate stack handling that pendsv_handler
	 * does. Thread_create sets 17 entries in stack, and the 9
	 * entries we pop here will be pushed back in pendsv_handler
	 * in the same order.
	 *
	 *
	 *                      pop {r4-r11, lr}
	 *                      ldr r0, [sp]
	 *          stack
	 *  offset -------
	 *        |   16  | <- Reset value of PSR
	 *         -------
	 *        |   15  | <- Task entry
	 *         -------
	 *        |   14  | <- LR for task
	 *         -------
	 *        |  ...  |                             register
	 *         -------                              -------
	 *        |   9   | <- Task argument ---->     |   r0  |
	 * psp after pop--<                             -------
	 *        |   8   | <- EXC_RETURN    ---->     |   lr  |
	 *         -------                              -------
	 *        |   7   |                            |  r11  |
	 *         -------                              -------
	 *        |  ...  |                            |  ...  |
	 *         -------                              -------
	 *        |   0   |                            |   r4  |
	 * psp ->  -------                              -------
	 *
	 * Instead of "pop {r0}", use "ldr r0, [sp]" to ensure consistent
	 * with the way how PendSV saves _old_ context[1].
	 */
	asm volatile("pop {r4-r11, lr}\n"
	             "ldr r0, [sp]\n");
	/* Okay, we are ready to run first task, get address from
	 * stack[15]. We just pop 9 register so #24 comes from
	 * (15 - 9) * sizeof(entry of sp) = 6 * 4.
	 */
	asm volatile("ldr pc, [sp, #24]\n");

	/* Never reach here */
	while(1);
}


int thread_create(void (*run)(void *), void *userdata)
{
	int thread_id = 0;
	uint32_t *stack;

	for (thread_id = 0; thread_id < MAX_TASKS; thread_id++) {
		if (tasks[thread_id].in_use == 0)
			break;
	}

	if (thread_id == MAX_TASKS)
		return -1;

	/* Create the stack */
	stack = (uint32_t *) malloc(STACK_SIZE * sizeof(uint32_t));
	tasks[thread_id].orig_stack = stack;
	if (stack == 0)
		return -1;

	stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push */
	stack[8] = (unsigned int) THREAD_PSP;
	stack[9] = (unsigned int) userdata;
	stack[14] = (unsigned) &thread_self_terminal;
	stack[15] = (unsigned int) run;
	stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit */

	tasks[thread_id].stack = stack;
	tasks[thread_id].in_use = 1;

	return thread_id;

}

void thread_kill(int thread_id)
{
	tasks[thread_id].in_use = 0;

	/* Free the stack */
	free(tasks[thread_id].orig_stack);
}

void thread_self_terminal()
{
	/* This will kill the stack.
	 * For now, disable context switches to save ourselves.
	 */
	asm volatile("cpsid i\n");
	thread_kill(last_task);
	asm volatile("cpsie i\n");

	/* And now wait for death to kick in */
	while (1);
}
