CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS ?= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -g -O0 
LINKER_SCRIPT = ./link.ld
LINKER_FLAGS = -nostdlib -T$(LINKER_SCRIPT)

SRC_DIR = src
DRIVERS_DIR = drivers
STARTUP_DIR = startup
EXAMPLE_DIR = examples

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

DRIVERS_SRC = $(shell find $(DRIVERS_DIR) -name '*.c')
STARTUP_SRC = $(STARTUP_DIR)/startup.c
DRIVERS_INC = $(shell find $(DRIVERS_DIR) -type d)
INC_FLAGS = $(addprefix -I, $(DRIVERS_INC))

COMMON_SRC = $(DRIVERS_SRC) $(STARTUP_SRC)
COMMON_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(COMMON_SRC))

MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MAIN_SRC))

EXAMPLE_SRCS = $(wildcard $(EXAMPLE_DIR)/*.c) 
EXAMPLE_NAMES = $(basename $(notdir $(EXAMPLE_SRCS)))

# Generic build rule
$(OBJ_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

all: $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.bin

$(BUILD_DIR)/main.elf: $(MAIN_OBJ) $(COMMON_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Xlinker -Map=$(BUILD_DIR)/main.map $(LINKER_FLAGS) -o $@ $^ -lgcc

$(BUILD_DIR)/main.bin: $(BUILD_DIR)/main.elf
	$(OBJCOPY) -O binary $< $@

# ------------------------------ examples --------------------------------------
$(BUILD_DIR)/examples/%.elf: $(OBJ_DIR)/$(EXAMPLE_DIR)/%.o $(COMMON_OBJ)
	@mkdir -p $(BUILD_DIR)/examples 
	$(CC) $(CFLAGS) -Xlinker -Map=$(BUILD_DIR)/examples/$*.map $(LINKER_FLAGS) -o $@ $^ -lgcc 

$(BUILD_DIR)/examples/%.bin: $(BUILD_DIR)/examples/%.elf 
	$(OBJCOPY) -O binary $< $@

examples: $(foreach ex,$(EXAMPLE_NAMES),$(BUILD_DIR)/examples/$(ex).bin)
# ------------------------------------------------------------------------------
flash: $(BUILD_DIR)/main.bin
	st-flash --reset write $< 0x08000000

flash-example-%: $(BUILD_DIR)/examples/%.bin	
	st-flash --reset write $< 0x08000000

debug: $(BUILD_DIR)/main.elf
	openocd -f board/st_nucleo_f4.cfg \
	-c "reset_config srst_only srst_nogate connect_assert_srst" \
	-c "init" \
	-c "reset halt" \
	-c "program $< verify" \
	-c "reset halt"

debug-example-%: $(BUILD_DIR)/examples/%.elf
	openocd -f board/st_nucleo_f4.cfg \
	-c "reset_config srst_only srst_nogate connect_assert_srst" \
	-c "init" \
	-c "reset halt" \
	-c "program $< verify" \
	-c "reset halt"

connect: $(BUILD_DIR)/main.elf
	gdb-multiarch $<

connect-example-%: $(BUILD_DIR)/examples/%.elf 
	gdb-multiarch $<

clean:
	rm -rf $(BUILD_DIR)

