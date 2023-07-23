################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Game/subdir.mk
-include Core/Util/subdir.mk
-include Core/Scheduler/subdir.mk
-include Core/Mem_manger/subdir.mk
-include Core/Math/subdir.mk
-include Core/Input/subdir.mk
-include Core/HW_specific/Startup/subdir.mk
-include Core/HW_specific/subdir.mk
-include Core/Graphics/subdir.mk
-include Core/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32_GAME_CONSOLE_APP
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32_GAME_CONSOLE_APP.elf \

MAP_FILES += \
STM32_GAME_CONSOLE_APP.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32_GAME_CONSOLE_APP.list \

OBJCOPY_BIN += \
STM32_GAME_CONSOLE_APP.bin \


# All Target
all: main-build

# Main-build Target
main-build: STM32_GAME_CONSOLE_APP.elf secondary-outputs

# Tool invocations
STM32_GAME_CONSOLE_APP.elf STM32_GAME_CONSOLE_APP.map: $(OBJS) $(USER_OBJS) C:\Users\Islam\STM32CubeIDE\workspace_1.4.0\STM32_GAME_CONSOLE_APP\STM32F429ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32_GAME_CONSOLE_APP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Islam\STM32CubeIDE\workspace_1.4.0\STM32_GAME_CONSOLE_APP\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32_GAME_CONSOLE_APP.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32_GAME_CONSOLE_APP.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32_GAME_CONSOLE_APP.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32_GAME_CONSOLE_APP.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32_GAME_CONSOLE_APP.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32_GAME_CONSOLE_APP.bin STM32_GAME_CONSOLE_APP.elf STM32_GAME_CONSOLE_APP.list STM32_GAME_CONSOLE_APP.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
