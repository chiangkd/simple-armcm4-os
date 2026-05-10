#include <stdint.h>
#include "stm32f30x.h"
#include "led.h"
#include "uart.h"
static char greet[] = "Hello STM32F303ZE via ST-Link (USART3)!\r\n";

int main(void)
{
    turn_on_led_all();
    UART3_Config(115200);
    UART3_SendString((greet));
	for(;;);
}
