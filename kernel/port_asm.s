.syntax unified

.type PendSV_Handler, %function
.global PendSV_Handler
PendSV_Handler:
	cpsid i				/* turn off interrupt */

	/* save user task */
	mrs r0, psp					/* Load psp to r0 */

	stmdb r0!, {r4-r11, lr}		/* r4-r11 and lr to PSP */

	/* Turn on the privilege mode and use MSP */
	mov r1, #0
	msr control, r1
	isb

	/* pop kernal state from MSP */
	pop {r4-r11, ip, lr}
	msr psr_nzcvq, ip

	push {r0-r3, lr}
	bl   pendsv_save_psp
	pop  {r0-r3, lr}

	/* Enable IRQ */
	cpsie i

	bx lr

.type SVC_Handler, %function
.global SVC_Handler
SVC_Handler:
	cpsid i				/* turn off interrupt */
	
	/* save user task */
	mrs r0, psp					/* Load psp to r0 */
	
	stmdb r0!, {r4-r11, lr}		/* r4-r11 and lr to PSP */

	/* Turn on the privilege mode and use MSP */
	mov r1, #0
	msr control, r1
	isb

	/* pop kernal state from MSP */ 
	pop {r4-r11, ip, lr}
	msr psr_nzcvq, ip

	push {r0-r3, lr}
	bl   set_syscall_flag   /* r0 (latest psp address) */
	pop  {r0-r3, lr}

	/* Enable IRQ */
	cpsie i

	bx lr

.type platform_init_env, %function
.global platform_init_env
platform_init_env:
	/* r0: stack address */

	/* save kernel state */
    mrs  ip, psr /* Save psr to the ip */
    push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

	/* change stack pointer from msp to psp */
	msr psp, r0
	mov r0, #2		/* Bit[1] = 1(Use PSP), Bit[0] = 0 (keep privilege) */
	msr control, r0
	isb

	/* Switch to handler mode */
	mov r7, #0

	/* When trigger system call, auto stacking mechanism will occur. */
	svc 0

	bx lr

.global switch_to_task
.type switch_to_task, %function
switch_to_task:
    /* r0 = tasks[curr_task_idx].stack */
	/* Back up main() state to MSP */
    mrs   ip, psr
    push  {r4-r11, ip, lr}

	/* Pop r4-r11 and EXC_RETURN to lr */
    ldmia r0!, {r4-r11, lr}

    msr   psp, r0

	/* Exception return */
    bx    lr

.global syscall
syscall:
	svc 0
	bx lr
