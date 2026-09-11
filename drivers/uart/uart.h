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
    uint8_t mode;
    uint16_t baud;
    uint8_t stop_bits;
    uint8_t word_length;
    uint8_t parity_bits;
    uint8_t hardware_flow_control;
    
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

#define USART_MODE_TX           (0)
#define USART_MODE_RX           (1)
#define USART_MODE_TXRX         (2)

#define USART_8_DATA_BITS       (0)
#define USART_9_DATA_BITS       (1)

#define USART_STOP_BIT_1        (0)
#define USART_STOP_BIT_0x5      (1)
#define USART_STOP_BIT_2        (2)
#define USART_STOP_BIT_1x5      (3)

#define USART_BAUD_RATE_9600    (9600)
#define USART_BAUD_RATE_1200    (1200)
#define USART_BAUD_RATE_115200  (115200)
#define USART_BAUD_RATE_19200   (19200)

#define USART_PARITY_ODD        (2)
#define USART_PARITY_EVEN       (1)
#define USART_PARITY_NO         (0)

#define USART_HW_FLOW_CTRL_NO       (0)
#define USART_HW_FLOW_CTRL_CTS      (1)
#define USART_HW_FLOW_CTRL_RTS      (2)
#define USART_HW_FLOW_CTRL_CTS_RTS  (3)

void USART2_config(USART_handle_t* USART_handle);

void USART2_transmit_char(uint8_t chr); 
void USART2_transmit_string(uint8_t* string);

uint8_t USART2_receive_char(void);

void USART2_transmit_char_IT(uint8_t chr);
uint8_t USART2_receive_char_IT(void);

void USART2_config_interrupt(USART_handle_t* USART_handle);

int32_t _write(int32_t handle, uint8_t* data, int32_t size);

#endif
