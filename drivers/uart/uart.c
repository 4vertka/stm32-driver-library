#include "gpio.h"
#include "rcc.h"
#include <uart.h>
#include <generic.h>

/*
void USART_enable(USART_handler_t* USART_handler) {
    USART_handler->USART_reg->CR1 |= (1U << 13);                // enable usart 

    //set word length 
    if (USART_handler->USART_config.word_length == USART_8_DATA_BITS) 
        USART_handler->USART_reg->CR1 &= ~(1U << 12);
    else if (USART_handler->USART_config.word_length == USART_9_DATA_BITS) 
        USART_handler->USART_reg->CR1 |= (1U << 12);
    
    //set stop bits
    USART_handler->USART_reg->CR2 &= ~(3U << 12);
    USART_handler->USART_reg->CR2 |= (USART_handler->USART_config.stop_bits << 12);
    
}
*/ 

void USART2_config(USART_handle_t* USART_handle) {
    RCC_USART2_bus_clock_enable();

    GPIO_USART2_TXRX_pins_enable();
}
