#ifndef __THREAD_H_
#define __THREAD_H_

#define MAX_TASKS 10
#define STACK_SIZE 256

typedef struct {
	void *stack;
	void *orig_stack;
	uint8_t in_use;
} tcb_t;

extern tcb_t tasks[MAX_TASKS];

void pendsv_save_psp(uint32_t *task_psp);
void thread_start();
int thread_create(void (*run)(void *), void *userdata);
void thread_kill(int thread_id);
void thread_self_terminal();

#endif
