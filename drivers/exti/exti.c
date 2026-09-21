#include <generic.h>
#include <exti.h>
#include <gpio.h>

void irq_set_priority(uint8_t irq_number, uint8_t priority) {
    uint8_t pr_reg = irq_number/4;
    uint8_t pr_irq_num = irq_number%4;

    uint8_t shift = (8 * pr_irq_num) + (8 - 4);

    *(NVIC_IPR_ADDR + pr_reg) |= (priority << shift);
}

void irq_enable(uint8_t irq_num) {
    if (irq_num <= 31)
        *NVIC_ISER0 |= (1U << irq_num);
    else if (irq_num > 31 && irq_num < 64)
        *NVIC_ISER1 |= (1U << (irq_num % 32));
    else if (irq_num >= 64 && irq_num < 96) {
        *NVIC_ISER2 |= (1U << (irq_num % 32));
    }
}

void irq_disable(uint8_t irq_num) {
    if (irq_num <= 31)
        *NVIC_ICER0 = (1U << irq_num);
    else if (irq_num > 31 && irq_num < 64)
        *NVIC_ICER1 |= (1U << (irq_num % 32));
    else if (irq_num >= 64 && irq_num < 96)
        *NVIC_ICER2 |= (1U << (irq_num % 32));
}

void EXTI_clear_pending(uint8_t pin) {
    EXTI->PR |= (1U << pin);
}
