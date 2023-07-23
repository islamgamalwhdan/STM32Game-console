################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Input/gamepad.c \
../Core/Input/gyro.c \
../Core/Input/l3gd20.c \
../Core/Input/stmpe811.c \
../Core/Input/touchpad.c 

OBJS += \
./Core/Input/gamepad.o \
./Core/Input/gyro.o \
./Core/Input/l3gd20.o \
./Core/Input/stmpe811.o \
./Core/Input/touchpad.o 

C_DEPS += \
./Core/Input/gamepad.d \
./Core/Input/gyro.d \
./Core/Input/l3gd20.d \
./Core/Input/stmpe811.d \
./Core/Input/touchpad.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Input/%.o Core/Input/%.su: ../Core/Input/%.c Core/Input/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Core/Math -I../Core/Mem_manger -I../Core/Graphics -I../Core/Graphics/fonts -I../Core/Graphics/Sprites -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Input

clean-Core-2f-Input:
	-$(RM) ./Core/Input/gamepad.d ./Core/Input/gamepad.o ./Core/Input/gamepad.su ./Core/Input/gyro.d ./Core/Input/gyro.o ./Core/Input/gyro.su ./Core/Input/l3gd20.d ./Core/Input/l3gd20.o ./Core/Input/l3gd20.su ./Core/Input/stmpe811.d ./Core/Input/stmpe811.o ./Core/Input/stmpe811.su ./Core/Input/touchpad.d ./Core/Input/touchpad.o ./Core/Input/touchpad.su

.PHONY: clean-Core-2f-Input

