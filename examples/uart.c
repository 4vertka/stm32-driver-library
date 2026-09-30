#include "rcc.h"
#include "systick.h"
#include <generic.h>
#include <uart.h>
#include <gpio.h>

int main() { 

    RCC_SysClock_Init();

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);

    USART_handle_t uart = {0};
    uart.USART_reg = USART2;
    uart.USART_config.baud = 9600;
    uart.USART_config.word_length = USART_8_DATA_BITS;
    uart.USART_config.mode = USART_MODE_TXRX;

    USART2_config(&uart);
    
    while (1) {
        uint8_t data = USART2_receive_char();
        USART2_transmit_char(data);        
    }

}
