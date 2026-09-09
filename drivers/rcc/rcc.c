#include <rcc.h>
#include <gpio.h>
#include <generic.h>

/*
 * 1. Enable HSE 
 * 2. Enable power (PW) and voltage regulator
 * 3. Set FLASH prefatch and latency 
 * 4. Set prescaler 
 * 5. Enable PLL clock 
 * 6. Set the clock source
*/

RCC_reg_t* const RCC_dbg = RCC;

void RCC_HSE_enable(void) {
    //activate hse in cr register
    RCC->CR |= (1U << RCC_HSE_ON);
    while (!(RCC->CR & (1U << RCC_HSE_RDY))) {}
}

void RCC_HSE_disable(void) {
    RCC->CR &= ~(1U << RCC_HSE_ON);
}

void RCC_HSI_enable(void) {
    RCC->CR |= (1U << RCC_HSI_ON);
    while (!(RCC->CR & (1U << RCC_HSI_RDY))) {}
}

void RCC_HSI_disable(void) {
    RCC->CR &= ~(1U << RCC_HSI_ON);
}

void RCC_PLL_config(uint8_t m, uint16_t n, uint8_t p, uint8_t q) {
    RCC_PLL_disable();
    while (RCC->CR & (1U << RCC_PLL_RDY)) {} 

    RCC->PLLCFGR &= ~(0x3FU << 0);
    RCC->PLLCFGR |= ((m & 0x3FU) << 0);
    RCC->PLLCFGR &= ~(0x1FFU << 6);
    RCC->PLLCFGR |= ((n & 0x1FFU) << 6);
    RCC->PLLCFGR &= ~(0x3U << 16);
    RCC->PLLCFGR |= ((p & 0x3U) << 16);
    RCC->PLLCFGR &= ~(0xFU << 24);
    RCC->PLLCFGR |= ((q & 0xFU) << 24);
    RCC->PLLCFGR |= (1U << RCC_PLLSRC);
}

void RCC_PLL_enable(void) {
    RCC->CR |= (1U << RCC_PLL_ON);
    while (!(RCC->CR & (1 << RCC_PLL_RDY))) {}
}

void RCC_PLL_disable(void) {
    RCC->CR &= ~(1U << RCC_PLL_ON);
}

void RCC_PWR_config(void) {
    //power interface clock enable
    RCC->APB1ENR |= (1U << 28);
    //voltage regulator
    PWR->CR |= (3U << 14);
}

void RCC_FLASH_config(uint8_t latency) {
    FLASH_REG->ACR |= (latency << 0); 
    FLASH_REG->ACR |= (1U << 9); 
    FLASH_REG->ACR |= (1U << 10);
    FLASH_REG->ACR |= (1U << 8); 
}

void RCC_bus_prescaler_config(uint8_t ahb, uint8_t apb1, uint8_t apb2) {
    // AHB1 prescaler 
    RCC->CFGR &= ~(15U << 4);
    RCC->CFGR |= (ahb << 4);
    
    // APB1 prescaler
    RCC->CFGR &= ~(7U << 10);
    RCC->CFGR |= (apb1 << 10);
    
    // APB2 prescaler 
    RCC->CFGR &= ~(7U << 13);
    RCC->CFGR |= (apb2 << 13);
}

void RCC_set_sysclock(uint8_t src) {
    RCC->CFGR &= ~(3U << 0);
    RCC->CFGR |= (src << 0);
    while (((RCC->CFGR >> 2) & 3U) != src) {}
}

void RCC_SysClock_Init(void) {
    RCC_HSE_enable();
    RCC_PWR_config();
    RCC_FLASH_config(5);
    RCC_bus_prescaler_config(RCC_AHB_DIV1, RCC_APB_DIV4, RCC_APB_DIV2);
    RCC_PLL_config(RCC_DEFAULT_PLLM_VAL, RCC_DEFAULT_PLLN_VAL, RCC_DEFAULT_PLLP_VAL, 7);
    RCC_PLL_enable();
    RCC_set_sysclock(RCC_PLL_SYSCLOCK);
}

uint32_t RCC_get_AHB_clock_hz(void) {
    uint8_t bits = (RCC->CFGR >> 4) & 0x0F;
    uint32_t hz = RCC_Get_PLL_frequ() * 1000000;
    switch (bits) {
    case RCC_AHB_DIV2: {
        hz /= 2;
        break;
    }
    case RCC_AHB_DIV4: {
        hz /= 4;
        break;
    }
    case RCC_AHB_DIV8: {
        hz /= 8;
        break;
    }
    case RCC_AHB_DIV16: {
        hz /= 16;
        break;
    } 
    case RCC_AHB_DIV64: {
        hz /=  64;
        break;
    }
    case RCC_AHB_DIV128: {
        hz /= 128;
        break;
    }
    case RCC_AHB_DIV256: {
        hz /= 256;
        break;
    }
    case RCC_AHB_DIV512: {
        hz /= 512;
        break;
    }
    default: {break;}
    }

    return hz;
}

uint32_t RCC_get_APB1_clock_hz(void) {
    uint8_t bits = (RCC->CFGR >> 10) & 0x07;
    uint32_t hz = RCC_get_AHB_clock_hz();
    switch (bits) {
    case RCC_APB_DIV2: {
        hz /= 2;
        break;
    }
    case RCC_APB_DIV4: {
        hz /= 4;
        break;
    }
    case RCC_APB_DIV8: {
        hz /= 8;
        break;
    }
    case RCC_APB_DIV16: {
        hz /= 16;
        break;
    }

    default: {break;}
    }

    return hz;
}

uint32_t RCC_get_APB2_clock_hz(void) {
    uint8_t bits = (RCC->CFGR >> 13) & 0x07;
    
    uint32_t hz = RCC_get_AHB_clock_hz();
    switch (bits) {
    case RCC_APB_DIV2: {
        hz /= 2;
        break;
    }
    case RCC_APB_DIV4: {
        hz /= 4;
        break;
    }
    case RCC_APB_DIV8: {
        hz /= 8;
        break;
    }
    case RCC_APB_DIV16: {
        hz /= 16;
        break;
    }
    default: {break;}
    }

    return hz;

}

uint32_t RCC_Get_PLL_frequ(void) {
    uint32_t PLL_clock_speed = 0;
    uint32_t PLL_src= 0;
    uint8_t m = 0;
    uint16_t n = 0;
    uint16_t n_mask = 0;
    uint8_t p = 0;
    
    if (RCC->PLLCFGR & (1 << 22)) {
        PLL_src = HSE_CLOCK_SPEED;
    } else {
        PLL_src = HSI_CLOCK_SPEED;
    }
  
    //get PLLM 
    m = RCC->PLLCFGR & 0x3FU;

    //get PLLP
    uint8_t p_code = (RCC->PLLCFGR >> 16) & 0x3U;
    p = (p_code + 1) * 2;

    //get PLLN
    for (int32_t i = 6; i <= 14; i++) {
        n_mask |= (1U << i);
    }    
    n = (RCC->PLLCFGR & n_mask) >> 6;

    PLL_clock_speed = (PLL_src * n) / (p * m);

    return PLL_clock_speed;

}

void RCC_USART2_bus_clock_enable(void) {
    RCC->APB1ENR |= (1U << 17);
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

