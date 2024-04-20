TARGET = ch32v208

BUILD_DIR = ./build
#TOOLCHAIN_PATH = ./xpack-riscv-none-elf-gcc-12.2.0-1/bin
TOOLCHAIN_PATH = ./mrs-gcc/bin
TOOLCHAIN_PREFIX = $(TOOLCHAIN_PATH)/riscv-none-elf-

# binaries
CC = $(TOOLCHAIN_PREFIX)gcc
#AS = $(TOOLCHAIN_PREFIX)gcc
CP = $(TOOLCHAIN_PREFIX)objcopy
SZ = $(TOOLCHAIN_PREFIX)size
OD = $(TOOLCHAIN_PREFIX)objdump

LIB_DIR = ./ch32v20x
SRC_DIR += $(LIB_DIR)
SRC_DIR += ./src
SRC_DIR += ./gd32vf103

SRC := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
SRC += $(shell find $(SRC_DIR) -name *.S)
#SRC += $(LIB_DIR)/Startup/startup_ch32v20x_D8W.S
#SRC += $(LIB_DIR)/ble/lib/ble_task_scheduler.S
INC_DIR := $(shell find $(SRC_DIR) -type d)
#INC_DIR += ./gd32vf103
#GD32V_LIB = ./gd32vf103/usbfs
#INC_DIR += $(GD32V_LIB)/ustd
#INC_DIR += $(GD32V_LIB)/driver/Include
#INC_DIR += $(shell find $(INC_DIR) -type d)
INC = $(addprefix -I,$(INC_DIR))
OBJ := $(SRC:%=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

ARCH = -march=rv32imac -mabi=ilp32
ARCH += -mcmodel=medany
#OPT = -O3
OPT = -g
FLAGS += $(INC) $(ARCH) $(OPT)
FLAGS += -MMD -MP
FLAGS += -Wl,-Bstatic
FLAGS += -ffunction-sections -fdata-sections
#FLAGS += -fno-common
FLAGS += -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -Wunused -Wuninitialized

CFLAGS = $(FLAGS)
CFLAGS += -std=gnu99
# CPPFLAGS = $(CFLAGS)
ASFLAGS = $(FLAGS)
ASFLAGS += -x assembler-with-cpp

LDSCRIPT = $(shell find $(SRC_DIR) -name *.ld)
#LDSCRIPT = $(LIB_DIR)/Ld/Link.ld
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Wl,-Map,$(BUILD_DIR)/$(TARGET).map
#LDFLAGS += $(FLAGS)
LDFLAGS += -nostartfiles
#LDFLAGS += -nostdlib
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += --specs=nano.specs --specs=nosys.specs
PERIF_LIB = $(shell find $(SRC_DIR) -name *.a)
LDFLAGS += $(PERIF_LIB)

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
