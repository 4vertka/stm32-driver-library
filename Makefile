CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS ?= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -g -O0 -Xlinker -Map=main.map

SRC_DIR = src
DRIVERS_DIR = drivers
STARTUP_DIR = startup

BUILD_DIR = build

LINKER_SCRIPT = ./link.ld
LINKER_FLAGS = -nostdlib -T$(LINKER_SCRIPT)

TARGET = main.elf
BIN = main.bin

MAIN_SRC = $(SRC_DIR)/main.c
DRIVERS_SRC = $(shell find $(DRIVERS_DIR) -name '*.c')
STARTUP_SRC = $(STARTUP_DIR)/startup.c

SRCS = $(MAIN_SRC) $(DRIVERS_SRC) $(STARTUP_SRC)

DRIVERS_INC = $(shell find $(DRIVERS_DIR) -type d)
INC_FLAGS = $(addprefix -I, $(DRIVERS_INC))

OBJECT_FILES = $(SRCS:.c=.o)

all: $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(TARGET): $(OBJECT_FILES)
	$(shell mkdir -p $(BUILD_DIR))
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/$(TARGET)
	$(OBJCOPY) -O binary $< $@

flash: $(BUILD_DIR)/$(BIN)
	st-flash --reset write $< 0x08000000

debug: $(BUILD_DIR)/$(TARGET)
	openocd -f board/st_nucleo_f4.cfg \
	-c "reset_config srst_only srst_nogate connect_assert_srst" \
	-c "init" \
	-c "reset halt" \
	-c "program $< verify" \
	-c "reset halt"

connect: $(BUILD_DIR)/$(TARGET)
	gdb-multiarch $<

clean:
	rm -rf $(BUILD_DIR) $(shell find $(DRIVERS_DIR) -name '*.o') $(STARTUP_DIR)/*.o $(SRC_DIR)/*.o ./*.map

