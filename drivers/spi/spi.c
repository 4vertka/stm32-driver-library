#include <spi.h>

void SPI1_config(void) {
    //slave management (software)
    SPI1->CR1 |= (1U << 9);
    SPI1->CR1 |= (1U << 8);

    //set spi as master 
    SPI1->CR1 |= (1U << 2);

    //enable spi 
    SPI1->CR1 |= (1U << 6);
}

void SPI_transmit_char(uint8_t ch) {
    while (!(SPI1->SR & (1U << 1))) {}          // check if TXE (tranmit buffer is empty)
    SPI1->DR = ch;
    while (!(SPI1->SR & (1U << 7))) {}          //wait until bus is free
}

void SPI_init(SPI_handle_t* SPI_handle) {
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

    //dff 
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.dff << 11);

    //cpha
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.cpha << 0);

    //cpol
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.cpol << 1);

    //ssm 
    SPI_handle->SPI_reg->CR1 |= (SPI_handle->SPI_config.ssm << 9);
}

void SPI_deinit(SPI_reg_t* SPI_reg) {}

void SPI_transmit(SPI_reg_t* SPI_reg, uint8_t *TXbuffer, uint32_t size) {

    while (size > 0) {
        while (!(SPI_reg->SR & (1U << 1))) {}          // check if TXE (tranmit buffer is empty)
        // check if dff bit is 8-bit or 16-bit mode
        if (SPI_reg->CR1 & (1U << 11)) {
            SPI_reg->DR = *((uint16_t*)TXbuffer);
            size -= 2;
            (uint16_t*)TXbuffer++;
        }else {
            SPI_reg->DR = *TXbuffer;
            size--;
            TXbuffer++;
        }
        
        //while (!(SPI1->SR & (1U << 7))) {}             // wait until bus is free 
    }

}

void SPI_receive(SPI_reg_t *SPI_reg) {}

void SPI_irq_exti_setup(uint8_t pin, uint8_t mode) {}

void SPI_irq_set_priority(uint8_t irq_num, uint8_t priority) {}

void SPI_irq_enable(uint8_t irq_num) {}
