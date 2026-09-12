#include "rcc.h"
#include "spi/spi.h"
#include "systick/systick.h"
#include "uart.h"
#include <stdint.h>
#include <gpio.h>
#include <generic.h>
#include <ringbuffer.h>

// button pc 13

volatile uint8_t rx_char;

volatile char rb_buf[ RING_BUFFER_SIZE + 1 ];
ring_buffer_t rb = {
  len: RING_BUFFER_SIZE,
  buf: rb_buf,
  pos: 0,
  ext: 0
};
volatile int newline = 0;

int main(void) {

    /*RCC_SysClock_Init();

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);
    
    USART_handle_t usart;
    usart.USART_reg = USART2;
    usart.USART_config.mode = USART_MODE_TXRX;
    usart.USART_config.baud = USART_BAUD_RATE_9600;
    usart.USART_config.word_length = USART_8_DATA_BITS;
    usart.USART_config.parity_bits = USART_PARITY_NO;
    usart.USART_config.stop_bits = USART_STOP_BIT_1;
       
    USART2_config(&usart);
    
    USART2->CR1 |= (1U << 5);
    GPIO_irq_enable(NVIC_IRQ_USART2);

    */
        
    SPI_handle_t spi;
    spi.SPI_reg = SPI1;
    spi.SPI_config.mode = SPI_MODE_MASTER;
    spi.SPI_config.clock_speed = SPI_CLOCK_SPEED_DIV16;
    spi.SPI_config.bus_cfg =  SPI_BUS_FULL_DUPLEX;
    spi.SPI_config.cpol = SPI_CPOL_HIGH;
    spi.SPI_config.cpha = SPI_CPHA_HIGH;
    spi.SPI_config.ssm = SPI_SMM_ENABLE;
    spi.SPI_config.dff = SPI_DFF_BITS8;
    spi.SPI_config.dma = SPI_DMA_DISABLE;

    SPI_init(&spi);

    while (1) {
        

        /*while (rb.pos != rb.ext) {
            USART2_transmit_char(ringbuf_read(&rb));
        }
        if (newline == 1) {
            USART2_transmit_char('\r');
            USART2_transmit_char('\n');
            newline = 0;
        }*/
        //GPIO_toggle_ODR_pin(GPIOA, 5);
        //for (volatile int i = 0; i < 1000000; i++); 
        //USART2_transmit_string("hello uart2\n");
        //SYSTICK_delay(1000);
        
        //USART2_receive_char();
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

void Systick_Handler(void) {
    ++SYST_ticks;
    GPIO_toggle_ODR_pin(GPIOA, 5);
}

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

void USART2_IRQ_Handler(void) {
    //check if the interrupt source is RXNE
    /*if ((USART2->SR & (1U << 5))) {
        rx_char = USART2->DR;
        USART2_transmit_char(rx_char);
        USART2_transmit_char('\r');
        USART2_transmit_char('\n');
        USART2->SR &= ~(1U << 5);
    }*/ 

    if (USART2->SR & (1U << 5)) {
        uint8_t ch = USART2->DR;
        ringbuf_write(rb, ch);
        if (ch == '\r') newline = 1;
    }

}

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
