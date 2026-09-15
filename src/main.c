#include "pwm/pwm.h"
#include "rcc.h"
#include "spi/spi.h"
#include "systick/systick.h"
#include "uart.h"
#include <stdint.h>
#include <gpio.h>
#include <generic.h>
#include <ringbuffer.h>
#include <pwm.h>
#include <exti.h>

// button pc 13

int main(void) {

    RCC_SysClock_Init();

    TIM2_TIM5_handle_t tim;
    tim.TIM2_TIM5_reg = TIM2;
    tim.TIM2_TIM5_conf.reload = 16000;
    tim.TIM2_TIM5_conf.interrupt = ENABLE;

    TIM2_TIM5_init(&tim);

    GPIO_clock(GPIOA, ENABLE);
    GPIO_handle_t led;
    led.GPIO_reg = GPIOA;
    led.GPIO_config.pin = 5;
    led.GPIO_config.mode = GPIO_MODE_OUTPUT;
    led.GPIO_config.otyper = GPIO_PUSH_PULL;
    led.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    led.GPIO_config.speed = GPIO_SPEED_LOW;

    GPIO_init(&led);

    irq_enable(NVIC_IRQ_TIM2);
        
    while (1) {
        //GPIO_toggle_ODR_pin(led.GPIO_reg, led.GPIO_config.pin);
        //TIM_delay(tim.TIM2_TIM5_reg, 1000);
    }
}
