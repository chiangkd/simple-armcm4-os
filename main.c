#include <stdint.h>
#include "stm32f303ze.h"


void gpio_peri_clk_ctrl(GPIO_ID gpiox, uint8_t enable)
{
    if (enable) {
        if (gpiox ==  GPIOA) GPIOA_PCLK_EN();
        else if (gpiox == GPIOB) GPIOB_PCLK_EN();
        else if (gpiox == GPIOC) GPIOC_PCLK_EN();
        else if (gpiox == GPIOD) GPIOD_PCLK_EN();
        else if (gpiox == GPIOE) GPIOE_PCLK_EN();
        else if (gpiox == GPIOF) GPIOF_PCLK_EN();
        else if (gpiox == GPIOG) GPIOG_PCLK_EN();
        else if (gpiox == GPIOH) GPIOH_PCLK_EN();
    } else {
        if (gpiox == GPIOA) GPIOA_PCLK_DIS();
        else if (gpiox == GPIOB) GPIOB_PCLK_DIS();
        else if (gpiox == GPIOC) GPIOC_PCLK_DIS();
        else if (gpiox == GPIOD) GPIOD_PCLK_DIS();
        else if (gpiox == GPIOE) GPIOE_PCLK_DIS();
        else if (gpiox == GPIOF) GPIOF_PCLK_DIS();
        else if (gpiox == GPIOG) GPIOG_PCLK_DIS();
        else if (gpiox == GPIOH) GPIOH_PCLK_DIS();
    }
}


void turn_on_led_all()
{
// Turn ON the LED
    // 1. Address of the Clock control register (AHB ENR)
    // - 0x40021000 + 0x14 = 0x40021014
    // 2. Address of the GPIO mode register (used to control mode)
    // - LD1 -> PB0:  base: 0x48000400 + GPIOx_MODER: 0x0  (Set [1:0] to 0x01: General purpose output)
    // - LD2 -> PB7:  base: 0x48000400 + GPIOx_MODER: 0x0  (Set [15:14] to 0x01: General purpose output)
    // - LD3 -> PB14: base: 0x48000400 + GPIOx_MODER: 0x0  (Set [29:28] to 0x01: General purpose output)

    // 3. Address of the GPIO output data register (used to write)
    // - LD1 -> PB0:  base: 0x48000400 + GPIOx_ODR: 0x14  (Set [0] to 0x01: Port output data)
    // - LD2 -> PB7:  base: 0x48000400 + GPIOx_ODR: 0x14  (Set [7] to 0x01: Port output data)
    // - LD3 -> PB14: base: 0x48000400 + GPIOx_ODR: 0x14  (Set [14] to 0x01: Port output data)

    gpio_peri_clk_ctrl(GPIOB, 1);
    REG_TYPE *gpiob_moder = (REG_TYPE *) (GPIOB_BASEADDR + 0x0);
    *(gpiob_moder) &= ~((3 << 0) | (3 << 14) | (3 << 28));;
    *(gpiob_moder) |=  ((1 << 0) | (1 << 14) | (1 << 28));

    REG_TYPE *gpio_odr = (REG_TYPE *) (GPIOB_BASEADDR + 0x14);
    *(gpio_odr) |= (1 << 0) | (1 << 7) | (1 << 14);
}

int main(void)
{
    turn_on_led_all();
	for(;;);
}

// void EXTI0_IRQHandler(void)
// {
// 	// Handle the interrupt
// 	GPIO_irq_handle(0);
// }