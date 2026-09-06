#include <rcc.h>
#include <gpio.h>
#include <generic.h>

RCC_reg_t* const RCC_dbg = RCC;

void RCC_HSE_enable(void) {
    //activate hse in cr register
    RCC->CR |= (1U << RCC_HSE_ON);
    while (!(RCC->CR & (1U << RCC_HSE_RDY))) {}

    //RCC->PLLCFGR |= (1U << RCC_PLLSRC);

    //pll config
    //RCC->CR |= (1U << RCC_PLL_ON);
    //while (!(RCC->CR & (1 << RCC_PLL_RDY))) {}
}

void RCC_HSE_disable(void) {
    RCC->CR &= ~(1U << RCC_HSE_ON);
}

void RCC_HSI_enable(void) {
    RCC->CR |= (1U << RCC_HSI_ON);
    while (!(RCC->CR & (1U << RCC_HSI_RDY))) {}
}

void RCC_HSI_disable() {
    RCC->CR &= ~(1U << RCC_HSI_ON);
}

void RCC_PLL_enable(void) {
    RCC->PLLCFGR |= (1U << RCC_PLLSRC);

    RCC->CR |= (1U << RCC_PLL_ON);
    while (!(RCC->CR & (1 << RCC_PLL_RDY))) {}
}

void RCC_PLL_disable(void) {
    RCC->CR &= ~(1U << RCC_PLL_ON);
}

void RCC_MCO1(uint8_t clock, uint8_t div) {
    // MCO1 = PA8
    GPIO_handle_t GPIO_MCO1;
    GPIO_MCO1.GPIO_reg = GPIOA;
    GPIO_MCO1.GPIO_config.pin = 8;
    GPIO_MCO1.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_MCO1.GPIO_config.speed = GPIO_SPEED_HIGH;
    GPIO_MCO1.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_MCO1.GPIO_config.af = GPIO_AF0; // AF0 = MCO_1

    GPIO_clock(GPIO_MCO1.GPIO_reg, ENABLE);
    GPIO_init(&GPIO_MCO1);

    //writing to clock MCO1
    RCC->CFGR &= ~(3U << 21);
    RCC->CFGR |= ((clock & 3U) << 21);

    //writing a divisor for MCO1 
    RCC->CFGR &= ~(7U << 24);
    RCC->CFGR |= ((div & 7U) << 24);

}

void RCC_MCO2(uint8_t clock, uint8_t div) {
    // MCO2 = PC9
    GPIO_handle_t GPIO_MCO2;
    GPIO_MCO2.GPIO_reg = GPIOC;
    GPIO_MCO2.GPIO_config.pin = 9;
    GPIO_MCO2.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_MCO2.GPIO_config.speed = GPIO_SPEED_HIGH;
    GPIO_MCO2.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_MCO2.GPIO_config.af = GPIO_AF0; // AF0 = MCO_2

    GPIO_clock(GPIO_MCO2.GPIO_reg, ENABLE);
    GPIO_init(&GPIO_MCO2);

    //writing to clock MCO2
    RCC->CFGR &= ~(3U << 30);
    RCC->CFGR |= ((clock & 3U) << 30);

    //writing a divisor for MCO2; 
    RCC->CFGR &= ~(7U << 27);
    RCC->CFGR |= ((div & 7U) << 27);

}
