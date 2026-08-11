#include <stdint.h>
#include <stdbool.h>
#include "kernel.h"
#include "thread.h"
#include "malloc.h"
#include "port.h"

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

tcb_t tasks[MAX_TASKS];

extern volatile bool need_schedule;
extern uint32_t curr_task_idx;

void pendsv_save_psp(uint32_t *task_psp)
{
	// Save the interrupted task's stack pointer
	tasks[curr_task_idx].stack = task_psp;
    
	// Notify main function to switch the task
    need_schedule = true;
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

