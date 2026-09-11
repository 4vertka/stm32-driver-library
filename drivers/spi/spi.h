#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR; 
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_reg_t;

typedef struct {
    uint8_t mode;
    uint8_t bus_cfg;
    uint8_t clock_speed;
    uint8_t dff;
    uint8_t cpol;
    uint8_t cpha;
    uint8_t ssm;
} SPI_config_t;

typedef struct {
    SPI_reg_t* SPI_reg;
    SPI_config_t SPI_config;
} SPI_handle_t;

#define SPI1_ADDR           (0x40013000U)
#define SPI2_ADDR           (0x40003800U)
#define SPI3_ADDR           (0x40003C00U)

#define SPI1                ((SPI_reg_t*) SPI1_ADDR)
#define SPI2                ((SPI_reg_t*) SPI2_ADDR)
#define SPI3                ((SPI_reg_t*) SPI3_ADDR)

#define SPI_MODE_SLAVE      (0)
#define SPI_MODE_MASTER     (1)

#define SPI_BUS_FULL_DUPLEX (0)
#define SPI_BUS_HALF_DUPLEX (1)
#define SPI_BUS_SIMPLEX_RX  (2)

#define SPI_CLOCK_SPEED_DIV2    (0)
#define SPI_CLOCK_SPEED_DIV4    (1)
#define SPI_CLOCK_SPEED_DIV8    (2)
#define SPI_CLOCK_SPEED_DIV16   (3)
#define SPI_CLOCK_SPEED_DIV32   (4)
#define SPI_CLOCK_SPEED_DIV64   (5)
#define SPI_CLOCK_SPEED_DIV128  (6)
#define SPI_CLOCK_SPEED_DIV256  (7)

#define SPI_DFF_BITS8           (0)
#define SPI_DFF_BITS16          (1)

#define SPI_CPOL_LOW            (0)
#define SPI_CPOL_HIGH           (1)

#define SPI_CPHA_LOW            (0)
#define SPI_CPHA_HIGH           (1)

#define SPI_SMM_DISABLE        (0)
#define SPI_SMM_ENABLE         (1)


void SPI_init(SPI_handle_t* SPI_handle);
void SPI_deinit(SPI_reg_t* SPI_reg);

void SPI_transmit(SPI_reg_t* SPI_reg, uint8_t* TXbuffer, uint32_t size);
void SPI_receive(SPI_reg_t* SPI_reg);

void SPI_irq_exti_setup(uint8_t pin, uint8_t mode);
void SPI_irq_set_priority(uint8_t irq_num, uint8_t priority);
void SPI_irq_enable(uint8_t irq_num);

void SPI1_config(void);
void SPI_transmit_char(uint8_t ch);
uint8_t SPI_receive_char(void);

#endif
