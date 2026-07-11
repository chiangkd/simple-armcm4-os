#ifndef __THREAD_H_
#define __THREAD_H_

void thread_start();
int thread_create(void (*run)(void *), void *userdata);
void thread_kill(int thread_id);
void thread_self_terminal();

#endif
