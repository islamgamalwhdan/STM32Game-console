################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/GUI/GameEngine.c \
../Core/GUI/gpu.c \
../Core/GUI/ili9341.c 

OBJS += \
./Core/GUI/GameEngine.o \
./Core/GUI/gpu.o \
./Core/GUI/ili9341.o 

C_DEPS += \
./Core/GUI/GameEngine.d \
./Core/GUI/gpu.d \
./Core/GUI/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
Core/GUI/%.o Core/GUI/%.su: ../Core/GUI/%.c Core/GUI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/GUI -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Core/GUI/fonts -I../Core/GUI/Sprites -I../Bootloader -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-GUI

clean-Core-2f-GUI:
	-$(RM) ./Core/GUI/GameEngine.d ./Core/GUI/GameEngine.o ./Core/GUI/GameEngine.su ./Core/GUI/gpu.d ./Core/GUI/gpu.o ./Core/GUI/gpu.su ./Core/GUI/ili9341.d ./Core/GUI/ili9341.o ./Core/GUI/ili9341.su

.PHONY: clean-Core-2f-GUI

