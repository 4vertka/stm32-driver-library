#ifndef RCC_H 
#define RCC_H 

#include <stdint.h>

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t _reserved1[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t _reserved2[2];
    volatile uint32_t AHB1ENR; 
    volatile uint32_t AHB2ENR;
    volatile uint32_t _reserved3[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t _reserved4[2]; 
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR; 
    volatile uint32_t _reserved5[2];
    volatile uint32_t APB1LPENR; 
    volatile uint32_t APB2LPENR; 
    volatile uint32_t _reserved6[2];
    volatile uint32_t BDCR; 
    volatile uint32_t CSR;
    volatile uint32_t _reserved7[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR; 
    volatile uint32_t _reserved8; 
    volatile uint32_t DCKCFGR; 
} RCC_reg_t;

#define RCC_ADDR                (0x40023800U)
#define RCC                     ((RCC_reg_t*) RCC_ADDR)

#define RCC_HSI_ON              (0)
#define RCC_HSI_RDY             (1)

#define RCC_HSE_ON              (16)
#define RCC_HSE_RDY             (17)

void RCC_HSE_enable(void);

#endif
