#include <gpio.h>
#include <rcc.h>
#include <generic.h>

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

    //alternate function 
    if (GPIO_handle->GPIO_config.mode == GPIO_MODE_AF) {
        if (GPIO_handle->GPIO_config.pin <= GPIO_PIN_7) {
            GPIO_handle->GPIO_reg->AFR[0] &= ~(15U << (GPIO_handle->GPIO_config.pin * 4));
            GPIO_handle->GPIO_reg->AFR[0] |= (GPIO_handle->GPIO_config.af << (GPIO_handle->GPIO_config.pin * 4));
        }
        if (GPIO_handle->GPIO_config.pin > 7 && GPIO_handle->GPIO_config.pin <= 15) {
            GPIO_handle->GPIO_reg->AFR[1] &= ~(15U << ((GPIO_handle->GPIO_config.pin - 8) * 4));
            GPIO_handle->GPIO_reg->AFR[1] |= (GPIO_handle->GPIO_config.af << ((GPIO_handle->GPIO_config.pin - 8) * 4));
        }
    }

}

void GPIO_deinit(GPIO_reg_t* GPIO_reg) {
    if (GPIO_reg == GPIOA)
        GPIOA_reg_reset();
    else if (GPIO_reg == GPIOB) 
        GPIOB_reg_reset();
    else if (GPIO_reg == GPIOC) 
        GPIOC_reg_reset();
    else if (GPIO_reg == GPIOD) 
        GPIOD_reg_reset();
    else if (GPIO_reg == GPIOE)
        GPIOE_reg_reset();
    else if (GPIO_reg == GPIOH)
        GPIOH_reg_reset();
}

void GPIO_clock(GPIO_reg_t* GPIO_reg, uint8_t mode) {
    switch (mode) {
    case ENABLE: {
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
        break;
    }
    case DISABLE: {
        if (GPIO_reg == GPIOA) 
            GPIOA_bus_clock_disable();
        else if (GPIO_reg == GPIOB)
            GPIOB_bus_clock_disable();
        else if (GPIO_reg == GPIOC) 
            GPIOC_bus_clock_disable();
        else if (GPIO_reg == GPIOD) 
            GPIOD_bus_clock_disable();
        else if (GPIO_reg == GPIOE)
            GPIOE_bus_clock_disable();
        else if (GPIO_reg == GPIOH)
            GPIOH_bus_clock_disable();
        break;
    }
    default: {}
    }
}

uint8_t GPIO_read_IDR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin) {
    return (uint8_t)((GPIO_reg->IDR >> pin) & 1U);
}

uint16_t GPIO_read_IDR_port(GPIO_reg_t* GPIO_reg) {
    return (uint16_t)GPIO_reg->IDR;
}

void GPIO_write_ODR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin, uint8_t mode) {
    if (mode == SET) {
        GPIO_reg->ODR |= (1U << pin);    
    }else {
        GPIO_reg->ODR &= ~(1U << pin);
    }
}

void GPIO_write_ODR_port(GPIO_reg_t* GPIO_reg, uint16_t value) {
    GPIO_reg->ODR = value;
}

void GPIO_toggle_ODR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin) {
    GPIO_reg->ODR ^= (1U << pin);
}

void GPIO_irq_exti_setup(uint8_t pin, uint8_t mode) {
    //setting exti line for a pin
    SYSCFG->EXTICR[pin/4] &= ~(15U << ((pin % 4) * 4));
    SYSCFG->EXTICR[pin/4] |= (2U << ((pin % 4) * 4));


    EXTI->IMR |= (1U << pin);

    //falling/rising edge
    if (mode == GPIO_EXTI_FALLING_EDGE) {
        EXTI->RTSR &= ~(1U << pin);
        EXTI->FTSR |= (1U << pin);
    }else if (mode == GPIO_EXTI_RISING_EDGE) {
        EXTI->RTSR |= (1U << pin);
        EXTI->FTSR &= ~(1U << pin);
    }
}

void GPIO_irq_set_priority(uint8_t irq_number, uint8_t priority) {
    uint8_t pr_reg = irq_number/4;
    uint8_t pr_irq_num = irq_number%4;
    
    uint8_t shift = (8 * pr_irq_num) + (8 - 4);

    *(NVIC_IPR_ADDR + pr_reg) |= (priority << shift);
}

void GPIO_irq_enable(uint8_t irq_num) {
    if (irq_num <= 31) 
        *NVIC_ISER0 |= (1U << irq_num);
    else if (irq_num > 31 && irq_num < 64) 
        *NVIC_ISER1 |= (1U << (irq_num % 32));
    else if (irq_num >= 64 && irq_num < 96) {
        *NVIC_ISER2 |= (1U << (irq_num % 32));
    }
}

void GPIO_irq_disable(uint8_t irq_num) {
    if (irq_num <= 31) 
        *NVIC_ICER0 |= (1U << irq_num);
    else if (irq_num > 31 && irq_num < 64)
        *NVIC_ICER1 |= (1U << (irq_num % 32));
    else if (irq_num >= 64 && irq_num < 96)
        *NVIC_ICER2 |= (1U << (irq_num % 32));
}

void GPIO_USART2_TXRX_pins_enable(void) {

    GPIO_clock(GPIOA, ENABLE);

    GPIO_handle_t GPIO_tx;
    GPIO_tx.GPIO_reg = GPIOA;
    GPIO_tx.GPIO_config.pin = 2;
    GPIO_tx.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_tx.GPIO_config.otyper = GPIO_PUSH_PULL;
    GPIO_tx.GPIO_config.speed = GPIO_SPEED_HIGH;
    GPIO_tx.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_tx.GPIO_config.af = GPIO_AF7;
    
    GPIO_init(&GPIO_tx);

    GPIO_handle_t GPIO_rx;
    GPIO_rx.GPIO_reg = GPIOA;
    GPIO_rx.GPIO_config.pin = 3;
    GPIO_rx.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_rx.GPIO_config.otyper = GPIO_PUSH_PULL;
    GPIO_rx.GPIO_config.speed = GPIO_SPEED_HIGH;
    GPIO_rx.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_rx.GPIO_config.af = GPIO_AF7;
    
    GPIO_init(&GPIO_rx);
}

void GPIO_SPI_pins_enable(void) {
    GPIO_clock(GPIOA, ENABLE);

    GPIO_handle_t miso;                      //miso pin
    miso.GPIO_reg = GPIOA;
    miso.GPIO_config.pin = 6;
    miso.GPIO_config.mode = GPIO_MODE_AF;
    miso.GPIO_config.af = GPIO_AF5;
    
    GPIO_handle_t mosi;                      //mosi pin
    mosi.GPIO_reg = GPIOA;
    mosi.GPIO_config.pin = 7;
    mosi.GPIO_config.mode = GPIO_MODE_AF;
    mosi.GPIO_config.af = GPIO_AF5;
    
    GPIO_init(&miso);
    GPIO_init(&mosi);

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

void GPIOA_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 0);
}
void GPIOB_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 1);
}
void GPIOC_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 2);
}
void GPIOD_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 3);
}
void GPIOE_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 4);
}
void GPIOH_bus_clock_disable(void) {
    RCC->AHB1ENR &= ~(1U << 7);
}

void GPIOA_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 0);
    RCC->AHB1RSTR &= ~(1U << 0);
}
void GPIOB_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 1);
    RCC->AHB1RSTR &= ~(1U << 1);
}
void GPIOC_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 2);
    RCC->AHB1RSTR &= ~(1U << 2);
}
void GPIOD_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 3);
    RCC->AHB1RSTR &= ~(1U << 3);
}
void GPIOE_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 4);
    RCC->AHB1RSTR &= ~(1U << 4);
}
void GPIOH_reg_reset(void) {
    RCC->AHB1RSTR |= (1U << 7);
    RCC->AHB1RSTR &= ~(1U << 7);
}
