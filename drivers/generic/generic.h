#ifndef GENERIC_H
#define GENERIC_H

#include <stdint.h>

typedef struct {
    volatile uint32_t MEMRMP; 
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
} SYSCFG_reg_t;

#define SYSCFG_ADDR             (0x40013800U)
#define SYSCFG                  ((SYSCFG_reg_t*) SYSCFG_ADDR)

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_reg_t;

#define PWR_ADDR                (0x40007000U)
#define PWR                     ((PWR_reg_t*) PWR_ADDR)

typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t OPTCR;
} FLASH_reg_t;

#define FLASH_REG_ADDR          (0x40023C00U)
#define FLASH_REG               ((FLASH_reg_t*)FLASH_REG_ADDR)

// Busses base addresses
#define APB1_BUS_ADDR           (0x40000000U)
#define APB2_BUS_ADDR           (0x40010000U)
#define AHB1_BUS_ADDR           (0x40020000U)
#define AHB2_BUS_ADDR           (0x50000000U)

#define SYSCFG_EXTI_GPIOA       (0)
#define SYSCFG_EXTI_GPIOB       (1)
#define SYSCFG_EXTI_GPIOC       (2)
#define SYSCFG_EXTI_GPIOD       (3)
#define SYSCFG_EXTI_GPIOE       (4)
#define SYSCFG_EXTI_GPIOH       (7)

#define ENABLE                  (1)
#define DISABLE                 (0)

#define SET                     (1)
#define RESET                   (0)

void SYSCFG_bus_clock_enable(void);

#endif
