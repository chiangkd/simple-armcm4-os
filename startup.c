#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (64U * 1024U)        // 128 KB
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER SRAM_END

extern void main(void);
void reset_handler(void)
{
	/* jump to C entry point */
	main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vectors[] = {
	(void *)STACK_POINTER,
	(uint32_t *) reset_handler,	/* code entry point */
};
