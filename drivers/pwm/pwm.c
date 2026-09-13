#include <pwm.h>
#include <rcc.h>

void TIM2_TIM5_init(TIM2_TIM5_handle_t* tim) {
    //enable the bus clock for tim
    if (tim->TIM2_TIM5_reg == TIM2) 
        RCC_TIM2_bus_clock_enable();

    //formula for prescaler Required freq = CLK / (PSC + 1)
    uint16_t clock_freq = RCC_get_APB1_clock_hz() / 1000000;
    uint16_t prescaler_val = clock_freq - 1;
    tim->TIM2_TIM5_reg->PSC = prescaler_val;

    //set reload value
    tim->TIM2_TIM5_reg->ARR = tim->TIM2_TIM5_conf.reload;

    //enable tim 
    tim->TIM2_TIM5_reg->CR1 |= (1U << 0);

    //wait until uif bit is set than reset uif bit
    while(!(tim->TIM2_TIM5_reg->SR & (1U << 0))) {}
    tim->TIM2_TIM5_reg->SR &= ~(1U << 0);
}

void TIM_delay(TIM2_TIM5_reg_t* tim, uint32_t ms) {
    for (uint32_t i = 0; i <= ms; i++) {
        tim->CNT = 0;
        while (!(tim->SR & (1U << 0))) {}
        tim->SR &= ~ (1U << 0);
    }
}
