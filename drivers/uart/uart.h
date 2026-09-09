#ifndef UART_H
#define UART_H 

#include <stdint.h>

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_reg_t;

typedef struct {
    volatile uint8_t mode;
    volatile uint16_t baud;
    volatile uint8_t stop_bits;
    volatile uint8_t word_length;
    volatile uint8_t parity_bits;
    volatile uint8_t hardware_flow_control;
} USART_config_t;

typedef struct {
    USART_reg_t* USART_reg;
    USART_config_t USART_config;
} USART_handle_t;

#define USART1_ADDR             (0x40011000U)
#define USART2_ADDR             (0x40004400U)
#define USART6_ADDR             (0x40011400U)

#define USART1                  ((USART_reg_t*) USART1_ADDR)
#define USART2                  ((USART_reg_t*) USART2_ADDR)
#define USART6                  ((USART_reg_t*) USART6_ADDR)

#define USART_8_DATA_BITS       (0)
#define USART_9_DATA_BITS       (1)

#define USART_1_STOP_BIT        (0)
#define USART_0x5_STOP_BIT      (1)
#define USART_2_STOP_BIT        (2)

void USART2_config(USART_handle_t* USART_handle);

void USART2_transmit_char(uint8_t chr); 
void USART2_transmit_string(uint8_t* string);

uint8_t USART2_receive_char(void);


#endif
