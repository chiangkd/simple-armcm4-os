#ifndef __PORT_H_
#define __PORT_H_

void platform_init(void);
void platform_init_env(uint32_t *task_stack);
void switch_to_task(uint32_t *task_stack);

void syscall(void);
void SysTick_Handler(void);
void PendSV_Handler(void);

#endif
