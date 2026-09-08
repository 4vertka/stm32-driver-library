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

#define RCC_PLL_ON              (24)
#define RCC_PLL_RDY             (25)

#define RCC_PLLSRC              (22)

#define RCC_MCO1_HSI_CLOCK      (0)
#define RCC_MCO1_LSE_CLOCK      (1)
#define RCC_MCO1_HSE_CLOCK      (2)
#define RCC_MCO1_PLL_CLOCK      (3)

#define RCC_MCO1PRE_DIVNO       (0)
#define RCC_MCO1PRE_DIV2        (4)
#define RCC_MCO1PRE_DIV3        (5)
#define RCC_MCO1PRE_DIV4        (6)
#define RCC_MCO1PRE_DIV5        (7)

#define RCC_MCO2_SYSCLK         (0)
#define RCC_MCO2_PLLI2S_CLOCK   (1) 
#define RCC_MCO2_HSE_CLOCK      (2) 
#define RCC_MCO2_PLL_CLOCK     (3)

#define RCC_MCO2PRE_DIVNO       (0)
#define RCC_MCO2PRE_DIV2        (4)
#define RCC_MCO2PRE_DIV3        (5)
#define RCC_MCO2PRE_DIV4        (6)
#define RCC_MCO2PRE_DIV5        (7)

#define RCC_DEFAULT_PLLM_VAL    (16)
#define RCC_DEFAULT_PLLN_VAL    (336)
#define RCC_DEFAULT_PLLP_VAL    (1)

#define RCC_AHB_DIV1            (1)
#define RCC_AHB_DIV2            (8)
#define RCC_AHB_DIV4            (9)
#define RCC_AHB_DIV8            (10)
#define RCC_AHB_DIV16           (11)
#define RCC_AHB_DIV64           (12)
#define RCC_AHB_DIV128          (13)
#define RCC_AHB_DIV256          (14)
#define RCC_AHB_DIV512          (15)

#define RCC_APB_DIV1            (1) 
#define RCC_APB_DIV2            (4)
#define RCC_APB_DIV4            (5)
#define RCC_APB_DIV8            (6)
#define RCC_APB_DIV16           (7)

#define RCC_HSI_SYSCLOCK        (0)
#define RCC_HSE_SYSCLOCK        (1) 
#define RCC_PLL_SYSCLOCK        (2) 

#define HSI_CLOCK_SPEED         (16)
#define HSE_CLOCK_SPEED         (8)

void RCC_HSE_enable(void);
void RCC_HSE_disable(void);

void RCC_HSI_enable(void);
void RCC_HSI_disable(void);

void RCC_PLL_enable(void);
void RCC_PLL_disable(void);

void RCC_PWR_config(void);

void RCC_FLASH_config(uint8_t latency);

void RCC_bus_prescaler_config(uint8_t ahb, uint8_t apb1, uint8_t apb2);

void RCC_set_sysclock(uint8_t src);

void RCC_SysClock_Init(void);

uint32_t RCC_Get_PLL_frequ(void);

void RCC_USART2_bus_clock_enable(void);

void RCC_MCO1(uint8_t clock, uint8_t div);
void RCC_MCO2(uint8_t clock, uint8_t div);

#endif
