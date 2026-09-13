#ifndef I2C_H
#define I2C_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_reg_t;

typedef struct {
    uint32_t speed;
    uint8_t addr;
    uint8_t ack;
    uint16_t duty;
} I2C_conf_t;

typedef struct {
    I2C_reg_t* I2C_reg;
    I2C_conf_t I2C_conf;
} I2C_handle_t;

#define I2C1_ADDR           (0x40005400U)
#define I2C2_ADDR           (0x40005800U)
#define I2C3_ADDR           (0x40005C00U)

#define I2C1                ((I2C_reg_t*) I2C1_ADDR)
#define I2C2                ((I2C_reg_t*) I2C2_ADDR)
#define I2C3                ((I2C_reg_t*) I2C3_ADDR)

#define I2C_CLOCK_SPEED_SM      (100000)
#define I2C_clock_SPEED_FM2K    (200000)
#define I2C_clock_SPEED_FM4K    (400000)

#define I2C_ACK_DISABLE         (0)
#define I2C_ACK_ENABLE          (1)

#define I2C_FM_DUTY_2           (0)
#define I2C_FM_DUTY_16DIV9      (1)

void I2C_init(I2C_handle_t* I2C_handle);
void I2C_deinit(I2C_reg_t* I2C_reg);

void I2C_transmit(I2C_reg_t* I2C_reg, uint8_t* buffer, uint32_t size);
void I2C_receive(I2C_reg_t* I2C_reg, uint8_t* buffer, uint32_t size);

#endif
