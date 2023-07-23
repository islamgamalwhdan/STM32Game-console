################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/HW_specific/MCU_init.c \
../Core/HW_specific/stm32f429i_discovery.c \
../Core/HW_specific/stm32f429i_discovery_sdram.c \
../Core/HW_specific/stm32f4xx_hal_msp.c \
../Core/HW_specific/stm32f4xx_it.c \
../Core/HW_specific/syscalls.c \
../Core/HW_specific/sysmem.c \
../Core/HW_specific/system_stm32f4xx.c \
../Core/HW_specific/util_spe.c 

OBJS += \
./Core/HW_specific/MCU_init.o \
./Core/HW_specific/stm32f429i_discovery.o \
./Core/HW_specific/stm32f429i_discovery_sdram.o \
./Core/HW_specific/stm32f4xx_hal_msp.o \
./Core/HW_specific/stm32f4xx_it.o \
./Core/HW_specific/syscalls.o \
./Core/HW_specific/sysmem.o \
./Core/HW_specific/system_stm32f4xx.o \
./Core/HW_specific/util_spe.o 

C_DEPS += \
./Core/HW_specific/MCU_init.d \
./Core/HW_specific/stm32f429i_discovery.d \
./Core/HW_specific/stm32f429i_discovery_sdram.d \
./Core/HW_specific/stm32f4xx_hal_msp.d \
./Core/HW_specific/stm32f4xx_it.d \
./Core/HW_specific/syscalls.d \
./Core/HW_specific/sysmem.d \
./Core/HW_specific/system_stm32f4xx.d \
./Core/HW_specific/util_spe.d 


# Each subdirectory must supply rules for building sources it contributes
Core/HW_specific/%.o Core/HW_specific/%.su: ../Core/HW_specific/%.c Core/HW_specific/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Bootloader -I../Core/Graphics -I../Core/Graphics/Sprites -I../Core/Graphics/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-HW_specific

clean-Core-2f-HW_specific:
	-$(RM) ./Core/HW_specific/MCU_init.d ./Core/HW_specific/MCU_init.o ./Core/HW_specific/MCU_init.su ./Core/HW_specific/stm32f429i_discovery.d ./Core/HW_specific/stm32f429i_discovery.o ./Core/HW_specific/stm32f429i_discovery.su ./Core/HW_specific/stm32f429i_discovery_sdram.d ./Core/HW_specific/stm32f429i_discovery_sdram.o ./Core/HW_specific/stm32f429i_discovery_sdram.su ./Core/HW_specific/stm32f4xx_hal_msp.d ./Core/HW_specific/stm32f4xx_hal_msp.o ./Core/HW_specific/stm32f4xx_hal_msp.su ./Core/HW_specific/stm32f4xx_it.d ./Core/HW_specific/stm32f4xx_it.o ./Core/HW_specific/stm32f4xx_it.su ./Core/HW_specific/syscalls.d ./Core/HW_specific/syscalls.o ./Core/HW_specific/syscalls.su ./Core/HW_specific/sysmem.d ./Core/HW_specific/sysmem.o ./Core/HW_specific/sysmem.su ./Core/HW_specific/system_stm32f4xx.d ./Core/HW_specific/system_stm32f4xx.o ./Core/HW_specific/system_stm32f4xx.su ./Core/HW_specific/util_spe.d ./Core/HW_specific/util_spe.o ./Core/HW_specific/util_spe.su

.PHONY: clean-Core-2f-HW_specific

