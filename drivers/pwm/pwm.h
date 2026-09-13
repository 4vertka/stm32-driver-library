#ifndef PWM_H
#define PWM_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t _RESERVED1;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t _RESERVED2;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
    volatile uint32_t TIM2_OR;
    volatile uint32_t TIM5_OR;
     
} TIM2_TIM5_reg_t;

#define TIM2_ADDR               (0x40000000U)
#define TIM3_ADDR               (0x40000400U)
#define TIM4_ADDR               (0x40000800U)
#define TIM5_ADDR               (0x40000C00U)

#define TIM2                    ((TIM2_TIM5_reg_t*) TIM2_ADDR)
#define TIM3                    ((TIM2_TIM5_reg_t*) TIM3_ADDR)
#define TIM4                    ((TIM2_TIM5_reg_t*) TIM4_ADDR)
#define TIM5                    ((TIM2_TIM5_reg_t*) TIM5_ADDR)

#endif
