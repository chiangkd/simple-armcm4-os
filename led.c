#include "led.h"

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
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Set PB0, 7, 14 moder as OUTPUT
    GPIOB->MODER &= ~((0x3 << (0*2)) | (0x3 << (7*2)) | (0x3 << (14*2))); // clear
    GPIOB->MODER |=  ((0x1 << (0*2)) | (0x1 << (7*2)) | (0x1 << (14*2))); // output

    // Set push-pull
    GPIOB->OTYPER &= ~((1 << 0) | (1 << 7) | (1 << 14)); 

    // Set high speed
    GPIOB->OSPEEDR |= ((0x3 << (0*2)) | (0x3 << (7*2)) | (0x3 << (14*2)));

    // Set no pull-up pull-down R
    GPIOB->PUPDR &= ~((0x3 << (0*2)) | (0x3 << (7*2)) | (0x3 << (14*2)));

    // Turn on LED
    GPIOB->ODR |= (1 << 0) | (1 << 7) | (1 << 14);
}
