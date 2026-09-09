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

    //enable uart
    USART2->CR1 = 0;                //reset all bits in usart register
    USART2->CR1 |= (1U << 13);      //enable usart

    //word length 
    USART2->CR1 |= (USART_handle->USART_config.word_length << 12);
    
    //baud rate 
    uint32_t pll_freq = RCC_Get_PLL_frequ();
    float usart_div = 16000000.0 / (float)USART_handle->USART_config.baud;
    
    uint16_t usart_div_mantissa = (uint16_t) usart_div;

    float fraction = usart_div - usart_div_mantissa;
    uint8_t usart_div_fraction = (uint8_t)(fraction * 16.0f + 0.5f);

    if (usart_div_fraction == 16) {
        usart_div_fraction = 0;
        usart_div_mantissa += 1;
    }

    USART2->BRR = 0;
    USART2->BRR |= usart_div_fraction;
    USART2->BRR |= (usart_div_mantissa << 4);

    //usart rx/tx enable 
    USART2->CR1 |= (1U << 2);       //receive enable
    USART2->CR1 |= (1U << 3);       //transmit enable

}

void USART2_send_char(uint8_t chr) {
    //copy data in USART2->DR register and wait until TC = 1
    USART2->DR = chr;

    while (!(USART2->SR & (1U << 6))) {}   //wait until TC = 1
}

void USART2_send_string(uint8_t* string) {
    while (*string) USART2_send_char(*string++);
}

uint8_t USART2_get_char(void) {
    uint8_t tmp;
    while (!(USART2->SR & (1 << 5))) {}         //wait until rxne bit (read data register bit) is set (ready to be read)
    
    tmp = USART2->DR;                           //read the data from register, clear rxne bit
    
    return tmp;
}
