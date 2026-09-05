#include <stdint.h>
#include <gpio.h>

int main(void) {
    GPIO_handle_t GPIO_handle;
    GPIO_handle.GPIO_reg = GPIOA;
    GPIO_handle.GPIO_config.pin = 5;
    GPIO_handle.GPIO_config.mode = GPIO_MODE_OUTPUT;
    GPIO_handle.GPIO_config.otyper = GPIO_PUSH_PULL;
    GPIO_handle.GPIO_config.speed = GPIO_SPEED_LOW;
    GPIO_handle.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;

    GPIO_clock_enable(GPIO_handle.GPIO_reg);
    GPIO_init(&GPIO_handle);


    while (1) {
        GPIO_handle.GPIO_reg->ODR ^= (1U << GPIO_handle.GPIO_config.pin);
        for (int i = 0; i < 1000000; i++) {}
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
    Systick_Handler
};
