#include <generic.h>
#include <systick.h>

volatile uint32_t SYST_ticks = 0;

void SYSTICK_init(uint32_t ticks, uint8_t clk_src, uint8_t ext, uint8_t enable_clock) {
    SYSTICK->RVR = (ticks / 1000) - 1;               //reload register
    SYSTICK->CVR = 0;                       //clear current val reg

    SYSTICK->CSR |= (enable_clock << 0);    //enable/disable systick 
    SYSTICK->CSR |= (ext << 1);             //assert/dont assert interrupt
    SYSTICK->CSR |= (clk_src << 2);         //choose clock source (HSI, HSE)
}

void SYSTICK_delay(uint32_t delay) {
    uint32_t start = SYST_ticks;
    while ((SYST_ticks - start) < delay) {}
}
