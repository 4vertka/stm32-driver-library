#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_reg_t;

typedef struct {
    uint8_t pin;
    uint8_t mode;
    uint8_t otyper;
    uint8_t speed;
    uint8_t pupdr;
} GPIO_config_t;

typedef struct {
   GPIO_reg_t* GPIO_reg;
   GPIO_config_t GPIO_config;
} GPIO_handle_t;

#define GPIOA_ADDR              (0x40020000U)
#define GPIOB_ADDR              (0x40020400U)
#define GPIOC_ADDR              (0x40020800U)
#define GPIOD_ADDR              (0x40020C00U)
#define GPIOE_ADDR              (0x40021000U)
#define GPIOH_ADDR              (0x40021C00U)

#define GPIOA                   ((GPIO_reg_t*) GPIOA_ADDR)
#define GPIOB                   ((GPIO_reg_t*) GPIOB_ADDR)
#define GPIOC                   ((GPIO_reg_t*) GPIOC_ADDR)
#define GPIOD                   ((GPIO_reg_t*) GPIOD_ADDR)
#define GPIOE                   ((GPIO_reg_t*) GPIOE_ADDR)
#define GPIOH                   ((GPIO_reg_t*) GPIOH_ADDR)

#define GPIO_MODE_INPUT         (0)
#define GPIO_MODE_OUTPUT        (1)
#define GPIO_MODE_AF            (2)
#define GPIO_MODE_ANALOG        (3)

#define GPIO_PUSH_PULL          (0)
#define GPIO_OPEN_DRAIN         (1)

#define GPIO_SPEED_LOW          (0)
#define GPIO_SPEED_MEDIUM       (1)
#define GPIO_SPEED_HIGH         (2)
#define GPIO_SPEED_VERYHIGH     (3)

#define GPIO_NO_PULLUP_NO_PULLDOWN  (0)
#define GPIO_PULLUP                 (1)
#define GPIO_PULLDOWN               (2)

#define GPIO_AF0                (0)
#define GPIO_AF1                (1)
#define GPIO_AF2                (2)
#define GPIO_AF3                (3)
#define GPIO_AF4                (4)
#define GPIO_AF5                (5)
#define GPIO_AF6                (6)
#define GPIO_AF7                (7)
#define GPIO_AF8                (8)
#define GPIO_AF9                (9)
#define GPIO_AF10               (10)
#define GPIO_AF11               (11)
#define GPIO_AF12               (12)
#define GPIO_AF13               (13)
#define GPIO_AF14               (14)
#define GPIO_AF15               (15)

//init/deinit
void GPIO_init(GPIO_handle_t* GPIO_handle);
void GPIO_deinit(GPIO_reg_t* GPIO_handle);


void GPIO_clock_enable(GPIO_reg_t* GPIO_reg);


void GPIOA_bus_clock_enable(void);
void GPIOB_bus_clock_enable(void);
void GPIOC_bus_clock_enable(void);
void GPIOD_bus_clock_enable(void);
void GPIOE_bus_clock_enable(void);
void GPIOH_bus_clock_enable(void);

#endif
