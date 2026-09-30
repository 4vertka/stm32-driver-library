# STM32 Bare-Metal Driver Library

> Bare-metal peripheral driver library for STM32F401RE
> Written in C without HAL, CubeMX, CMSIS dependencies

## Hardware
- Board: STM32F401RE NUCLEO
- MCU: ARM Cortex-M4

## Project Structure
```
drivers/
    rcc/
    gpio/
    uart/
    spi/
    i2c/
    pwm/
    exti/
    systick/
    generic/
src/
    main.c 
startup/ 
    startup.c 
Makefile
link.ld
```  

## Drivers implemented
- RCC     - HSI/HSE/PLL config, clock getter functions, MCO
- GPIO    - Input/Output/AF/Analog, EXTI setup
- UART    - TX/RX polling
- SPI     - Full/Half duplex, TX/RX polling
- I2C     - Master TX/RX, Standard mode
- TIM     - Basic timer, delay
- EXTI    - NVIC config, IRQ enable/disable 
- SYSTICK - milisecond delay, tick counter

## Prerequisites
To build this project you need to install the following packages
#### Ubuntu/Debian
```
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi stlink-tools openocd gdb-multiarch make
```
#### Arch linux
```
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils stlink openocd gdb make
```
#### MacOS
```
brew install arm-none-eabi-gcc stlink openocd make
```

## Build
#### Build elf/bin image
```
make all 
```
#### Flash firmware
```
make flash
```
#### Start debugging with OpenOCD and connect to debugger using GDB
```
make debug
make connect
```
#### Clean project 
```
make clean
```

## API reference

#### RCC -> drivers/rcc
```
// Init system clokc to external 84MHZ clock via PLL
void RCC_SysClock_Init(void);

// Get bus frequencies
uint32_t RCC_get_AHB_clock_hz(void);
uint32_t RCC_get_APB1_clock_hz(void);
uint32_t RCC_get_APB2_clock_hz(void);

// Get MCO1/2 pin frequencies 
void RCC_MCO1(uint8_t clock, uint8_t div);
void RCC_MCO2(uint8_t clock, uint8_t div);

// Enable clock for peripherals

//USART2
void RCC_USART2_bus_clock_enable(void);

// SPI
void RCC_SPI1_bus_clock_enable(void);
void RCC_SPI1_bus_clock_disable(void);

// I2C
void RCC_I2C1_bus_clock_enable(void);
void RCC_I2C1_bus_clock_disable(void);

// TIM
void RCC_TIM2_bus_clock_enable(void);
void RCC_TIM2_bus_clock_disable(void);
```

#### GPIO -> drivers/gpio 
```
// Init/deinit GPIO pin 
void GPIO_init(GPIO_handle_t* handle);
void GPIO_deinit(GPIO_reg_t* GPIO_handle);

// GPIO set bus clock 
void GPIO_clock(GPIO_reg_t* GPIO_reg, uint8_t mode);

// Read/Write pin/port 
uint8_t GPIO_read_IDR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin);
uint16_t GPIO_read_IDR_port(GPIO_reg_t* GPIO_reg);

void GPIO_write_ODR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin, uint8_t mode);
void GPIO_write_ODR_port(GPIO_reg_t* GPIO_reg, uint16_t value);

void GPIO_toggle_ODR_pin(GPIO_reg_t* GPIO_reg, uint8_t pin);

// EXTI Interrupts for GPIO pin setup
void GPIO_irq_exti_setup(uint8_t pin, uint8_t mode);

// Enable RX/TX pins for USART 
void GPIO_USART2_TXRX_pins_enable(void);

// Enable pins for SPI 
void GPIO_SPI_pins_enable(void);

// Enable pins for I2C
void GPIO_I2C_pins_enable(void);
```

#### UART -> drivers/uart (currently only for USART2)
```
// Configure USART2
void USART2_config(USART_handle_t* USART_handle);

// USART2 transmit/receive (blocking)
void USART2_transmit_char(uint8_t chr); 
void USART2_transmit_string(uint8_t* string);

uint8_t USART2_receive_char(void);
```

#### SPI -> drivers/spi (currently onle for SPI1)
```
// SPI init/deinit 
void SPI_init(SPI_handle_t* SPI_handle);
void SPI_deinit(SPI_reg_t* SPI_reg);

// SPI transmit/receive
void SPI_transmit(SPI_reg_t* SPI_reg, uint8_t* data, uint32_t size);
void SPI_receive(SPI_reg_t* SPI_reg, uint8_t* data, uint32_t size);

// SPI enable interrupt 
void SPI1_enable_interrupt(SPI_reg_t* SPI_reg);
```

#### I2C -> drivers/i2c
```
// I2C init/deinit 
void I2C_init(I2C_handle_t* I2C_handle);
void I2C_deinit(I2C_reg_t* I2C_reg);

// I2C trainsmit/receive 
void I2C_transmit(I2C_reg_t* I2C_reg,uint8_t address, uint8_t* buffer, uint32_t size);
void I2C_receive(I2C_reg_t* I2C_reg, uint8_t address, uint8_t* buffer, uint32_t size);
```

#### TIM -> drivers/pwm (currently only for TIM2-TIM5)
```
// TIM init 
void TIM2_TIM5_init(TIM2_TIM5_handle_t* tim);

// TIM delay in microseconds
void TIM_delay(TIM2_TIM5_reg_t* tim, uint32_t ms);
```

#### EXTI -> drivers/exti
```
// EXTI setup
void irq_exti_setup(uint8_t pin, uint8_t mode);

// EXTI set priority
void irq_set_priority(uint8_t irq_number, uint8_t priority);

// IRQ enable/disable 
void irq_enable(uint8_t irq_num);
void irq_disable(uint8_t irq_num);

// IRQ clear pending 
void EXTI_clear_pending(uint8_t pin);
```

#### SYSTICK -> drivers/systick
```
// SYSTICK init
void SYSTICK_init(uint32_t ticks, uint8_t clk_src, uint8_t ext, uint8_t enable_clock);

// SYSTICK delay in microseconds 
void SYSTICK_delay(uint32_t tick);
```

## Building Examples
#### Build all examples of drivers in build/examples 
```
make examples
```
#### Flash each example 
```
make flash-example-gpio
make flash-example-uart
make flash-example-spi
```

### GPIO/SYSTICK EXAMPLE
```C 
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
```

### UART EXAMPLE 
```C
#include "rcc.h"
#include "systick.h"
#include <generic.h>
#include <uart.h>
#include <gpio.h>

int main() {

    RCC_SysClock_Init();

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);

    USART_handle_t uart = {0};
    uart.USART_reg = USART2;
    uart.USART_config.baud = 9600;
    uart.USART_config.word_length = USART_8_DATA_BITS;
    uart.USART_config.mode = USART_MODE_TXRX;

    USART2_config(&uart);

    while (1) {
        uint8_t data = USART2_receive_char();
        USART2_transmit_char(data);
    }

}

```

### SPI EXAMPLE
```C 
#include "exti.h"
#include <generic.h>
#include <spi.h>
#include <gpio.h>
#include <uart.h>
#include <systick.h>

int main() {

    SYSTICK_init(16000000, SYST_CLKSRC_INTERNAL, SYST_TICKINT_EXT, ENABLE);

    GPIO_SPI_pins_enable();

    SPI_handle_t spi = {0};
    spi.SPI_reg = SPI1;
    spi.SPI_config.mode = SPI_MODE_MASTER;
    spi.SPI_config.cpha = SPI_CPHA_LOW;
    spi.SPI_config.cpol = SPI_CPOL_LOW;
    spi.SPI_config.clock_speed = 3;
    spi.SPI_config.ssm = SPI_SMM_ENABLE;
    spi.SPI_config.dff = SPI_DFF_BITS8;
    spi.SPI_config.dma = SPI_DMA_DISABLE;
    spi.SPI_config.bus_cfg = SPI_BUS_FULL_DUPLEX;
    SPI_init(&spi);

    USART_handle_t uart = {0};
    uart.USART_reg = USART2;
    uart.USART_config.baud = 9600;
    uart.USART_config.word_length = USART_8_DATA_BITS;
    uart.USART_config.mode = USART_MODE_TXRX;
    uart.USART_config.stop_bits = USART_STOP_BIT_1;
    USART2_config(&uart);

    GPIO_handle_t rst = {0};
    rst.GPIO_reg = GPIOC;
    rst.GPIO_config.pin = 10;
    rst.GPIO_config.mode = GPIO_MODE_OUTPUT;
    GPIO_init(&rst);

    GPIO_handle_t sda = {0};
    sda.GPIO_reg = GPIOC;
    sda.GPIO_config.pin = 11;
    sda.GPIO_config.mode = GPIO_MODE_OUTPUT;
    GPIO_init(&sda);

    GPIO_write_ODR_pin(GPIOC, 11, ENABLE);
    GPIO_write_ODR_pin(GPIOC, 10, DISABLE);

    SYSTICK_delay(10);
    GPIO_write_ODR_pin(GPIOC, 10, ENABLE);
    SYSTICK_delay(50);

    uint8_t cmd = ((0x37 << 1) & 0x7E) | 0x80;
    uint8_t ver;
    char msg[8];
    const char hex[] = "0123456789ABCDEF";

    while(1) {
        GPIO_write_ODR_pin(GPIOC, 11, DISABLE);
        SPI_transmit(SPI1, &cmd, 1);
        SPI_receive(SPI1, &ver, 1);
        GPIO_write_ODR_pin(GPIOC, 11, ENABLE);

        msg[0] = hex[ver >> 4];
        msg[1] = hex[ver & 0xF];
        msg[2] = '\r';
        msg[3] = '\n';
        msg[4] = '\0';
        USART2_transmit_string(msg);

        SYSTICK_delay(500);
    }
}

```

## Memory map of MCU (can be viewed in link.ld)
1. Flash
    - Start Addr:     0x08000000
    - Size:           512K
2. SRAM
    - Start addr:     0x20000000
    - Size:           96K
## Reference 
- STM32 RM0008 Reference Manual
- Cortex -M4 Devices Generic User Guide
- STM32F401xD Datasheet

## Author
Oleksandr Pysarchuk 

