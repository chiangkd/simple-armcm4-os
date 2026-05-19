.thumb
.syntax unified

.global activate
.global SVC_Handler
.type SVC_Handler, %function

activate:
	/* save kernel state */
	mrs ip, psr
	push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

	/* load user state */
	ldmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

	msr psp, r0

	/* check the situaion and determine the transition */
	mov r0, #0xfffffff0
	cmp lr, r0                      @ lr - 0xfffffff0

	/* if "lr" does not point to exception return, then switch to process stack */
	ittt ls                         @ "ls" condition means unsinged lower or the same
	movls r0, #3
	msrls control, r0
	isbls

	/* jump to user task */
	bx lr

SVC_Handler:
	/* save user state */
	mrs r0, psp
	stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

	/* load kernel state */
	pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
	msr psr, ip

	bx lr
