#include "rcc.h"
#include <spi.h>

/* Turn on SPI clock
 * Configure CR1 register
 * Configure CR2 register 
*/

void SPI_init(SPI_handle_t* SPI_handle) {
    if (SPI_handle->SPI_reg == SPI1) 
        RCC_SPI1_bus_clock_enable();

    SPI_handle->SPI_reg->CR1 = 0;

    //mode 
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.mode << 2);
    
    //bus conf
    if (SPI_handle->SPI_config.bus_cfg == SPI_BUS_FULL_DUPLEX) {
        SPI_handle->SPI_reg->CR1 &= ~(1U << 15);
    }else if (SPI_handle->SPI_config.bus_cfg == SPI_BUS_HALF_DUPLEX) {
        SPI_handle->SPI_reg->CR1 |= (1U << 15);
        //SPI_handle->SPI_reg->CR1 |= (1U << 14);
    }else if (SPI_handle->SPI_config.bus_cfg == SPI_BUS_SIMPLEX_RX) {
        SPI_handle->SPI_reg->CR1 &= ~(1U << 15);
        SPI_handle->SPI_reg->CR1 |= (1U << 10); 
    }

    //clock speed
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.clock_speed << 3);

    //MSB first
    SPI_handle->SPI_reg->CR1 &= ~(1U << 7);

    //dff 
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.dff << 11);

    //cpha
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.cpha << 0);

    //cpol
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.cpol << 1);

    //ssm 
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.ssm << 9);
    if (SPI_handle->SPI_config.ssm == SPI_SMM_ENABLE) 
        SPI_handle->SPI_reg->CR1 |= (1U << 8);

    if (SPI_handle->SPI_config.dma == SPI_DMA_DISABLE) 
        SPI_handle->SPI_reg->CR2 = 0;
}

void SPI_deinit(SPI_reg_t* SPI_reg) {}

void SPI_transmit(SPI_reg_t* SPI_reg, uint8_t *data, uint32_t size) {
    int i = 0;
    while (i < size) {
        while (!((SPI_reg->SR) & (1U << 1))) {}             //wait for TXE bit until TX buffer is empty
        SPI1->DR = data[i];
        i++;
    }

    while (!((SPI_reg->SR) & (1U << 1))) {}
    while (!((SPI_reg->SR) & (1U << 7))) {}                  //check if SPI is not busy

    //Clear the Overrun flag by reading DR and SR
    uint8_t tmp = SPI_reg->DR;
    tmp = SPI_reg->SR;
}

void SPI_receive(SPI_reg_t *SPI_reg, uint8_t* data, uint32_t size) {
    while (size) {
        while (((SPI_reg->SR) & (1U << 7))) {}              //wait for BSY bit to reset
        SPI_reg->DR = 0;                                    //dummy data
        while (!((SPI_reg->SR) & (1U << 0))) {}
        *data++ = (SPI_reg->DR);
        size--;
    }
}

