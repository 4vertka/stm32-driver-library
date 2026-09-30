#include "exti.h"
#include <generic.h>
#include <spi.h>
#include <gpio.h>
#include <uart.h>
#include <systick.h>

int main() {

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);

    GPIO_SPI_pins_enable();

    SPI_handle_t spi = {0};
    spi.SPI_reg = SPI1;
    spi.SPI_config.mode = SPI_MODE_MASTER;
    spi.SPI_config.cpha = SPI_CPHA_LOW;
    spi.SPI_config.cpol = SPI_CPOL_LOW;
    spi.SPI_config.clock_speed = 3;
    spi.SPI_config.ssm = SPI_SMM_ENABLE;
    spi.SPI_config.dff = SPI_DFF_BITS8;
    spi.SPI_config.dma = SPI_DMA_DISABLE;
    spi.SPI_config.bus_cfg = SPI_BUS_FULL_DUPLEX;
    SPI_init(&spi);

    USART_handle_t uart = {0};
    uart.USART_reg = USART2;
    uart.USART_config.baud = 9600;
    uart.USART_config.word_length = USART_8_DATA_BITS;
    uart.USART_config.mode = USART_MODE_TXRX;
    uart.USART_config.stop_bits = USART_STOP_BIT_1;
    USART2_config(&uart);

    GPIO_handle_t rst = {0};
    rst.GPIO_reg = GPIOC;
    rst.GPIO_config.pin = 10;
    rst.GPIO_config.mode = GPIO_MODE_OUTPUT;
    GPIO_init(&rst);

    GPIO_handle_t sda = {0};
    sda.GPIO_reg = GPIOC;
    sda.GPIO_config.pin = 11;
    sda.GPIO_config.mode = GPIO_MODE_OUTPUT;
    GPIO_init(&sda);

    GPIO_write_ODR_pin(GPIOC, 11, ENABLE);
    GPIO_write_ODR_pin(GPIOC, 10, DISABLE);

    SYSTICK_delay(10);
    GPIO_write_ODR_pin(GPIOC, 10, ENABLE);
    SYSTICK_delay(50);

    uint8_t cmd = ((0x37 << 1) & 0x7E) | 0x80;
    uint8_t ver;
    char msg[8];
    const char hex[] = "0123456789ABCDEF";

    while(1) {
        GPIO_write_ODR_pin(GPIOC, 11, DISABLE);
        SPI_transmit(SPI1, &cmd, 1);
        SPI_receive(SPI1, &ver, 1);
        GPIO_write_ODR_pin(GPIOC, 11, ENABLE);

        msg[0] = hex[ver >> 4];
        msg[1] = hex[ver & 0xF];
        msg[2] = '\r';
        msg[3] = '\n';
        msg[4] = '\0';
        USART2_transmit_string(msg);

        SYSTICK_delay(500);
    }
}
