#include <generic.h>
#include <gpio.h>
#include <systick.h>

int main() {

    GPIO_clock(GPIOA, ENABLE);

    GPIO_handle_t led;
    led.GPIO_reg = GPIOA;
    led.GPIO_config.pin = 5;
    led.GPIO_config.mode = GPIO_MODE_OUTPUT;
    led.GPIO_config.otyper = GPIO_PUSH_PULL;
    led.GPIO_config.pupdr = GPIO_NO_PULLUP_NO_PULLDOWN;
    led.GPIO_config.speed = GPIO_SPEED_LOW;

    GPIO_init(&led);

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);

    while (1) {
        GPIO_toggle_ODR_pin(led.GPIO_reg, led.GPIO_config.pin);
        SYSTICK_delay(1000);
    }
}
