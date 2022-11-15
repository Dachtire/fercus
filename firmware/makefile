TARGET = ch32v203

BUILD_DIR = ./build
LIB_DIR = ./ch32v20x
#TOOLCHAIN_PATH = ./xpack-riscv-none-elf-gcc-12.2.0-1/bin
#TOOLCHAIN_PREFIX = $(TOOLCHAIN_PATH)/riscv-none-elf-
# TOOLCHAIN_PATH = ./xpack-riscv-none-embed-gcc-10.2.0-1.2/bin
TOOLCHAIN_PATH = ./mrs-gcc/bin
TOOLCHAIN_PREFIX = $(TOOLCHAIN_PATH)/riscv-none-embed-

# binaries
CC = $(TOOLCHAIN_PREFIX)gcc
#AS = $(TOOLCHAIN_PREFIX)gcc
CP = $(TOOLCHAIN_PREFIX)objcopy
SZ = $(TOOLCHAIN_PREFIX)size
OD = $(TOOLCHAIN_PREFIX)objdump

SRC_DIR += ./src
SRC_DIR += ./gd32vf103
SRC_DIR += $(LIB_DIR)

SRC := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
SRC += $(LIB_DIR)/Startup/startup_ch32v20x_D6.S
INC_DIR := $(shell find $(SRC_DIR) -type d)
#INC_DIR += ./gd32vf103
#GD32V_LIB = ./gd32vf103/usbfs
#INC_DIR += $(GD32V_LIB)/ustd
#INC_DIR += $(GD32V_LIB)/driver/Include
#INC_DIR += $(shell find $(INC_DIR) -type d)
INC = $(addprefix -I,$(INC_DIR))
OBJ := $(SRC:%=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

#ARCH = -march=rv32imafc -mabi=ilp32f
ARCH = -march=rv32imac -mabi=ilp32
#ARCH += -mcmodel=medany
# OPT = -O3
# OPT = -g
FLAGS += $(INC) $(ARCH) $(OPT)
FLAGS += -MMD -MP
FLAGS += -Wl,-Bstatic
FLAGS += -ffunction-sections -fdata-sections
#FLAGS += -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -Wunused -Wuninitialized -g

CFLAGS = $(FLAGS)
CFLAGS += -std=gnu17
# CPPFLAGS = $(CFLAGS)
ASFLAGS = $(FLAGS)
ASFLAGS += -x assembler-with-cpp

LDSCRIPT = $(LIB_DIR)/Ld/Link.ld
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Wl,-Map,$(BUILD_DIR)/$(TARGET).map
#LDFLAGS += $(FLAGS)
LDFLAGS += -nostartfiles
#LDFLAGS += -nostdlib
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += --specs=nano.specs --specs=nosys.specs

-include $(DEP)

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@
	$(CP) -O ihex $@ $(BUILD_DIR)/$(TARGET).hex
	$(CP) -O binary -S $@ $(BUILD_DIR)/$(TARGET).bin
	$(SZ) $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# assembly
$(BUILD_DIR)/%.S.o: %.S
	mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

# c++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	# $(MKDIR_P) $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -rf $(BUILD_DIR)

dfu: $(BUILD_DIR)/$(TARGET).elf
	sudo ./wchisp flash $(BUILD_DIR)/$(TARGET).elf
