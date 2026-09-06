#include "rcc.h"
#include <stdint.h>
#include <gpio.h>
#include <generic.h>


// button pc 13

int main(void) {
    /*
    GPIO_handle_t GPIO_handle;
    GPIO_handle.GPIO_reg = GPIOA;
    GPIO_handle.GPIO_config.pin = 5;
    GPIO_handle.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_handle.GPIO_config.otyper = GPIO_PUSH_PULL;
    GPIO_handle.GPIO_config.speed = GPIO_SPEED_LOW;
    GPIO_handle.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_handle.GPIO_config.af = GPIO_AF5;

    //GPIOA_bus_clock_enable();
    GPIO_clock(GPIO_handle.GPIO_reg, ENABLE);
    GPIO_init(&GPIO_handle);

    GPIO_handle_t GPIO_button;
    GPIO_button.GPIO_reg = GPIOC;
    GPIO_button.GPIO_config.pin = 13;
    GPIO_button.GPIO_config.mode = GPIO_MODE_INPUT;
    GPIO_button.GPIO_config.speed = GPIO_SPEED_LOW;
    GPIO_button.GPIO_config.pupdr = GPIO_PULLUP;

    GPIO_clock(GPIO_button.GPIO_reg, ENABLE);
    GPIO_init(&GPIO_button);

    SYSCFG_bus_clock_enable();

    //settings exti line for pin
    //SYSCFG->EXTICR[GPIO_button.GPIO_config.pin/4] &= ~(15U << ((GPIO_button.GPIO_config.pin % 4) * 4));
    //SYSCFG->EXTICR[GPIO_button.GPIO_config.pin/4] |= (2U << ((GPIO_button.GPIO_config.pin % 4) * 4));
   
    //type of input falling edge
   // EXTI->IMR |= (1U << GPIO_button.GPIO_config.pin);
    //EXTI->RTSR &= ~(1U << GPIO_button.GPIO_config.pin);
    //EXTI->FTSR |= (1U << GPIO_button.GPIO_config.pin);
    GPIO_irq_exti_setup(GPIO_button.GPIO_config.pin, GPIO_EXTI_FALLING_EDGE);
    GPIO_irq_set_priority(NVIC_IRQ_EXTI15_10, NVIC_IRQ_PRIORITY_15);
    GPIO_irq_enable(NVIC_IRQ_EXTI15_10);
    */
    
    /*
    GPIO_handle_t GPIO_mco;
    GPIO_mco.GPIO_reg = GPIOA;
    GPIO_mco.GPIO_config.pin = 8;
    GPIO_mco.GPIO_config.mode = GPIO_MODE_AF;
    GPIO_mco.GPIO_config.speed = GPIO_SPEED_LOW;
    GPIO_mco.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    GPIO_mco.GPIO_config.af = GPIO_AF0;

    //activating hse 
    RCC->CR |= (1U << 16);
    while (!(RCC->CR & (1 << 17))) {}

    //pll config
    RCC->CR |= (1U << 24);
    while (!(RCC->CR & (1 << 25))) {}

    // reading external clock MCO1
    RCC->CFGR &= ~(3U << 21);
    RCC->CFGR |= (MCO1_HSE_CLOCK << 21);
   
    // reading pll clock MCO2
    RCC->CFGR &= ~(3U << 30);
    RCC->CFGR |= (MCO2_PLCC_CLOCK << 30);
    
    RCC->CFGR &= ~(7U << 27);
    RCC->CFGR |= (4U << 27)
    */

    RCC_HSE_enable();
    RCC_PLL_enable();
    RCC_MCO1(RCC_MCO1_HSE_CLOCK, RCC_MCO1PRE_DIV2);
    RCC_MCO2(RCC_MCO2_PLL_CLOCK, RCC_MCO2PRE_DIV2);
    
    while (1) {
        //if ((GPIO_button.GPIO_reg->IDR & (1 << GPIO_button.GPIO_config.pin)) != 0) {
        //    GPIO_write_ODR_pin(GPIO_handle.GPIO_reg, GPIO_handle.GPIO_config.pin, ENABLE);
        //}else {
        //    GPIO_write_ODR_pin(GPIO_handle.GPIO_reg, GPIO_handle.GPIO_config.pin, DISABLE);
        //}
        //GPIO_toggle_ODR_pin(GPIO_handle.GPIO_reg, GPIO_handle.GPIO_config.pin);
        //GPIO_write_ODR_pin(GPIO_handle.GPIO_reg, GPIO_handle.GPIO_config.pin, ENABLE);
        //for (int i = 0; i < 1000000; i++) {}
        //GPIO_write_ODR_pin(GPIO_handle.GPIO_reg, GPIO_handle.GPIO_config.pin, DISABLE);
        //for (int i = 0; i < 1000000; i++) {}
    }
    
}

extern void _estack(void);

void Reset_Handler(void) {
    extern uint32_t _sbss, _ebss, _sdata, _edata, _sidata;

    uint32_t *dst = &_sbss;

    while (dst < &_ebss) {
        *dst = 0;
        dst++;
    }

    uint32_t* src = &_sidata;
    dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }

    main();

    while (1) {}
}


void NMI_Handler(void) {}

void HardFault_Handler(void) {}

void MemManage_Handler(void) {}

void BusFault_Handler(void) {}

void UsageFault_Handler(void) {}

void SVCall_Handler(void) {}

void Debug_Monitor_Handler(void) {}

void PendSV_Handler(void) {}

void Systick_Handler(void) {}

void WWDG_IRQ_Handler(void) {}

void EXTI16xPVD_IRQ_Handler(void) {}

void EXTI21xTAMP_STAMP_IRQ_Handler(void) {}

void EXTI22xRTC_WKUP_IRQ_Handler(void) {}

void FLASH_IRQ_Handler(void) {}

void RCC_IRQ_Handler(void) {}

void EXTI0_IRQ_Handler(void) {
}

void EXTI1_IRQ_Handler(void) {}

void EXTI2_IRQ_Handler(void) {}

void EXTI3_IRQ_Handler(void) {}

void EXTI4_IRQ_Handler(void) {}

void DMA1_Stream0_IRQ_Handler(void) {}

void DMA1_Stream1_IRQ_Handler(void) {}

void DMA1_Stream2_IRQ_Handler(void) {}

void DMA1_Stream3_IRQ_Handler(void) {}

void DMA1_Stream4_IRQ_Handler(void) {}

void DMA1_Stream5_IRQ_Handler(void) {}

void DMA1_Stream6_IRQ_Handler(void) {}

void ADC_IRQ_Handler(void) {}

void EXTI9_5_IRQ_Handler(void) {}

void TIM1_BRK_TIM9_IRQ_Handler(void) {}

void TIM1_UP_TIM10_IRQ_Handler(void) {}

void TIM1_TRG_COM_TIM11_IRQ_Handler(void) {}

void TIM1_CC_IRQ_Handler(void) {}

void TIM2_IRQ_Handler(void) {}

void TIM3_IRQ_Handler(void) {}

void TIM4_IRQ_Handler(void) {}

void I2C1_EV_IRQ_Handler(void) {}

void I2C1_ER_IRQ_Handler(void) {}

void I2C2_EV_IRQ_Handler(void) {}

void I2C2_ER_IRQ_Handler(void) {}

void SPI1_IRQ_Handler(void) {}

void SPI2_IRQ_Handler(void) {}

void USART1_IRQ_Handler(void) {}

void USART2_IRQ_Handler(void) {}

void EXTI15_10_IRQ_Handler() {
    if (EXTI->PR & (1 << GPIO_PIN_13)) {
        EXTI->PR |= (1 << GPIO_PIN_13);

        GPIO_toggle_ODR_pin(GPIOA, GPIO_PIN_5);
    }
}

void EXTI17xRTC_Alarm_IRQ_Handler(void) {}

void EXTI18xOTG_FS_WKUP_IRQ_Handler(void) {}

void DMA1_Stream7_IRQ_Handler(void) {}

void SDIO_IRQ_Handler(void) {}

void TIM5_IRQ_Handler(void) {}

void SPI3_IRQ_Handler(void) {} 

void DMA2_Stream0_IRQ_Handler(void) {}
void DMA2_Stream1_IRQ_Handler(void) {}
void DMA2_Stream2_IRQ_Handler(void) {}
void DMA2_Stream3_IRQ_Handler(void) {}
void DMA2_Stream4_IRQ_Handler(void) {}

void OTG_FS_IRQ_Handler(void) {}

void DMA2_Stream5_IRQ_Handler(void) {}
void DMA2_Stream6_IRQ_Handler(void) {}
void DMA2_Stream7_IRQ_Handler(void) {}

void USART6_IRQ_Handler(void) {}

void I2C3_EV_IRQ_Handler(void) {}
void I2C3_ER_IRQ_Handler(void) {}

void FPU_IRQ_Handler(void) {}

void SPI4_IRQ_Handler(void) {}

__attribute__((section(".vector_table")))
void (*const vector_table[16+85])(void) = {
//------------------------------internal interrupts-----------------------------------------
    _estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVCall_Handler,
    Debug_Monitor_Handler,
    0,
    PendSV_Handler,
    Systick_Handler,
    //------------------------------external interrupts-----------------------------------------
    WWDG_IRQ_Handler,
    EXTI16xPVD_IRQ_Handler,
    EXTI21xTAMP_STAMP_IRQ_Handler,
    EXTI22xRTC_WKUP_IRQ_Handler,
    FLASH_IRQ_Handler,
    RCC_IRQ_Handler,
    EXTI0_IRQ_Handler,
    EXTI1_IRQ_Handler,
    EXTI2_IRQ_Handler,
    EXTI3_IRQ_Handler,
    EXTI4_IRQ_Handler,
    DMA1_Stream0_IRQ_Handler,
    DMA1_Stream1_IRQ_Handler,
    DMA1_Stream2_IRQ_Handler,
    DMA1_Stream3_IRQ_Handler,
    DMA1_Stream4_IRQ_Handler,
    DMA1_Stream5_IRQ_Handler,
    DMA1_Stream6_IRQ_Handler,
    ADC_IRQ_Handler,
    0,
    0,
    0,
    0,
    EXTI9_5_IRQ_Handler,
    TIM1_BRK_TIM9_IRQ_Handler,
    TIM1_UP_TIM10_IRQ_Handler,
    TIM1_TRG_COM_TIM11_IRQ_Handler,
    TIM1_CC_IRQ_Handler,
    TIM2_IRQ_Handler,
    TIM3_IRQ_Handler,
    TIM4_IRQ_Handler,
    I2C1_EV_IRQ_Handler,
    I2C1_ER_IRQ_Handler,
    I2C2_EV_IRQ_Handler,
    I2C2_ER_IRQ_Handler,
    SPI1_IRQ_Handler,
    SPI2_IRQ_Handler,
    USART1_IRQ_Handler,
    USART2_IRQ_Handler,
    0,
    EXTI15_10_IRQ_Handler,
    EXTI17xRTC_Alarm_IRQ_Handler,
    EXTI18xOTG_FS_WKUP_IRQ_Handler,
    0,
    0,
    0,
    0,
    DMA1_Stream7_IRQ_Handler,
    0,
    SDIO_IRQ_Handler,
    TIM5_IRQ_Handler,
    SPI3_IRQ_Handler,
    0,
    0,
    0,
    0,
    DMA2_Stream0_IRQ_Handler,
    DMA2_Stream1_IRQ_Handler,
    DMA2_Stream2_IRQ_Handler,
    DMA2_Stream3_IRQ_Handler,
    DMA2_Stream4_IRQ_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    OTG_FS_IRQ_Handler,
    DMA2_Stream5_IRQ_Handler,
    DMA2_Stream6_IRQ_Handler,
    DMA2_Stream7_IRQ_Handler,
    USART6_IRQ_Handler,
    I2C3_EV_IRQ_Handler,
    I2C3_ER_IRQ_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    FPU_IRQ_Handler,
    0,
    0,
    SPI4_IRQ_Handler
};
