#include <i2c.h>
#include <rcc.h>
#include <gpio.h>
/*
 * set mode
 * set speed
 * set address
 * set ack
 * set rise time for i2c pin
*/
void I2C_init(I2C_handle_t* I2C_handle) {
    if (I2C_handle->I2C_reg == I2C1) 
        RCC_I2C1_bus_clock_enable();
    
    GPIO_I2C_pins_enable();

    I2C_handle->I2C_reg->CR1 |= (1U << 15);
    I2C_handle->I2C_reg->CR1 &= ~(1U << 15);

    //set clock speed
    uint32_t freq = RCC_get_APB1_clock_hz() / 1000000;
    I2C_handle->I2C_reg->CR2 = freq & 0x3F;

    //ccr 
    uint16_t ccr_val = 0;
    if (I2C_handle->I2C_conf.speed <= I2C_CLOCK_SPEED_SM) {
        ccr_val = (RCC_get_APB1_clock_hz() / (2 * I2C_handle->I2C_conf.speed));
        I2C_handle->I2C_reg->CCR = (ccr_val & 0xFFF);
    }

    //reset time
    I2C_handle->I2C_reg->TRISE = (RCC_get_APB1_clock_hz() / 1000000) + 1;

    //duty
    I2C_handle->I2C_reg->CCR |= (I2C_handle->I2C_conf.duty << 14);

    //ack 
    I2C_handle->I2C_reg->CR1 |= (I2C_handle->I2C_conf.ack << 10);

    I2C_handle->I2C_reg->OAR1 = (1U << 14);

    //enable I2C
    I2C_handle->I2C_reg->CR1 |= (1U << 0);
}

void I2C_deinit(I2C_reg_t* I2C_reg) {}


void I2C_transmit(I2C_reg_t* I2C_reg, uint8_t address, uint8_t* buffer, uint32_t size) {
    I2C_reg->CR1 |= (1U << 8);
    while (!(I2C_reg->SR1 & (1U << 0))) {}

    I2C_reg->DR = address << 1;
    while (!(I2C_reg->SR1 & (1U << 1))) {}
    (void)(I2C_reg->SR1 | I2C_reg->SR2);

    for (uint32_t i = 0; i < size; i++) {
        while (!(I2C_reg->SR1 & (1U << 7))) {}
        I2C_reg->DR = buffer[i];
    }

    while (!(I2C_reg->SR1 & (1U << 2))) {}
    I2C_reg->CR1 |= (1U << 9);
}

void I2C_receive(I2C_reg_t* I2C_reg, uint8_t address, uint8_t* buffer, uint32_t size) {
    I2C_reg->CR1 |= (1U << 10);
    I2C_reg->CR1 |= (1U << 8);
    while (!(I2C_reg->SR1 & (1U << 0))) {}

    I2C_reg->DR = (address << 1) | 1U;
    while (!(I2C_reg->SR1 & (1U << 1))) {}
    (void)(I2C_reg->SR1 | I2C_reg->SR2);

    for (uint32_t i = 0; i < size; i++) {
        if (i + 1 == size) {
            I2C_reg->CR1 &= ~(1U << 10);
            I2C_reg->CR1 |= (1U << 9);
        }
        while (!(I2C_reg->SR1 & (1U << 6))) {}
        buffer[i] = I2C_reg->DR;
    }
}
