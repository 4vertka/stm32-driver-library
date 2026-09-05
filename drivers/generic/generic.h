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
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_reg_t;

#define EXTI_ADDR               (0x40013C00U)
#define EXTI                    ((EXTI_reg_t*) EXTI_ADDR)

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

// Cortex-M4

//Interrupt set-enable registers
#define NVIC_ISER0              (volatile uint32_t*)(0xE000E100)
#define NVIC_ISER1              (volatile uint32_t*)(0xE000E104)
#define NVIC_ISER2              (volatile uint32_t*)(0xE000E108)
#define NVIC_ISER3              (volatile uint32_t*)(0xE000E10C)
#define NVIC_ISER4              (volatile uint32_t*)(0xE000E110)
#define NVIC_ISER5              (volatile uint32_t*)(0xE000E114)
#define NVIC_ISER6              (volatile uint32_t*)(0xE000E118)
#define NVIC_ISER7              (volatile uint32_t*)(0xE000E11C)

//Interrupt clear-enable registers
#define NVIC_ICER0              (volatile uint32_t*)(0xE000E180)
#define NVIC_ICER1              (volatile uint32_t*)(0xE000E184)
#define NVIC_ICER2              (volatile uint32_t*)(0xE000E188)
#define NVIC_ICER3              (volatile uint32_t*)(0xE000E18C)
#define NVIC_ICER4              (volatile uint32_t*)(0xE000E190)
#define NVIC_ICER5              (volatile uint32_t*)(0xE000E194)
#define NVIC_ICER6              (volatile uint32_t*)(0xE000E198)
#define NVIC_ICER7              (volatile uint32_t*)(0xE000E19C)

//Interrupt priority register
#define NVIC_IPR_ADDR           (volatile uint32_t*)(0xE000E400)

#define NVIC_IRQ_PRIORITY_0     (0)
#define NVIC_IRQ_PRIORITY_1     (1)
#define NVIC_IRQ_PRIORITY_2     (2)
#define NVIC_IRQ_PRIORITY_3     (3)
#define NVIC_IRQ_PRIORITY_4     (4)
#define NVIC_IRQ_PRIORITY_5     (5)
#define NVIC_IRQ_PRIORITY_6     (6)
#define NVIC_IRQ_PRIORITY_7     (7)
#define NVIC_IRQ_PRIORITY_8     (8)
#define NVIC_IRQ_PRIORITY_9     (9)
#define NVIC_IRQ_PRIORITY_10    (10)
#define NVIC_IRQ_PRIORITY_11    (11)
#define NVIC_IRQ_PRIORITY_12    (12)
#define NVIC_IRQ_PRIORITY_13    (13)
#define NVIC_IRQ_PRIORITY_14    (14)
#define NVIC_IRQ_PRIORITY_15    (15)

#define NVIC_IRQ_EXTI0          (6)
#define NVIC_IRQ_EXTI1          (7)
#define NVIC_IRQ_EXTI2          (8)
#define NVIC_IRQ_EXTI3          (9)
#define NVIC_IRQ_EXTI4          (10)
#define NVIC_IRQ_EXTI9_5        (23)
#define NVIC_IRQ_EXTI16         (1)
#define NVIC_IRQ_EXTI21         (2)
#define NVIC_IRQ_EXTI22         (3)
#define NVIC_IRQ_EXTI15_10      (40)
#define NVIC_IRQ_EXTI17         (41)
#define NVIC_IRQ_EXTI18         (42)

void SYSCFG_bus_clock_enable(void);

#endif
