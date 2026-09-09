#include "gpio.h"
#include "rcc.h"
#include <uart.h>
#include <generic.h>

void USART2_config(USART_handle_t* USART_handle) {

    RCC_USART2_bus_clock_enable();

    GPIO_USART2_TXRX_pins_enable();
    
    USART_handle->USART_reg->CR1 = 0;                //reset all bits in usart register
    
    //enable uart
    USART_handle->USART_reg->CR1 |= (1U << 13);      //enable usart

    //word length 
    USART_handle->USART_reg->CR1 |= (USART_handle->USART_config.word_length << 12);
   
    //calculate baud rate
    USART_handle->USART_reg->BRR = RCC_get_APB1_clock_hz() / USART_handle->USART_config.baud;

    //parity even/odd
    if (USART_handle->USART_config.parity_bits == USART_PARITY_EVEN) {
        USART_handle->USART_reg->CR1 |= (1U << 10);
        USART_handle->USART_reg->CR1 &= ~(1U << 9);
    }else if (USART_handle->USART_config.parity_bits == USART_PARITY_ODD) {
        USART_handle->USART_reg->CR1 |= (1U << 10);
        USART_handle->USART_reg->CR1 |= (1U << 9);
    }

    //usart rx/tx enable
    if (USART_handle->USART_config.mode == USART_MODE_RX)
        USART_handle->USART_reg->CR1 |= (1U << 2);       
    else if (USART_handle->USART_config.mode == USART_MODE_TX) 
        USART_handle->USART_reg->CR1 |= (1U << 3);       
    else if (USART_handle->USART_config.mode == USART_MODE_TXRX)  {
        USART_handle->USART_reg->CR1 |= (1U << 2);       //receive enable
        USART_handle->USART_reg->CR1 |= (1U << 3);       //transmit enable
    }

    //stop bits 
    if (USART_handle->USART_config.stop_bits == USART_STOP_BIT_0x5) {
        USART_handle->USART_reg->CR2 |= (1U << 12);
    }else if (USART_handle->USART_config.stop_bits == USART_STOP_BIT_2) {
        USART_handle->USART_reg->CR2 |= (2U << 12);
    }else if (USART_handle->USART_config.stop_bits == USART_STOP_BIT_1x5) {
        USART_handle->USART_reg->CR2 |= (3U << 12);
    }
}

void USART2_transmit_char(uint8_t chr) {
    //copy data in USART2->DR register and wait until TC = 1

    while (!(USART2->SR & (1U << 7))) {}   //wait until TC = 1
    USART2->DR = chr;
}

void USART2_transmit_string(uint8_t* string) {
    while (*string) USART2_transmit_char(*string++);
}

uint8_t USART2_receive_char(void) {
    while (USART2->SR & (1 << 5)) {
        return USART2->DR;
    }
    return 0;
}
