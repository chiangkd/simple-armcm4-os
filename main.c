#include <stdint.h>
#include "stm32f30x.h"
#include "led.h"

// static char greet[] = "Hello STM32F303ZE via ST-Link (USART3)!\r\n";

int main(void)
{
    turn_on_led_all();
    // usart_transmit((greet));
	for(;;);
}
