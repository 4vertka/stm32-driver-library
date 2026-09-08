#ifndef SYSTICK_H
#define SYSTICK_H 

#include <stdint.h>

extern volatile uint32_t SYST_ticks;

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t RVR;
    volatile uint32_t CVR;
    volatile uint32_t CALIB;
} SYSTICK_reg_t;

#define SYSTICK_ADDR            (0xE000E010U)
#define SYSTICK                 ((SYSTICK_reg_t*) SYSTICK_ADDR)

#define SYST_CLKSRC_EXTERNAL    (0)
#define SYST_CLKSRC_INTERNAL    (1)

#define SYST_TICKINT_NOEXT      (0)
#define SYST_TICKINT_EXT        (1)

#define SYST_COUNTER_DISABLE    (0)
#define SYST_COUNTER_ENABLE     (1)

void SYSTICK_init(uint32_t ticks, uint8_t clk_src, uint8_t ext, uint8_t enable_clock);
void SYSTICK_delay(uint32_t tick);
#endif
