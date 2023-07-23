################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GameEngine.c \
../Core/Src/MCU_init.c \
../Core/Src/Math_lib.c \
../Core/Src/Scheduler.c \
../Core/Src/auxiliary.c \
../Core/Src/gamepad.c \
../Core/Src/gpu.c \
../Core/Src/gyro.c \
../Core/Src/ili9341.c \
../Core/Src/l3gd20.c \
../Core/Src/main.c \
../Core/Src/printf.c \
../Core/Src/stm32f429i_discovery.c \
../Core/Src/stm32f429i_discovery_sdram.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stmpe811.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/touchpad.c \
../Core/Src/umm_malloc.c \
../Core/Src/util_spe.c 

OBJS += \
./Core/Src/GameEngine.o \
./Core/Src/MCU_init.o \
./Core/Src/Math_lib.o \
./Core/Src/Scheduler.o \
./Core/Src/auxiliary.o \
./Core/Src/gamepad.o \
./Core/Src/gpu.o \
./Core/Src/gyro.o \
./Core/Src/ili9341.o \
./Core/Src/l3gd20.o \
./Core/Src/main.o \
./Core/Src/printf.o \
./Core/Src/stm32f429i_discovery.o \
./Core/Src/stm32f429i_discovery_sdram.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stmpe811.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/touchpad.o \
./Core/Src/umm_malloc.o \
./Core/Src/util_spe.o 

C_DEPS += \
./Core/Src/GameEngine.d \
./Core/Src/MCU_init.d \
./Core/Src/Math_lib.d \
./Core/Src/Scheduler.d \
./Core/Src/auxiliary.d \
./Core/Src/gamepad.d \
./Core/Src/gpu.d \
./Core/Src/gyro.d \
./Core/Src/ili9341.d \
./Core/Src/l3gd20.d \
./Core/Src/main.d \
./Core/Src/printf.d \
./Core/Src/stm32f429i_discovery.d \
./Core/Src/stm32f429i_discovery_sdram.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stmpe811.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/touchpad.d \
./Core/Src/umm_malloc.d \
./Core/Src/util_spe.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../FATFS/Target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../FATFS/Target -O0 -ffunction-sections -fdata-sections -Wall -save-temps -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GameEngine.d ./Core/Src/GameEngine.o ./Core/Src/GameEngine.su ./Core/Src/MCU_init.d ./Core/Src/MCU_init.o ./Core/Src/MCU_init.su ./Core/Src/Math_lib.d ./Core/Src/Math_lib.o ./Core/Src/Math_lib.su ./Core/Src/Scheduler.d ./Core/Src/Scheduler.o ./Core/Src/Scheduler.su ./Core/Src/auxiliary.d ./Core/Src/auxiliary.o ./Core/Src/auxiliary.su ./Core/Src/gamepad.d ./Core/Src/gamepad.o ./Core/Src/gamepad.su ./Core/Src/gpu.d ./Core/Src/gpu.o ./Core/Src/gpu.su ./Core/Src/gyro.d ./Core/Src/gyro.o ./Core/Src/gyro.su ./Core/Src/ili9341.d ./Core/Src/ili9341.o ./Core/Src/ili9341.su ./Core/Src/l3gd20.d ./Core/Src/l3gd20.o ./Core/Src/l3gd20.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/printf.d ./Core/Src/printf.o ./Core/Src/printf.su ./Core/Src/stm32f429i_discovery.d ./Core/Src/stm32f429i_discovery.o ./Core/Src/stm32f429i_discovery.su ./Core/Src/stm32f429i_discovery_sdram.d ./Core/Src/stm32f429i_discovery_sdram.o ./Core/Src/stm32f429i_discovery_sdram.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stmpe811.d ./Core/Src/stmpe811.o ./Core/Src/stmpe811.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/touchpad.d ./Core/Src/touchpad.o ./Core/Src/touchpad.su ./Core/Src/umm_malloc.d ./Core/Src/umm_malloc.o ./Core/Src/umm_malloc.su ./Core/Src/util_spe.d ./Core/Src/util_spe.o ./Core/Src/util_spe.su

.PHONY: clean-Core-2f-Src

