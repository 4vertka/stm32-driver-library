# STM32 Bare-Metal Driver Library

> Bare-metal peripheral driver library for STM32F401RE
> Written in C without HAL, CubeMX, CMSIS dependencies
> All drivers operate on register level

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

RCC     - HSI/HSE/PLL config, clock getter functions, MCO
GPIO    - Input/Output/AF/Analog, EXTI setup
UART    - TX/RX polling
SPI     - Full/Half duplex, TX/RX polling
I2C     - Master TX/RX, Standard mode
TIM     - Basic timer, delay
EXTI    - NVIC config, IRQ enable/disable 
SYSTICK - milisecond delay, tick counter

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
### Build elf/bin image
```
make all 
```
### Flash firmware
```
make flash
```
### Start debugging with OpenOCD and connect to debugger using GDB
```
make debug
make connect
```
### Clean project 
```
make clean
```

## API reference

### RCC -> drivers/rcc
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

### GPIO -> drivers/gpio 
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

### UART -> drivers/uart (currently only for USART2)
```
// Configure USART2
void USART2_config(USART_handle_t* USART_handle);

// USART2 transmit/receive (blocking)
void USART2_transmit_char(uint8_t chr); 
void USART2_transmit_string(uint8_t* string);

uint8_t USART2_receive_char(void);
```

### SPI -> drivers/spi (currently onle for SPI1)
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

### I2C -> drivers/i2c
```
// I2C init/deinit 
void I2C_init(I2C_handle_t* I2C_handle);
void I2C_deinit(I2C_reg_t* I2C_reg);

// I2C trainsmit/receive 
void I2C_transmit(I2C_reg_t* I2C_reg,uint8_t address, uint8_t* buffer, uint32_t size);
void I2C_receive(I2C_reg_t* I2C_reg, uint8_t address, uint8_t* buffer, uint32_t size);
```

### TIM -> drivers/pwm (currently only for TIM2-TIM5)
```
// TIM init 
void TIM2_TIM5_init(TIM2_TIM5_handle_t* tim);

// TIM delay in microseconds
void TIM_delay(TIM2_TIM5_reg_t* tim, uint32_t ms);
```

### EXTI -> drivers/exti
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

### SYSTICK -> drivers/systick
```
// SYSTICK init
void SYSTICK_init(uint32_t ticks, uint8_t clk_src, uint8_t ext, uint8_t enable_clock);

// SYSTICK delay in microseconds 
void SYSTICK_delay(uint32_t tick);
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

