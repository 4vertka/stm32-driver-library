#include <i2c.h>

void I2C_init(I2C_handle_t* I2C_handle) {}

void I2C_deinit(I2C_reg_t* I2C_reg) {}

void I2C_transmit(I2C_reg_t* I2C_reg, uint8_t* buffer, uint32_t size) {}

void I2C_receive(I2C_reg_t* I2C_reg, uint8_t* buffer, uint32_t size) {}
