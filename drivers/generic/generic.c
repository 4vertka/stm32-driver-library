#include <generic.h>
#include <rcc.h>

void SYSCFG_bus_clock_enable(void) {
    RCC->APB2ENR |= (1U << 14);
}
