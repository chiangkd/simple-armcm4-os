.syntax unified

.type SVC_Handler, %function
.global SVC_Handler
SVC_Handler:
	/* save user state */
	mrs r0, psp
	stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

	/* load kernel state */
	pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
	msr psr_nzcvq, ip

	bx lr

.syntax unified

.global syscall
syscall:
	svc 0
	bx lr
