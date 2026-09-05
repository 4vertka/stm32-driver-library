#include <gpio.h>
#include <rcc.h>

GPIO_reg_t* const GPIOA_dbg = GPIOA;
GPIO_reg_t* const GPIOB_dbg = GPIOB;
GPIO_reg_t* const GPIOC_dbg = GPIOC;
GPIO_reg_t* const GPIOD_dbg = GPIOD;
GPIO_reg_t* const GPIOE_dbg = GPIOE;
GPIO_reg_t* const GPIOH_dbg = GPIOH;

void GPIO_init(GPIO_handle_t* GPIO_handle) {
    //mode setup (moder)
    GPIO_handle->GPIO_reg->MODER &= ~(3U << GPIO_handle->GPIO_config.pin);
    GPIO_handle->GPIO_reg->MODER |= (GPIO_handle->GPIO_config.mode << (2 * GPIO_handle->GPIO_config.pin));
    
    //output type (otyper)
    GPIO_handle->GPIO_reg->OTYPER &= ~(1U << GPIO_handle->GPIO_config.pin);
    GPIO_handle->GPIO_reg->OTYPER |= (GPIO_handle->GPIO_config.otyper << GPIO_handle->GPIO_config.pin);

    //speed (ospeedr)
    GPIO_handle->GPIO_reg->OSPEEDR &= ~(3U << GPIO_handle->GPIO_config.pin);
    GPIO_handle->GPIO_reg->OSPEEDR |= (GPIO_handle->GPIO_config.speed << (2 * GPIO_handle->GPIO_config.pin));

    //pull-up/pull-down
    GPIO_handle->GPIO_reg->PUPDR &= ~(3U << GPIO_handle->GPIO_config.pin);
    GPIO_handle->GPIO_reg->PUPDR |= (GPIO_handle->GPIO_config.pupdr << (2 * GPIO_handle->GPIO_config.pin));
}


void GPIO_deinit(GPIO_reg_t* GPIO_reg) {
    if (GPIO_reg == GPIOA) {}
    else if (GPIO_reg == GPIOB) {}
    else if (GPIO_reg == GPIOC) {}
    else if (GPIO_reg == GPIOD) {}
    else if (GPIO_reg == GPIOE) {}
    else if (GPIO_reg == GPIOH) {}
} 

void GPIO_clock_enable(GPIO_reg_t* GPIO_reg) {
    if (GPIO_reg == GPIOA) 
        GPIOA_bus_clock_enable();
    else if (GPIO_reg == GPIOB)
        GPIOB_bus_clock_enable();
    else if (GPIO_reg == GPIOC) 
        GPIOC_bus_clock_enable();
    else if (GPIO_reg == GPIOD) 
        GPIOD_bus_clock_enable();
    else if (GPIO_reg == GPIOE)
        GPIOE_bus_clock_enable();
    else if (GPIO_reg == GPIOH)
        GPIOH_bus_clock_enable();
}

void GPIOA_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 0);
}
void GPIOB_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 1);
}
void GPIOC_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 2);
}
void GPIOD_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 3);
}
void GPIOE_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 4);
}
void GPIOH_bus_clock_enable(void) {
    RCC->AHB1ENR |= (1U << 7);
}
