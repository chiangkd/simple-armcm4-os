#include "led.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

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

    // Enable GPIOB clock

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_14;

    // Set PB0, 7, 14 moder as OUTPUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

    // Set push-pull
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    // Set high speed
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Set no pull-up pull-down R
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOB, &GPIO_InitStructure);


    // Turn on LED
    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_14);
}
